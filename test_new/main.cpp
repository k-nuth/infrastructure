// /**
//  * Copyright (c) 2016-2020 Knuth Project developers.
//  *
//  * This file is part of the Knuth Project.
//  *
//  * This program is free software: you can redistribute it and/or modify
//  * it under the terms of the GNU Affero General Public License as published by
//  * the Free Software Foundation, either version 3 of the License, or
//  * (at your option) any later version.
//  *
//  * This program is distributed in the hope that it will be useful,
//  * but WITHOUT ANY WARRANTY; without even the implied warranty of
//  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  * GNU Affero General Public License for more details.
//  *
//  * You should have received a copy of the GNU Affero General Public License
//  * along with this program.  If not, see <http://www.gnu.org/licenses/>.
//  */

// #define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
// #include "doctest.h"

// //#include <kth/infrastructure/wallet/cashaddr.hpp>
// // #include <kth/infrastructure/wallet/payment_address.hpp>

// // #include <knuth/keoken/transaction_extractor.hpp>
// // #include <knuth/keoken/message/base.hpp>
// // #include <knuth/keoken/message/create_asset.hpp>
// // #include <knuth/keoken/message/send_tokens.hpp>
// // #include <knuth/keoken/utility.hpp>

// // using namespace knuth::keoken;

// #include <kth/infrastructure/utility/data.hpp>
// #include <kth/infrastructure/formats/base_16.hpp>
// #include <kth/infrastructure/utility/container_source.hpp>

// using kth::data_chunk;
// using kth::to_chunk;
// using kth::base16_literal;
// using kth::data_source;
// using kth::istream_reader;


// TEST_CASE("[test_read_null_terminated_string_unlimited] 1") {
//     data_chunk data = {'A', 'B', 'C', 0};
//     kth::data_source ds(data);
//     kth::istream_reader source(ds);

//     auto ret = read_null_terminated_string_unlimited(source);
//     REQUIRE(ret == "ABC"); 
// }

// TEST_CASE("[test_read_null_terminated_string_unlimited] 2") {
//     data_chunk data = {0};
//     kth::data_source ds(data);
//     kth::istream_reader source(ds);

//     auto ret = read_null_terminated_string_unlimited(source);
//     REQUIRE(ret == ""); 
// }

// TEST_CASE("[test_read_null_terminated_string_unlimited] 3") {
//     data_chunk data = {};
//     bc::data_source ds(data);
//     bc::istream_reader source(ds);

//     auto ret = read_null_terminated_string_unlimited(source);
//     REQUIRE(ret == ""); 
// }


// TEST_CASE("[test_read_null_terminated_string] 1") {
//     data_chunk data = {'A', 'B', 'C', 0};
//     bc::data_source ds(data);
//     bc::istream_reader source(ds);

//     auto ret = read_null_terminated_string(source, 4);
//     REQUIRE(bool(ret));
//     REQUIRE(*ret == "ABC"); 
// }

// TEST_CASE("[test_read_null_terminated_string] 2") {
//     data_chunk data = {'A', 'B', 'C', 0};
//     bc::data_source ds(data);
//     bc::istream_reader source(ds);

//     auto ret = read_null_terminated_string(source, 5);
//     REQUIRE(bool(ret));
//     REQUIRE(*ret == "ABC"); 
// }

// TEST_CASE("[test_read_null_terminated_string] 3") {
//     data_chunk data = {'A', 'B', 'C', 0};
//     bc::data_source ds(data);
//     bc::istream_reader source(ds);

//     auto ret = read_null_terminated_string(source, 3);
//     REQUIRE(! bool(ret));
// }

// TEST_CASE("[test_read_null_terminated_string] 4") {
//     data_chunk data = {'A', 'B', 'C', 0};
//     bc::data_source ds(data);
//     bc::istream_reader source(ds);

//     auto ret = read_null_terminated_string(source, 2);
//     REQUIRE(! bool(ret));
// }

// TEST_CASE("[test_read_null_terminated_string] 5") {
//     data_chunk data = {'A', 'B', 'C', 0};
//     bc::data_source ds(data);
//     bc::istream_reader source(ds);

//     auto ret = read_null_terminated_string(source, 1);
//     REQUIRE(! bool(ret));
// }

// TEST_CASE("[test_read_null_terminated_string] 6") {
//     data_chunk data = {'A', 'B', 'C', 0};
//     bc::data_source ds(data);
//     bc::istream_reader source(ds);

//     auto ret = read_null_terminated_string(source, 0);
//     REQUIRE(! bool(ret));
// }

// TEST_CASE("[test_read_null_terminated_string] 7") {
//     data_chunk data = {0};
//     bc::data_source ds(data);
//     bc::istream_reader source(ds);

//     auto ret = read_null_terminated_string(source, 0);
//     REQUIRE(! bool(ret));
// }

// TEST_CASE("[test_read_null_terminated_string] 8") {
//     data_chunk data = {0};
//     bc::data_source ds(data);
//     bc::istream_reader source(ds);

//     auto ret = read_null_terminated_string(source, 1);
//     REQUIRE(bool(ret));
//     REQUIRE(*ret == ""); 
// }

// TEST_CASE("[test_read_null_terminated_string] 9") {
//     data_chunk data = {};
//     bc::data_source ds(data);
//     bc::istream_reader source(ds);

//     auto ret = read_null_terminated_string(source, 1);
//     REQUIRE(! bool(ret));
// }



