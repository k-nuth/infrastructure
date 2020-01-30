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
#ifndef LIBBITCOIN_INFRASTUCTURE_CONFIG_BASE64_HPP
#define LIBBITCOIN_INFRASTUCTURE_CONFIG_BASE64_HPP

#include <iostream>
#include <string>

#include <bitcoin/infrastructure/define.hpp>
#include <bitcoin/infrastructure/utility/data.hpp>

namespace kth {
namespace config {

/**
 * Serialization helper for base64 encoded data.
 */
class BI_API base64 {
public:

    base64() = default;
    base64(base64 const& x) = default;
    base64(base64&& x) = default;
    base64& operator=(base64 const&) = default;
    base64& operator=(base64&&) = default;

    explicit
    base64(std::string const& base64);

    explicit
    base64(data_chunk const& value);

    explicit
    base64(data_chunk&& value);


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
    std::istream& operator>>(std::istream& input, base64& argument);

    /**
     * Overload stream out.
     * @param[in]   output    The output stream to write the value to.
     * @param[out]  argument  The object from which to obtain the value.
     * @return                The output stream reference.
     */
    friend 
    std::ostream& operator<<(std::ostream& output, base64 const& argument);

private:

    /**
     * The state of this object.
     */
    data_chunk value_;
};

} // namespace config
} // namespace kth

#endif
