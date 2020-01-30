// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
#ifndef KTH_INFRASTRUCTURE_WRITER_HPP
#define KTH_INFRASTRUCTURE_WRITER_HPP

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
