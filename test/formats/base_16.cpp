// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <test_helpers.hpp>
#include <kth/infrastructure.hpp>

using namespace kth;

// Start Boost Suite: base 16 tests

TEST_CASE("base16 literal test", "[base 16 tests]") {
    auto result = base16_literal("01ff42bc");
    const byte_array<4> expected
    {
        {
            0x01, 0xff, 0x42, 0xbc
        }
    };
    BOOST_REQUIRE(result == expected);
}

BOOST_AUTO_TEST_CASE(base16_odd_length_invalid_test)
{
    auto const& hex_str = "10a7fd15cb45bda9e90e19a15";
    data_chunk data;
    BOOST_REQUIRE(!decode_base16(data, hex_str));
}

BOOST_AUTO_TEST_CASE(base16_short_hash_test)
{
    auto const& hex_str = "f85beb6356d0813ddb0dbb14230a249fe931a135";
    short_hash hash;
    BOOST_REQUIRE(decode_base16(hash, hex_str));
    BOOST_REQUIRE_EQUAL(encode_base16(hash), hex_str);
    short_hash const expected
    {
        {
           0xf8, 0x5b, 0xeb, 0x63, 0x56, 0xd0, 0x81, 0x3d, 0xdb, 0x0d,
           0xbb, 0x14, 0x23, 0x0a, 0x24, 0x9f, 0xe9, 0x31, 0xa1, 0x35
        }
    };
    BOOST_REQUIRE(hash == expected);
}

// TODO: this should be tested for correctness, not just round-tripping.
BOOST_AUTO_TEST_CASE(base16_round_trip_test)
{
    auto const& hex_str = "10a7fd15cb45bda9e90e19a15f";
    data_chunk data;
    BOOST_REQUIRE(decode_base16(data, hex_str));
    BOOST_REQUIRE_EQUAL(encode_base16(data), hex_str);
}

BOOST_AUTO_TEST_CASE(base16_array_test)
{
    byte_array<4> converted;
    BOOST_REQUIRE(decode_base16(converted, "01ff42bc"));
    const byte_array<4> expected
    {
        {
            0x01, 0xff, 0x42, 0xbc
        }
    };
    BOOST_REQUIRE(converted == expected);
}

BOOST_AUTO_TEST_SUITE_END()
