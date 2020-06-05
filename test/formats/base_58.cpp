// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <test_helpers.hpp>
#include <kth/infrastructure.hpp>

using namespace kth;

// Start Boost Suite: base 58 tests

void encdec_test(std::string const& hex, std::string const& encoded) {
    data_chunk data, decoded;
    REQUIRE(decode_base16(data, hex));
    REQUIRE(encode_base58(data) == encoded);
    REQUIRE(decode_base58(decoded, encoded));
    REQUIRE(decoded == data);
}

TEST_CASE("base58 test", "[base 58 tests]") {
    encdec_test("", "");
    encdec_test("61", "2g");
    encdec_test("626262", "a3gV");
    encdec_test("636363", "aPEr");
    encdec_test("73696d706c792061206c6f6e6720737472696e67", "2cFupjhnEsSn59qHXstmK2ffpLv2");
    encdec_test("00eb15231dfceb60925886b67d065299925915aeb172c06647", "1NS17iag9jJgTHD1VXjvLCEnZuQ3rJDE9L");
    encdec_test("516b6fcd0f", "ABnLTmg");
    encdec_test("bf4f89001e670274dd", "3SEo3LWLoPntC");
    encdec_test("572e4794", "3EFU7m");
    encdec_test("ecac89cad93923c02321", "EJDM8drfXA6uyA");
    encdec_test("10c8511e", "Rt5zm");
    encdec_test("00000000000000000000", "1111111111");
}

TEST_CASE("base58 address test", "[base 58 tests]") {
    data_chunk const pubkey
    {
        {
            0x00, 0x5c, 0xc8, 0x7f, 0x4a, 0x3f, 0xdf, 0xe3,
            0xa2, 0x34, 0x6b, 0x69, 0x53, 0x26, 0x7c, 0xa8,
            0x67, 0x28, 0x26, 0x30, 0xd3, 0xf9, 0xb7, 0x8e,
            0x64
        }
    };
    std::string address = "19TbMSWwHvnxAKy12iNm3KdbGfzfaMFViT";
    BOOST_REQUIRE(encode_base58(pubkey) == address);
    data_chunk decoded;
    BOOST_REQUIRE(decode_base58(decoded, address));
    BOOST_REQUIRE(decoded == pubkey);
}

BOOST_AUTO_TEST_CASE(is_b58)
{
    std::string const base58_chars = "123456789ABCDEFGHJKLMNPQRSTUVWXYZabcdefghijkmnopqrstuvwxyz";
    for (char ch: base58_chars)
    {
        BOOST_REQUIRE(is_base58(ch));
    }

    std::string const non_base58_chars = "0OIl+- //#";
    for (char ch: non_base58_chars)
    {
        BOOST_REQUIRE(!is_base58(ch));
    }

    BOOST_REQUIRE(is_base58("abcdjkk11"));
    BOOST_REQUIRE(!is_base58("abcdjkk011"));
}

BOOST_AUTO_TEST_CASE(base58_array_test)
{
    byte_array<25> converted;
    BOOST_REQUIRE(decode_base58(converted, "19TbMSWwHvnxAKy12iNm3KdbGfzfaMFViT"));
    const byte_array<25> expected
    {
        {
            0x00, 0x5c, 0xc8, 0x7f, 0x4a, 0x3f, 0xdf, 0xe3,
            0xa2, 0x34, 0x6b, 0x69, 0x53, 0x26, 0x7c, 0xa8,
            0x67, 0x28, 0x26, 0x30, 0xd3, 0xf9, 0xb7, 0x8e,
            0x64
        }
    };
    BOOST_REQUIRE(converted == expected);
}

BOOST_AUTO_TEST_SUITE_END()
