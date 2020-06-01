// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <kth/infrastructure/message/network_address.hpp>

#include <algorithm>
#include <cstdint>

#include <kth/infrastructure/utility/container_sink.hpp>
#include <kth/infrastructure/utility/container_source.hpp>
#include <kth/infrastructure/utility/istream_reader.hpp>
#include <kth/infrastructure/utility/ostream_writer.hpp>

namespace kth::infrastructure::message {

// TODO(legacy): create derived address that adds the timestamp.

bool network_address::operator==(network_address const& x) const {
    return (services_ == x.services_) && (port_ == x.port_) && (ip_ == x.ip_);
}

bool network_address::operator!=(network_address const& x) const {
    return !(*this == x);
}

bool network_address::is_valid() const {
    return (timestamp_ != 0)
        || (services_ != 0)
        || (port_ != 0)
        || (ip_ != null_address);
}

void network_address::reset() {
    timestamp_ = 0;
    services_ = 0;
    ip_.fill(0);
    port_ = 0;
}

bool network_address::from_data(uint32_t version, data_chunk const& data, bool with_timestamp) {
    data_source istream(data);
    return from_data(version, istream, with_timestamp);
}

// bool network_address::from_data(uint32_t version, std::istream& stream, bool with_timestamp) {
//     istream_reader source(stream);
//     return from_data(version, source, with_timestamp);
// }

bool network_address::from_data(uint32_t version, data_source& stream, bool with_timestamp) {
    istream_reader source(stream);
    return from_data(version, source, with_timestamp);
}



// bool network_address::from_data(uint32_t version, reader& source, bool with_timestamp) {
//     reset();

//     if (with_timestamp) {
//         timestamp_ = source.read_4_bytes_little_endian();
//     }

//     services_ = source.read_8_bytes_little_endian();
//     auto ip = source.read_bytes(ip_.size());
//     port_ = source.read_2_bytes_big_endian();

//     if ( ! source) {
//         reset();
//     }

//     // TODO(legacy): add array to reader interface (can't use template).
//     std::move(ip.begin(), ip.end(), ip_.data());
//     return source;
// }

data_chunk network_address::to_data(uint32_t version, bool with_timestamp) const {
    data_chunk data;
    auto const size = serialized_size(version, with_timestamp);
    data.reserve(size);
    data_sink ostream(data);
    to_data(version, ostream, with_timestamp);
    ostream.flush();
    KTH_ASSERT(data.size() == size);
    return data;
}

// void network_address::to_data(uint32_t version, std::ostream& stream, bool with_timestamp) const {
//     ostream_writer sink(stream);
//     to_data(version, sink, with_timestamp);
// }


void network_address::to_data(uint32_t version, data_sink& stream, bool with_timestamp) const {
    ostream_writer sink(stream);
    to_data(version, sink, with_timestamp);
}


// void network_address::to_data(uint32_t version, writer& sink, bool with_timestamp) const {
//     if (with_timestamp) {
//         sink.write_4_bytes_little_endian(timestamp_);
//     }

//     sink.write_8_bytes_little_endian(services_);
//     sink.write_bytes(ip_.data(), ip_.size());
//     sink.write_2_bytes_big_endian(port_);
// }

size_t network_address::serialized_size(uint32_t version, bool with_timestamp) const {
    return network_address::satoshi_fixed_size(version, with_timestamp);
}

size_t network_address::satoshi_fixed_size(uint32_t version, bool with_timestamp) {
    size_t result = 26;

    if (with_timestamp) {
        result += 4u;
    }

    return result;
}

uint32_t network_address::timestamp() const {
    return timestamp_;
}

void network_address::set_timestamp(uint32_t value) {
    timestamp_ = value;
}

uint64_t network_address::services() const {
    return services_;
}

void network_address::set_services(uint64_t value) {
    services_ = value;
}

ip_address& network_address::ip() {
    return ip_;
}

ip_address const& network_address::ip() const {
    return ip_;
}

void network_address::set_ip(ip_address const& value) {
    ip_ = value;
}

uint16_t network_address::port() const {
    return port_;
}

void network_address::set_port(uint16_t value) {
    port_ = value;
}

network_address network_address::factory_from_data(uint32_t version, data_chunk const& data, bool with_timestamp) {
    network_address instance;
    instance.from_data(version, data, with_timestamp);
    return instance;
}

// network_address network_address::factory_from_data(uint32_t version, std::istream& stream, bool with_timestamp) {
//     network_address instance;
//     instance.from_data(version, stream, with_timestamp);
//     return instance;
// }

network_address network_address::factory_from_data(uint32_t version, data_source& stream, bool with_timestamp) {
    network_address instance;
    instance.from_data(version, stream, with_timestamp);
    return instance;
}



// network_address network_address::factory_from_data(uint32_t version, reader& source, bool with_timestamp) { 
//     network_address instance;
//     instance.from_data(version, source, with_timestamp);
//     return instance;
// }

} // namespace kth::infrastructure::message
