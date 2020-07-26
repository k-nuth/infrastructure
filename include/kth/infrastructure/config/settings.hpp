// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_INFRASTUCTURE_CONFIG_SETTINGS_HPP
#define KTH_INFRASTUCTURE_CONFIG_SETTINGS_HPP


//TODO(fernando): is it Ok this in infrastructure?

namespace kth::infrastructure::config {

// For configuration settings initialization in other libraries.
enum class settings {
    none,
    mainnet,
    testnet,
    regtest
};

} // namespace kth::infrastructure::config

#endif
