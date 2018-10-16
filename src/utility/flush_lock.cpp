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
#include <bitcoin/infrastructure/utility/flush_lock.hpp>

#include <memory>

#include <boost/filesystem.hpp>

#include <bitcoin/infrastructure/unicode/file_lock.hpp>
#include <bitcoin/infrastructure/unicode/ifstream.hpp>
#include <bitcoin/infrastructure/unicode/ofstream.hpp>

namespace libbitcoin {

// static
bool flush_lock::create(std::string const& file)
{
    bc::ofstream stream(file);
    return stream.good();
}

// static
bool flush_lock::exists(std::string const& file)
{
    bc::ifstream stream(file);
    return stream.good();
    ////return boost::filesystem::exists(file);
}

// static
bool flush_lock::destroy(std::string const& file)
{
    return boost::filesystem::remove(file);
    ////std::remove(file.c_str());
}

flush_lock::flush_lock(const path& file)
  : file_(file.string()), locked_(false)
{
}

bool flush_lock::try_lock()
{
    return !exists(file_);
}

// Lock is idempotent, returns true if locked on return.
bool flush_lock::lock_shared()
{
    if (locked_)
        return true;

    locked_ = create(file_);
    return locked_;
}

// Unlock is idempotent, returns true if unlocked on return.
bool flush_lock::unlock_shared()
{
    if (!locked_)
        return true;

    locked_ = !destroy(file_);
    return !locked_;
}

} // namespace libbitcoin
