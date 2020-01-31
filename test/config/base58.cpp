// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
#include <boost/test/test_tools.hpp>
#include <boost/test/unit_test_suite.hpp>
#include <kth/infrastructure.hpp>

using namespace bc;
using namespace bc::config;

#define BASE58_ENCODED_A "vYxp6yFC7qiVtK1RcGQQt3L6EqTc8YhEDLnSMLqDvp8D"
#define BASE58_DECODED_A \
{{ \
    0x03, 0x1b, 0xab, 0x84, 0xe6, 0x87, 0xe3, 0x65, 0x14, 0xee, 0xaf, 0x5a, \
    0x01, 0x7c, 0x30, 0xd3, 0x2c, 0x1f, 0x59, 0xdd, 0x4e, 0xa6, 0x62, 0x9d, \
    0xa7, 0x97, 0x0c, 0xa3, 0x74, 0x51, 0x3d, 0xd0,  0x06 \
}}

BOOST_AUTO_TEST_SUITE(base58_tests)

BOOST_AUTO_TEST_CASE(base58__constructor__default__does_not_throw)
{
    BOOST_REQUIRE_NO_THROW(base58());
}

BOOST_AUTO_TEST_CASE(base58__constructor__valid_string_cast__decodes)
{
    data_chunk const original(BASE58_DECODED_A);
    data_chunk const instance(base58(BASE58_ENCODED_A));
    BOOST_REQUIRE(original == instance);
}

////BOOST_AUTO_TEST_CASE(base58__constructor__bogus_string__throws_invalid_option)
////{
////    //BX_REQUIRE_THROW_INVALID_OPTION_VALUE(base58("bo-gus"));
////}

////BOOST_AUTO_TEST_CASE(base58__constructor__copy_address_primitives__round_trips)
////{
////    //BX_SERIALIZE_COPY_ROUND_TRIP(base58, BASE58_ENCODED_A);
////}

BOOST_AUTO_TEST_SUITE_END()
