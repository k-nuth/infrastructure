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
#ifndef LIBBITCOIN_INFRASTUCTURE_MESSAGE_NETWORK_ADDRESS_HPP
#define LIBBITCOIN_INFRASTUCTURE_MESSAGE_NETWORK_ADDRESS_HPP

#include <cstdint>
#include <istream>
#include <vector>

#include <bitcoin/infrastructure/define.hpp>
#include <bitcoin/infrastructure/utility/data.hpp>
#include <bitcoin/infrastructure/utility/reader.hpp>
#include <bitcoin/infrastructure/utility/writer.hpp>
#include <bitcoin/infrastructure/utility/container_sink.hpp>
#include <bitcoin/infrastructure/utility/container_source.hpp>

namespace libbitcoin {
namespace message {

using ip_address = byte_array<16>;
constexpr ip_address null_address {{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }};

class BI_API network_address {
public:
    using list = std::vector<network_address>;

    network_address() = default;

    constexpr 
    network_address(uint32_t timestamp, uint64_t services, ip_address const& ip, uint16_t port)
        : timestamp_(timestamp)
        , services_(services)
        , ip_(ip)
        , port_(port)
    {}


    network_address(network_address const& x) = default;
    network_address& operator=(network_address const& x) = default;

    bool operator==(network_address const& x) const;
    bool operator!=(network_address const& x) const;


    // Starting version 31402, addresses are prefixed with a timestamp.
    uint32_t timestamp() const;
    void set_timestamp(uint32_t value);

    uint64_t services() const;
    void set_services(uint64_t value);

    ip_address& ip();
    ip_address const& ip() const;
    void set_ip(ip_address const& value);

    uint16_t port() const;
    void set_port(uint16_t value);

    size_t serialized_size(uint32_t version, bool with_timestamp) const;

    bool from_data(uint32_t version, data_chunk const& data, bool with_timestamp);
    // bool from_data(uint32_t version, std::istream& stream, bool with_timestamp);
    bool from_data(uint32_t version, data_source& stream, bool with_timestamp);



    // bool from_data(uint32_t version, reader& source, bool with_timestamp);

    template <typename R>
    bool from_data(uint32_t version, R& source, bool with_timestamp) {
        reset();

        if (with_timestamp) {
            timestamp_ = source.read_4_bytes_little_endian();
        }

        services_ = source.read_8_bytes_little_endian();
        auto ip = source.read_bytes(ip_.size());
        port_ = source.read_2_bytes_big_endian();

        if ( ! source) {
            reset();
        }

        // TODO(libbitcoin): add array to reader interface (can't use template).
        std::move(ip.begin(), ip.end(), ip_.data());
        return source;
    }



    data_chunk to_data(uint32_t version, bool with_timestamp) const;
    // void to_data(uint32_t version, std::ostream& stream, bool with_timestamp) const;
    void to_data(uint32_t version, data_sink& stream, bool with_timestamp) const;


    // void to_data(uint32_t version, writer& sink, bool with_timestamp) const;
    template <typename W>
    void to_data(uint32_t version, W& sink, bool with_timestamp) const {
        if (with_timestamp) {
            sink.write_4_bytes_little_endian(timestamp_);
        }

        sink.write_8_bytes_little_endian(services_);
        sink.write_bytes(ip_.data(), ip_.size());
        sink.write_2_bytes_big_endian(port_);
    }


    bool is_valid() const;
    void reset();

    static 
    network_address factory_from_data(uint32_t version, data_chunk const& data, bool with_timestamp);
    
    // static 
    // network_address factory_from_data(uint32_t version, std::istream& stream, bool with_timestamp);

    static 
    network_address factory_from_data(uint32_t version, data_source& stream, bool with_timestamp);



    // static 
    // network_address factory_from_data(uint32_t version, reader& source, bool with_timestamp);
    
    template <typename R>
    static
    network_address factory_from_data(uint32_t version, R& source, bool with_timestamp) { 
        network_address instance;
        instance.from_data(version, source, with_timestamp);
        return instance;
    }


    static 
    size_t satoshi_fixed_size(uint32_t version, bool with_timestamp);


private:
    uint32_t timestamp_{0};
    uint64_t services_{0};
    ip_address ip_{null_address};
    uint16_t port_{0};
};

// version::services::none
constexpr uint32_t no_services = 0;
constexpr uint32_t no_timestamp = 0;
constexpr uint16_t unspecified_ip_port = 0;
constexpr ip_address unspecified_ip_address {{
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00
}};

// Defaults to full node services.
constexpr network_address unspecified_network_address {
    no_timestamp,
    no_services,
    unspecified_ip_address,
    unspecified_ip_port
};

} // namespace message
} // namespace libbitcoin

#endif
