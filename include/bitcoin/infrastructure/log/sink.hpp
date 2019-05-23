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
#ifndef BITPRIM_INFRASTRUCTURE_LOG_SINK_HPP
#define BITPRIM_INFRASTRUCTURE_LOG_SINK_HPP

#include <iostream>

#include <boost/smart_ptr.hpp>

#include <bitcoin/infrastructure/define.hpp>
#include <bitcoin/infrastructure/log/rotable_file.hpp>
#include <bitcoin/infrastructure/log/severity.hpp>
#include <bitcoin/infrastructure/unicode/ofstream.hpp>

namespace libbitcoin {
namespace log {

using file = boost::shared_ptr<bc::ofstream>;

/// Initializes null (as opposed to default) logging sinks.
void initialize();

/// Initializes default non-rotable libbitcoin logging sinks and formats.
void initialize(log::file& debug_file, log::file& error_file,
    log::stream& output_stream, log::stream& error_stream, bool verbose);

/// Initializes default rotable libbitcoin logging sinks and formats.
void initialize(const rotable_file& debug_file, const rotable_file& error_file,
    log::stream& output_stream, log::stream& error_stream, bool verbose);

/// Log stream operator.
formatter& operator<<(formatter& stream, severity value);

} // namespace log
} // namespace libbitcoin

#endif
