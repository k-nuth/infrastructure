// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
#ifndef KTH_INFRASTRUCTURE_LOG_ATTRIBUTES_HPP
#define KTH_INFRASTRUCTURE_LOG_ATTRIBUTES_HPP

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
