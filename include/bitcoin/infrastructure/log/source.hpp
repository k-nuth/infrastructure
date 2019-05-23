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
#ifndef BITPRIM_INFRASTRUCTURE_LOG_SOURCE_HPP
#define BITPRIM_INFRASTRUCTURE_LOG_SOURCE_HPP

#include <string>

#include <boost/log/attributes/clock.hpp>
#include <boost/log/sources/global_logger_storage.hpp>
#include <boost/log/sources/severity_channel_logger.hpp>

#include <bitcoin/infrastructure/define.hpp>
#include <bitcoin/infrastructure/log/attributes.hpp>
#include <bitcoin/infrastructure/log/severity.hpp>

namespace libbitcoin {
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
} // namespace libbitcoin

#endif
