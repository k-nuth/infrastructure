// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <map>
#include <vector>

#include <test_helpers.hpp>

#include <kth/infrastructure.hpp>

using namespace kth;

// Start Boost Suite: data tests

TEST_CASE("data  to byte  value  expected size and value", "[data tests]") {
    uint8_t const expected = 42;
    auto const result = to_array(expected);
    REQUIRE(result.size() == 1u);
    REQUIRE(result[0] == expected);
}

TEST_CASE("data  build chunk  empty  empty", "[data tests]") {
    auto const result = build_chunk({});
    REQUIRE(result.empty());
}

TEST_CASE("data  build chunk  one slice  expected size and value", "[data tests]") {
    uint8_t const expected = 42;
    auto const chunk1 = std::vector<uint8_t>{ 24 };
    auto const chunk2 = std::vector<uint8_t>{ expected };
    auto const chunk3 = std::vector<uint8_t>{ 48 };
    auto const result = build_chunk(
    {
        // Inline initialization doesn't work with vector (?).
        chunk1, chunk2, chunk3
    });
    REQUIRE(result.size() == 3);
    REQUIRE(result[1] == expected);
}

TEST_CASE("data  build chunk  three slices  expected size and value", "[data tests]") {
    size_t const size1 = 2;
    size_t const size2 = 1;
    size_t const size3 = 3;
    uint8_t const expected = 42;
    auto const result = build_chunk(
    {
        std::array<uint8_t, size1>{ { 0, 0} },
        std::array<uint8_t, size2>{ { expected } },
        std::array<uint8_t, size3>{ { 0, 0, 0 } }
    });
    REQUIRE(result.size() == size1 + size2 + size3);
    REQUIRE(result[size1] == expected);
}

TEST_CASE("data  build chunk  extra reserve  expected size and capacity", "[data tests]") {
    uint8_t const size1 = 2;
    uint8_t const size2 = 1;
    uint8_t const size3 = 3;
    auto const reserve = 42;
    auto const result = build_chunk(
    {
        std::array<uint8_t, size1>{ { 0, 0 } },
        std::array<uint8_t, size2>{ { 0 } },
        std::array<uint8_t, size3>{ { 0, 0, 0 } }
    }, reserve);
    REQUIRE(result.size() == size1 + size2 + size3);
    REQUIRE(result.capacity() == size1 + size2 + size3 + reserve);
}

TEST_CASE("data  build array  empty  true unchanged", "[data tests]") {
    uint8_t const expected = 42;
    std::array<uint8_t, 3> value{ { 0, expected, 0 } };
    auto const result = build_array(value, {});
    REQUIRE(result);
    REQUIRE(value[1] == expected);
}

TEST_CASE("data  build array  under capacity  true excess unchanged", "[data tests]") {
    uint8_t const expected1 = 24;
    uint8_t const expected2 = 42;
    uint8_t const expected3 = 48;
    std::array<uint8_t, 3> value{ { 0, 0, expected3 } };
    auto const result = build_array(value,
    {
        std::array<uint8_t, 2>{ { expected1, expected2 } }
    });
    REQUIRE(result);
    REQUIRE(value[0] == expected1);
    REQUIRE(value[1] == expected2);
    REQUIRE(value[2] == expected3);
}

TEST_CASE("data  build array  exact fill multiple slices  true expected values", "[data tests]") {
    size_t const size1 = 2;
    size_t const size2 = 1;
    size_t const size3 = 3;
    uint8_t const expected = 42;
    std::array<uint8_t, size1 + size2 + size3> value;
    auto const two_byte_vector = std::vector<uint8_t>{ { expected, expected } };
    auto const result = build_array(value,
    {
        two_byte_vector,
        std::array<uint8_t, size2>{ { expected } },
        std::array<uint8_t, size3>{ { expected, 0, 0 } }
    });
    REQUIRE(result);
    REQUIRE(value[size1] == expected);
    REQUIRE(value[size1 + size2] == expected);
}

TEST_CASE("data  build array  overflow  returns false", "[data tests]") {
    std::array<uint8_t, 2> value;
    auto const result = build_array(value,
    {
        std::array<uint8_t, 2>{ { 1, 2 } },
        std::array<uint8_t, 2>{ { 3, 4 } }
    });
    REQUIRE(!result);
}

TEST_CASE("data  extend data  twice  expected", "[data tests]") {
    uint8_t const expected = 24;
    data_chunk buffer1{ 0 };
    extend_data(buffer1, null_hash);
    data_chunk buffer2{ expected };
    extend_data(buffer1, buffer2);
    extend_data(buffer1, null_hash);
    REQUIRE(buffer1.size() == 2u * hash_size + 2u);
    REQUIRE(buffer1[hash_size + 1] == expected);
}

TEST_CASE("data  slice  empty selection  compiles", "[data tests]") {
    const byte_array<3> source
    {
        { 0, 0, 0 }
    };

    slice<2, 2>(source);
    REQUIRE(true);
}

TEST_CASE("data  slice  three bytes front  expected", "[data tests]") {
    uint8_t const expected = 24;
    const byte_array<3> source
    {
        { expected, 42, 42 }
    };

    auto const result = slice<0, 3>(source)[0];
    REQUIRE(result == expected);
}

TEST_CASE("data  slice  three bytes middle  expected", "[data tests]") {
    uint8_t const expected = 24;
    const byte_array<3> source
    {
        { 42, expected, 42 }
    };

    auto const result = slice<1, 2>(source)[0];
    BOOST_REQUIRE_EQUAL(result, expected);
}

BOOST_AUTO_TEST_CASE(data__slice__three_bytes_end__expected)
{
    uint8_t const expected = 24;
    const byte_array<3> source
    {
        { 42, 42, expected }
    };

    auto const result = slice<2, 3>(source)[0];
    BOOST_REQUIRE_EQUAL(result, expected);
}

BOOST_AUTO_TEST_CASE(data__split__two_bytes__expected)
{
    uint8_t const expected_left = 42;
    uint8_t const expected_right = 24;
    const byte_array<2> source
    {
        { expected_left, expected_right }
    };

    auto const parts = split(source);
    BOOST_REQUIRE_EQUAL(parts.left[0], expected_left);
    BOOST_REQUIRE_EQUAL(parts.right[0], expected_right);
}

BOOST_AUTO_TEST_CASE(data__split__long_hash__expected)
{
    uint8_t const l = 42;
    uint8_t const u = 24;
    long_hash source
    {
        {
            l, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            u, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        }
    };

    auto const parts = split(source);
    BOOST_REQUIRE_EQUAL(parts.left[0], l);
    BOOST_REQUIRE_EQUAL(parts.right[0], u);
}

BOOST_AUTO_TEST_CASE(data__splice_two__two_bytes_each__expected)
{
    uint8_t const expected_left = 42;
    uint8_t const expected_right = 24;

    const byte_array<2> left
    {
        { expected_left, 0 }
    };

    const byte_array<2> right
    {
        { 0, expected_right }
    };

    auto const combined = splice(left, right);
    BOOST_REQUIRE_EQUAL(combined[0], expected_left);
    BOOST_REQUIRE_EQUAL(combined[3], expected_right);
}

BOOST_AUTO_TEST_CASE(data__splice_three__one_two_three_bytes__expected)
{
    uint8_t const expected_left = 42;
    uint8_t const expected_right = 24;

    const byte_array<1> left
    {
        { expected_left }
    };

    const byte_array<2> middle
    {
        { 0, 0 }
    };

    const byte_array<3> right
    {
        { 0, 0, expected_right }
    };

    auto const combined = splice(left, middle, right);
    BOOST_REQUIRE_EQUAL(combined[0], expected_left);
    BOOST_REQUIRE_EQUAL(combined[5], expected_right);
}

BOOST_AUTO_TEST_CASE(data__to_array_slice__double_long_hash__expected)
{
    uint8_t const l = 42;
    uint8_t const u = 24;
    data_chunk const source
    {
        l, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        u, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
    };

    auto const result = to_array<long_hash_size>(source);
    BOOST_REQUIRE_EQUAL(result[0], l);
    BOOST_REQUIRE_EQUAL(result[long_hash_size / 2], u);
}

BOOST_AUTO_TEST_CASE(data__to_chunk__long_hash__expected)
{
    uint8_t const l = 42;
    uint8_t const u = 24;
    const long_hash source
    {
        {
            l, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            u, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        }
    };

    auto const result = to_chunk(source);
    BOOST_REQUIRE_EQUAL(result[0], l);
    BOOST_REQUIRE_EQUAL(result[32], u);
}

BOOST_AUTO_TEST_CASE(data__starts_with__empty_empty__true)
{
    static data_chunk const buffer{};
    static data_chunk const sequence{};
    BOOST_REQUIRE(starts_with(buffer.begin(), buffer.end(), sequence));
}

BOOST_AUTO_TEST_CASE(data__starts_with__not_empty_empty__false)
{
    static data_chunk const buffer{};
    static data_chunk const sequence{ 42 };
    BOOST_REQUIRE(!starts_with(buffer.begin(), buffer.end(), sequence));
}

BOOST_AUTO_TEST_CASE(data__starts_with__same_same__true)
{
    static data_chunk const buffer{ 42 };
    static data_chunk const sequence{ 42 };
    BOOST_REQUIRE(starts_with(buffer.begin(), buffer.end(), sequence));
}

BOOST_AUTO_TEST_CASE(data__starts_with__too_short__false)
{
    static data_chunk const buffer{ 42 };
    static data_chunk const sequence{ 42, 24 };
    BOOST_REQUIRE(!starts_with(buffer.begin(), buffer.end(), sequence));
}

BOOST_AUTO_TEST_CASE(data__xor_data0__same__zeros)
{
    static data_chunk const source{ 0, 1 };
    auto const result = xor_data<2>(source, source);
    BOOST_REQUIRE_EQUAL(result.size(), 2u);
    BOOST_REQUIRE_EQUAL(result[0], 0);
    BOOST_REQUIRE_EQUAL(result[1], 0);
}

BOOST_AUTO_TEST_CASE(data__xor_data1__empty__empty)
{
    static data_chunk const source{};
    auto const result = xor_data<0>(source, source, 0);
    BOOST_REQUIRE_EQUAL(result.size(), 0);
}

BOOST_AUTO_TEST_CASE(data__xor_data1__same__zeros)
{
    static data_chunk const source{ 0, 1 };
    auto const result = xor_data<2>(source, source, 0);
    BOOST_REQUIRE_EQUAL(result.size(), 2u);
    BOOST_REQUIRE_EQUAL(result[0], 0);
    BOOST_REQUIRE_EQUAL(result[1], 0);
}

BOOST_AUTO_TEST_CASE(data__xor_data1__same_offset__zeros)
{
    static data_chunk const source{ 0, 1, 0 };
    auto const result = xor_data<2>(source, source, 1);
    BOOST_REQUIRE_EQUAL(result.size(), 2u);
    BOOST_REQUIRE_EQUAL(result[0], 0);
    BOOST_REQUIRE_EQUAL(result[1], 0);
}

BOOST_AUTO_TEST_CASE(data__xor_data1__distinct__ones)
{
    static data_chunk const source{ 0, 1, 0 };
    static data_chunk const opposite{ 1, 0, 1 };
    auto const result = xor_data<3>(source, opposite, 0);
    BOOST_REQUIRE_EQUAL(result.size(), 3u);
    BOOST_REQUIRE_EQUAL(result[0], 1);
    BOOST_REQUIRE_EQUAL(result[1], 1);
    BOOST_REQUIRE_EQUAL(result[2], 1);
}

BOOST_AUTO_TEST_CASE(data__xor_data1__distinct_bites__bits)
{
    static data_chunk const source1{ 42, 13 };
    static data_chunk const source2{ 24, 13 };
    auto const result = xor_data<2>(source1, source2, 0);
    BOOST_REQUIRE_EQUAL(result.size(), 2u);
    BOOST_REQUIRE_EQUAL(result[0], 50u);
    BOOST_REQUIRE_EQUAL(result[1], 0);
}

BOOST_AUTO_TEST_CASE(data__xor_data2__distinct_bites__bits)
{
    static data_chunk const source1{ 0, 42, 13 };
    static data_chunk const source2{ 0, 0, 24, 13 };
    auto const result = xor_data<2>(source1, source2, 1, 2);
    BOOST_REQUIRE_EQUAL(result.size(), 2u);
    BOOST_REQUIRE_EQUAL(result[0], 50u);
    BOOST_REQUIRE_EQUAL(result[1], 0);
}

BOOST_AUTO_TEST_SUITE_END()
