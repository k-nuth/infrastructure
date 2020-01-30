// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
#ifndef KTH_INFRASTRUCTURE_LOG_SEVERITY_HPP
#define KTH_INFRASTRUCTURE_LOG_SEVERITY_HPP

#include <bitcoin/infrastructure/define.hpp>

namespace kth {
namespace log {

enum class severity {
    verbose,
    debug,
    info,
    warning,
    error,
    fatal
};

} // namespace log
} // namespace kth

#endif
