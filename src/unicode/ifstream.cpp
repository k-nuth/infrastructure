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
#include <bitcoin/infrastructure/unicode/ifstream.hpp>

#include <fstream>
#include <string>

#include <bitcoin/infrastructure/unicode/unicode.hpp>

namespace kth {

// Construct bc::ifstream.
ifstream::ifstream(std::string const& path, std::ifstream::openmode mode)
#ifdef _MSC_VER
  : std::ifstream(bc::to_utf16(path), mode)
#else
  : std::ifstream(path, mode)
#endif
{
}

} // namespace kth
