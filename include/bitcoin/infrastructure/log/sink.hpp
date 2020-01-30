// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
#ifndef KTH_INFRASTRUCTURE_LOG_SINK_HPP
#define KTH_INFRASTRUCTURE_LOG_SINK_HPP

#include <iostream>

#include <boost/smart_ptr.hpp>

#include <bitcoin/infrastructure/define.hpp>
#include <bitcoin/infrastructure/log/rotable_file.hpp>
#include <bitcoin/infrastructure/log/severity.hpp>
#include <bitcoin/infrastructure/unicode/ofstream.hpp>

namespace kth {
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
} // namespace kth

#endif
