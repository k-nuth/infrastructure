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
#ifndef LIBBITCOIN_INFRASTUCTURE_CONFIG_BASE58_HPP
#define LIBBITCOIN_INFRASTUCTURE_CONFIG_BASE58_HPP

#include <iostream>
#include <string>

#include <bitcoin/infrastructure/define.hpp>
#include <bitcoin/infrastructure/utility/data.hpp>

namespace kth {
namespace config {

/**
 * Serialization helper for base58 encoded text.
 */
class BI_API base58 {
public:

    base58() = default;
    base58(base58 const& x) = default;
    base58(base58&& x) = default;
    base58& operator=(base58 const&) = default;
    base58& operator=(base58&&) = default;


    explicit
    base58(std::string const& base58);

    explicit
    base58(data_chunk const& value);

    explicit
    base58(data_chunk&& value);

    /**
     * Overload cast to internal type.
     * @return  This object's value cast to internal type reference.
     */
    explicit
    operator data_chunk const&() const;

    /**
     * Overload cast to generic data reference.
     * @return  This object's value cast to a generic data.
     */
    explicit
    operator data_slice() const;

    /**
     * Overload stream in. Throws if input is invalid.
     * @param[in]   input     The input stream to read the value from.
     * @param[out]  argument  The object to receive the read value.
     * @return                The input stream reference.
     */
    friend 
    std::istream& operator>>(std::istream& input, base58& argument);

    /**
     * Overload stream out.
     * @param[in]   output    The output stream to write the value to.
     * @param[out]  argument  The object from which to obtain the value.
     * @return                The output stream reference.
     */
    friend 
    std::ostream& operator<<(std::ostream& output, const base58& argument);

private:
    data_chunk value_;
};

} // namespace config
} // namespace kth

#endif
