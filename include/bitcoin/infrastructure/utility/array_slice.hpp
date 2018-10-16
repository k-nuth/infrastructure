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
#ifndef BITPRIM_INFRASTRUCTURE_ARRAY_SLICE_HPP
#define BITPRIM_INFRASTRUCTURE_ARRAY_SLICE_HPP

#include <cstddef>

namespace libbitcoin {

/**
 * An read-only STL-style wrapper for array-style collections.
 *
 * This class allows std::array, std::vector, std::string, and c-style arrays
 * to be used interchangeably in functions that expect an iterable container.
 * This is not a substitute for move overloads. Consider also that a contiguous
 * buffer (c-style array) is more performant than the iterator abstraction.
 */
template <typename Iterable>
class array_slice {
public:
    //implicit
    template <typename Container>
    array_slice(Container const& container);        //NOLINT

    array_slice(Iterable const* begin, Iterable const* end);

    Iterable const* begin() const;
    Iterable const* end() const;
    Iterable const* data() const;
    std::size_t size() const;
    bool empty() const;

private:
    Iterable const* begin_;
    Iterable const* end_;
};

} // namespace libbitcoin

#include <bitcoin/infrastructure/impl/utility/array_slice.ipp>

#endif

