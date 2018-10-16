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
#ifndef BITPRIM_INFRASTRUCTURE_MONITOR_HPP
#define BITPRIM_INFRASTRUCTURE_MONITOR_HPP

#include <atomic>
#include <cstddef>
#include <memory>
#include <string>
#include <utility>

#include <bitcoin/infrastructure/define.hpp>

// libbitcoin defines the log and tracking but does not use them.
// These are defined in bc so that they can be used in network and blockchain.

namespace libbitcoin {

/// A reference counting wrapper for closures placed on the asio work heap.
class BI_API monitor
{
public:
    using count = std::atomic<size_t>;
    using count_ptr = std::shared_ptr<count>;

    monitor(count_ptr counter, std::string&& name);
    virtual ~monitor();

    template <typename Handler>
    void invoke(Handler handler) const
    {
        ////trace(*counter_, "*");
        handler();
    }

    void trace(size_t /*unused*/, std::string const& /*unused*/) const
    {
        ////#ifndef NDEBUG
        ////    LOG_DEBUG(LOG_SYSTEM)
        ////        << action << " " << name_ << " {" << count << "}";
        ////#endif
    }

private:
    count_ptr counter_;
    std::string const name_;
};

} // namespace libbitcoin

#endif
