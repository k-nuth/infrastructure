///////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2014-2015 libbitcoin developers (see COPYING).
//
//        GENERATED SOURCE CODE, DO NOT EDIT EXCEPT EXPERIMENTALLY
//
///////////////////////////////////////////////////////////////////////////////
#ifndef KNUTH_INFRASTRUCTURE_VERSION_HPP_
#define KNUTH_INFRASTRUCTURE_VERSION_HPP_

/**
 * The semantic version of this repository as: [major].[minor].[patch]
 * For interpretation of the versioning scheme see: http://semver.org
 */

#ifdef KNUTH_PROJECT_VERSION
#define KNUTH_INFRASTRUCTURE_VERSION KNUTH_PROJECT_VERSION
#else
#define KNUTH_INFRASTRUCTURE_VERSION "0.0.0"
#endif

// #define LIBBITCOIN_VERSION KNUTH_INFRASTRUCTURE_VERSION

namespace kth { namespace infrastructure {
char const* version();
}} /*namespace libbitcoin::infrastructure*/
 

#endif // KNUTH_INFRASTRUCTURE_VERSION_HPP_
