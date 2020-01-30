// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
#ifndef KTH_INFRASTRUCTURE_OSTREAM_WRITER_HPP
#define KTH_INFRASTRUCTURE_OSTREAM_WRITER_HPP

// #include <ostream>

#include <bitcoin/infrastructure/error.hpp>
#include <bitcoin/infrastructure/utility/container_sink.hpp>
#include <bitcoin/infrastructure/utility/writer.hpp>

namespace kth {

class BI_API ostream_writer
    // : public writer
{
public:
    explicit
    ostream_writer(std::ostream& stream);

    // explicit
    // ostream_writer(data_sink& stream);

    template <unsigned Size>
    void write_forward(const byte_array<Size>& value);

    template <unsigned Size>
    void write_reverse(const byte_array<Size>& value);

    template <typename Integer>
    void write_big_endian(Integer value);

    template <typename Integer>
    void write_little_endian(Integer value);

    /// Context.
    // implicit
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
    void write_error_code(code const& ec);
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
    void write_string(std::string const& value, size_t size);

    /// Write required length string, padded with nulls.
    void write_string(std::string const& value);

    /// Advance iterator without writing.
    void skip(size_t size);

private:
    std::ostream& stream_;
    // data_sink& stream_;
};

} // namespace kth

#include <bitcoin/infrastructure/impl/utility/ostream_writer.ipp>

#endif
