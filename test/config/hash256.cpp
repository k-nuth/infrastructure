// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <test_helpers.hpp>
#include <boost/program_options.hpp>
#include <kth/infrastructure.hpp>

using namespace kth;
using namespace kth::infrastructure::config;

// Start Boost Suite: hash256 tests

// Start Boost Suite: hash256  construct

TEST_CASE("hash256  construct  default  null hash", "[hash256  construct]") {
    const hash256 uninitialized_hash;
    auto const expectation = encode_hash(kth::null_hash);
    auto const result = encode_hash(uninitialized_hash);
    REQUIRE(expectation == result);
}

// End Boost Suite

// End Boost Suite
