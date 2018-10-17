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
#include <bitcoin/infrastructure/config/hash256.hpp>

#include <iostream>
#include <sstream>
#include <string>

#include <boost/program_options.hpp>

#include <bitcoin/infrastructure/define.hpp>
#include <bitcoin/infrastructure/formats/base_16.hpp>
#include <bitcoin/infrastructure/math/hash.hpp>

namespace libbitcoin {
namespace config {

hash256::hash256(std::string const& hexcode)
    : hash256()
{
    std::stringstream(hexcode) >> *this;
}

hash256::hash256(hash_digest const& value)
    : value_(value)
{}

std::string hash256::to_string() const {
    std::stringstream value;
    value << *this;
    return value.str();
}

hash256::operator hash_digest const&() const {
    return value_;
}

std::istream& operator>>(std::istream& input, hash256& argument) {
    std::string hexcode;
    input >> hexcode;

    if ( ! decode_hash(argument.value_, hexcode)) {
        using namespace boost::program_options;
        BOOST_THROW_EXCEPTION(invalid_option_value(hexcode));
    }

    return input;
}

std::ostream& operator<<(std::ostream& output, const hash256& argument) {
    output << encode_hash(argument.value_);
    return output;
}

} // namespace config
} // namespace libbitcoin
