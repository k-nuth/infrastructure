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
#ifndef BITPRIM_INFRASTRUCTURE_WRITER_HPP
#define BITPRIM_INFRASTRUCTURE_WRITER_HPP

#include <cstddef>
#include <cstdint>
#include <string>
#include <bitcoin/infrastructure/define.hpp>
// #include <bitcoin/infrastructure/math/hash.hpp>
#include <bitcoin/infrastructure/hash_define.hpp>
#include <bitcoin/infrastructure/utility/data.hpp>

namespace libbitcoin {

/// Writer interface.
class BI_API writer
{
public:
    /// Context.
    virtual operator bool() const = 0;
    virtual bool operator!() const = 0;

    /// Write hashes.
    virtual void write_hash(const hash_digest& value) = 0;
    virtual void write_short_hash(const short_hash& value) = 0;
    virtual void write_mini_hash(const mini_hash& value) = 0;

    /// Write big endian integers.
    virtual void write_2_bytes_big_endian(uint16_t value) = 0;
    virtual void write_4_bytes_big_endian(uint32_t value) = 0;
    virtual void write_8_bytes_big_endian(uint64_t value) = 0;
    virtual void write_variable_big_endian(uint64_t value) = 0;
    virtual void write_size_big_endian(size_t value) = 0;

    /// Write little endian integers.
    virtual void write_2_bytes_little_endian(uint16_t value) = 0;
    virtual void write_4_bytes_little_endian(uint32_t value) = 0;
    virtual void write_8_bytes_little_endian(uint64_t value) = 0;
    virtual void write_variable_little_endian(uint64_t value) = 0;
    virtual void write_size_little_endian(size_t value) = 0;

    /// Write one byte.
    virtual void write_byte(uint8_t value) = 0;

    /// Write all bytes.
    virtual void write_bytes(data_chunk const& data) = 0;

    /// Write required size buffer.
    virtual void write_bytes(const uint8_t* data, size_t size) = 0;

    /// Write variable length string.
    virtual void write_string(std::string const& value) = 0;

    /// Write required length string, padded with nulls.
    virtual void write_string(std::string const& value, size_t size) = 0;

    /// Advance iterator without writing.
    virtual void skip(size_t size) = 0;
};

} // namespace libbitcoin

#endif
