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
#include <bitcoin/infrastructure/config/base16.hpp>

#include <iostream>
#include <sstream>
#include <string>

#include <boost/program_options.hpp>

#include <bitcoin/infrastructure/define.hpp>
#include <bitcoin/infrastructure/formats/base_16.hpp>
#include <bitcoin/infrastructure/utility/data.hpp>

namespace libbitcoin {
namespace config {

// base16::base16()
// {
// }

base16::base16(std::string const& hexcode) {
    std::stringstream(hexcode) >> *this;
}

base16::base16(data_chunk const& value)
    : value_(value)
{}

base16::base16(base16 const& x)
    : base16(x.value_)
{}

base16::operator data_chunk const&() const {
    return value_;
}

base16::operator data_slice() const {
    return value_;
}

std::istream& operator>>(std::istream& input, base16& argument) {
    std::string hexcode;
    input >> hexcode;

    if ( ! decode_base16(argument.value_, hexcode)) {
        using namespace boost::program_options;
        BOOST_THROW_EXCEPTION(invalid_option_value(hexcode));
    }

    return input;
}

std::ostream& operator<<(std::ostream& output, const base16& argument) {
    output << encode_base16(argument.value_);
    return output;
}

} // namespace config
} // namespace libbitcoin
