/**
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
#ifndef KNUTH_INFRASTRUCTURE_SERIALIZER_HPP
#define KNUTH_INFRASTRUCTURE_SERIALIZER_HPP

#include <cstddef>
#include <cstdint>
#include <string>

#include <bitcoin/infrastructure/error.hpp>
// #include <bitcoin/infrastructure/math/hash.hpp>
#include <bitcoin/infrastructure/hash_define.hpp>
#include <bitcoin/infrastructure/utility/data.hpp>
////#include <bitcoin/infrastructure/utility/noncopyable.hpp>
#include <bitcoin/infrastructure/utility/writer.hpp>

namespace libbitcoin {

/// Writer to wrap arbitrary iterator.
template <typename Iterator>
class serializer
//   : public writer/*, noncopyable*/
{
public:
    using functor = std::function<void (serializer<Iterator> &)>;

    explicit
    serializer(Iterator begin);

    template <typename Buffer>
    void write_forward(const Buffer& data);

    template <typename Buffer>
    void write_reverse(const Buffer& data);

    template <typename Integer>
    void write_big_endian(Integer value);

    template <typename Integer>
    void write_little_endian(Integer value);

    /// Context.
    // implicit
    operator bool() const;
    
    bool operator!() const;

    /// Write hashes.
    void write_hash(hash_digest const& hash);
    void write_short_hash(short_hash const& hash);
    void write_mini_hash(const mini_hash& hash);

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
    void write_string(std::string const& value);

    /// Write required length string, padded with nulls.
    void write_string(std::string const& value, size_t size);

    /// Advance iterator without writing.
    void skip(size_t size);

    // non-interface
    //-------------------------------------------------------------------------

    /// Delegate write to a write function.
    void write_delegated(functor write);

    /// Utility for variable skipping of writer.
    size_t read_size_big_endian();

    /// Utility for variable skipping of writer.
    size_t read_size_little_endian();

private:
    bool valid_;
    Iterator iterator_;
};

// Factories.
//-----------------------------------------------------------------------------

template <typename Iterator>
serializer<Iterator> make_unsafe_serializer(Iterator begin);

} // namespace libbitcoin

#include <bitcoin/infrastructure/impl/utility/serializer.ipp>

#endif
