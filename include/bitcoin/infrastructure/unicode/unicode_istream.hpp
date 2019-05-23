﻿/**
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
#ifndef BITPRIM_INFRASTRUCTURE_UNICODE_ISTREAM_HPP
#define BITPRIM_INFRASTRUCTURE_UNICODE_ISTREAM_HPP

#include <cstddef>
#include <iostream>

#include <bitcoin/infrastructure/define.hpp>

namespace libbitcoin {

/**
 * Class to expose a narrowing input stream.
 * std::wcin must be patched by console_streambuf if used for Windows input.
 */
class BI_API unicode_istream
    : public std::istream
{
public:
    /**
     * Construct instance of a conditionally-narrowing input stream.
     * @param[in]  narrow_stream  A narrow input stream such as std::cin.
     * @param[in]  wide_stream    A wide input stream such as std::wcin.
     * @param[in]  size           The wide buffer size.
     */
    unicode_istream(std::istream& narrow_stream, std::wistream& wide_stream,
        size_t size);

    /**
     * Delete the unicode_streambuf that wraps wide_stream.
     */

#ifdef _MSC_VER
    ~unicode_istream() override;
#else
    ~unicode_istream() override = default;
#endif

};

} // namespace libbitcoin

#endif
