/**
 * Copyright (c) 2016-2020 Knuth Project.
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
#ifndef KNUTH_INFRASTRUCTURE_SCOPE_LOCK_HPP
#define KNUTH_INFRASTRUCTURE_SCOPE_LOCK_HPP

#include <memory>

#include <bitcoin/infrastructure/define.hpp>
#include <bitcoin/infrastructure/utility/thread.hpp>

namespace libbitcoin {

/// This class is thread safe.
/// Reserve exclusive access to a resource while this object is in scope.
class BI_API scope_lock
{
public:
    using ptr = std::shared_ptr<scope_lock>;

    /// Lock using the specified mutex reference.
    explicit
    scope_lock(shared_mutex& mutex);

    /// Unlock.
    ~scope_lock();

private:
    shared_mutex& mutex_;
};

} // namespace libbitcoin

#endif
