/**
 * Copyright (c) 2011-2017 libbitcoin developers (see AUTHORS)
 *
 * This file is part of libbitcoin.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <bitcoin/infrastructure/config/authority.hpp>

#include <algorithm>
#include <regex>
#include <sstream>

#include <boost/algorithm/string.hpp>
#include <boost/format.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/program_options.hpp>

#include <bitcoin/infrastructure/formats/base_16.hpp>
#include <bitcoin/infrastructure/utility/asio.hpp>
#include <bitcoin/infrastructure/utility/assert.hpp>
#include <bitcoin/infrastructure/utility/string.hpp>

namespace libbitcoin {
namespace config {

using namespace boost::program_options;

// host:    [2001:db8::2] or  2001:db8::2  or 1.2.240.1
// returns: [2001:db8::2] or [2001:db8::2] or 1.2.240.1
static 
std::string to_host_name(std::string const& host) {
    if (host.find(":") == std::string::npos || host.find("[") == 0) {
        return host;
    }

    auto const hostname = boost::format("[%1%]") % host;
    return hostname.str();
}

// host: [2001:db8::2] or 2001:db8::2 or 1.2.240.1
static 
std::string to_authority(std::string const& host, uint16_t port) {
    std::stringstream authority;
    authority << to_host_name(host);
    if (port > 0) {
        authority << ":" << port;
    }

    return authority.str();
}

static 
std::string to_ipv6(std::string const& ipv4_address) {
    return std::string("::ffff:") + ipv4_address;
}

static 
asio::ipv6 to_ipv6(asio::ipv4 const& ipv4_address) {
    // Create an IPv6 mapped IPv4 address via serialization.
    auto const ipv6 = to_ipv6(ipv4_address.to_string());
    return asio::ipv6::from_string(ipv6);
}

static 
asio::ipv6 to_ipv6(asio::address const& ip_address) {
    if (ip_address.is_v6()) {
        return ip_address.to_v6();
    }

    BITCOIN_ASSERT_MSG(ip_address.is_v4(), "The address must be either IPv4 or IPv6.");
    return to_ipv6(ip_address.to_v4());
}

static 
std::string to_ipv4_hostname(asio::address const& ip_address) {
    // std::regex requires gcc 4.9, so we are using boost::regex for now.
    // Bitprim: we use std::regex, becase we drop support por GCC<5
    static 
    std::regex const regular("^::ffff:([0-9\\.]+)$");

    auto const address = ip_address.to_string();
    std::sregex_iterator it(address.begin(), address.end(), regular), end;
    if (it == end) {
        return "";
    }

    auto const& match = *it;
    return match[1];
}

static 
std::string to_ipv6_hostname(asio::address const& ip_address) {
    // IPv6 URLs use a bracketed IPv6 address, see rfc2732.
    auto const hostname = boost::format("[%1%]") % to_ipv6(ip_address);
    return hostname.str();
}

authority::authority()
    : port_(0)
{}

authority::authority(authority const& x)
    : authority(x.ip_, x.port_)
{}

// authority: [2001:db8::2]:port or 1.2.240.1:port
authority::authority(std::string const& authority) {
    std::stringstream(authority) >> *this;
}

// This is the format returned from peers on the bitcoin network.
authority::authority(const message::network_address& address)
    : authority(address.ip(), address.port())
{}

static 
asio::ipv6 to_boost_address(const message::ip_address& in) {
    asio::ipv6::bytes_type bytes;
    BITCOIN_ASSERT(bytes.size() == in.size());
    std::copy_n(in.begin(), in.size(), bytes.begin());
    const asio::ipv6 out(bytes);
    return out;
}

static 
message::ip_address to_BI_address(const asio::ipv6& in) {
    message::ip_address out;
    auto const bytes = in.to_bytes();
    BITCOIN_ASSERT(bytes.size() == out.size());
    std::copy_n(bytes.begin(), bytes.size(), out.begin());
    return out;
}

authority::authority(const message::ip_address& ip, uint16_t port)
    : ip_(to_boost_address(ip)), port_(port)
{}

// host: [2001:db8::2] or 2001:db8::2 or 1.2.240.1
authority::authority(std::string const& host, uint16_t port)
    : authority(to_authority(host, port))
{}

authority::authority(asio::address const& ip, uint16_t port)
    : ip_(to_ipv6(ip)), port_(port)
{}

authority::authority(asio::endpoint const& endpoint)
    : authority(endpoint.address(), endpoint.port())
{}

authority::operator const bool() const {
    return port_ != 0;
}

asio::ipv6 authority::asio_ip() const {
    return ip_;
}

message::ip_address authority::ip() const {
    return to_BI_address(ip_);
}

uint16_t authority::port() const {
    return port_;
}

std::string authority::to_hostname() const {
    auto ipv4_hostname = to_ipv4_hostname(ip_);
    return ipv4_hostname.empty() ? to_ipv6_hostname(ip_) : ipv4_hostname;
}

message::network_address authority::to_network_address() const {
    static constexpr uint32_t services = 0;
    static constexpr uint32_t timestamp = 0;
    const message::network_address network_address {
        timestamp, services, ip(), port(),
    };

    return network_address;
}

std::string authority::to_string() const {
    std::stringstream value;
    value << *this;
    return value.str();
}

bool authority::operator==(authority const& x) const {
    return port() == x.port() && ip() == x.ip();
}

bool authority::operator!=(authority const& x) const {
    return !(*this == x);
}

std::istream& operator>>(std::istream& input, authority& argument) {
    using std::regex;
    using std::sregex_iterator;

    std::string value;
    input >> value;

    // std::regex requires gcc 4.9, so we are using boost::regex for now.
    // Bitprim: we use std::regex, becase we drop support por GCC<5
    static 
    regex const regular(R"(^(([0-9\.]+)|\[([0-9a-f:\.]+)\])(:([0-9]{1,5}))?$)");

    sregex_iterator it(value.begin(), value.end(), regular), end;
    if (it == end) {
        BOOST_THROW_EXCEPTION(invalid_option_value(value));
    }

    auto const& match = *it;
    std::string port(match[5]);
    std::string ip_address(match[3]);
    if (ip_address.empty()) {
        ip_address = to_ipv6(match[2]);
    }

    try {
        argument.ip_ = asio::ipv6::from_string(ip_address);
        argument.port_ = port.empty() ? 0 : boost::lexical_cast<uint16_t>(port);
    } catch (...) {
        BOOST_THROW_EXCEPTION(invalid_option_value(value));
    }

    return input;
}

std::ostream& operator<<(std::ostream& output, authority const& argument) {
    output << to_authority(argument.to_hostname(), argument.port());
    return output;
}

} // namespace config
} // namespace libbitcoin