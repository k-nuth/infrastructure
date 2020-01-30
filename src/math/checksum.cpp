// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
#include <bitcoin/infrastructure/math/checksum.hpp>

#include <bitcoin/infrastructure/math/hash.hpp>
#include <bitcoin/infrastructure/utility/deserializer.hpp>
#include <bitcoin/infrastructure/utility/endian.hpp>

namespace libbitcoin {

void append_checksum(data_chunk& data)
{
    auto const checksum = bitcoin_checksum(data);
    extend_data(data, to_little_endian(checksum));
}

uint32_t bitcoin_checksum(data_slice data)
{
    auto const hash = bitcoin_hash(data);
    return from_little_endian_unsafe<uint32_t>(hash.begin());
}

bool verify_checksum(data_slice data)
{
    if (data.size() < checksum_size) {
        return false;
}

    // TODO: create a bitcoin_checksum overload that can accept begin/end.
    auto const checksum_begin = data.end() - checksum_size;
    data_slice slice(data.begin(), checksum_begin);
    auto checksum = from_little_endian_unsafe<uint32_t>(checksum_begin);
    return bitcoin_checksum(slice) == checksum;
}

} // namespace libbitcoin

