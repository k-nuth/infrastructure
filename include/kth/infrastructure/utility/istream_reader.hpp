// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
#ifndef KTH_INFRASTRUCTURE_ISTREAM_READER_HPP
#define KTH_INFRASTRUCTURE_ISTREAM_READER_HPP

#include <cstddef>
#include <cstdint>
#include <istream>

#include <kth/infrastructure/utility/reader.hpp>

namespace kth {

class BI_API istream_reader
    // : public reader
{
public:
    explicit
    istream_reader(std::istream& stream);

    template <unsigned Size>
    byte_array<Size> read_forward();

    template <unsigned Size>
    byte_array<Size> read_reverse();

    template <typename Integer>
    Integer read_big_endian();

    template <typename Integer>
    Integer read_little_endian();

    /// Context.
    // implicit
    operator bool() const;
    
    bool operator!() const;
    bool is_exhausted() const;
    void invalidate();

    /// Read hashes.
    hash_digest read_hash();
    short_hash read_short_hash();
    mini_hash read_mini_hash();

    /// Read big endian integers.
    uint16_t read_2_bytes_big_endian();
    uint32_t read_4_bytes_big_endian();
    uint64_t read_8_bytes_big_endian();
    uint64_t read_variable_big_endian();
    size_t read_size_big_endian();

    /// Read little endian integers.
    code read_error_code();
    uint16_t read_2_bytes_little_endian();
    uint32_t read_4_bytes_little_endian();
    uint64_t read_8_bytes_little_endian();
    uint64_t read_variable_little_endian();
    size_t read_size_little_endian();

    /// Read/peek one byte.
    uint8_t peek_byte();
    uint8_t read_byte();

    /// Read all remaining bytes.
    data_chunk read_bytes();

    /// Read required size buffer.
    data_chunk read_bytes(size_t size);

    /// Read variable length string.
    std::string read_string();

    /// Read required size string and trim nulls.
    std::string read_string(size_t size);

    /// Advance iterator without reading.
    void skip(size_t size);

private:
    // The buffer is faulted or at eof.
    bool empty() const;

    std::istream& stream_;
};

} // namespace kth

#include <kth/infrastructure/impl/utility/istream_reader.ipp>

#endif
