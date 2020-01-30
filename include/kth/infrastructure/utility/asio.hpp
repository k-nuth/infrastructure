// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
#ifndef KTH_INFRASTRUCTURE_ASIO_HPP
#define KTH_INFRASTRUCTURE_ASIO_HPP

#include <chrono>
#include <memory>

#include <boost/asio.hpp>
#include <boost/thread.hpp>

#include <bitcoin/infrastructure/compat.hpp>

// Convenience namespace for commonly used boost asio aliases.

namespace kth {
namespace asio {

namespace error = boost::asio::error;

using hours = std::chrono::hours;
using minutes = std::chrono::minutes;
using seconds = std::chrono::seconds;
using milliseconds = std::chrono::milliseconds;
using microseconds = std::chrono::microseconds;

// Steady clock: use for continuity, not time of day determinations.
using steady_clock = std::chrono::steady_clock;
using duration = steady_clock::duration;
using time_point = steady_clock::time_point;
using timer = boost::asio::basic_waitable_timer<steady_clock>;

using service = boost::asio::io_service;
using address = boost::asio::ip::address;
using ipv4 = boost::asio::ip::address_v4;
using ipv6 = boost::asio::ip::address_v6;
using tcp = boost::asio::ip::tcp;
using endpoint = boost::asio::ip::tcp::endpoint;

using socket = tcp::socket;
using acceptor = tcp::acceptor;
using resolver = tcp::resolver;
using query = tcp::resolver::query;
using iterator = tcp::resolver::iterator;

// Boost thread is used because of thread_specific_ptr limitation:
// stackoverflow.com/q/22448022/1172329
using thread = boost::thread;

using socket_ptr = std::shared_ptr<socket>;

constexpr int max_connections = boost::asio::socket_base::max_connections;

} // namespace asio
} // namespace kth

#endif
