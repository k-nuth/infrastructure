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
#ifndef BITPRIM_INFRASTRUCTURE_CONDITIONAL_LOCK_HPP
#define BITPRIM_INFRASTRUCTURE_CONDITIONAL_LOCK_HPP

#include <memory>
#include <bitcoin/infrastructure/define.hpp>
#include <bitcoin/infrastructure/utility/thread.hpp>

namespace libbitcoin {

class BI_API conditional_lock
{
public:
    /// Conditional lock using specified mutex pointer.
    explicit conditional_lock(std::shared_ptr<shared_mutex> mutex_ptr);

    /// Unlock.
    virtual ~conditional_lock();

private:
    const std::shared_ptr<shared_mutex> mutex_ptr_;
};

} // namespace libbitcoin

#endif
