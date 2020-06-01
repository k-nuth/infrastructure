// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_INFRASTUCTURE_CONFIG_ENDPOINT_HPP
#define KTH_INFRASTUCTURE_CONFIG_ENDPOINT_HPP

#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

#include <boost/asio.hpp>

#include <kth/infrastructure/config/authority.hpp>
#include <kth/infrastructure/define.hpp>
#include <kth/infrastructure/formats/base_16.hpp>

namespace kth::infrastructure::config {

/**
 * Serialization helper for a network endpoint in URI format.
 * This is a container for a {scheme, host, port} tuple.
 */
class KI_API endpoint {
public:
    /**
     * A list of endpoints.
     * This must provide operator<< for ostream in order to be used as a
     * boost::program_options default_value.
     */
    using list = std::vector<endpoint>;


    endpoint();

    /**
     * Copy constructor.
     * @param[in]  x  The object to copy into self on construct.
     */
    endpoint(endpoint const& x);

    /**
     * Initialization constructor.
     * The scheme and port may be undefined, in which case the port is reported
     * as zero and the scheme is reported as an empty string.
     * @param[in]  value  The initial value of the [scheme://]host[:port] form.
     */
    // explicit
    // implicit
    endpoint(std::string const& value);

    /**
     * Initialization constructor.
     * @param[in]  authority  The value to initialize with.
     */
    explicit
    endpoint(authority const& authority);

    /**
     * Initialization constructor.
     * @param[in]  host  The host name or ip address to initialize with.
     * @param[in]  port  The port to initialize with.
     */
    endpoint(std::string const& host, uint16_t port);

    /**
     * Initialization constructor.
     * @param[in]  endpoint  The endpoint addresss to initialize with.
     */
    explicit
    endpoint(asio::endpoint const& host);

    /**
     * Initialization constructor.
     * @param[in]  ip    The boost ip addresss to initialize with.
     * @param[in]  port  The port to initialize with.
     */
    endpoint(asio::address const& ip, uint16_t port);

    /**
     * Getter.
     * @return True if the endpoint is initialized.
     */
    // implicit
    operator bool const() const;    //NOLINT

    /**
     * Getter.
     * @return The scheme of the endpoint or empty string.
     */
    std::string const& scheme() const;

    /**
     * Getter.
     * @return The host name or ip address of the endpoint.
     */
    std::string const& host() const;

    /**
     * Getter.
     * @return The tcp port of the endpoint.
     */
    uint16_t port() const;

    /**
     * Get the endpoint as a string.
     * An empty scheme and/or empty port is omitted.
     * @return The endpoint in the [scheme://]host[:port] form.
     */
    std::string to_string() const;

    /**
     * Override the equality operator.
     * @param[in]  x  The x object with which to compare.
     */
    bool operator==(endpoint const& x) const;

    /**
     * Define stream in. Throws if input is invalid.
     * @param[in]   input     The input stream to read the value from.
     * @param[out]  argument  The object to receive the read value.
     * @return                The input stream reference.
     */
    friend 
    std::istream& operator>>(std::istream& input, endpoint& argument);

    /**
     * Define stream out.
     * @param[in]   output    The output stream to write the value to.
     * @param[out]  argument  The object from which to obtain the value.
     * @return                The output stream reference.
     */
    friend 
    std::ostream& operator<<(std::ostream& output, endpoint const& argument);

private:
    std::string scheme_;
    std::string host_;
    uint16_t port_;
};

} // namespace kth::infrastructure::config

#endif
