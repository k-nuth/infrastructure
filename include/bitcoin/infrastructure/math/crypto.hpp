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
#ifndef LIBBITCOIN_INFRASTUCTURE_AES256_HPP
#define LIBBITCOIN_INFRASTUCTURE_AES256_HPP

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

} // namespace libbitcoin

#endif

