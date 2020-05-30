// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_INFRASTRUCTURE_PSEUDO_RANDOM_HPP
#define KTH_INFRASTRUCTURE_PSEUDO_RANDOM_HPP

#include <cstdint>
#include <random>

#include <kth/infrastructure/constants.hpp>
#include <kth/infrastructure/define.hpp>
#include <kth/infrastructure/utility/asio.hpp>
#include <kth/infrastructure/utility/data.hpp>

namespace kth {

class KI_API pseudo_random
{
  public:
    /**
     * Fill a container with randomness using the default random engine.
     */
    template <typename Container>
    static void fill(Container& out)
    {
        // uniform_int_distribution is undefined for sizes < 16 bits.
        std::uniform_int_distribution<uint16_t> distribution(0, max_uint8);
        auto& twister = pseudo_random::get_twister();

        auto const fill = [&distribution, &twister](uint8_t byte)
        {
            return distribution(twister);
        };

        std::transform(out.begin(), out.end(), out.begin(), fill);
    }

    /**
     * Shuffle a container using the default random engine.
     */
    template <typename Container>
    static void shuffle(Container& out)
    {
        std::shuffle(out.begin(), out.end(), get_twister());
    }

    /**
     * Generate a pseudo random number within the domain.
     * @return  The 64 bit number.
     */
    static uint64_t next();

    /**
     * Generate a pseudo random number within [begin, end].
     * @return  The 64 bit number.
     */
    static uint64_t next(uint64_t begin, uint64_t end);

    /**
     * Convert a time duration to a value in the range [max/ratio, max].
     * @param[in]  maximum  The maximum value to return.
     * @param[in]  ratio    The determinant of the minimum duration as the inverse
     *                      portion of the maximum duration.
     * @return              The randomized duration.
     */
    static asio::duration duration(asio::duration const& expiration,
        uint8_t ratio=2);

  private:
    static std::mt19937& get_twister();
};

/**
 * DEPRECATED
 * Generate a pseudo random number within the domain.
 * @return  The 64 bit number.
 */
BI_API uint64_t pseudo_random();

/**
 * DEPRECATED
 * Generate a pseudo random number within [begin, end].
 * @return  The 64 bit number.
 */
BI_API uint64_t pseudo_random(uint64_t begin, uint64_t end);

/**
 * DEPRECATED
 * Fill a buffer with randomness using the default random engine.
 */
BI_API void pseudo_random_fill(data_chunk& out);

/**
 * DEPRECATED
 * Convert a time duration to a value in the range [max/ratio, max].
 * @param[in]  maximum  The maximum value to return.
 * @param[in]  ratio    The determinant of the minimum duration as the inverse
 *                      portion of the maximum duration.
 * @return              The randomized duration.
 */
BI_API asio::duration pseudo_randomize(asio::duration const& expiration,
    uint8_t ratio=2);

} // namespace kth

#endif
