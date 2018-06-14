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
#ifndef LIBBITCOIN_INFRASTRUCTURE_LOG_STATSD_SINK_HPP
#define LIBBITCOIN_INFRASTRUCTURE_LOG_STATSD_SINK_HPP

#include <boost/asio.hpp>
#include <bitcoin/infrastructure/define.hpp>
#include <bitcoin/infrastructure/config/authority.hpp>
#include <bitcoin/infrastructure/log/rotable_file.hpp>
#include <bitcoin/infrastructure/utility/threadpool.hpp>

namespace libbitcoin {
namespace log {

void initialize_statsd(const rotable_file& file);

void initialize_statsd(threadpool& pool, const config::authority& server);

} // namespace log
} // namespace libbitcoin

#endif
