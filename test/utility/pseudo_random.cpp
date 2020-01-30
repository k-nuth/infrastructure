// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
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
    const uint8_t ratio = 1;
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
    const uint8_t ratio = 255;
    int const max_seconds = 420;
    const asio::milliseconds maximum(max_seconds);
    const asio::milliseconds minimum(max_seconds - max_seconds / ratio);
    auto const result = pseudo_randomize(maximum, ratio);
    BOOST_REQUIRE(result <= maximum);
    BOOST_REQUIRE(result >= minimum);
}

BOOST_AUTO_TEST_SUITE_END()
