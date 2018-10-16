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
#ifndef BITPRIM_INFRASTRUCTURE_INTERPROCESS_LOCK_HPP
#define BITPRIM_INFRASTRUCTURE_INTERPROCESS_LOCK_HPP

#include <memory>
#include <string>

#include <boost/filesystem.hpp>

#include <bitcoin/infrastructure/define.hpp>
#include <bitcoin/infrastructure/unicode/file_lock.hpp>

namespace libbitcoin {

/// This class is not thread safe.
/// Guard a resource againt concurrent use by another instance of this app.
class BI_API interprocess_lock
{
public:
    using path = boost::filesystem::path;

    interprocess_lock(const path& file);
    virtual ~interprocess_lock();

    bool lock();
    bool unlock();

private:
    using lock_file = interprocess::file_lock;
    using lock_ptr = std::shared_ptr<lock_file>;

    static bool create(std::string const& file);
    static bool destroy(std::string const& file);

    lock_ptr lock_;
    std::string const file_;
};

} // namespace libbitcoin

#endif
