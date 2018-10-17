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
    operator bool() const;
    bool operator!() const;

    /// Write hashes.
    void write_hash(hash_digest const& value);
    void write_short_hash(short_hash const& value);
    void write_mini_hash(const mini_hash& value);

    /// Write big endian integers.
    void write_2_bytes_big_endian(uint16_t value);
    void write_4_bytes_big_endian(uint32_t value);
    void write_8_bytes_big_endian(uint64_t value);
    void write_variable_big_endian(uint64_t value);
    void write_size_big_endian(size_t value);

    /// Write little endian integers.
    void write_2_bytes_little_endian(uint16_t value);
    void write_4_bytes_little_endian(uint32_t value);
    void write_8_bytes_little_endian(uint64_t value);
    void write_variable_little_endian(uint64_t value);
    void write_size_little_endian(size_t value);

    /// Write one byte.
    void write_byte(uint8_t value);

    /// Write all bytes.
    void write_bytes(data_chunk const& data);

    /// Write required size buffer.
    void write_bytes(const uint8_t* data, size_t size);

    /// Write variable length string.
    void write_string(std::string const& value);

    /// Write required length string, padded with nulls.
    void write_string(std::string const& value, size_t size);

    /// Advance iterator without writing.
    void skip(size_t size);
};

} // namespace libbitcoin

#endif
