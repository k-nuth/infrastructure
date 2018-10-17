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
#ifndef LIBBITCOIN_INFRASTUCTURE_WALLET_HD_PRIVATE_KEY_HPP
#define LIBBITCOIN_INFRASTUCTURE_WALLET_HD_PRIVATE_KEY_HPP

#include <cstdint>
#include <iostream>
#include <string>

#include <bitcoin/infrastructure/define.hpp>
#include <bitcoin/infrastructure/math/elliptic_curve.hpp>
#include <bitcoin/infrastructure/utility/data.hpp>
// #include <bitcoin/infrastructure/wallet/ec_private.hpp>
// #include <bitcoin/infrastructure/wallet/ec_public.hpp>
#include <bitcoin/infrastructure/wallet/hd_public.hpp>

namespace libbitcoin {
namespace wallet {

constexpr
uint64_t to_prefixes(uint32_t private_prefix, uint32_t public_prefix) {
    return uint64_t(private_prefix) << 32 | public_prefix;
}

/// An extended private key, as defined by BIP 32.
class BI_API hd_private : public hd_public {
public:
    // static constexpr
    // uint64_t to_prefixes(uint32_t private_prefix, uint32_t public_prefix) {
    //     return uint64_t(private_prefix) << 32 | public_prefix;
    // }

    static constexpr uint64_t mainnet = to_prefixes(76066276, hd_public::mainnet);
    static constexpr uint64_t testnet = to_prefixes(70615956, hd_public::testnet);

    static constexpr
    uint32_t to_prefix(uint64_t prefixes) {
        return prefixes >> 32;
    }

    /// Constructors.
    hd_private() = default;
    hd_private(hd_private const& x) = default;
    hd_private& operator=(hd_private x);

    explicit
    hd_private(data_chunk const& seed, uint64_t prefixes = mainnet);
    
    explicit
    hd_private(hd_key const& private_key);

    hd_private(hd_key const& private_key, uint64_t prefixes);
    hd_private(hd_key const& private_key, uint32_t prefix);
    
    explicit
    hd_private(std::string const& encoded);

    hd_private(std::string const& encoded, uint64_t prefixes);
    hd_private(std::string const& encoded, uint32_t prefix);

    /// Operators.
    bool operator<(hd_private const& x) const;
    bool operator==(hd_private const& x) const;
    bool operator!=(hd_private const& x) const;

    friend 
    std::istream& operator>>(std::istream& in, hd_private& to);
    
    friend 
    std::ostream& operator<<(std::ostream& out, hd_private const& of);

    // Swap implementation required to properly handle base class.
    friend 
    void swap(hd_private& left, hd_private& right);

    /// Cast operators.
    explicit
    operator ec_secret const&() const;

    /// Serializer.
    std::string encoded() const;

    /// Accessors.
    ec_secret const& secret() const;

    /// Methods.
    hd_key to_hd_key() const;
    hd_public to_public() const;
    hd_private derive_private(uint32_t index) const;
    hd_public derive_public(uint32_t index) const;

private:
    /// Factories.
    static hd_private from_seed(data_slice seed, uint64_t prefixes);
    static hd_private from_key(hd_key const& decoded);
    static hd_private from_key(hd_key const& key, uint32_t public_prefix);
    static hd_private from_key(hd_key const& key, uint64_t prefixes);
    static hd_private from_string(std::string const& encoded);
    static hd_private from_string(std::string const& encoded, uint32_t public_prefix);
    static hd_private from_string(std::string const& encoded, uint64_t prefixes);

    hd_private(ec_secret const& secret, const hd_chain_code& chain_code, hd_lineage const& lineage);

    /// Members.
    /// This should be const, apart from the need to implement assignment.
    ec_secret secret_ {null_hash};
};

} // namespace wallet
} // namespace libbitcoin

#endif
