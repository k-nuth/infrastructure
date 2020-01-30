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
#ifndef LIBBITCOIN_STRING_IPP
#define LIBBITCOIN_STRING_IPP

#include <boost/algorithm/string/trim.hpp>
#include <boost/lexical_cast.hpp>

namespace kth {

template <typename Value>
Value deserialize(std::string const& text, bool trim) {
    if (trim) {
        return boost::lexical_cast<Value>(boost::trim_copy(text));
    } 
    return boost::lexical_cast<Value>(text);
}

template <typename Value>
void deserialize(Value& value, std::string const& text, bool trim) {
    if (trim) {
        value = boost::lexical_cast<Value>(boost::trim_copy(text));
    } else {
        value = boost::lexical_cast<Value>(text);
    }
}

template <typename Value>
void deserialize(std::vector<Value>& collection, std::string const& text, bool trim) {
    // This had problems with the inclusion of the ideographic (CJK) space
    // (0xe3,0x80, 0x80). Need to infuse the local in bc::split().
    auto const tokens = split(text, " \n\r\t");
    for (auto const& token: tokens) {
        Value value;
        deserialize(value, token, true);
        collection.push_back(value);
    }
}

template <typename Value>
std::string serialize(const Value& value, std::string const& fallback) {
    std::stringstream stream;
    stream << value;
    auto const& text = stream.str();
    return text.empty() ? fallback : text;
}

} // namespace kth

#endif
