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
#ifndef BITPRIM_INFRASTRUCTURE_CRASH_LOCK_HPP
#define BITPRIM_INFRASTRUCTURE_CRASH_LOCK_HPP

#include <memory>
#include <boost/filesystem.hpp>
#include <bitcoin/infrastructure/define.hpp>
#include <bitcoin/infrastructure/unicode/file_lock.hpp>

namespace libbitcoin {

/// This class is not thread safe.
/// Guard a resource that may be corrupted due to an interrupted write.
class BI_API flush_lock
{
public:
    using path = boost::filesystem::path;

    flush_lock(const path& file);

    bool try_lock();
    bool lock_shared();
    bool unlock_shared();

private:
    static bool create(std::string const& file);
    static bool exists(std::string const& file);
    static bool destroy(std::string const& file);

    bool locked_;
    std::string const file_;
};

} // namespace libbitcoin

#endif
