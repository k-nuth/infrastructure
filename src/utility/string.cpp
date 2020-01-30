/**
 * Copyright (c) 2016-2020 Knuth Project.
 *
 * This file is part of Knuth Project.
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
#include <bitcoin/infrastructure/utility/string.hpp>

#include <string>
#include <vector>

#include <boost/algorithm/string.hpp>

namespace kth {

std::string join(const string_list& words, std::string const& delimiter) {
    return boost::join(words, delimiter);
}

// Note that use of token_compress_on may cause unexpected results when
// working with CSV-style lists that accept empty elements.
string_list split(std::string const& sentence, std::string const& delimiter, bool trim) {
    string_list words;
    auto const compress = boost::token_compress_on;
    auto const delimit = boost::is_any_of(delimiter);

    if (trim) {
        auto const trimmed = boost::trim_copy(sentence);
        boost::split(words, trimmed, delimit, compress);
    } else {
        boost::split(words, sentence, delimit, compress);
}

    return words;
}

} // namespace libbitcoin
