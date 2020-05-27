// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_INFRASTUCTURE_CONFIG_AUTHORITY_HPP
#define KTH_INFRASTUCTURE_CONFIG_AUTHORITY_HPP

#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

#include <kth/infrastructure/define.hpp>
#include <kth/infrastructure/message/network_address.hpp>
#include <kth/infrastructure/utility/asio.hpp>

namespace kth::infrastructure::config {

/**
 * Serialization helper for a network authority.
 * This is a container for a {ip address, port} tuple.
 */
class KI_API authority {
public:
    /**
     * A list of authorities.
     * This must provide operator<< for ostream in order to be used as a
     * boost::program_options default_value.
     */
    using list = std::vector<authority>;


    authority() = default;

    /**
     * Copy constructor.
     * @param[in]  x  The object to copy into self on construct.
     */
    authority(authority const& x);

    /**
     * Initialization constructor.
     * Deserialize a IPv4 or IPv6 address-based hostname[:port].
     * The port is optional and will be set to zero if not provided.
     * @param[in]  authority  The initial value in one of two forms:
     *                        [2001:db8::2]:port or 1.2.240.1:port
     */
    explicit
    authority(std::string const& authority);

    /**
     * Initialization constructor.
     * @param[in]  net  The network address (ip and port) to initialize with.
     */
    // implicit //Note(fernando): in kth-network it is used the implicit convertion
    authority(message::network_address const& address);

    /**
     * Initialization constructor.
     * @param[in]  ip    The ip addresss to initialize with.
     * @param[in]  port  The port to initialize with.
     */
    authority(message::ip_address const& ip, uint16_t port);

    /**
     * Initialization constructor.
     * @param[in]  host  The host to initialize with in one of three forms:
     *                   [2001:db8::2] or 2001:db8::2 or 1.2.240.1
     * @param[in]  port  The port to initialize with.
     */
    authority(std::string const& host, uint16_t port);

    /**
     * Initialization constructor.
     * @param[in]  ip    The boost ip addresss to initialize with.
     * @param[in]  port  The port to initialize with.
     */
    authority(asio::address const& ip, uint16_t port);

    /**
     * Initialization constructor.
     * @param[in]  endpoint  The boost endpoint address to initialize with.
     */
    explicit
    authority(asio::endpoint const& endpoint);

    /**
     * Getter.
     * @return True if the port is non-zero.
     */
    // implicit
    operator bool const() const;    //NOLINT

    /**
     * Getter.
     * @return The ip address of the authority.
     */
    asio::ipv6 asio_ip() const;

    /**
     * Getter.
     * @return The ip address of the authority.
     */
    message::ip_address ip() const;

    /**
     * Getter.
     * @return The tcp port of the authority.
     */
    uint16_t port() const;

    /**
     * Get the hostname of the authority as a string.
     * The form of the return is determined by the type of address.
     * @return The hostname in one of two forms: 2001:db8::2 or 1.2.240.1
     */
    std::string to_hostname() const;

    /**
     * Get the authority as a string.
     * The form of the return is determined by the type of address.
     * The port is optional and not included if zero-valued.
     * @return The authority in one of two forms:
     *         [2001:db8::2]:port or 1.2.240.1:port
     */
    std::string to_string() const;

    /**
     * Convert to bitcoin network address type.
     * @return  The authority converted to a network address.
     */
    message::network_address to_network_address() const;

    /**
     * Override the equality operator.
     * @param[in]  other  The other object with which to compare.
     */
    bool operator==(authority const& x) const;

    /**
     * Override the inequality operator.
     * @param[in]  other  The other object with which to compare.
     */
    bool operator!=(authority const& x) const;

    /**
     * Define stream in. Throws if input is invalid.
     * @param[in]   input     The input stream to read the value from.
     * @param[out]  argument  The object to receive the read value.
     * @return                The input stream reference.
     */
    friend 
    std::istream& operator>>(std::istream& input, authority& argument);

    /**
     * Define stream out.
     * @param[in]   output    The output stream to write the value to.
     * @param[out]  argument  The object from which to obtain the value.
     * @return                The output stream reference.
     */
    friend 
    std::ostream& operator<<(std::ostream& output, authority const& argument);

private:
    asio::ipv6 ip_;
    uint16_t port_{0};
};

} // namespace kth::config

#endif
