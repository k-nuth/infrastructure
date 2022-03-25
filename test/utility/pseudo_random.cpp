// Copyright (c) 2016-2022 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <kth/infrastructure.hpp>
#include <test_helpers.hpp>

using namespace kth;

// Start Boost Suite: pseudo random tests

TEST_CASE("pseudo random  pseudo randomize  zero duration  maximum", "[pseudo random tests]") {
    int const max_seconds = 0;
    const asio::seconds maximum(max_seconds);
    auto const result = pseudo_randomize(maximum, 1);
    REQUIRE(result == maximum);
}

TEST_CASE("pseudo random  pseudo randomize  subminute default percent  expected", "[pseudo random tests]") {
    int const max_seconds = 42;
    const asio::seconds maximum(max_seconds);
    const asio::seconds minimum(max_seconds - max_seconds / 2);
    auto const result = pseudo_randomize(maximum);
    REQUIRE(result <= maximum);
    REQUIRE(result >= minimum);
}

TEST_CASE("pseudo random  pseudo randomize  subminute ratio 0  maximum", "[pseudo random tests]") {
    int const max_seconds = 42;
    const asio::seconds maximum(max_seconds);
    auto const result = pseudo_randomize(maximum, 0);
    REQUIRE(result == maximum);
}

TEST_CASE("pseudo random  pseudo randomize  subminute ratio 1  expected", "[pseudo random tests]") {
    uint8_t const ratio = 1;
    int const max_seconds = 42;
    const asio::seconds maximum(max_seconds);
    const asio::seconds minimum(max_seconds - max_seconds / ratio);
    auto const result = pseudo_randomize(maximum, ratio);
    REQUIRE(result <= maximum);
    REQUIRE(result >= minimum);
}

TEST_CASE("pseudo random  pseudo randomize  subminute default ratio  expected", "[pseudo random tests]") {
    int const max_seconds = 42;
    const asio::seconds maximum(max_seconds);
    const asio::seconds minimum(max_seconds - max_seconds / 2);
    auto const result = pseudo_randomize(maximum);
    REQUIRE(result <= maximum);
    REQUIRE(result >= minimum);
}

// Use same (ms) resolution as function to prevent test rounding difference.
TEST_CASE("pseudo random  pseudo randomize  superminute ratio 255  expected", "[pseudo random tests]") {
    uint8_t const ratio = 255;
    int const max_seconds = 420;
    const asio::milliseconds maximum(max_seconds);
    const asio::milliseconds minimum(max_seconds - max_seconds / ratio);
    auto const result = pseudo_randomize(maximum, ratio);
    REQUIRE(result <= maximum);
    REQUIRE(result >= minimum);
}

// End Boost Suite
