// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
#ifndef KTH_INFRASTRUCTURE_LOG_STATSD_SINK_HPP
#define KTH_INFRASTRUCTURE_LOG_STATSD_SINK_HPP

#include <boost/asio.hpp>

#include <bitcoin/infrastructure/config/authority.hpp>
#include <bitcoin/infrastructure/define.hpp>
#include <bitcoin/infrastructure/log/rotable_file.hpp>
#include <bitcoin/infrastructure/utility/threadpool.hpp>

namespace kth {
namespace log {

void initialize_statsd(const rotable_file& file);

void initialize_statsd(threadpool& pool, const config::authority& server);

} // namespace log
} // namespace kth

#endif
