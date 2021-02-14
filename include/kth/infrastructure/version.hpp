// Copyright (c) 2016-2021 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

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

namespace kth::infrastructure {

char const* version();

} // namespace kth::infrastructure
 

#endif // KTH_INFRASTRUCTURE_VERSION_HPP_
