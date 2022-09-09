// Copyright (c) 2016-2022 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <kth/infrastructure/config/parameter.hpp>

#include <iostream>

#include <boost/algorithm/string.hpp>
#include <boost/program_options.hpp>

#include <kth/infrastructure/define.hpp>
#include <kth/infrastructure/utility/collection.hpp>
#include <kth/infrastructure/utility/string.hpp>

// #include <iostream>
// #include <iomanip>
#include <ranges>
#include <string_view>

namespace po = boost::program_options;
using namespace kth::infrastructure::config;

int constexpr parameter::not_positional = -1;
char constexpr parameter::no_short_name = 0x00;
char constexpr parameter::option_prefix_char = '-';

// 100% component coverage, common scenarios.
// A required argument may only be preceeded by required arguments.
// Requiredness may be in error if the metadata is inconsistent.
void parameter::initialize(po::option_description const& option, argument_list const& arguments) {
    set_position(position(option, arguments));
    set_args_limit(arguments_limit(get_position(), option, arguments));
    set_required(option.semantic()->is_required());
    set_long_name(option.long_name());
    set_short_name(short_name(option));
    set_description(option.description());
    set_format_name(option.format_name());
    set_format_parameter(option.format_parameter());
}

// 100% component coverage, all three scenarios (long, short, both)
int parameter::position(po::option_description const& option, argument_list const& arguments) const {
    return find_pair_position(arguments, option.long_name());
}

// 100% unit coverage, all three scenarios (long, short, both)
char parameter::short_name(po::option_description const& option) const {
    // This call requires boost 1.50, don't use it.
    //auto name = option.canonical_display_name(
    //    search_options::dashed_short_prefer_short);
    // This is a substitute that allows us to use boost 1.49.

    // auto const name = split(option.format_name()).front();
    //TODO(fernando): check if that is necessary right now (we are using Boost 1.72.0 or newer)

    // std::views::split(option.format_name(), " ")

    // auto const splitted = option.format_name() | views::split(' ') | views::transform([](auto&& inner_rng) {
    //     return inner_rng | views::filter(std::not_fn(isspace));
    // });

    // auto x = splited.front();

    auto const name = option.canonical_display_name(search_options::dashed_short_prefer_short);
    auto const is_short_name = name[0] == option_prefix_char && name[1] != option_prefix_char;
    return is_short_name ? name[1] : no_short_name;
}

// 100% component coverage
unsigned parameter::arguments_limit(int position, po::option_description const& option, argument_list const& arguments) const {
    if (position == parameter::not_positional) {
        return option.semantic()->max_tokens();
    }

    return arguments[position].second;
}
