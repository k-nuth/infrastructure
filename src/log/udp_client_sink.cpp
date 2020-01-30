/**
 * Copyright (c) 2016-2020 Knuth Project.
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
#include <bitcoin/infrastructure/log/udp_client_sink.hpp>

#include <cstddef>
#include <functional>
#include <string>

#include <boost/make_shared.hpp>

#include <bitcoin/infrastructure/error.hpp>
#include <utility>

namespace kth {
namespace log {

using namespace std::placeholders;
using namespace boost::asio;
using namespace boost::log;

udp_client_sink::udp_client_sink(socket_ptr socket, endpoint_ptr endpoint)
    : socket_(std::move(socket)), endpoint_(std::move(endpoint))
{}

void udp_client_sink::consume(const record_view& record, std::string const& message) {
    send(message);
}

void udp_client_sink::send(std::string const& message) {
    if ( ! socket_ || !endpoint_) {
        return;
    }

    auto const payload = boost::make_shared<std::string>(message);

    // This is not guarded against interleaving of messages that exceed 64k.
    socket_->async_send_to(buffer(*payload), *endpoint_, std::bind(&udp_client_sink::handle_send, this, _1, _2, payload));
}

void udp_client_sink::handle_send(const boost_code& /*unused*/, size_t /*unused*/, message_ptr payload) {
    // This holds the message in scope until the send is completed.
    payload.reset();
}

} // namespace log
} // namespace libbitcoin
