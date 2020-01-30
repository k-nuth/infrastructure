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
#include <bitcoin/infrastructure/config/checkpoint.hpp>

#include <cstddef>
#include <iostream>
#include <regex>
#include <string>

#include <boost/lexical_cast.hpp>
#include <boost/program_options.hpp>

#include <bitcoin/infrastructure/define.hpp>
#include <bitcoin/infrastructure/formats/base_16.hpp>
#include <bitcoin/infrastructure/math/hash.hpp>

namespace kth {
namespace config {

// using namespace boost;
using namespace boost::program_options;

checkpoint::checkpoint()
    : hash_(bc::null_hash) 
{}

checkpoint::checkpoint(std::string const& value)
    : checkpoint()
{
    std::stringstream(value) >> *this;
}

checkpoint::checkpoint(checkpoint const& x)
    : hash_(x.hash()), height_(x.height())
{}

// This is intended for static initialization (i.e. of the internal defaults).
checkpoint::checkpoint(std::string const& hash, size_t height)
    : height_(height)
{
    if ( ! decode_hash(hash_, hash)) {
        BOOST_THROW_EXCEPTION(invalid_option_value(hash));
    }
}

checkpoint::checkpoint(hash_digest const& hash, size_t height)
    : hash_(hash), height_(height)
{}

hash_digest const& checkpoint::hash() const {
    return hash_;
}

size_t const checkpoint::height() const {
    return height_;
}

std::string checkpoint::to_string() const {
    std::stringstream value;
    value << *this;
    return value.str();
}

config::checkpoint::list checkpoint::sort(list const& checks) {
    auto const comparitor = [](checkpoint const& left, checkpoint const& right) {
        return left.height() < right.height();
    };

    auto copy = checks;
    std::sort(copy.begin(), copy.end(), comparitor);
    return copy;
}

bool checkpoint::covered(size_t height, list const& checks) {
    return !checks.empty() && height <= checks.back().height();
}

bool checkpoint::validate(hash_digest const& hash, size_t height, list const& checks) {
    auto const match_invalid = [&height, &hash](const config::checkpoint& item) {
        return height == item.height() && hash != item.hash();
    };

    auto const it = std::find_if(checks.begin(), checks.end(), match_invalid);
    return it == checks.end();
}

bool checkpoint::operator==(checkpoint const& x) const {
    return height_ == x.height_ && hash_ == x.hash_;
}

std::istream& operator>>(std::istream& input, checkpoint& argument) {
    std::string value;
    input >> value;

    // std::regex requires gcc 4.9, so we are using boost::regex for now.
    // Knuth: we use std::regex, becase we drop support por GCC<5
    static
    std::regex const regular("^([0-9a-f]{64})(:([0-9]{1,20}))?$");

    std::sregex_iterator it(value.begin(), value.end(), regular), end;
    if (it == end) {
        BOOST_THROW_EXCEPTION(invalid_option_value(value));
    }

    auto const& match = *it;
    if ( ! decode_hash(argument.hash_, match[1])) {
        BOOST_THROW_EXCEPTION(invalid_option_value(value));
    }

    try {
        argument.height_ = boost::lexical_cast<size_t>(match[3]);
    } catch (...) {
        BOOST_THROW_EXCEPTION(invalid_option_value(value));
    }

    return input;
}

std::ostream& operator<<(std::ostream& output, checkpoint const& argument) {
    output << encode_hash(argument.hash()) << ":" << argument.height();
    return output;
}

} // namespace config
} // namespace kth
