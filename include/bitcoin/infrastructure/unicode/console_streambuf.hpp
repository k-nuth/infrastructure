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
#ifndef KNUTH_INFRASTRUCTURE_CONSOLE_STREAMBUF_HPP
#define KNUTH_INFRASTRUCTURE_CONSOLE_STREAMBUF_HPP

#include <cstddef>
#include <streambuf>

#include <bitcoin/infrastructure/define.hpp>

namespace libbitcoin {

/**
 * Class to patch Windows stdin keyboard input, file input is not a problem.
 * This class and members are no-ops when called in non-MSVC++ builds.
 */
class BI_API console_streambuf : public std::wstreambuf
{
public:
    /**
     * Initialize stdio to use utf8 translation on Windows.
     * @param[in]  size  The stream buffer size.
     */
    static 
    void initialize(size_t size);

protected:
    /**
     * Protected construction, use static initialize method.
     * @param[in]  stream_buffer  The stream buffer to patch.
     * @param[in]  size           The stream buffer size.
     */
    console_streambuf(std::wstreambuf const& stream_buffer, size_t size);

    /**
     * Delete stream buffer.
     */
#ifdef _MSC_VER
    ~console_streambuf() override;
#else
    ~console_streambuf() override = default;
#endif


    /**
     * Implement alternate console read.
     * @param[in]  buffer  Pointer to the buffer to fill with console reads.
     * @param[in]  size    The size of the buffer that may be populated.
     */
    std::streamsize xsgetn(wchar_t* buffer, std::streamsize size) override;

    /**
     * Implement alternate console read.
     */
    std::wstreambuf::int_type underflow() override;

private:
    // The constructed buffer size.
    size_t buffer_size_;

    // The dynamically-allocated buffers.
    wchar_t* buffer_;
};

} // namespace libbitcoin

#endif
