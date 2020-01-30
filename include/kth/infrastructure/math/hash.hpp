// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
#ifndef KTH_INFRASTUCTURE_HASH_HPP
#define KTH_INFRASTUCTURE_HASH_HPP

#include <cstddef>
#include <string>
#include <vector>

#include <boost/functional/hash_fwd.hpp>
#include <boost/multiprecision/cpp_int.hpp>

#include <kth/infrastructure/compat.hpp>
#include <kth/infrastructure/define.hpp>
#include <kth/infrastructure/hash_define.hpp>
#include <kth/infrastructure/utility/data.hpp>
#include <kth/infrastructure/utility/endian.hpp>

namespace kth {

// // Common bitcoin hash container sizes.
// static constexpr size_t hash_size = 32;
// static constexpr size_t half_hash_size = hash_size / 2;
// static constexpr size_t quarter_hash_size = half_hash_size / 2;
// static constexpr size_t long_hash_size = 2 * hash_size;
// static constexpr size_t short_hash_size = 20;
// static constexpr size_t mini_hash_size = 6;

// // Common bitcoin hash containers.
// typedef byte_array<hash_size> hash_digest;
// typedef byte_array<half_hash_size> half_hash;
// typedef byte_array<quarter_hash_size> quarter_hash;
// typedef byte_array<long_hash_size> long_hash;
// typedef byte_array<short_hash_size> short_hash;
// typedef byte_array<mini_hash_size> mini_hash;

// // Lists of common bitcoin hashes.
// typedef std::vector<hash_digest> hash_list;
// typedef std::vector<half_hash> half_hash_list;
// typedef std::vector<quarter_hash> quarter_hash_list;
// typedef std::vector<long_hash> long_hash_list;
// typedef std::vector<short_hash> short_hash_list;
// typedef std::vector<mini_hash> mini_hash_list;

// Alias for boost big integer type.
using uint256_t = boost::multiprecision::uint256_t;

// // Null-valued common bitcoin hashes.

// constexpr hash_digest null_hash
// {
//     {
//         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
//     }
// };

constexpr half_hash null_half_hash
{
    {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
    }
};

constexpr quarter_hash null_quarter_hash
{
    {
        0, 0, 0, 0, 0, 0, 0, 0
    }
};

constexpr long_hash null_long_hash
{
    {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
    }
};

constexpr short_hash null_short_hash
{
    {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0
    }
};


constexpr mini_hash null_mini_hash
{
    {
        0, 0, 0, 0, 0, 0
    }
};


inline uint256_t to_uint256(hash_digest const& hash)
{
    return from_little_endian<uint256_t>(hash.begin(), hash.end());
}

/// Generate a scrypt hash to fill a byte array.
template <size_t Size>
byte_array<Size> scrypt(data_slice data, data_slice salt, uint64_t N,
    uint32_t p, uint32_t r);

/// Generate a scrypt hash of specified length.
BI_API data_chunk scrypt(data_slice data, data_slice salt, uint64_t N,
    uint32_t p, uint32_t r, size_t length);

/// Generate a bitcoin hash.
BI_API hash_digest bitcoin_hash(data_slice data);

//TODO(fernando): see what to do with Currency
// #ifdef KTH_CURRENCY_LTC
/// Generate a litecoin hash.
BI_API hash_digest litecoin_hash(data_slice data);
// #endif //KTH_CURRENCY_LTC

/// Generate a bitcoin short hash.
BI_API short_hash bitcoin_short_hash(data_slice data);

/// Generate a ripemd160 hash
BI_API short_hash ripemd160_hash(data_slice data);
BI_API data_chunk ripemd160_hash_chunk(data_slice data);

/// Generate a sha1 hash.
BI_API short_hash sha1_hash(data_slice data);
BI_API data_chunk sha1_hash_chunk(data_slice data);

/// Generate a sha256 hash.
BI_API hash_digest sha256_hash(data_slice data);
BI_API data_chunk sha256_hash_chunk(data_slice data);

/// Generate a sha256 hash.
/// This hash function was used in electrum seed stretching (obsoleted).
BI_API hash_digest sha256_hash(data_slice first, data_slice second);

// Generate a hmac sha256 hash.
BI_API hash_digest hmac_sha256_hash(data_slice data, data_slice key);

/// Generate a sha512 hash.
BI_API long_hash sha512_hash(data_slice data);

/// Generate a hmac sha512 hash.
BI_API long_hash hmac_sha512_hash(data_slice data, data_slice key);

/// Generate a pkcs5 pbkdf2 hmac sha512 hash.
BI_API long_hash pkcs5_pbkdf2_hmac_sha512(data_slice passphrase,
    data_slice salt, size_t iterations);

} // namespace kth

// Extend std and boost namespaces with our hash wrappers.
//-----------------------------------------------------------------------------

namespace std
{
template <size_t Size>
struct hash<bc::byte_array<Size>>
{
    size_t operator()(const bc::byte_array<Size>& hash) const
    {
        return boost::hash_range(hash.begin(), hash.end());
    }
};
} // namespace std

namespace boost
{
template <size_t Size>
struct hash<bc::byte_array<Size>>
{
    size_t operator()(const bc::byte_array<Size>& hash) const
    {
        return boost::hash_range(hash.begin(), hash.end());
    }
};
} // namespace boost

#include <kth/infrastructure/impl/math/hash.ipp>

#endif
