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
#ifndef KNUTH_INFRASTRUCTURE_OFSTREAM_HPP
#define KNUTH_INFRASTRUCTURE_OFSTREAM_HPP

#include <fstream>
#include <string>

#include <bitcoin/infrastructure/define.hpp>

namespace libbitcoin {

/**
 * Use bc::ofstream in place of std::ofstream.
 * This provides utf8 to utf16 path translation for Windows.
 */
class BI_API ofstream
    : public std::ofstream
{
public:
    /**
     * Construct bc::ofstream.
     * @param[in]  path  The utf8 path to the file.
     * @param[in]  mode  The file opening mode.
     */
    explicit
    ofstream(std::string const& path, std::ofstream::openmode mode = std::ofstream::out);
};

} // namespace libbitcoin

#endif
