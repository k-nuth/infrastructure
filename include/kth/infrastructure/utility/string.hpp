// Copyright (c) 2016-2022 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_INFRASTRUCTURE_STRING_HPP
#define KTH_INFRASTRUCTURE_STRING_HPP

#include <string>
#include <string_view>
#include <utility>
#include <vector>

#include <kth/infrastructure/define.hpp>
// #include <kth/infrastructure/define.hpp>
// #include <kth/infrastructure/utility/data.hpp>
// #include <boost/algorithm/string/trim.hpp>
// #include <boost/lexical_cast.hpp>

namespace kth {

//TODO(fernando): check where this is used. Code smell.
using string_list = std::vector<std::string>;

constexpr
std::pair<std::string_view, std::string_view> split2(std::string_view x, char c) {
    auto const p = x.find(c);
    if (p == x.npos) {
        return {"", ""};
    }

    return {
        std::string_view(x.begin(), x.begin() + p),
        std::string_view(x.begin() + (p + 1), x.end())
    };
}

template <typename Value>
Value deserialize(std::string const& text, bool trim);

template <typename Value>
void deserialize(Value& value, std::string const& text, bool trim);

template <typename Value>
void deserialize(std::vector<Value>& collection, std::string const& text, bool trim);

template <typename Value>
std::string serialize(const Value& value, std::string const& fallback="");

KI_API std::string join(const string_list& words, std::string const& delimiter=" ");

KI_API string_list split(std::string const& sentence, std::string const& delimiter=" ", bool trim=true);

} // namespace kth

#include <kth/infrastructure/impl/utility/string.ipp>

#endif
