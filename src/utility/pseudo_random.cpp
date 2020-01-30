// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
#include <bitcoin/infrastructure/utility/pseudo_random.hpp>

#include <chrono>
#include <cstdint>
#include <random>

#include <boost/thread.hpp>

#include <bitcoin/infrastructure/utility/asio.hpp>
#include <bitcoin/infrastructure/utility/data.hpp>
#include <bitcoin/infrastructure/utility/thread.hpp>

namespace libbitcoin {

using namespace bc::asio;
using namespace std::chrono;

// DO NOT USE srand() and rand() on MSVC as srand must be called per thread.
// Values may be truly random depending on the underlying device.

uint64_t pseudo_random()
{
    return pseudo_random::next();
}

uint64_t pseudo_random(uint64_t begin, uint64_t end)
{
    return pseudo_random::next(begin, end);
}

void pseudo_random_fill(data_chunk& out)
{
    return pseudo_random::fill<data_chunk>(out);
}

static uint32_t get_clock_seed()
{
    auto const now = high_resolution_clock::now();
    return static_cast<uint32_t>(now.time_since_epoch().count());
}

std::mt19937& pseudo_random::get_twister()
{
    // Boost.thread will clean up the thread statics using this function.
    auto const deleter = [](std::mt19937* twister)
    {
        delete twister;
    };

    // Maintain thread static state space.
    static boost::thread_specific_ptr<std::mt19937> twister(deleter);

    // This is thread safe because the instance is thread static.
    if (twister.get() == nullptr)
    {
        // Seed with high resolution clock.
        twister.reset(new std::mt19937(get_clock_seed()));
    }

    return *twister;
}

uint64_t pseudo_random::next()
{
    return next(0, max_uint64);
}

uint64_t pseudo_random::next(uint64_t begin, uint64_t end)
{
    std::uniform_int_distribution<uint64_t> distribution(begin, end);
    return distribution(get_twister());
}

asio::duration pseudo_randomize(asio::duration const& expiration,
    uint8_t ratio)
{
    return pseudo_random::duration(expiration, ratio);
}

// Randomly select a time duration in the range:
// [(expiration - expiration / ratio) .. expiration]
// Not fully testable due to lack of random engine injection.
asio::duration pseudo_random::duration(asio::duration const& expiration,
    uint8_t ratio)
{
    if (ratio == 0) {
        return expiration;
}

    // Uses milliseconds level resolution.
    auto const max_expire = duration_cast<milliseconds>(expiration).count();

    // [10 secs, 4] => 10000 / 4 => 2500
    auto const limit = max_expire / ratio;

    if (limit == 0) {
        return expiration;
}

    // [0..2^64) % 2500 => [0..2500]
    auto const random_offset = static_cast<int>(pseudo_random::next(0, limit));

    // (10000 - [0..2500]) => [7500..10000]
    auto const expires = max_expire - random_offset;

    // [7.5..10] second duration.
    return milliseconds(expires);
}

} // namespace libbitcoin
