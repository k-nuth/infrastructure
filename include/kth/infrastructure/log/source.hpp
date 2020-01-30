// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
#ifndef KTH_INFRASTRUCTURE_LOG_SOURCE_HPP
#define KTH_INFRASTRUCTURE_LOG_SOURCE_HPP

#include <string>

#include <boost/log/attributes/clock.hpp>
#include <boost/log/sources/global_logger_storage.hpp>
#include <boost/log/sources/severity_channel_logger.hpp>

#include <bitcoin/infrastructure/define.hpp>
#include <bitcoin/infrastructure/log/attributes.hpp>
#include <bitcoin/infrastructure/log/severity.hpp>

namespace kth {
namespace log {

typedef boost::log::sources::severity_channel_logger_mt<severity, std::string>
    severity_source;

BOOST_LOG_INLINE_GLOBAL_LOGGER_INIT(source, severity_source) {
    static auto const name = attributes::timestamp.get_name();
    severity_source logger;
    logger.add_attribute(name, boost::log::attributes::utc_clock());
    return logger;
}

#define BI_LOG_SEVERITY(id, level) \
    BOOST_LOG_CHANNEL_SEV(bc::log::source::get(), id, bc::log::severity::level)

#define LOG_VERBOSE(module) BI_LOG_SEVERITY(module, verbose)
#define LOG_DEBUG(module) BI_LOG_SEVERITY(module, debug)
#define LOG_INFO(module) BI_LOG_SEVERITY(module, info)
#define LOG_WARNING(module) BI_LOG_SEVERITY(module, warning)
#define LOG_ERROR(module) BI_LOG_SEVERITY(module, error)
#define LOG_FATAL(module) BI_LOG_SEVERITY(module, fatal)

} // namespace log
} // namespace kth

#endif
