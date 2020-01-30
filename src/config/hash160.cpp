// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
#include <bitcoin/infrastructure/config/hash160.hpp>

#include <iostream>
#include <sstream>
#include <string>

#include <boost/program_options.hpp>

#include <bitcoin/infrastructure/define.hpp>
#include <bitcoin/infrastructure/formats/base_16.hpp>
#include <bitcoin/infrastructure/math/hash.hpp>

namespace libbitcoin {
namespace config {

hash160::hash160(std::string const& hexcode) {
    std::stringstream(hexcode) >> *this;
}

hash160::hash160(short_hash const& value)
    : value_(value)
{}

hash160::operator short_hash const&() const {
    return value_;
}

std::istream& operator>>(std::istream& input, hash160& argument) {
    std::string hexcode;
    input >> hexcode;

    if ( ! decode_base16(argument.value_, hexcode)) {
        using namespace boost::program_options;
        BOOST_THROW_EXCEPTION(invalid_option_value(hexcode));
    }

    return input;
}

std::ostream& operator<<(std::ostream& output, hash160 const& argument) {
    output << encode_base16(argument.value_);
    return output;
}

} // namespace config
} // namespace libbitcoin
