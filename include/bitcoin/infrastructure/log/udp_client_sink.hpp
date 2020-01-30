// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
#ifndef KTH_INFRASTRUCTURE_LOG_UDP_CLIENT_SINK_HPP
#define KTH_INFRASTRUCTURE_LOG_UDP_CLIENT_SINK_HPP

#include <string>

#include <boost/asio.hpp>
#include <boost/log/sinks/basic_sink_backend.hpp>
#include <boost/shared_ptr.hpp>

#include <bitcoin/infrastructure/define.hpp>
#include <bitcoin/infrastructure/error.hpp>

namespace kth {
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
    void handle_send(const boost_code& /*unused*/, size_t /*unused*/, message_ptr payload);

private:
    socket_ptr socket_;
    endpoint_ptr const endpoint_;
};

} // namespace log
} // namespace kth

#endif
