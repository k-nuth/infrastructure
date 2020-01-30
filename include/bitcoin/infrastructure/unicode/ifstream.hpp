﻿/**
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
#ifndef KNUTH_INFRASTRUCTURE_IFSTREAM_HPP
#define KNUTH_INFRASTRUCTURE_IFSTREAM_HPP

#include <fstream>
#include <string>

#include <bitcoin/infrastructure/define.hpp>

namespace kth {

/**
 * Use bc::ifstream in place of std::ifstream.
 * This provides utf8 to utf16 path translation for Windows.
 */
class BI_API ifstream
    : public std::ifstream
{
public:
    /**
     * Construct bc::ifstream.
     * @param[in]  path  The utf8 path to the file.
     * @param[in]  mode  The file opening mode.
     */
    explicit
    ifstream(std::string const& path, std::ifstream::openmode mode = std::ifstream::in);
};

} // namespace libbitcoin

#endif
