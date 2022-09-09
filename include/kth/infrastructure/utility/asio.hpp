// Copyright (c) 2016-2022 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_INFRASTRUCTURE_ASIO_HPP
#define KTH_INFRASTRUCTURE_ASIO_HPP

#include <chrono>
#include <memory>

#include <boost/thread.hpp>

#include <kth/infrastructure/compat.hpp>
#include <kth/infrastructure/utility/asio_helper.hpp>

// Convenience namespace for commonly used boost asio aliases.
namespace kth::asio {

namespace error = ::asio::error;

using hours = std::chrono::hours;
using minutes = std::chrono::minutes;
using seconds = std::chrono::seconds;
using milliseconds = std::chrono::milliseconds;
using microseconds = std::chrono::microseconds;

// Steady clock: use for continuity, not time of day determinations.
using steady_clock = std::chrono::steady_clock;
using duration = steady_clock::duration;
using time_point = steady_clock::time_point;
using timer = ::asio::basic_waitable_timer<steady_clock>;

using service = ::asio::io_service;
using address = ::asio::ip::address;
using ipv4 = ::asio::ip::address_v4;
using ipv6 = ::asio::ip::address_v6;
using tcp = ::asio::ip::tcp;
using endpoint = ::asio::ip::tcp::endpoint;

using socket = tcp::socket;
using acceptor = tcp::acceptor;
using resolver = tcp::resolver;
using query = tcp::resolver::query;
using iterator = tcp::resolver::iterator;

// Boost thread is used because of thread_specific_ptr limitation:
// stackoverflow.com/q/22448022/1172329
using thread = boost::thread;

using socket_ptr = std::shared_ptr<socket>;

constexpr int max_connections = ::asio::socket_base::max_connections;

} // namespace kth::asio

#define FMT_HEADER_ONLY 1
#include <fmt/format.h>

// template <>
// struct fmt::formatter<kth::asio::ipv6> {
//     constexpr auto parse(format_parse_context& ctx) { return ctx.begin(); }

//     template <typename FormatContext>
//     auto format(kth::asio::ipv6 const& addr, FormatContext& ctx) {
//         return format_to(ctx.out(), "{}", addr.to_string());
//     }
// };

template <>
struct fmt::formatter<kth::asio::ipv6> : formatter<std::string> {
    template <typename FormatContext>
    auto format(kth::asio::ipv6 const& addr, FormatContext& ctx) const {
        return formatter<std::string>::format(addr.to_string(), ctx);
    }
};

#endif
