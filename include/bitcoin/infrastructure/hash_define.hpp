/**
 * Copyright (c) 2017-2018 Bitprim Inc.
 *
 * This file is part of Bitprim.
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
#ifndef LIBBITCOIN_INFRASTRUCTURE_HASH_DEFINE_HPP
#define LIBBITCOIN_INFRASTRUCTURE_HASH_DEFINE_HPP

#include <cstddef>
#include <string>
#include <vector>
#include <boost/functional/hash_fwd.hpp>
#include <boost/multiprecision/cpp_int.hpp>
#include <bitcoin/infrastructure/compat.hpp>
#include <bitcoin/infrastructure/define.hpp>
#include <bitcoin/infrastructure/utility/data.hpp>
#include <bitcoin/infrastructure/utility/endian.hpp>

namespace libbitcoin {

// Common bitcoin hash container sizes.
static BI_CONSTEXPR size_t hash_size = 32;
static BI_CONSTEXPR size_t half_hash_size = hash_size / 2;
static BI_CONSTEXPR size_t quarter_hash_size = half_hash_size / 2;
static BI_CONSTEXPR size_t long_hash_size = 2 * hash_size;
static BI_CONSTEXPR size_t short_hash_size = 20;
static BI_CONSTEXPR size_t mini_hash_size = 6;

// Common bitcoin hash containers.
typedef byte_array<hash_size> hash_digest;
typedef byte_array<half_hash_size> half_hash;
typedef byte_array<quarter_hash_size> quarter_hash;
typedef byte_array<long_hash_size> long_hash;
typedef byte_array<short_hash_size> short_hash;
typedef byte_array<mini_hash_size> mini_hash;

// Lists of common bitcoin hashes.
typedef std::vector<hash_digest> hash_list;
typedef std::vector<half_hash> half_hash_list;
typedef std::vector<quarter_hash> quarter_hash_list;
typedef std::vector<long_hash> long_hash_list;
typedef std::vector<short_hash> short_hash_list;
typedef std::vector<mini_hash> mini_hash_list;

// // Alias for boost big integer type.
// typedef boost::multiprecision::uint256_t uint256_t;

// // Null-valued common bitcoin hashes.

BI_CONSTEXPR hash_digest null_hash
{
    {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
    }
};

// BI_CONSTEXPR half_hash null_half_hash
// {
//     {
//         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
//     }
// };

// BI_CONSTEXPR quarter_hash null_quarter_hash
// {
//     {
//         0, 0, 0, 0, 0, 0, 0, 0
//     }
// };

// BI_CONSTEXPR long_hash null_long_hash
// {
//     {
//         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
//     }
// };

// BI_CONSTEXPR short_hash null_short_hash
// {
//     {
//         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//         0, 0, 0, 0
//     }
// };

// BI_CONSTEXPR mini_hash null_mini_hash
// {
//     {
//         0, 0, 0, 0, 0, 0
//     }
// };

// inline uint256_t to_uint256(const hash_digest& hash)
// {
//     return from_little_endian<uint256_t>(hash.begin(), hash.end());
// }

// /// Generate a scrypt hash to fill a byte array.
// template <size_t Size>
// byte_array<Size> scrypt(data_slice data, data_slice salt, uint64_t N,
//     uint32_t p, uint32_t r);

// /// Generate a scrypt hash of specified length.
// BI_API data_chunk scrypt(data_slice data, data_slice salt, uint64_t N,
//     uint32_t p, uint32_t r, size_t length);

// /// Generate a bitcoin hash.
// BI_API hash_digest bitcoin_hash(data_slice data);

// #ifdef BITPRIM_CURRENCY_LTC
// /// Generate a litecoin hash.
// BI_API hash_digest litecoin_hash(data_slice data);
// #endif //BITPRIM_CURRENCY_LTC

// /// Generate a bitcoin short hash.
// BI_API short_hash bitcoin_short_hash(data_slice data);

// /// Generate a ripemd160 hash
// BI_API short_hash ripemd160_hash(data_slice data);
// BI_API data_chunk ripemd160_hash_chunk(data_slice data);

// /// Generate a sha1 hash.
// BI_API short_hash sha1_hash(data_slice data);
// BI_API data_chunk sha1_hash_chunk(data_slice data);

// /// Generate a sha256 hash.
// BI_API hash_digest sha256_hash(data_slice data);
// BI_API data_chunk sha256_hash_chunk(data_slice data);

// /// Generate a sha256 hash.
// /// This hash function was used in electrum seed stretching (obsoleted).
// BI_API hash_digest sha256_hash(data_slice first, data_slice second);

// // Generate a hmac sha256 hash.
// BI_API hash_digest hmac_sha256_hash(data_slice data, data_slice key);

// /// Generate a sha512 hash.
// BI_API long_hash sha512_hash(data_slice data);

// /// Generate a hmac sha512 hash.
// BI_API long_hash hmac_sha512_hash(data_slice data, data_slice key);

// /// Generate a pkcs5 pbkdf2 hmac sha512 hash.
// BI_API long_hash pkcs5_pbkdf2_hmac_sha512(data_slice passphrase,
//     data_slice salt, size_t iterations);

} // namespace libbitcoin

// Extend std and boost namespaces with our hash wrappers.
//-----------------------------------------------------------------------------

// namespace std
// {
// template <size_t Size>
// struct hash<bc::byte_array<Size>>
// {
//     size_t operator()(const bc::byte_array<Size>& hash) const
//     {
//         return boost::hash_range(hash.begin(), hash.end());
//     }
// };
// } // namespace std

// namespace boost
// {
// template <size_t Size>
// struct hash<bc::byte_array<Size>>
// {
//     size_t operator()(const bc::byte_array<Size>& hash) const
//     {
//         return boost::hash_range(hash.begin(), hash.end());
//     }
// };
// } // namespace boost

// #include <bitcoin/infrastructure/impl/math/hash.ipp>

#endif
