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

#ifdef BITPRIM_PROJECT_VERSION
#define BITPRIM_INFRASTRUCTURE_VERSION BITPRIM_PROJECT_VERSION
#else
#define BITPRIM_INFRASTRUCTURE_VERSION "0.0.0"
#endif

// #define LIBBITCOIN_VERSION BITPRIM_INFRASTRUCTURE_VERSION

namespace libbitcoin { namespace infrastructure {
char const* version();
}} /*namespace libbitcoin::infrastructure*/
 

#endif // BITPRIM_INFRASTRUCTURE_VERSION_HPP_
