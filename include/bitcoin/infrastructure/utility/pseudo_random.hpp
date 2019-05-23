/**
 * Copyright (c) 2016-2019 Knuth Project.
 *
 * This file is part of Knuth Project.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef KNUTH_INFRASTRUCTURE_PSEUDO_RANDOM_HPP
#define KNUTH_INFRASTRUCTURE_PSEUDO_RANDOM_HPP

#include <cstdint>
#include <random>

#include <bitcoin/infrastructure/constants.hpp>
#include <bitcoin/infrastructure/define.hpp>
#include <bitcoin/infrastructure/utility/asio.hpp>
#include <bitcoin/infrastructure/utility/data.hpp>

namespace libbitcoin {

class BI_API pseudo_random
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

} // namespace libbitcoin

#endif
