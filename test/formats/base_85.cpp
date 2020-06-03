// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <test_helpers.hpp>
#include <kth/infrastructure.hpp>

using namespace kth;

// Start Boost Suite: base 85 tests

#define BASE85_ENCODED "HelloWorld"
#define BASE85_DECODED \
{ \
    0x86, 0x4F, 0xD2, 0x6F, 0xB5, 0x59, 0xF7, 0x5B \
}

#define BASE85_ENCODED_INVALID_CHAR "Test\n"
#define BASE85_ENCODED_INVALID_LENGTH "Hello World"
#define BASE85_DECODED_INVALID \
{ \
    0x86, 0x4F, 0xD2, 0x6F, 0xB5, 0x59, 0xF7, 0x5B, 0x42 \
}

BOOST_AUTO_TEST_CASE(encode_base85_empty_test)
{
    std::string encoded;
    BOOST_REQUIRE(encode_base85(encoded, data_chunk()));
    BOOST_REQUIRE(encoded.empty());
}

BOOST_AUTO_TEST_CASE(decode_base85_empty_test)
{
    data_chunk result;
    BOOST_REQUIRE(decode_base85(result, ""));
    BOOST_REQUIRE(result.empty());
}

BOOST_AUTO_TEST_CASE(encode_base85_valid_test)
{
    std::string encoded;
    data_chunk decoded(BASE85_DECODED);
    BOOST_REQUIRE(encode_base85(encoded, decoded));
    BOOST_REQUIRE_EQUAL(encoded, BASE85_ENCODED);
}

BOOST_AUTO_TEST_CASE(encode_base85_invalid_test)
{
    std::string encoded;
    data_chunk decoded(BASE85_DECODED_INVALID);
    BOOST_REQUIRE(!encode_base85(encoded, decoded));
    BOOST_REQUIRE(encoded.empty());
}

BOOST_AUTO_TEST_CASE(decode_base85_valid_test)
{
    data_chunk result;
    BOOST_REQUIRE(decode_base85(result, BASE85_ENCODED));
    BOOST_REQUIRE(result == data_chunk(BASE85_DECODED));
}

BOOST_AUTO_TEST_CASE(decode_base85_invalid_char_test)
{
    data_chunk result;
    BOOST_REQUIRE(!decode_base85(result, BASE85_ENCODED_INVALID_CHAR));
    BOOST_REQUIRE(result.empty());
}

BOOST_AUTO_TEST_CASE(decode_base85_invalid_length_test)
{
    data_chunk result;
    BOOST_REQUIRE(!decode_base85(result, BASE85_ENCODED_INVALID_LENGTH));
    BOOST_REQUIRE(result.empty());
}

// The semicolon is not in the Z85 alphabet, and such characters are treated as
// valid but with zero value in the reference implementation.
BOOST_AUTO_TEST_CASE(decode_base85_outside_alphabet_test)
{
    data_chunk result;
    BOOST_REQUIRE(decode_base85(result, ";;;;;"));
    BOOST_REQUIRE(result == data_chunk({ 0, 0, 0, 0 }));
}

BOOST_AUTO_TEST_SUITE_END()
