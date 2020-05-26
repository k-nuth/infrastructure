// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <boost/test/unit_test.hpp>
#include <kth/infrastructure.hpp>

#include <cstdio>
#include <boost/preprocessor/repetition/repeat.hpp>

using namespace kth;

BOOST_AUTO_TEST_SUITE(log_tests)

BOOST_AUTO_TEST_SUITE(log__general)

BOOST_AUTO_TEST_CASE(log_general__debug) {

    // LOG_DEBUG(LOG_SYSTEM, "hello", "world", 1);
    // spdlog::debug(KTH_STRREP("{} ", KTH_PP_NARG("hello", "world", 1) + 1), LOG_SYSTEM, "hello", "world", 1);
    // spdlog::debug(KTH_STRREP("{} ", 3 + 1), LOG_SYSTEM, "hello", "world", 1);
    // spdlog::debug("{} {} {} {}", LOG_SYSTEM, "hello", "world", 1);

    spdlog::debug("{} " KTH_STRREP("{} ", 3), LOG_SYSTEM, "hello", "world", 1);
    LOG_DEBUG(LOG_SYSTEM, "hello", "world", 1);




    // #define Fold(z, n, text)  text
    // #define STRREP(str, n) BOOST_PP_REPEAT(n, Fold, str)
    // #define NUMS 3 + 1

    // // printf("%s\n", STRREP("-", 6));
    // // printf("%s\n", STRREP("-", (3 + 1)));
    // // printf("%s\n", STRREP("-", NUMS));
    // printf("%s\n", "{} " STRREP("-", 3));


    // data_chunk const blocks{ { 0xba, 0xad, 0xf0, 0x0d } };
    // binary const prefix(32, blocks);
    // BOOST_REQUIRE_EQUAL(prefix.encoded(), "10111010101011011111000000001101");

}

// BOOST_AUTO_TEST_CASE(prefix_encoded__32_bits_unsigned__expected_value)
// {
//     binary const prefix(32, uint32_t(0x0df0adba));
//     BOOST_REQUIRE_EQUAL(prefix.encoded(), "10111010101011011111000000001101");
// }
// BOOST_AUTO_TEST_CASE(prefix_encoded__8_bits_unsigned__expected_value)
// {
//     binary const prefix(8, uint32_t(0x0df0adba));
//     BOOST_REQUIRE_EQUAL(prefix.encoded(), "10111010");
// }

BOOST_AUTO_TEST_SUITE_END()

// BOOST_AUTO_TEST_SUITE(binary__to_string)

// BOOST_AUTO_TEST_CASE(prefix_to_string__32_bits__expected_value)
// {
//     data_chunk const blocks{ { 0xba, 0xad, 0xf0, 0x0d } };
//     binary const prefix(32, blocks);
//     std::stringstream stream;
//     stream << prefix;
//     BOOST_REQUIRE_EQUAL(stream.str(), "10111010101011011111000000001101");
// }

// BOOST_AUTO_TEST_SUITE_END()

// BOOST_AUTO_TEST_SUITE(binary__shift_left)

// BOOST_AUTO_TEST_CASE(shift_left_by_zero)
// {
//     binary::size_type distance = 0;
//     binary instance(16, data_chunk{ 0xAA, 0xAA, 0xAA });
//     binary expected(16, data_chunk{ 0xAA, 0xAA });
//     instance.shift_left(distance);
//     BOOST_REQUIRE(expected == instance);
// }

// BOOST_AUTO_TEST_CASE(shift_left_alternate_initial)
// {
//     binary::size_type distance = 16;
//     binary instance(24, data_chunk{ 0xAB, 0xCD, 0xEF });
//     binary expected(8, data_chunk{ 0xEF });
//     instance.shift_left(distance);
//     BOOST_REQUIRE(expected == instance);
// }

// BOOST_AUTO_TEST_CASE(shift_left_by_less_than_byte)
// {
//     binary::size_type distance = 5;
//     binary instance(24, data_chunk{ 0xAA, 0xAA, 0xAA });
//     binary expected(19, data_chunk{ 0x55, 0x55, 0x40});
//     instance.shift_left(distance);
//     BOOST_REQUIRE(expected == instance);
// }

// BOOST_AUTO_TEST_CASE(shift_left_by_less_than_byte_to_byte_align)
// {
//     binary::size_type distance = 5;
//     binary instance(21, data_chunk{ 0xAA, 0xAA, 0xAA });
//     binary expected(16, data_chunk{ 0x55, 0x55 });
//     instance.shift_left(distance);
//     BOOST_REQUIRE(expected == instance);
// }

// BOOST_AUTO_TEST_CASE(shift_left_by_byte_single)
// {
//     binary::size_type distance = 8;
//     binary instance(24, data_chunk{ 0xAA, 0xAA, 0xAA });
//     binary expected(16, data_chunk{ 0xAA, 0xAA });
//     instance.shift_left(distance);
//     BOOST_REQUIRE(expected == instance);
// }

// BOOST_AUTO_TEST_CASE(shift_left_by_greater_than_byte)
// {
//     binary::size_type distance = 13;
//     binary instance(24, data_chunk{ 0xAA, 0xAA, 0xAA });
//     binary expected(11, data_chunk{ 0x55, 0x40 });
//     instance.shift_left(distance);
//     BOOST_REQUIRE(expected == instance);
// }

// BOOST_AUTO_TEST_CASE(shift_left_by_greater_than_byte_not_initially_aligned)
// {
//     binary::size_type distance = 13;
//     binary instance(18, data_chunk{ 0xAA, 0xAA, 0xAA });
//     binary expected(5, data_chunk{ 0x50 });
//     instance.shift_left(distance);
//     BOOST_REQUIRE(expected == instance);
// }

// BOOST_AUTO_TEST_CASE(shift_left_by_byte_multiple)
// {
//     binary::size_type distance = 16;
//     binary instance(24, data_chunk{ 0xAA, 0xAA, 0xAA });
//     binary expected(8, data_chunk{ 0xAA });
//     instance.shift_left(distance);
//     BOOST_REQUIRE(expected == instance);
// }

// BOOST_AUTO_TEST_CASE(shift_left_by_size)
// {
//     binary::size_type distance = 24;
//     binary instance(24, data_chunk{ 0xAA, 0xAA, 0xAA });
//     binary expected(0, data_chunk{});
//     instance.shift_left(distance);
//     BOOST_REQUIRE(expected == instance);
// }

// BOOST_AUTO_TEST_CASE(shift_left_by_greater_than_size)
// {
//     binary::size_type distance = 30;
//     binary instance(24, data_chunk{ 0xAA, 0xAA, 0xAA });
//     binary expected(0, data_chunk{});
//     instance.shift_left(distance);
//     BOOST_REQUIRE(expected == instance);
// }

// BOOST_AUTO_TEST_SUITE_END()

// BOOST_AUTO_TEST_SUITE(binary__shift_right)

// BOOST_AUTO_TEST_CASE(shift_right_by_zero)
// {
//     binary::size_type distance = 0;
//     binary instance(16, data_chunk{ 0xAA, 0xAA, 0xAA });
//     binary expected(16, data_chunk{ 0xAA, 0xAA });
//     instance.shift_right(distance);
//     BOOST_REQUIRE(expected == instance);
// }

// BOOST_AUTO_TEST_CASE(shift_right_by_less_than_byte)
// {
//     binary::size_type distance = 5;
//     binary instance(24, data_chunk{ 0xAA, 0xAA, 0xAA });
//     binary expected(29, data_chunk{ 0x05, 0x55, 0x55, 0x50});
//     instance.shift_right(distance);
//     BOOST_REQUIRE(expected == instance);
// }

// BOOST_AUTO_TEST_CASE(shift_right_by_less_than_byte_to_byte_align)
// {
//     binary::size_type distance = 3;
//     binary instance(21, data_chunk{ 0xAA, 0xAA, 0xAA });
//     binary expected(24, data_chunk{ 0x15, 0x55, 0x55 });
//     instance.shift_right(distance);
//     BOOST_REQUIRE(expected == instance);
// }

// BOOST_AUTO_TEST_CASE(shift_right_by_byte_single)
// {
//     binary::size_type distance = 8;
//     binary instance(24, data_chunk{ 0xAA, 0xAA, 0xAA });
//     binary expected(32, data_chunk{ 0x00, 0xAA, 0xAA, 0xAA });
//     instance.shift_right(distance);
//     BOOST_REQUIRE(expected == instance);
// }

// BOOST_AUTO_TEST_CASE(shift_right_by_greater_than_byte)
// {
//     binary::size_type distance = 13;
//     binary instance(24, data_chunk{ 0xAA, 0xAA, 0xAA });
//     binary expected(37, data_chunk{ 0x00, 0x05, 0x55, 0x55, 0x50 });
//     instance.shift_right(distance);
//     BOOST_REQUIRE(expected == instance);
// }

// BOOST_AUTO_TEST_CASE(shift_right_by_greater_than_byte_not_initially_aligned)
// {
//     binary::size_type distance = 13;
//     binary instance(18, data_chunk{ 0xAA, 0xAA, 0xAA });
//     binary expected(31, data_chunk{ 0x00, 0x05, 0x55, 0x54 });
//     instance.shift_right(distance);
//     BOOST_REQUIRE(expected == instance);
// }

// BOOST_AUTO_TEST_CASE(shift_right_by_byte_multiple)
// {
//     binary::size_type distance = 16;
//     binary instance(24, data_chunk{ 0xAA, 0xAA, 0xAA });
//     binary expected(40, data_chunk{ 0x00, 0x00, 0xAA, 0xAA, 0xAA });
//     instance.shift_right(distance);
//     BOOST_REQUIRE(expected == instance);
// }

// BOOST_AUTO_TEST_CASE(shift_right_by_size)
// {
//     binary::size_type distance = 24;
//     binary instance(24, data_chunk{ 0xAA, 0xAA, 0xAA });
//     binary expected(48, data_chunk{ 0x00, 0x00, 0x00, 0xAA, 0xAA, 0xAA });
//     instance.shift_right(distance);
//     BOOST_REQUIRE(expected == instance);
// }

// BOOST_AUTO_TEST_CASE(shift_right_by_greater_than_size)
// {
//     binary::size_type distance = 30;
//     binary instance(24, data_chunk{ 0xAA, 0xAA, 0xAA });
//     binary expected(54, data_chunk{ 0x00, 0x00, 0x00, 0x02, 0xAA, 0xAA, 0xA8 });
//     instance.shift_right(distance);
//     BOOST_REQUIRE(expected == instance);
// }

// BOOST_AUTO_TEST_SUITE_END()

// BOOST_AUTO_TEST_SUITE(binary__append)

// BOOST_AUTO_TEST_CASE(append_to_zero_length)
// {
//     binary instance(0, data_chunk{ 0x00 });
//     binary augment(24, data_chunk{ 0xAA, 0xBB, 0xCC });
//     binary expected(24, data_chunk{ 0xAA, 0xBB, 0xCC });
//     instance.append(augment);
//     BOOST_REQUIRE(expected == instance);
// }

// BOOST_AUTO_TEST_CASE(append_zero_length_to_content)
// {
//     binary instance(24, data_chunk{ 0xAA, 0xBB, 0xCC });
//     binary augment(0, data_chunk{});
//     binary expected(24, data_chunk{ 0xAA, 0xBB, 0xCC });
//     instance.append(augment);
//     BOOST_REQUIRE(expected == instance);
// }

// BOOST_AUTO_TEST_CASE(append_byte_aligned_instances)
// {
//     binary instance(24, data_chunk{ 0xAA, 0xBB, 0xCC });
//     binary augment(24, data_chunk{ 0xDD, 0xEE, 0xFF });
//     binary expected(48, data_chunk{ 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF });
//     instance.append(augment);
//     BOOST_REQUIRE(expected == instance);
// }

// BOOST_AUTO_TEST_CASE(append_byte_nonaligned_instances)
// {
//     binary instance(20, data_chunk{ 0xAA, 0xBB, 0xCC });
//     binary augment(13, data_chunk{ 0xDD, 0xEE });
//     binary expected(33, data_chunk{ 0xAA, 0xBB, 0xCD, 0xDE, 0x80 });
//     instance.append(augment);
//     BOOST_REQUIRE(expected == instance);
// }

// //
// // prepend tests
// //
// BOOST_AUTO_TEST_CASE(prepend_to_zero_length)
// {
//     binary instance(0, data_chunk{ 0x00 });
//     binary augment(24, data_chunk{ 0xAA, 0xBB, 0xCC });
//     binary expected(24, data_chunk{ 0xAA, 0xBB, 0xCC });
//     instance.prepend(augment);
//     BOOST_REQUIRE(expected == instance);
// }

// BOOST_AUTO_TEST_CASE(prepend_zero_length_to_content)
// {
//     binary instance(24, data_chunk{ 0xAA, 0xBB, 0xCC });
//     binary augment(0, data_chunk{});
//     binary expected(24, data_chunk{ 0xAA, 0xBB, 0xCC });
//     instance.prepend(augment);
//     BOOST_REQUIRE(expected == instance);
// }

// BOOST_AUTO_TEST_CASE(prepend_byte_aligned_instances)
// {
//     binary instance(24, data_chunk{ 0xAA, 0xBB, 0xCC });
//     binary augment(24, data_chunk{ 0xDD, 0xEE, 0xFF });
//     binary expected(48, data_chunk{ 0xDD, 0xEE, 0xFF, 0xAA, 0xBB, 0xCC });
//     instance.prepend(augment);
//     BOOST_REQUIRE(expected == instance);
// }

// BOOST_AUTO_TEST_CASE(prepend_byte_nonaligned_instances)
// {
//     binary instance(20, data_chunk{ 0xAA, 0xBB, 0xCC });
//     binary augment(13, data_chunk{ 0xDD, 0xEE });
//     binary expected(33, data_chunk{ 0xDD, 0xED, 0x55, 0xDE, 0x00 });
//     instance.prepend(augment);
//     BOOST_REQUIRE(expected == instance);
// }

// BOOST_AUTO_TEST_SUITE_END()

// BOOST_AUTO_TEST_SUITE(binary__substring)

// BOOST_AUTO_TEST_CASE(substring_start_after_end)
// {
//     binary instance(20, data_chunk{ 0xAA, 0xBB, 0xCC });
//     binary::size_type start = 21;
//     binary::size_type length = 10;
//     binary expected(0, data_chunk{});
//     binary result = instance.substring(start, length);
//     BOOST_REQUIRE(expected == result);
// }

// BOOST_AUTO_TEST_CASE(substring_length_zero)
// {
//     binary instance(20, data_chunk{ 0xAA, 0xBB, 0xCC });
//     binary::size_type start = 5;
//     binary::size_type length = 0;
//     binary expected(0, data_chunk{});
//     binary result = instance.substring(start, length);
//     BOOST_REQUIRE(expected == result);
// }

// BOOST_AUTO_TEST_CASE(substring_byte_aligned_start)
// {
//     binary instance(20, data_chunk{ 0xAA, 0xBB, 0xCC });
//     binary::size_type start = 8;
//     binary::size_type length = 10;
//     binary expected(10, data_chunk{ 0xBB, 0xC0 });
//     binary result = instance.substring(start, length);
//     BOOST_REQUIRE(expected == result);
// }

// BOOST_AUTO_TEST_CASE(substring_byte_nonaligned_start)
// {
//     binary instance(20, data_chunk{ 0xAA, 0xBB, 0xCC });
//     binary::size_type start = 10;
//     binary::size_type length = 10;
//     binary expected(10, data_chunk{ 0xEF, 0x00 });
//     binary result = instance.substring(start, length);
//     BOOST_REQUIRE(expected == result);
// }

// BOOST_AUTO_TEST_CASE(substring_request_exceeds_string)
// {
//     binary instance(20, data_chunk{ 0xAA, 0xBB, 0xCC });
//     binary::size_type start = 10;
//     binary::size_type length = 15;
//     binary expected(10, data_chunk{ 0xEF, 0x00 });
//     binary result = instance.substring(start, length);
//     BOOST_REQUIRE(expected == result);
// }

// BOOST_AUTO_TEST_CASE(substring_implicit_length)
// {
//     binary instance(20, data_chunk{ 0xAA, 0xBB, 0xCC });
//     binary::size_type start = 10;
//     binary expected(10, data_chunk{ 0xEF, 0x00 });
//     binary result = instance.substring(start);
//     BOOST_REQUIRE(expected == result);
// }

// BOOST_AUTO_TEST_SUITE_END()

// BOOST_AUTO_TEST_SUITE(binary__blocks)

// BOOST_AUTO_TEST_CASE(string_to_prefix__32_bits__expected_value)
// {
//     data_chunk const blocks{ { 0xba, 0xad, 0xf0, 0x0d } };
//     binary const prefix("10111010101011011111000000001101");
//     BOOST_REQUIRE(prefix.blocks() == blocks);
// }

// BOOST_AUTO_TEST_CASE(prefix_to_bytes__32_bits__expected_value)
// {
//     data_chunk const blocks{ { 0xba, 0xad, 0xf0, 0x0d } };
//     binary const prefix(32, blocks);
//     BOOST_REQUIRE(prefix.blocks() == blocks);
// }

// BOOST_AUTO_TEST_CASE(bytes_to_prefix__zero_bits__round_trips)
// {
//     data_chunk const bytes;
//     binary const prefix(0, bytes);
//     std::stringstream stream;
//     stream << prefix;
//     BOOST_REQUIRE_EQUAL(prefix.size(), 0u);
//     BOOST_REQUIRE_EQUAL(prefix.blocks().size(), 0u);
//     BOOST_REQUIRE(stream.str().empty());
// }

// BOOST_AUTO_TEST_CASE(prefix_to_bytes__zero_bits__round_trips)
// {
//     data_chunk const blocks{ { 0x00, 0x00, 0x00, 0x00 } };
//     binary const prefix(0, blocks);
//     auto const bytes = prefix.blocks();
//     std::stringstream stream;
//     stream << prefix;
//     BOOST_REQUIRE_EQUAL(prefix.size(), 0u);
//     BOOST_REQUIRE_EQUAL(prefix.blocks().size(), 0u);
//     BOOST_REQUIRE_EQUAL(bytes.size(), 0u);
//     BOOST_REQUIRE(stream.str().empty());
// }

// BOOST_AUTO_TEST_CASE(bytes_to_prefix__one_bit__round_trips)
// {
//     data_chunk bytes{ { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF } };
//     auto prefix = binary(1, bytes);
//     std::stringstream stream;
//     stream << prefix;
//     BOOST_REQUIRE_EQUAL(prefix.size(), 1u);
//     BOOST_REQUIRE_EQUAL(prefix.blocks().size(), 1u);
//     BOOST_REQUIRE_EQUAL(stream.str(), "1");
// }

// BOOST_AUTO_TEST_CASE(prefix_to_bytes__one_bit__round_trips)
// {
//     data_chunk const blocks{ { 0xff, 0xff, 0xff, 0xff } };
//     binary const prefix(1, blocks);
//     auto const bytes = prefix.blocks();
//     std::stringstream stream;
//     stream << prefix;
//     BOOST_REQUIRE_EQUAL(prefix.size(), 1u);
//     BOOST_REQUIRE_EQUAL(prefix.blocks().size(), 1u);
//     BOOST_REQUIRE_EQUAL(bytes.size(), 1u);
//     BOOST_REQUIRE_EQUAL(stream.str(), "1");
// }

// BOOST_AUTO_TEST_CASE(bytes_to_prefix__two_bits_leading_zero__round_trips)
// {
//     data_chunk const bytes{ { 0x01, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42 } };
//     auto const prefix = binary(2, bytes);
//     std::stringstream stream;
//     stream << prefix;
//     BOOST_REQUIRE_EQUAL(prefix.size(), 2u);
//     BOOST_REQUIRE_EQUAL(prefix.blocks().size(), 1u);
//     BOOST_REQUIRE_EQUAL(stream.str(), "00");
// }

// BOOST_AUTO_TEST_CASE(prefix_to_bytes__two_bits_leading_zero__round_trips)
// {
//     data_chunk const blocks{ { 0x42, 0x42, 0x42, 0x01 } };
//     binary const prefix(2, blocks);
//     auto bytes = prefix.blocks();
//     std::stringstream stream;
//     stream << prefix;
//     BOOST_REQUIRE_EQUAL(prefix.size(), 2u);
//     BOOST_REQUIRE_EQUAL(prefix.blocks().size(), 1u);
//     BOOST_REQUIRE_EQUAL(bytes.size(), 1u);
//     BOOST_REQUIRE_EQUAL(stream.str(), "01");
// }

// BOOST_AUTO_TEST_CASE(bytes_to_prefix__two_bytes_leading_null_byte__round_trips)
// {
//     data_chunk const bytes{ { 0xFF, 0x00 } };
//     auto const prefix = binary(16, bytes);
//     std::stringstream stream;
//     stream << prefix;
//     BOOST_REQUIRE_EQUAL(prefix.size(), 16u);
//     BOOST_REQUIRE_EQUAL(prefix.blocks().size(), 2u);
//     BOOST_REQUIRE_EQUAL(stream.str(), "1111111100000000");
// }

// BOOST_AUTO_TEST_CASE(prefix_to_bytes__two_bytes_leading_null_byte__round_trips)
// {
//     data_chunk const blocks{ { 0x00, 0x00 } };
//     binary const prefix(16, blocks);
//     auto bytes = prefix.blocks();
//     std::stringstream stream;
//     stream << prefix;
//     BOOST_REQUIRE_EQUAL(prefix.size(), 16u);
//     BOOST_REQUIRE_EQUAL(prefix.blocks().size(), 2u);
//     BOOST_REQUIRE_EQUAL(bytes.size(), 2u);
//     BOOST_REQUIRE_EQUAL(stream.str(), "0000000000000000");
// }

// BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()
