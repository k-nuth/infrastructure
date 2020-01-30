/**
 * Copyright (c) 2016-2020 Knuth Project.
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
#ifndef KNUTH_INFRASTRUCTURE_DATA_HPP
#define KNUTH_INFRASTRUCTURE_DATA_HPP

#include <array>
#include <cstddef>
#include <cstdint>
#include <initializer_list>
#include <iterator>
#include <queue>
#include <vector>

#include <bitcoin/infrastructure/define.hpp>
#include <bitcoin/infrastructure/utility/array_slice.hpp>

namespace kth {

// Define a byte array of a specified length.
template <size_t Size>
using byte_array = std::array<uint8_t, Size>;

template <size_t Size>
struct byte_array_parts
{
    byte_array<Size> left;
    byte_array<Size> right;
};

// Define arbitrary byte storage types.
using one_byte = byte_array<1>;
using data_slice = array_slice<uint8_t>;
using data_chunk = std::vector<uint8_t>;
using data_queue = std::queue<data_chunk>;
using data_stack = std::vector<data_chunk>;
using loaf = std::initializer_list<data_slice>;

/**
 * Create a single byte arrray with an initial value.
 */
inline one_byte to_array(uint8_t byte);

/**
* Create a single byte data chunk with an initial value.
*/
inline data_chunk to_chunk(uint8_t byte);

/**
 * Concatenate several data slices into a single data_chunk.
 * @param  extra_reserve  Include this many additional bytes when calling
 * `reserve` on the data_chunk (as an optimization).
 */
inline data_chunk build_chunk(loaf slices, size_t extra_reserve=0);

/**
 * Concatenate several data slices into a single fixed size array.
 * Returns false if the slices don't fit in the array. Underfill is ok.
 */
template <size_t Size>
bool build_array(byte_array<Size>& out, loaf slices);

/**
 * Extend iterable object by appending x.
 */
template <typename Target, typename Extension>
void extend_data(Target& bytes, const Extension& x);

/**
 * Extracty a subarray from start position with length end minus start.
 */
template <size_t Start, size_t End, size_t Size>
byte_array<End - Start> slice(const std::array<uint8_t, Size>& bytes);

/**
 * Break an evenly-sized array array into two equal length parts.
 */
template <size_t Size>
byte_array_parts<Size / 2> split(const byte_array<Size>& bytes);

/**
 * Concatenate two arrays into a new array.
 */
template <size_t Left, size_t Right>
byte_array<Left + Right> splice(const std::array<uint8_t, Left>& left,
    const std::array<uint8_t, Right>& right);

/**
 * Concatenate three arrays into a new array.
 */
template <size_t Left, size_t Middle, size_t Right>
byte_array<Left + Middle + Right> splice(const std::array<uint8_t, Left>& left,
    const std::array<uint8_t, Middle>& middle,
    const std::array<uint8_t, Right>& right);

/**
 * Convert the data slice to an array. Underfill is ok.
 */
template <size_t Size>
byte_array<Size> to_array(data_slice bytes);

/**
 * Create a data chunk from an iterable object.
 */
template <typename Source>
data_chunk to_chunk(const Source& bytes);

/**
 * Safely determine if a buffer starts with a byte sequence.
 */
template <typename Source>
bool starts_with(const typename Source::const_iterator& begin,
    const typename Source::const_iterator& end, const Source& value);

/**
 * Perform an exclusive or (xor) across two buffers to the length specified.
 * Return the resulting buffer. Caller must ensure length does not exceed
 * either buffer.
 */
template <size_t Size>
byte_array<Size> xor_data(data_slice bytes1, data_slice bytes2);

/**
 * Perform an exclusive or (xor) across two buffers to the length specified.
 * Return the resulting buffer. Caller must ensure offset and length do not
 * exceed either buffer.
 */
template <size_t Size>
byte_array<Size> xor_data(data_slice bytes1, data_slice bytes2, size_t offset);

/**
 * Perform an exclusive or (xor) across two buffers to the length specified.
 * Return the resulting buffer. Caller must ensure offsets and lengths do not
 * exceed the respective buffers.
 */
template <size_t Size>
byte_array<Size> xor_data(data_slice bytes1, data_slice bytes2, size_t offset1,
    size_t offset2);

} // namespace libbitcoin

#include <bitcoin/infrastructure/impl/utility/data.ipp>

#endif
