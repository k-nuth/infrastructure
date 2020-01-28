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
#ifndef LIBBITCOIN_INFRASTUCTURE_ELLIPTIC_CURVE_HPP
#define LIBBITCOIN_INFRASTUCTURE_ELLIPTIC_CURVE_HPP

#include <cstddef>

#include <bitcoin/infrastructure/compat.hpp>
#include <bitcoin/infrastructure/define.hpp>
#include <bitcoin/infrastructure/math/hash.hpp>
#include <bitcoin/infrastructure/utility/data.hpp>

namespace libbitcoin {

/// The sign byte value for an even (y-valued) key.
static constexpr uint8_t ec_even_sign = 2;

/// Private key:
static constexpr size_t ec_secret_size = 32;
using ec_secret = byte_array<ec_secret_size>;

/// Compressed public key:
static constexpr size_t ec_compressed_size = 33;
using ec_compressed = byte_array<ec_compressed_size>;

using point_list = std::vector<ec_compressed>;

/// Uncompressed public key:
static constexpr size_t ec_uncompressed_size = 65;
using ec_uncompressed = byte_array<ec_uncompressed_size>;

// Parsed ECDSA signature:
static constexpr size_t ec_signature_size = 64;
using ec_signature = byte_array<ec_signature_size>;

// DER encoded signature:
static constexpr size_t max_der_signature_size = 72;
using der_signature = data_chunk;

/// DER encoded signature with sighash byte for contract endorsement:
static constexpr size_t min_endorsement_size = 9;
static constexpr size_t max_endorsement_size = 73;
using endorsement = data_chunk;

/// Recoverable ecdsa signature for message signing:
struct BI_API recoverable_signature
{
    ec_signature signature;
    uint8_t recovery_id;
};

static constexpr ec_compressed null_compressed_point =
{
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

static constexpr ec_uncompressed null_uncompressed_point =
{
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

// Add and multiply EC values
// ----------------------------------------------------------------------------

/// Compute the sum a += G*b, where G is the curve's generator point.
/// return false on failure (such as infinity or zero).
BI_API bool ec_add(ec_compressed& point, ec_secret const& secret);

/// Compute the sum a += G*b, where G is the curve's generator point.
/// return false on failure (such as infinity or zero).
BI_API bool ec_add(ec_uncompressed& point, ec_secret const& secret);

/// Compute the sum a = (a + b) % n, where n is the curve order.
/// return false on failure (such as a zero result).
BI_API bool ec_add(ec_secret& left, ec_secret const& right);

/// Compute the product point *= secret.
/// return false on failure (such as infinity or zero).
BI_API bool ec_multiply(ec_compressed& point, ec_secret const& secret);

/// Compute the product point *= secret.
/// return false on failure (such as infinity or zero).
BI_API bool ec_multiply(ec_uncompressed& point, ec_secret const& secret);

/// Compute the product a = (a * b) % n, where n is the curve order.
/// return false on failure (such as a zero result).
BI_API bool ec_multiply(ec_secret& left, ec_secret const& right);

// Convert keys
// ----------------------------------------------------------------------------

/// Convert an uncompressed public point to compressed.
BI_API bool compress(ec_compressed& out, ec_uncompressed const& point);

/// Convert a compressed public point to decompressed.
BI_API bool decompress(ec_uncompressed& out, ec_compressed const& point);

/// Convert a secret to a compressed public point.
BI_API bool secret_to_public(ec_compressed& out, ec_secret const& secret);

/// Convert a secret parameter to an uncompressed public point.
BI_API bool secret_to_public(ec_uncompressed& out, ec_secret const& secret);

// Verify keys
// ----------------------------------------------------------------------------

/// Verify a secret.
BI_API bool verify(ec_secret const& secret);

/// Verify a point.
BI_API bool verify(ec_compressed const& point);

/// Verify a point.
BI_API bool verify(ec_uncompressed const& point);

// Detect public keys
// ----------------------------------------------------------------------------

/// Determine if the compressed public key is even (y-valued).
bool is_even_key(ec_compressed const& point);

/// Fast detection of compressed public key structure.
bool is_compressed_key(data_slice point);

/// Fast detection of uncompressed public key structure.
bool is_uncompressed_key(data_slice point);

/// Fast detection of compressed or uncompressed public key structure.
bool is_public_key(data_slice point);

/// Fast detection of endorsement structure (DER with signature hash type).
bool is_endorsement(const endorsement& endorsement);

// DER parse/encode
// ----------------------------------------------------------------------------

/// Parse an endorsement into signature hash type and DER signature.
BI_API bool parse_endorsement(uint8_t& sighash_type,
    der_signature& der_signature, endorsement&& endorsement);

/// Parse a DER encoded signature with optional strict DER enforcement.
/// Treat an empty DER signature as invalid, in accordance with BIP66.
BI_API bool parse_signature(ec_signature& out,
    der_signature const& der_signature, bool strict);

/// Encode an EC signature as DER (strict).
BI_API bool encode_signature(der_signature& out, ec_signature const& signature);

// EC sign/verify
// ----------------------------------------------------------------------------

/// Create a deterministic ECDSA signature using a private key.
BI_API bool sign(ec_signature& out, ec_secret const& secret,
    hash_digest const& hash);

/// Verify an EC signature using a compressed point.
BI_API bool verify_signature(ec_compressed const& point,
    hash_digest const& hash, ec_signature const& signature);

/// Verify an EC signature using an uncompressed point.
BI_API bool verify_signature(ec_uncompressed const& point,
    hash_digest const& hash, ec_signature const& signature);

/// Verify an EC signature using a potential point.
BI_API bool verify_signature(data_slice point, hash_digest const& hash,
    ec_signature const& signature);

// Recoverable sign/recover
// ----------------------------------------------------------------------------

/// Create a recoverable signature for use in message signing.
BI_API bool sign_recoverable(recoverable_signature& out,
    ec_secret const& secret, hash_digest const& hash);

/// Recover the compressed point from a recoverable message signature.
BI_API bool recover_public(ec_compressed& out,
    recoverable_signature const& recoverable, hash_digest const& hash);

/// Recover the uncompressed point from a recoverable message signature.
BI_API bool recover_public(ec_uncompressed& out,
    recoverable_signature const& recoverable, hash_digest const& hash);

} // namespace libbitcoin

#endif
