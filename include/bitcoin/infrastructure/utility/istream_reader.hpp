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
#ifndef BITPRIM_INFRASTRUCTURE_ISTREAM_READER_HPP
#define BITPRIM_INFRASTRUCTURE_ISTREAM_READER_HPP

#include <cstddef>
#include <cstdint>
#include <istream>
#include <bitcoin/infrastructure/utility/reader.hpp>

namespace libbitcoin {

class BI_API istream_reader
  : public reader
{
public:
    explicit istream_reader(std::istream& stream);

    template <unsigned Size>
    byte_array<Size> read_forward();

    template <unsigned Size>
    byte_array<Size> read_reverse();

    template <typename Integer>
    Integer read_big_endian();

    template <typename Integer>
    Integer read_little_endian();

    /// Context.
    explicit operator bool() const override;
    bool operator!() const override;
    bool is_exhausted() const override;
    void invalidate() override;

    /// Read hashes.
    hash_digest read_hash() override;
    short_hash read_short_hash() override;
    mini_hash read_mini_hash() override;

    /// Read big endian integers.
    uint16_t read_2_bytes_big_endian() override;
    uint32_t read_4_bytes_big_endian() override;
    uint64_t read_8_bytes_big_endian() override;
    uint64_t read_variable_big_endian() override;
    size_t read_size_big_endian() override;

    /// Read little endian integers.
    code read_error_code() override;
    uint16_t read_2_bytes_little_endian() override;
    uint32_t read_4_bytes_little_endian() override;
    uint64_t read_8_bytes_little_endian() override;
    uint64_t read_variable_little_endian() override;
    size_t read_size_little_endian() override;

    /// Read/peek one byte.
    uint8_t peek_byte() override;
    uint8_t read_byte() override;

    /// Read all remaining bytes.
    data_chunk read_bytes() override;

    /// Read required size buffer.
    data_chunk read_bytes(size_t size) override;

    /// Read variable length string.
    std::string read_string() override;

    /// Read required size string and trim nulls.
    std::string read_string(size_t size) override;

    /// Advance iterator without reading.
    void skip(size_t size) override;

private:
    // The buffer is faulted or at eof.
    bool empty() const;

    std::istream& stream_;
};

} // namespace libbitcoin

#include <bitcoin/infrastructure/impl/utility/istream_reader.ipp>

#endif
