// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
#ifndef KTH_INFRASTUCTURE_MACHINE_SCRIPT_VERSION_HPP
#define KTH_INFRASTUCTURE_MACHINE_SCRIPT_VERSION_HPP

#include <cstdint>

namespace kth {
namespace machine {

/// Script versions (bip141).
enum class script_version
{
    /// Defined by bip141. 
    zero,

    /// All reserved script versions (1..16).
    reserved,

    /// All unversioned scripts.
    unversioned
};

} // namespace machine
} // namespace kth

#endif
