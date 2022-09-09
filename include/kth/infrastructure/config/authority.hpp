// Copyright (c) 2016-2022 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_INFRASTUCTURE_CONFIG_AUTHORITY_HPP
#define KTH_INFRASTUCTURE_CONFIG_AUTHORITY_HPP

// #ifdef KTH_INFRASTUCTURE_CONFIG_ENABLED

#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

#include <kth/infrastructure/define.hpp>
#include <kth/infrastructure/message/network_address.hpp>
#include <kth/infrastructure/utility/asio.hpp>

#define FMT_HEADER_ONLY 1
#include <fmt/format.h>

namespace kth::infrastructure::config {

/**
 * Serialization helper for a network authority.
 * This is a container for a {ip address, port} tuple.
 */
class KI_API authority {
public:
    using list = std::vector<authority>;

    authority() = default;

    // authority(authority const& x);

    explicit
    authority(std::string const& authority);

    // implicit //Note(fernando): in kth-network it is used the implicit convertion
    authority(message::network_address const& address);

    authority(message::ip_address const& ip, uint16_t port);

    authority(std::string const& host, uint16_t port);

    authority(asio::address const& ip, uint16_t port);

    explicit
    authority(asio::endpoint const& endpoint);

    explicit
    operator bool const() const;

    asio::ipv6 asio_ip() const;

    message::ip_address ip() const;

    uint16_t port() const;

    std::string to_hostname() const;

    std::string to_string() const;

    message::network_address to_network_address() const;

    bool operator==(authority const& x) const;

    bool operator!=(authority const& x) const;

    friend
    std::istream& operator>>(std::istream& input, authority& argument);

    // friend
    // std::ostream& operator<<(std::ostream& output, authority const& argument);

private:
    asio::ipv6 ip_;
    uint16_t port_{0};
};

} // namespace kth::infrastructure::config

template <>
struct fmt::formatter<kth::infrastructure::config::authority> : formatter<std::string> {
    template <typename FormatContext>
    auto format(kth::infrastructure::config::authority const& x, FormatContext& ctx) const {
        return formatter<std::string>::format(x.to_string(), ctx);
    }
};

// #endif // KTH_INFRASTUCTURE_CONFIG_ENABLED

#endif
