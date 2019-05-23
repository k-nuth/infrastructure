/**
 * Copyright (c) 2016-2019 Knuth Project.
 *
 * This file is part of Knuth Project.
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
#ifndef KNUTH_INFRASTRUCTURE_ASIO_HPP
#define KNUTH_INFRASTRUCTURE_ASIO_HPP

#include <chrono>
#include <memory>

#include <boost/asio.hpp>
#include <boost/thread.hpp>

#include <bitcoin/infrastructure/compat.hpp>

// Convenience namespace for commonly used boost asio aliases.

namespace libbitcoin {
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

BC_CONSTEXPR int max_connections = boost::asio::socket_base::max_connections;

} // namespace asio
} // namespace libbitcoin

#endif
