// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
#ifndef KTH_INFRASTRUCTURE_MULTI_INFRASTUCTURE_SUPPORT_HPP_
#define KTH_INFRASTRUCTURE_MULTI_INFRASTUCTURE_SUPPORT_HPP_

#include <string>

#include <bitcoin/infrastructure/config/settings.hpp>

namespace kth {

namespace netmagic {
constexpr uint32_t btc_mainnet = 0xd9b4bef9u;
constexpr uint32_t btc_testnet = 0x0709110bu;
constexpr uint32_t btc_regtest = 0xdab5bffau;

constexpr uint32_t ltc_mainnet = 0xdbb6c0fbu;
constexpr uint32_t ltc_testnet = 0xf1c8d2fdu;
constexpr uint32_t ltc_regtest = 0xdab5bffau;

constexpr uint32_t bch_mainnet = 0xe8f3e1e3u;
constexpr uint32_t bch_testnet = 0xf4f3e5f4u;
constexpr uint32_t bch_regtest = 0xfabfb5dau;
} // namespace netmagic

namespace config {

enum class currency {
    none,
    bitcoin,
    bitcoin_cash,
    litecoin
};

} // namespace config

config::currency get_currency();

// void set_network(config::settings x);
// void set_network(uint32_t identifier);
// config::settings get_network();
config::settings get_network(uint32_t identifier);

#ifdef KTH_CURRENCY_BCH
std::string cashaddr_prefix();
void set_cashaddr_prefix(std::string const& x);
#endif //KTH_CURRENCY_BCH

} /*namespace libbitcoin*/

#endif /*KTH_MULTI_INFRASTUCTURE_SUPPORT_HPP_*/
