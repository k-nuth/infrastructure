///////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2014-2015 libbitcoin developers (see COPYING).
//
//        GENERATED SOURCE CODE, DO NOT EDIT EXCEPT EXPERIMENTALLY
//
///////////////////////////////////////////////////////////////////////////////
#ifndef BITPRIM_INFRASTRUCTURE_VERSION_HPP_
#define BITPRIM_INFRASTRUCTURE_VERSION_HPP_

/**
 * The semantic version of this repository as: [major].[minor].[patch]
 * For interpretation of the versioning scheme see: http://semver.org
 */

// #define BITPRIM_INFRASTRUCTURE_VERSION "3.4.0"
#define BITPRIM_INFRASTRUCTURE_MAJOR_VERSION 0
#define BITPRIM_INFRASTRUCTURE_MINOR_VERSION 11
#define BITPRIM_INFRASTRUCTURE_PATCH_VERSION 0

// #define STR_HELPER(x) #x
// #define STR(x) STR_HELPER(x)
// #define BITPRIM_INFRASTRUCTURE_VERSION STR(LIBBITCOIN_MAJOR_VERSION) "." STR(LIBBITCOIN_MINOR_VERSION) "." STR(LIBBITCOIN_PATCH_VERSION)
// #undef STR
// #undef STR_HELPER

#define BITPRIM_INFRASTRUCTURE_VERSION_1 "0.11.0"

#ifdef BITPRIM_BUILD_NUMBER
#define BITPRIM_INFRASTRUCTURE_VERSION_2 BITPRIM_BUILD_NUMBER
#else
#define BITPRIM_INFRASTRUCTURE_VERSION_2 "v0.0.0"
#endif

// #pragma message("LIBBITCOIN_VERSION")
// #pragma message(LIBBITCOIN_VERSION)
// #pragma message("BITPRIM_BUILD_NUMBER")
// #pragma message(BITPRIM_BUILD_NUMBER)

namespace libbitcoin { 
namespace infrastructure {

char const* version();

} /*namespace infrastructure*/
} /*namespace libbitcoin*/
 

#endif // BITPRIM_INFRASTRUCTURE_VERSION_HPP_
