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
#ifndef LIBBITCOIN_INFRASTUCTURE_WALLET_HD_PUBLIC_KEY_HPP
#define LIBBITCOIN_INFRASTUCTURE_WALLET_HD_PUBLIC_KEY_HPP

#include <cstdint>
#include <iostream>
#include <string>

#include <bitcoin/infrastructure/define.hpp>
#include <bitcoin/infrastructure/math/elliptic_curve.hpp>
#include <bitcoin/infrastructure/utility/data.hpp>
// #include <bitcoin/infrastructure/wallet/ec_public.hpp>

namespace libbitcoin {
namespace wallet {

/// A constant used in key derivation.
static constexpr uint32_t hd_first_hardened_key = 1 << 31;

/// An hd key chain code.
static constexpr size_t hd_chain_code_size = 32;
using hd_chain_code = byte_array<hd_chain_code_size>;

/// A decoded hd public or private key.
static constexpr size_t hd_key_size = 82;
using hd_key = byte_array<hd_key_size>;

/// Key derivation information used in the serialization format.
struct BI_API hd_lineage {
    uint64_t prefixes;
    uint8_t depth;
    uint32_t parent_fingerprint;
    uint32_t child_number;

    bool operator==(hd_lineage const& x) const;
    bool operator!=(hd_lineage const& x) const;
};

class hd_private;

/// An extended public key, as defined by BIP 32.
class BI_API hd_public {
public:
    static constexpr uint32_t mainnet = 76067358;
    static constexpr uint32_t testnet = 70617039;

    static constexpr
    uint32_t to_prefix(uint64_t prefixes) {
        return prefixes & 0x00000000FFFFFFFF;
    }

    /// Constructors.
    hd_public();
    
    hd_public(hd_public const& x) = default;
    
    explicit
    hd_public(hd_key const& public_key);
    
    hd_public(hd_key const& public_key, uint32_t prefix);
    
    explicit
    hd_public(std::string const& encoded);

    hd_public(std::string const& encoded, uint32_t prefix);

    /// Operators.
    bool operator<(hd_public const& x) const;
    bool operator==(hd_public const& x) const;
    bool operator!=(hd_public const& x) const;
    hd_public& operator=(hd_public const& x);
    
    friend 
    std::istream& operator>>(std::istream& in, hd_public& to); 
    
    friend 
    std::ostream& operator<<(std::ostream& out, hd_public const& of);

    /// Cast operators.
    // implicit
    operator bool const() const;    //NOLINT
    
    explicit
    operator const ec_compressed&() const;

    /// Serializer.
    std::string encoded() const;

    /// Accessors.
    const hd_chain_code& chain_code() const;
    hd_lineage const& lineage() const;
    const ec_compressed& point() const;

    /// Methods.
    hd_key to_hd_key() const;
    hd_public derive_public(uint32_t index) const;

protected:
    /// Factories.
    static 
    hd_public from_secret(ec_secret const& secret, const hd_chain_code& chain_code, hd_lineage const& lineage);

    /// Helpers.
    uint32_t fingerprint() const;

    /// Members.
    /// These should be const, apart from the need to implement assignment.
    bool valid_{false};
    hd_chain_code chain_;
    hd_lineage lineage_;
    ec_compressed point_;

private:
    static 
    hd_public from_key(hd_key const& key);
    
    static 
    hd_public from_string(std::string const& encoded);
    
    static 
    hd_public from_key(hd_key const& key, uint32_t prefix);
    
    static
    hd_public from_string(std::string const& encoded, uint32_t prefix);

    hd_public(const ec_compressed& point, const hd_chain_code& chain_code, hd_lineage const& lineage);
};

} // namespace wallet
} // namespace libbitcoin

#endif
