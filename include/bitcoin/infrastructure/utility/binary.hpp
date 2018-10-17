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
#ifndef BITPRIM_INFRASTRUCTURE_BINARY_HPP
#define BITPRIM_INFRASTRUCTURE_BINARY_HPP

#include <cstdint>
#include <string>

#include <bitcoin/infrastructure/constants.hpp>
#include <bitcoin/infrastructure/utility/data.hpp>

namespace libbitcoin {

class BI_API binary {
public:
    using block = uint8_t;
    using size_type = std::size_t;

    static 
    BC_CONSTEXPR size_type bits_per_block = byte_bits;
    
    static 
    size_type blocks_size(size_type bit_size);
    
    static 
    bool is_base2(std::string const& text);

    binary() = default;
    binary(binary const& x) = default;

    explicit 
    binary(std::string const& bit_string);

    binary(size_type size, uint32_t number);
    binary(size_type size, data_slice blocks);

    void resize(size_type size);
    bool operator[](size_type index) const;
    data_chunk const& blocks() const;
    std::string encoded() const;

    /// size in bits
    size_type size() const;
    void append(binary const& post);
    void prepend(binary const& prior);
    void shift_left(size_type distance);
    void shift_right(size_type distance);
    binary substring(size_type start, size_type length=max_size_t) const;

    bool is_prefix_of(data_slice field) const;
    bool is_prefix_of(uint32_t field) const;
    bool is_prefix_of(binary const& field) const;

    bool operator<(binary const& x) const;
    bool operator==(binary const& x) const;
    bool operator!=(binary const& x) const;
    binary& operator=(binary const& x);
    
    friend 
    std::istream& operator>>(std::istream& in, binary& to);
    
    friend 
    std::ostream& operator<<(std::ostream& out, binary const& of);

private:
    static 
    uint8_t shift_block_right(uint8_t next, uint8_t current, uint8_t prior, size_type original_offset, size_type intended_offset);

    data_chunk blocks_;
    uint8_t final_block_excess_{0};
};

} // namespace libbitcoin

namespace std {

template <>
struct hash<bc::binary> {
    size_t operator()(const bc::binary& value) const {
        return std::hash<std::string>()(value.encoded());
    }
};

} // namespace std

#endif
