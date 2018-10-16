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
#ifndef BITPRIM_INFRASTRUCTURE_SEQUENTIAL_LOCK_HPP
#define BITPRIM_INFRASTRUCTURE_SEQUENTIAL_LOCK_HPP

#include <atomic>
#include <cstddef>

#include <bitcoin/infrastructure/define.hpp>

namespace libbitcoin {

/// This class is thread safe.
/// Encapsulation of sequential locking conditions.
class BI_API sequential_lock
{
public:
    using handle = size_t;

    /// Determine if the given handle is a write-locked handle.
    static bool is_write_locked(handle value)
    {
        return (value % 2) == 1;
    }

    sequential_lock();

    handle begin_read() const;
    bool is_read_valid(handle value) const;

    bool begin_write();
    bool end_write();

private:
    std::atomic<size_t> sequence_;
};

} // namespace libbitcoin

#endif
