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
#ifndef BITPRIM_INFRASTRUCTURE_TRACK_HPP
#define BITPRIM_INFRASTRUCTURE_TRACK_HPP

#include <atomic>
#include <cstddef>
#include <string>

// libbitcoin defines the log and tracking but does not use them.
// These are defined in bc so that they can be used in network and blockchain.

#define CONSTRUCT_TRACK(class_name) \
    track<class_name>(#class_name)

template <typename Shared>
class track
{
public:
    static std::atomic<size_t> instances;

protected:
    track(std::string const& class_name);
    ~track();

private:
    std::string const class_;
};

#include <bitcoin/infrastructure/impl/utility/track.ipp>

#endif
