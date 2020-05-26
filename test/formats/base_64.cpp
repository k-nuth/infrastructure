// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <boost/test/unit_test.hpp>

#include <kth/infrastructure.hpp>

using namespace kth;

BOOST_AUTO_TEST_SUITE(base_64_tests)

#define BASE64_MURRAY "TXVycmF5IFJvdGhiYXJk"
#define BASE64_DATA_MURRAY \
{ \
    0x4d, 0x75, 0x72, 0x72, 0x61, 0x79, 0x20, \
    0x52, 0x6f, 0x74, 0x68, 0x62, 0x61, 0x72, 0x64 \
}

#define BASE64_BOOK "TWFuLCBFY29ub215IGFuZCBTdGF0ZQ=="
#define BASE64_DATA_BOOK \
{ \
    0x4d, 0x61, 0x6e, 0x2c, 0x20, 0x45, 0x63, \
    0x6f, 0x6e, 0x6f, 0x6d, 0x79, 0x20, 0x61, \
    0x6e, 0x64, 0x20, 0x53, 0x74, 0x61, 0x74, 0x65 \
}

BOOST_AUTO_TEST_CASE(encode_base64_empty_test)
{
    data_chunk decoded;
    BOOST_REQUIRE_EQUAL(encode_base64(decoded), "");
}

BOOST_AUTO_TEST_CASE(decode_base64_empty_test)
{
    data_chunk result;
    BOOST_REQUIRE(decode_base64(result, ""));
    BOOST_REQUIRE(result == data_chunk());
}

BOOST_AUTO_TEST_CASE(encode_base64_test)
{
    data_chunk decoded(BASE64_DATA_MURRAY);
    BOOST_REQUIRE_EQUAL(encode_base64(decoded), BASE64_MURRAY);
}

BOOST_AUTO_TEST_CASE(decode_base64_valid_test)
{
    data_chunk result;
    BOOST_REQUIRE(decode_base64(result, BASE64_MURRAY));
    BOOST_REQUIRE(result == data_chunk(BASE64_DATA_MURRAY));
}

BOOST_AUTO_TEST_CASE(encode_base64_padded_test)
{
    data_chunk decoded(BASE64_DATA_BOOK);
    BOOST_REQUIRE_EQUAL(encode_base64(decoded), BASE64_BOOK);
}

BOOST_AUTO_TEST_CASE(decode_base64_padded_valid_test)
{
    data_chunk result;
    BOOST_REQUIRE(decode_base64(result, BASE64_BOOK));
    BOOST_REQUIRE(result == data_chunk(BASE64_DATA_BOOK));
}

BOOST_AUTO_TEST_CASE(decode_base64_invalid_test)
{
    data_chunk result;
    BOOST_REQUIRE(!decode_base64(result, "!@#$%^&*()"));
}

BOOST_AUTO_TEST_SUITE_END()
