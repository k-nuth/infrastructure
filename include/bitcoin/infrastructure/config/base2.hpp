/**
 * Copyright (c) 2011-2017 libbitcoin developers (see AUTHORS)
 *
 * This file is part of libbitcoin.
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
#ifndef LIBBITCOIN_INFRASTUCTURE_CONFIG_BASE2_HPP
#define LIBBITCOIN_INFRASTUCTURE_CONFIG_BASE2_HPP

#include <cstddef>
#include <iostream>
#include <string>

#include <bitcoin/infrastructure/define.hpp>
#include <bitcoin/infrastructure/utility/binary.hpp>

namespace kth {
namespace config {

/**
 * Serialization helper for base2 encoded data.
 */
class BI_API base2
{
public:

    base2() = default;
    base2(base2 const& x) = default;
    base2(base2&& x) = default;
    base2& operator=(base2 const&) = default;
    base2& operator=(base2&&) = default;

    /**
     * Initialization constructor.
     * @param[in]  bin  The value to initialize with.
     */
    explicit
    base2(std::string const& binary);

    /**
     * @param[in]  value  The value to initialize with.
     */
    explicit
    base2(binary const& value);


    /**
     * Get number of bits in value.
     */
    size_t size() const;

    /**
     * Overload cast to internal type.
     * @return  This object's value cast to internal type reference.
     */
    explicit
    operator binary const&() const;

    /**
     * Overload stream in. If input is invalid sets no bytes in argument.
     * @param[in]   input     The input stream to read the value from.
     * @param[out]  argument  The object to receive the read value.
     * @return                The input stream reference.
     */
    friend 
    std::istream& operator>>(std::istream& input, base2& argument);

    /**
     * Overload stream out.
     * @param[in]   output    The output stream to write the value to.
     * @param[out]  argument  The object from which to obtain the value.
     * @return                The output stream reference.
     */
    friend 
    std::ostream& operator<<(std::ostream& output, const base2& argument);

private:
    binary value_;
};

} // namespace config
} // namespace kth

#endif
