// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
#include <boost/test/unit_test.hpp>
#include <boost/program_options.hpp>
#include <kth/infrastructure.hpp>

using namespace bc;
using namespace bc::config;

BOOST_AUTO_TEST_SUITE(hash256_tests)

BOOST_AUTO_TEST_SUITE(hash256__construct)

BOOST_AUTO_TEST_CASE(hash256__construct__default__null_hash)
{
    const hash256 uninitialized_hash;
    auto const expectation = encode_hash(bc::null_hash);
    auto const result = encode_hash(uninitialized_hash);
    BOOST_REQUIRE_EQUAL(expectation, result);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()
