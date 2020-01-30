// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <string>
#include <sstream>
#include <boost/test/unit_test.hpp>
#include <bitcoin/infrastructure.hpp>

using namespace bc;

BOOST_AUTO_TEST_SUITE(unicode_ostream_tests)

// Use of L is not recommended as it will only work for ascii.
BOOST_AUTO_TEST_CASE(unicode_ostream__conditional__test)
{
    std::wstringstream wide_stream;
    std::stringstream narrow_stream;

    unicode_ostream output(narrow_stream, wide_stream, 256);
    output << "ascii";
    output.flush();

#ifdef _MSC_VER
    BOOST_REQUIRE(narrow_stream.str().empty());
    BOOST_REQUIRE_EQUAL(wide_stream.str().c_str(), L"ascii");
#else
    BOOST_REQUIRE(wide_stream.str().empty());
    BOOST_REQUIRE_EQUAL(narrow_stream.str(), "ascii");
#endif
}

BOOST_AUTO_TEST_CASE(unicode_ostream__non_ascii__test)
{
    auto const utf8 = "テスト";
    auto const utf16 = to_utf16(utf8);

    std::wstringstream wide_stream;
    std::stringstream narrow_stream;

    unicode_ostream output(narrow_stream, wide_stream, 256);
    output << utf8;
    output.flush();

#ifdef _MSC_VER
    BOOST_REQUIRE(narrow_stream.str().empty());
    BOOST_REQUIRE_EQUAL(wide_stream.str().c_str(), utf16.c_str());
#else
    BOOST_REQUIRE(wide_stream.str().empty());
    BOOST_REQUIRE_EQUAL(narrow_stream.str(), utf8);
#endif
}

BOOST_AUTO_TEST_CASE(unicode_ostream__overflow__test)
{
    // This is a 20x10 matrix of 3 bytes per character triples (1800 bytes).
    // The buffer is 256 (wide) and 1024 (narrow), resulting in a potential
    // character split because 256 is not a multiple of 3. The overflow
    // method of the output stream buffer must compensate for character
    // splitting as the utf8 stream is not character-oriented, otherwise
    // this will fail.
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

    std::wstringstream wide_stream;
    std::stringstream narrow_stream;

    unicode_ostream output(narrow_stream, wide_stream, 256);
    output << utf8_1800_bytes;
    output.flush();

#ifdef _MSC_VER
    BOOST_REQUIRE(narrow_stream.str().empty());
    BOOST_REQUIRE_EQUAL(wide_stream.str().c_str(), utf16_600_chars.c_str());
#else
    BOOST_REQUIRE(wide_stream.str().empty());
    BOOST_REQUIRE_EQUAL(narrow_stream.str(), utf8_1800_bytes);
#endif
}

BOOST_AUTO_TEST_SUITE_END()
