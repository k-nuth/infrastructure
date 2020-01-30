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
#include <bitcoin/infrastructure/config/endpoint.hpp>


#include <cstdint>
#include <iostream>
#include <regex>
#include <string>

#include <boost/lexical_cast.hpp>
#include <boost/program_options.hpp>

#include <bitcoin/infrastructure/config/endpoint.hpp>
#include <bitcoin/infrastructure/define.hpp>
#include <bitcoin/infrastructure/formats/base_16.hpp>
#include <bitcoin/infrastructure/utility/asio.hpp>

namespace kth {
namespace config {

using namespace boost::program_options;

endpoint::endpoint()
    : endpoint("localhost")
{}

endpoint::endpoint(endpoint const& x)
    : scheme_(x.scheme()), host_(x.host()), port_(x.port())
{}

endpoint::endpoint(std::string const& value) {
    std::stringstream(value) >> *this;
}

endpoint::endpoint(authority const& authority)
    : endpoint(authority.to_string())
{}

endpoint::endpoint(std::string const& host, uint16_t port)
    : host_(host), port_(port)
{}

endpoint::endpoint(asio::endpoint const& host)
    : endpoint(host.address(), host.port())
{}

endpoint::endpoint(asio::address const& ip, uint16_t port)
    : host_(ip.to_string()), port_(port)
{}

std::string const& endpoint::scheme() const {
    return scheme_;
}

std::string const& endpoint::host() const {
    return host_;
}

uint16_t endpoint::port() const {
    return port_;
}

std::string endpoint::to_string() const {
    std::stringstream value;
    value << *this;
    return value.str();
}

endpoint::operator bool const() const {
    // Return true if initialized.
    // TODO: this is a quick hack, along with http/https.
    return ! scheme_.empty();
}

bool endpoint::operator==(endpoint const& x) const {
    return host_ == x.host_ && port_ == x.port_ && scheme_ == x.scheme_;
}

std::istream& operator>>(std::istream& input, endpoint& argument) {
    std::string value;
    input >> value;

    // std::regex requires gcc 4.9, so we are using boost::regex for now.
    // Knuth: we use std::regex, becase we drop support por GCC<5
    static 
    std::regex const regular(R"(^((tcp|udp|http|https|inproc):\/\/)?(\[([0-9a-f:\.]+)\]|([^:]+))(:([0-9]{1,5}))?$)");

    std::sregex_iterator it(value.begin(), value.end(), regular), end;
    if (it == end) {
        BOOST_THROW_EXCEPTION(invalid_option_value(value));
    }

    auto const& match = *it;
    argument.scheme_ = match[2];
    argument.host_ = match[3];
    std::string port(match[7]);

    try {
        argument.port_ = port.empty() ? 0 : boost::lexical_cast<uint16_t>(port);
    } catch (...) {
        BOOST_THROW_EXCEPTION(invalid_option_value(value));
    }

    return input;
}

std::ostream& operator<<(std::ostream& output, endpoint const& argument) {
    if ( ! argument.scheme().empty()) {
        output << argument.scheme() << "://";
    }

    output << argument.host();

    if (argument.port() != 0) {
        output << ":" << argument.port();
    }

    return output;
}

} // namespace config
} // namespace libbitcoin
