// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
#include <sstream>
#include <string>

#include <boost/lexical_cast.hpp>
#include <boost/program_options.hpp>
#include <boost/test/unit_test.hpp>

#include <bitcoin/infrastructure.hpp>
#include <bitcoin/infrastructure/utility/collection.hpp>

using namespace bc;
using namespace bc::config;
using namespace boost::program_options;

BOOST_AUTO_TEST_SUITE(checkpoint_tests)

#define CHECKPOINT_HASH_A "000000000019d6689c085ae165831e934ff763ae46a2a6c172b3f1b60a8ce26f"
#define CHECKPOINT_A CHECKPOINT_HASH_A ":0"
#define CHECKPOINT_B "0000000069e244f73d78e8fd29ba2fd2ed618bd6fa2ee92559f542fdb26e7c1d:11111"
#define CHECKPOINT_C "000000002dd5588a74784eaa7ab0507a18ad16a236e7b1ce69f00d7ddfb5d0a6:33333"
#define CHECKPOINT_ABC CHECKPOINT_A "\n" CHECKPOINT_B "\n" CHECKPOINT_C

// ------------------------------------------------------------------------- //

BOOST_AUTO_TEST_SUITE(checkpoint__construct)

BOOST_AUTO_TEST_CASE(checkpoint__construct__default__null_hash)
{
    checkpoint const check;
    BOOST_REQUIRE(check.hash() == null_hash);
    BOOST_REQUIRE_EQUAL(check.height(), 0u);
}

BOOST_AUTO_TEST_CASE(checkpoint__construct__copy__expected)
{
    checkpoint const check1(CHECKPOINT_C);
    checkpoint const check2(check1);
    BOOST_REQUIRE_EQUAL(check2.height(), check1.height());
    BOOST_REQUIRE_EQUAL(encode_hash(check2.hash()), encode_hash(check1.hash()));
}

BOOST_AUTO_TEST_CASE(checkpoint__construct__string__expected)
{
    checkpoint const genesis(CHECKPOINT_B);
    BOOST_REQUIRE_EQUAL(genesis.height(), 11111u);
    BOOST_REQUIRE_EQUAL(genesis.to_string(), CHECKPOINT_B);
}

BOOST_AUTO_TEST_CASE(checkpoint__construct__digest__expected)
{
    size_t const expected_height = 42;
    auto const expected_hash = CHECKPOINT_HASH_A;
    hash_digest digest;
    bc::decode_hash(digest, expected_hash);
    checkpoint const genesis(digest, expected_height);
    BOOST_REQUIRE_EQUAL(genesis.height(), expected_height);
    BOOST_REQUIRE_EQUAL(encode_hash(genesis.hash()), expected_hash);
}

BOOST_AUTO_TEST_CASE(checkpoint__construct__invalid_height_value__throws_invalid_option_value)
{
    // 2^64
    BOOST_REQUIRE_THROW(checkpoint(CHECKPOINT_HASH_A ":18446744073709551616"), invalid_option_value);
}

BOOST_AUTO_TEST_CASE(checkpoint__construct__invalid_height_characters__throws_invalid_option_value)
{
    // 21 characters
    BOOST_REQUIRE_THROW(checkpoint(CHECKPOINT_HASH_A ":1000000000100000000001"), invalid_option_value);
}

BOOST_AUTO_TEST_CASE(checkpoint__construct__bogus_height_characters__throws_invalid_option_value) {
    BOOST_REQUIRE_THROW(checkpoint(CHECKPOINT_HASH_A ":xxx"), invalid_option_value);
}

BOOST_AUTO_TEST_CASE(checkpoint__construct__bogus_line_hash__throws_invalid_option_value) {
    BOOST_REQUIRE_THROW(checkpoint("bogus:42"), invalid_option_value);
}

BOOST_AUTO_TEST_CASE(checkpoint__construct__bogus_hash__throws_invalid_option_value) {
    BOOST_REQUIRE_THROW(checkpoint("bogus", 42), invalid_option_value);
}

BOOST_AUTO_TEST_SUITE_END()

// ------------------------------------------------------------------------- //

BOOST_AUTO_TEST_SUITE(checkpoint__istream)

BOOST_AUTO_TEST_CASE(checkpoint__istream__empty__expected) {
    checkpoint deserialized;
    std::stringstream serialized(CHECKPOINT_A);
    serialized >> deserialized;
    BOOST_REQUIRE_EQUAL(deserialized.to_string(), CHECKPOINT_A);
}

BOOST_AUTO_TEST_SUITE_END()

// ------------------------------------------------------------------------- //

BOOST_AUTO_TEST_SUITE(checkpoint__ostream)

static 
checkpoint::list const test_checkpoints_list({
    checkpoint{CHECKPOINT_A},
    checkpoint{CHECKPOINT_B},
    checkpoint{CHECKPOINT_C}
});

BOOST_AUTO_TEST_CASE(checkpoint__ostream__empty__expected) {
    std::stringstream serialized;
    serialized << checkpoint::list();
    BOOST_REQUIRE_EQUAL(serialized.str(), "");
}

BOOST_AUTO_TEST_CASE(checkpoint__ostream__populated__expected) {
    std::stringstream serialized;
    serialized << test_checkpoints_list;
    BOOST_REQUIRE_EQUAL(serialized.str(), CHECKPOINT_ABC);
}

BOOST_AUTO_TEST_CASE(checkpoint__ostream__boost_lexical_cast__expected) {
    auto const serialized = boost::lexical_cast<std::string>(test_checkpoints_list);
    BOOST_REQUIRE_EQUAL(serialized, CHECKPOINT_ABC);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()
