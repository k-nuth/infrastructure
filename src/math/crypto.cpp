// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
#include <bitcoin/infrastructure/math/crypto.hpp>

#include <bitcoin/infrastructure/math/elliptic_curve.hpp>
#include <bitcoin/infrastructure/math/hash.hpp>
#include <bitcoin/infrastructure/utility/assert.hpp>
#include <bitcoin/infrastructure/utility/data.hpp>

#include "../math/external/aes256.h"

namespace kth {

void aes256_encrypt(const aes_secret& key, aes_block& block)
{
    aes256_context context;
    aes256_init(&context, key.data());
    aes256_encrypt_ecb(&context, block.data());
    aes256_done(&context);
}

void aes256_decrypt(const aes_secret& key, aes_block& block)
{
    aes256_context context;
    aes256_init(&context, key.data());
    aes256_decrypt_ecb(&context, block.data());
    aes256_done(&context);
}

} // namespace kth
