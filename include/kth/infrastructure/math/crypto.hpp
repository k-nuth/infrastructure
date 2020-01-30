// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
#ifndef KTH_INFRASTUCTURE_AES256_HPP
#define KTH_INFRASTUCTURE_AES256_HPP

#include <cstdint>

#include <bitcoin/infrastructure/compat.hpp>
#include <bitcoin/infrastructure/define.hpp>
#include <bitcoin/infrastructure/utility/data.hpp>

namespace kth {

/**
 * The secret for aes256 block cypher.
 */
constexpr uint8_t aes256_key_size = 32;
using aes_secret = byte_array<aes256_key_size>;

/**
 * The data block for use with aes256 block cypher.
 */
constexpr uint8_t aes256_block_size = 16;
using aes_block = byte_array<aes256_block_size>;

/**
 * Perform aes256 encryption on the specified data block.
 */
BI_API void aes256_encrypt(const aes_secret& key, aes_block& block);

/**
 * Perform aes256 decryption on the specified data block.
 */
BI_API void aes256_decrypt(const aes_secret& key, aes_block& block);

} // namespace kth

#endif
