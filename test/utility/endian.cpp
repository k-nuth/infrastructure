/**
 * Copyright (c) 2016-2019 Knuth Project.
 *
 * This file is part of Knuth Project.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <boost/test/unit_test.hpp>
#include <bitcoin/infrastructure.hpp>

using namespace bc;

BOOST_AUTO_TEST_SUITE(endian_tests)

// Stream Tests

BOOST_AUTO_TEST_CASE(endian__from_big_endian_stream_unsafe__insufficient_data__stream_failure)
{
    static data_chunk const data{ 0xFF };
    data_source stream(data);
    BOOST_REQUIRE(!stream.eof());

    auto const value = from_little_endian_stream_unsafe<uint64_t>(stream);
    BOOST_REQUIRE(!stream);
    BOOST_REQUIRE(stream.eof());
}

BOOST_AUTO_TEST_CASE(endian__from_big_endian_stream_unsafe__eof__stream_partial_read)
{
    static uint8_t const content = 0xFF;
    static auto const shift = (sizeof(uint32_t) - sizeof(uint8_t)) * bc::byte_bits;
    const uint32_t expected = static_cast<uint32_t>(content) << shift;
    std::stringstream stream;
    stream.put(content);
    BOOST_REQUIRE(!stream.eof());

    auto const value = from_big_endian_stream_unsafe<uint32_t>(stream);
    BOOST_REQUIRE_EQUAL(value, expected);
    BOOST_REQUIRE(stream.fail());
    BOOST_REQUIRE(stream.eof());
}

BOOST_AUTO_TEST_CASE(endian__from_big_endian_stream_unsafe__valid__expected)
{
    static uint64_t const expected = 4234531234u;
    std::stringstream stream;
    auto bytes = to_big_endian(expected);
    auto const action = [&stream](uint8_t& value) { stream.put(value); };
    std::for_each(bytes.begin(), bytes.end(), action);
    auto const value = from_big_endian_stream_unsafe<uint64_t>(stream);
    BOOST_REQUIRE(stream);
    BOOST_REQUIRE_EQUAL(value, expected);
}

BOOST_AUTO_TEST_CASE(endian__from_little_endian_stream_unsafe__insufficient_data__stream_failure)
{
    static data_chunk const data{ 0xFF };
    data_source stream(data);
    BOOST_REQUIRE(!stream.eof());

    auto const value = from_little_endian_stream_unsafe<uint64_t>(stream);
    BOOST_REQUIRE(!stream);
    BOOST_REQUIRE(stream.eof());
}

BOOST_AUTO_TEST_CASE(endian__from_little_endian_stream_unsafe__eof__stream_partial_read)
{
    static uint8_t const content = 0xFF;
    auto const expected = static_cast<uint32_t>(content);
    std::stringstream stream;
    stream.put(content);
    BOOST_REQUIRE(!stream.eof());

    auto const value = from_little_endian_stream_unsafe<uint32_t>(stream);
    BOOST_REQUIRE_EQUAL(value, expected);
    BOOST_REQUIRE(stream.fail());
    BOOST_REQUIRE(stream.eof());
}

BOOST_AUTO_TEST_CASE(endian__from_little_endian_stream_unsafe__valid__expected)
{
    static uint64_t const expected = 4234531234u;
    std::stringstream stream;
    auto bytes = to_little_endian(expected);
    auto const action = [&stream](uint8_t& value) { stream.put(value); };
    std::for_each(bytes.begin(), bytes.end(), action);
    auto const value = from_little_endian_stream_unsafe<uint64_t>(stream);
    BOOST_REQUIRE(stream);
    BOOST_REQUIRE_EQUAL(value, expected);
}


// Non-Stream Tests

BOOST_AUTO_TEST_CASE(endian__from_little_endian_unsafe__one_byte__expected)
{
    static uint8_t const expected = 0xff;
    static auto const bytes = data_chunk{ expected };
    BOOST_REQUIRE_EQUAL(from_little_endian_unsafe<uint8_t>(bytes.begin()), expected);
}

BOOST_AUTO_TEST_CASE(endian__from_big_endian_unsafe__one_byte__expected)
{
    static uint8_t const expected = 0xff;
    static auto const bytes = data_chunk{ expected };
    BOOST_REQUIRE_EQUAL(from_big_endian_unsafe<uint8_t>(bytes.begin()), expected);
}

BOOST_AUTO_TEST_CASE(endian__round_trip32__little_to_big__expected)
{
    static const uint32_t expected = 123456789u;
    auto little_endian = to_little_endian<uint32_t>(expected);
    BOOST_REQUIRE_EQUAL(from_little_endian_unsafe<uint32_t>(little_endian.begin()), expected);

    std::reverse(little_endian.begin(), little_endian.end());
    BOOST_REQUIRE_EQUAL(from_big_endian_unsafe<uint32_t>(little_endian.begin()), expected);
}

BOOST_AUTO_TEST_CASE(endian__round_trip32__big_to_little__expected)
{
    static const uint32_t expected = 123456789u;
    auto big_endian = to_big_endian<uint32_t>(expected);
    BOOST_REQUIRE_EQUAL(from_big_endian_unsafe<uint32_t>(big_endian.begin()), expected);

    std::reverse(big_endian.begin(), big_endian.end());
    BOOST_REQUIRE_EQUAL(from_little_endian_unsafe<uint32_t>(big_endian.begin()), expected);
}

BOOST_AUTO_TEST_CASE(endian__round_trip32__big_to_big__expected)
{
    static const uint32_t expected = 123456789u;
    auto const big_endian = to_big_endian<uint32_t>(expected);
    BOOST_REQUIRE_EQUAL(from_big_endian_unsafe<uint32_t>(big_endian.begin()), expected);
}

BOOST_AUTO_TEST_CASE(endian__round_trip32__little_to_little__expected)
{
    static const uint32_t expected = 123456789u;
    auto const little_endian = to_little_endian<uint32_t>(expected);
    BOOST_REQUIRE_EQUAL(from_little_endian_unsafe<uint32_t>(little_endian.begin()), expected);
}

BOOST_AUTO_TEST_CASE(endian__round_trip64__little_to_little__expected)
{
    static uint64_t const expected = 0x1122334455667788;
    auto const little_endian = to_little_endian<uint64_t>(expected);
    BOOST_REQUIRE_EQUAL(from_little_endian_unsafe<uint64_t>(little_endian.begin()), expected);
}

BOOST_AUTO_TEST_CASE(endian__round_trip64__big_to_big__expected)
{
    static uint64_t const expected = 0x1122334455667788;
    auto const big_endian = to_big_endian<uint64_t>(expected);
    BOOST_REQUIRE_EQUAL(from_big_endian_unsafe<uint64_t>(big_endian.begin()), expected);
}

BOOST_AUTO_TEST_SUITE_END()
