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
#include <bitcoin/infrastructure.hpp>
#include <boost/test/unit_test.hpp>

using namespace bc;

BOOST_AUTO_TEST_SUITE(pseudo_random_tests)

BOOST_AUTO_TEST_CASE(pseudo_random__pseudo_randomize__zero_duration__maximum)
{
    int const max_seconds = 0;
    const asio::seconds maximum(max_seconds);
    auto const result = pseudo_randomize(maximum, 1);
    BOOST_REQUIRE(result == maximum);
}

BOOST_AUTO_TEST_CASE(pseudo_random__pseudo_randomize__subminute_default_percent__expected)
{
    int const max_seconds = 42;
    const asio::seconds maximum(max_seconds);
    const asio::seconds minimum(max_seconds - max_seconds / 2);
    auto const result = pseudo_randomize(maximum);
    BOOST_REQUIRE(result <= maximum);
    BOOST_REQUIRE(result >= minimum);
}

BOOST_AUTO_TEST_CASE(pseudo_random__pseudo_randomize__subminute_ratio_0__maximum)
{
    int const max_seconds = 42;
    const asio::seconds maximum(max_seconds);
    auto const result = pseudo_randomize(maximum, 0);
    BOOST_REQUIRE(result == maximum);
}

BOOST_AUTO_TEST_CASE(pseudo_random__pseudo_randomize__subminute_ratio_1__expected)
{
    uint8_t const ratio = 1;
    int const max_seconds = 42;
    const asio::seconds maximum(max_seconds);
    const asio::seconds minimum(max_seconds - max_seconds / ratio);
    auto const result = pseudo_randomize(maximum, ratio);
    BOOST_REQUIRE(result <= maximum);
    BOOST_REQUIRE(result >= minimum);
}

BOOST_AUTO_TEST_CASE(pseudo_random__pseudo_randomize__subminute_default_ratio__expected)
{
    int const max_seconds = 42;
    const asio::seconds maximum(max_seconds);
    const asio::seconds minimum(max_seconds - max_seconds / 2);
    auto const result = pseudo_randomize(maximum);
    BOOST_REQUIRE(result <= maximum);
    BOOST_REQUIRE(result >= minimum);
}

// Use same (ms) resolution as function to prevent test rounding difference.
BOOST_AUTO_TEST_CASE(pseudo_random__pseudo_randomize__superminute_ratio_255__expected)
{
    uint8_t const ratio = 255;
    int const max_seconds = 420;
    const asio::milliseconds maximum(max_seconds);
    const asio::milliseconds minimum(max_seconds - max_seconds / ratio);
    auto const result = pseudo_randomize(maximum, ratio);
    BOOST_REQUIRE(result <= maximum);
    BOOST_REQUIRE(result >= minimum);
}

BOOST_AUTO_TEST_SUITE_END()
