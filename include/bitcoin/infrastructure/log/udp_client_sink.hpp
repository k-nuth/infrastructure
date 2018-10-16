/**
 * Copyright (c) 2017-2018 Bitprim Inc.
 *
 * This file is part of Bitprim.
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
#ifndef BITPRIM_INFRASTRUCTURE_LOG_UDP_CLIENT_SINK_HPP
#define BITPRIM_INFRASTRUCTURE_LOG_UDP_CLIENT_SINK_HPP

#include <string>
#include <boost/asio.hpp>
#include <boost/log/sinks/basic_sink_backend.hpp>
#include <boost/shared_ptr.hpp>
#include <bitcoin/infrastructure/define.hpp>
#include <bitcoin/infrastructure/error.hpp>

namespace libbitcoin {
namespace log {

class BI_API udp_client_sink
  : public boost::log::sinks::basic_formatted_sink_backend<char,
        boost::log::sinks::synchronized_feeding>
{
public:
    using udp = boost::asio::ip::udp;
    using socket_ptr = boost::shared_ptr<udp::socket>;
    using endpoint_ptr = boost::shared_ptr<udp::endpoint>;

    udp_client_sink(socket_ptr socket, endpoint_ptr endpoint);

    void consume(const boost::log::record_view& record,
        std::string const& message);

protected:
    using message_ptr = boost::shared_ptr<std::string>;

    void send(std::string const& message);
    void handle_send(const boost_code&, size_t, message_ptr payload);

private:
    socket_ptr socket_;
    endpoint_ptr const endpoint_;
};

} // namespace log
} // namespace libbitcoin

#endif
