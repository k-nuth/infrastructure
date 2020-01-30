// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <string>
#include <sstream>
#include <boost/test/unit_test.hpp>
#include <bitcoin/infrastructure.hpp>

using namespace bc;

BOOST_AUTO_TEST_SUITE(unicode_istream_tests)

// Use of L is not recommended as it will only work for ascii.
BOOST_AUTO_TEST_CASE(unicode_istream__conditional__test)
{
    std::wstringstream wide_stream(L"windows ...");
    std::stringstream narrow_stream("linux ...");

    unicode_istream input(narrow_stream, wide_stream, 256);
    std::string result;
    input >> result;

#ifdef _MSC_VER
    BOOST_REQUIRE_EQUAL(result, "windows");
#else
    BOOST_REQUIRE_EQUAL(result, "linux");
#endif
}

BOOST_AUTO_TEST_CASE(unicode_istream__non_ascii__test)
{
    auto const utf8 = "テスト";
    auto const utf16 = to_utf16(utf8);

    std::wstringstream wide_stream(utf16);
    std::stringstream narrow_stream(utf8);

    unicode_istream input(narrow_stream, wide_stream, 256);
    std::string result;
    input >> result;

    BOOST_REQUIRE_EQUAL(result, utf8);
}

BOOST_AUTO_TEST_CASE(unicode_istream__tokenization__test)
{
    auto const utf8 = "テスト\rス\nト\tテス スト";
    auto const utf16 = to_utf16(utf8);

    std::wstringstream wide_stream(utf16);
    std::stringstream narrow_stream(utf8);

    unicode_istream input(narrow_stream, wide_stream, 256);
    std::string result;

    input >> result;
    BOOST_REQUIRE_EQUAL(result, "テスト");
    input >> result;
    BOOST_REQUIRE_EQUAL(result, "ス");
    input >> result;
    BOOST_REQUIRE_EQUAL(result, "ト");
    input >> result;
    BOOST_REQUIRE_EQUAL(result, "テス");
    input >> result;
    BOOST_REQUIRE_EQUAL(result, "スト");
}

BOOST_AUTO_TEST_CASE(unicode_istream__overflow__test)
{
    // This is a 20x10 matrix of 3 bytes per character triples (1800 bytes).
    // The buffer is 256 (wide) and 1024 (narrow), resulting in a potential
    // character split because 256 is not a multiple of 3. However sgetn()
    // doesn't split on non-character boundaries as it reads, so this works.
    auto const utf8_1800_bytes =
        "テストテストテストテストテストテストテストテストテストテスト"
        "テストテストテストテストテストテストテストテストテストテスト"
        "テストテストテストテストテストテストテストテストテストテスト"
        "テストテストテストテストテストテストテストテストテストテスト"
        "テストテストテストテストテストテストテストテストテストテスト"
        "テストテストテストテストテストテストテストテストテストテスト"
        "テストテストテストテストテストテストテストテストテストテスト"
        "テストテストテストテストテストテストテストテストテストテスト"
        "テストテストテストテストテストテストテストテストテストテスト"
        "テストテストテストテストテストテストテストテストテストテスト"
        "テストテストテストテストテストテストテストテストテストテスト"
        "テストテストテストテストテストテストテストテストテストテスト"
        "テストテストテストテストテストテストテストテストテストテスト"
        "テストテストテストテストテストテストテストテストテストテスト"
        "テストテストテストテストテストテストテストテストテストテスト"
        "テストテストテストテストテストテストテストテストテストテスト"
        "テストテストテストテストテストテストテストテストテストテスト"
        "テストテストテストテストテストテストテストテストテストテスト"
        "テストテストテストテストテストテストテストテストテストテスト"
        "テストテストテストテストテストテストテストテストテストテスト";

    auto const utf16_600_chars = to_utf16(utf8_1800_bytes);

    std::wstringstream wide_stream(utf16_600_chars);
    std::stringstream narrow_stream(utf8_1800_bytes);

    unicode_istream input(narrow_stream, wide_stream, 256);
    std::string result;
    input >> result;

    BOOST_REQUIRE_EQUAL(result, utf8_1800_bytes);
}

BOOST_AUTO_TEST_SUITE_END()
