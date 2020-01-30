// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
#include <bitcoin/infrastructure/config/base2.hpp>

#include <iostream>
#include <sstream>
#include <string>

#include <boost/program_options.hpp>

#include <bitcoin/infrastructure/define.hpp>
#include <bitcoin/infrastructure/utility/binary.hpp>

namespace kth {
namespace config {

base2::base2(std::string const& binary) {
    std::stringstream(binary) >> *this;
}

base2::base2(binary const& value)
    : value_(value)
{}

size_t base2::size() const {
    return value_.size();
}

base2::operator binary const&() const {
    return value_;
}

std::istream& operator>>(std::istream& input, base2& argument) {
    std::string binary;
    input >> binary;

    if ( ! binary::is_base2(binary)) {
        using namespace boost::program_options;
        BOOST_THROW_EXCEPTION(invalid_option_value(binary));
    }

    std::stringstream(binary) >> argument.value_;

    return input;
}

std::ostream& operator<<(std::ostream& output, const base2& argument) {
    output << argument.value_;
    return output;
}

} // namespace config
} // namespace kth
