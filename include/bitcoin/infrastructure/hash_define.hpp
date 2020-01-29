/**
 * Copyright (c) 2016-2020 Knuth Project.
 *
 * This file is part of Knuth Project.
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
#ifndef KNUTH_INFRASTRUCTURE_HASH_DEFINE_HPP
#define KNUTH_INFRASTRUCTURE_HASH_DEFINE_HPP

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
static constexpr size_t hash_size = 32;
static constexpr size_t half_hash_size = hash_size / 2;
static constexpr size_t quarter_hash_size = half_hash_size / 2;
static constexpr size_t long_hash_size = 2 * hash_size;
static constexpr size_t short_hash_size = 20;
static constexpr size_t mini_hash_size = 6;

// Common bitcoin hash containers.
using hash_digest = byte_array<hash_size>;
using half_hash = byte_array<half_hash_size>;
using quarter_hash = byte_array<quarter_hash_size>;
using long_hash = byte_array<long_hash_size>;
using short_hash = byte_array<short_hash_size>;
using mini_hash = byte_array<mini_hash_size>;

// Lists of common bitcoin hashes.
using hash_list = std::vector<hash_digest>;
using half_hash_list = std::vector<half_hash>;
using quarter_hash_list = std::vector<quarter_hash>;
using long_hash_list = std::vector<long_hash>;
using short_hash_list = std::vector<short_hash>;
using mini_hash_list = std::vector<mini_hash>;

// // Alias for boost big integer type.
// typedef boost::multiprecision::uint256_t uint256_t;

// // Null-valued common bitcoin hashes.

constexpr hash_digest null_hash
{
    {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
    }
};

// constexpr half_hash null_half_hash
// {
//     {
//         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
//     }
// };

// constexpr quarter_hash null_quarter_hash
// {
//     {
//         0, 0, 0, 0, 0, 0, 0, 0
//     }
// };

// constexpr long_hash null_long_hash
// {
//     {
//         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
//     }
// };

// constexpr short_hash null_short_hash
// {
//     {
//         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//         0, 0, 0, 0
//     }
// };

// constexpr mini_hash null_mini_hash
// {
//     {
//         0, 0, 0, 0, 0, 0
//     }
// };

// inline uint256_t to_uint256(hash_digest const& hash)
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

// #ifdef KNUTH_CURRENCY_LTC
// /// Generate a litecoin hash.
// BI_API hash_digest litecoin_hash(data_slice data);
// #endif //KNUTH_CURRENCY_LTC

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
