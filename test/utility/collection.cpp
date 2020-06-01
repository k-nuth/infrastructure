// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <boost/test/unit_test.hpp>

#include <vector>
#include <kth/infrastructure.hpp>

using namespace kth;

BOOST_AUTO_TEST_SUITE(collection_tests)

typedef std::vector<uint8_t> collection;

// distinct

BOOST_AUTO_TEST_CASE(collection__distinct__empty__same)
{
    collection parameter;
    auto const& result = distinct(parameter);
    BOOST_REQUIRE(parameter.empty());
    BOOST_REQUIRE(&result == &parameter);
}

BOOST_AUTO_TEST_CASE(collection__distinct__single__match)
{
    uint8_t const expected = 42;
    collection set{ expected };
    auto const& result = distinct(set);
    BOOST_REQUIRE_EQUAL(result.size(), 1u);
    BOOST_REQUIRE_EQUAL(result[0], expected);
}

BOOST_AUTO_TEST_CASE(collection__distinct__distinct_sorted__sorted)
{
    collection set{ 0, 2, 4, 6, 8 };
    auto const& result = distinct(set);
    BOOST_REQUIRE_EQUAL(result.size(), 5u);
    BOOST_REQUIRE_EQUAL(result[0], 0u);
    BOOST_REQUIRE_EQUAL(result[1], 2u);
    BOOST_REQUIRE_EQUAL(result[2], 4u);
    BOOST_REQUIRE_EQUAL(result[3], 6u);
    BOOST_REQUIRE_EQUAL(result[4], 8u);
}

BOOST_AUTO_TEST_CASE(collection__distinct__distinct_unsorted__sorted)
{
    collection set{ 2, 0, 8, 6, 4 };
    auto const& result = distinct(set);
    BOOST_REQUIRE_EQUAL(result.size(), 5u);
    BOOST_REQUIRE_EQUAL(result[0], 0u);
    BOOST_REQUIRE_EQUAL(result[1], 2u);
    BOOST_REQUIRE_EQUAL(result[2], 4u);
    BOOST_REQUIRE_EQUAL(result[3], 6u);
    BOOST_REQUIRE_EQUAL(result[4], 8u);
}

BOOST_AUTO_TEST_CASE(collection__distinct__distinct_unsorted_duplicates__sorted_distinct)
{
    collection set{ 2, 0, 0, 8, 6, 4 };
    auto const& result = distinct(set);
    BOOST_REQUIRE_EQUAL(result.size(), 5u);
    BOOST_REQUIRE_EQUAL(result[0], 0u);
    BOOST_REQUIRE_EQUAL(result[1], 2u);
    BOOST_REQUIRE_EQUAL(result[2], 4u);
    BOOST_REQUIRE_EQUAL(result[3], 6u);
    BOOST_REQUIRE_EQUAL(result[4], 8u);
}

// move_append

BOOST_AUTO_TEST_CASE(collection__move_append__both_empty__both_empty)
{
    collection source;
    collection target;
    move_append(target, source);
    BOOST_REQUIRE_EQUAL(source.size(), 0u);
    BOOST_REQUIRE_EQUAL(target.size(), 0u);
}

BOOST_AUTO_TEST_CASE(collection__move_append__source_empty__both_unchanged)
{
    collection source;
    collection target{ 0, 2, 4, 6, 8 };
    auto const expected = target.size();
    move_append(target, source);
    BOOST_REQUIRE_EQUAL(source.size(), 0u);
    BOOST_REQUIRE_EQUAL(target.size(), expected);
    BOOST_REQUIRE_EQUAL(target[0], 0u);
    BOOST_REQUIRE_EQUAL(target[1], 2u);
    BOOST_REQUIRE_EQUAL(target[2], 4u);
    BOOST_REQUIRE_EQUAL(target[3], 6u);
    BOOST_REQUIRE_EQUAL(target[4], 8u);
}

BOOST_AUTO_TEST_CASE(collection__move_append__target_empty__swapped_values)
{
    collection source{ 0, 2, 4, 6, 8 };
    collection target;
    auto const expected = source.size();
    move_append(target, source);
    BOOST_REQUIRE_EQUAL(source.size(), 0u);
    BOOST_REQUIRE_EQUAL(target.size(), expected);
    BOOST_REQUIRE_EQUAL(target[0], 0u);
    BOOST_REQUIRE_EQUAL(target[1], 2u);
    BOOST_REQUIRE_EQUAL(target[2], 4u);
    BOOST_REQUIRE_EQUAL(target[3], 6u);
    BOOST_REQUIRE_EQUAL(target[4], 8u);
}

BOOST_AUTO_TEST_CASE(collection__move_append__neither_empty__moved_in_order)
{
    collection source{ 10, 12, 14, 16, 18 };
    collection target{ 0, 2, 4, 6, 8 };
    auto const expected = source.size() + source.size();
    move_append(target, source);
    BOOST_REQUIRE_EQUAL(source.size(), 0u);
    BOOST_REQUIRE_EQUAL(target.size(), expected);
    BOOST_REQUIRE_EQUAL(target[0], 0u);
    BOOST_REQUIRE_EQUAL(target[1], 2u);
    BOOST_REQUIRE_EQUAL(target[2], 4u);
    BOOST_REQUIRE_EQUAL(target[3], 6u);
    BOOST_REQUIRE_EQUAL(target[4], 8u);
    BOOST_REQUIRE_EQUAL(target[5], 10u);
    BOOST_REQUIRE_EQUAL(target[6], 12u);
    BOOST_REQUIRE_EQUAL(target[7], 14u);
    BOOST_REQUIRE_EQUAL(target[8], 16u);
    BOOST_REQUIRE_EQUAL(target[9], 18u);
}

BOOST_AUTO_TEST_CASE(collection__pop__single__empty_and_returns_expected)
{
    uint8_t const expected = 42u;
    collection stack{ expected };
    auto const value = pop(stack);
    BOOST_REQUIRE(stack.empty());
    BOOST_REQUIRE_EQUAL(value, expected);
}

BOOST_AUTO_TEST_CASE(collection__pop__multiple__popped_and_returns_expected)
{
    uint8_t const expected = 42u;
    collection stack{ 0, 1, 2, 3, expected };
    auto const value = pop(stack);
    BOOST_REQUIRE_EQUAL(stack.size(), 4u);
    BOOST_REQUIRE_EQUAL(stack[0], 0u);
    BOOST_REQUIRE_EQUAL(stack[1], 1u);
    BOOST_REQUIRE_EQUAL(stack[2], 2u);
    BOOST_REQUIRE_EQUAL(stack[3], 3u);
    BOOST_REQUIRE_EQUAL(value, expected);
}

BOOST_AUTO_TEST_SUITE_END()
