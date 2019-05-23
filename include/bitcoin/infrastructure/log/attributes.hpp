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
#ifndef KNUTH_INFRASTRUCTURE_LOG_ATTRIBUTES_HPP
#define KNUTH_INFRASTRUCTURE_LOG_ATTRIBUTES_HPP

#include <string>

#include <boost/log/attributes/clock.hpp>
#include <boost/log/expressions/keyword.hpp>

#include <bitcoin/infrastructure/define.hpp>
#include <bitcoin/infrastructure/log/severity.hpp>

namespace libbitcoin {
namespace log {
namespace attributes {

// severity/channel/timestamp/message log entries
BOOST_LOG_ATTRIBUTE_KEYWORD(timestamp, "Timestamp", boost::posix_time::ptime)
BOOST_LOG_ATTRIBUTE_KEYWORD(severity, "Severity", libbitcoin::log::severity)
BOOST_LOG_ATTRIBUTE_KEYWORD(channel, "Channel", std::string)

} // namespace attributes
} // namespace log
} // namespace libbitcoin

#endif
