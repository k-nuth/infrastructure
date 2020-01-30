///////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2014-2015 libbitcoin developers (see COPYING).
//
//        GENERATED SOURCE CODE, DO NOT EDIT EXCEPT EXPERIMENTALLY
//
///////////////////////////////////////////////////////////////////////////////
#ifndef KTH_INFRASTRUCTURE_VERSION_HPP_
#define KTH_INFRASTRUCTURE_VERSION_HPP_

/**
 * The semantic version of this repository as: [major].[minor].[patch]
 * For interpretation of the versioning scheme see: http://semver.org
 */

#ifdef KTH_PROJECT_VERSION
#define KTH_INFRASTRUCTURE_VERSION KTH_PROJECT_VERSION
#else
#define KTH_INFRASTRUCTURE_VERSION "0.0.0"
#endif

// #define KTH_VERSION KTH_INFRASTRUCTURE_VERSION

namespace libbitcoin { namespace infrastructure {
char const* version();
}} /*namespace libbitcoin::infrastructure*/
 

#endif // KTH_INFRASTRUCTURE_VERSION_HPP_
