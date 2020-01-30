// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
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


base16::base16(std::string const& hexcode) {
    std::stringstream(hexcode) >> *this;
}

base16::base16(data_chunk const& value)
    : value_(value)
{}

base16::base16(data_chunk&& value)
    : value_(std::move(value))
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

std::ostream& operator<<(std::ostream& output, base16 const& argument) {
    output << encode_base16(argument.value_);
    return output;
}

} // namespace config
} // namespace libbitcoin
