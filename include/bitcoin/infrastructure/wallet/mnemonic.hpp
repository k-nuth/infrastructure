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
#ifndef LIBBITCOIN_INFRASTUCTURE_WALLET_MNEMONIC_HPP
#define LIBBITCOIN_INFRASTUCTURE_WALLET_MNEMONIC_HPP

#include <cstddef>
#include <string>
#include <vector>

#include <bitcoin/infrastructure/compat.hpp>
#include <bitcoin/infrastructure/define.hpp>
#include <bitcoin/infrastructure/math/hash.hpp>
#include <bitcoin/infrastructure/unicode/unicode.hpp>
#include <bitcoin/infrastructure/utility/data.hpp>
#include <bitcoin/infrastructure/utility/string.hpp>
#include <bitcoin/infrastructure/wallet/dictionary.hpp>

namespace kth {
namespace wallet {

/**
 * A valid mnemonic word count is evenly divisible by this number.
 */
static constexpr size_t mnemonic_word_multiple = 3;

/**
 * A valid seed byte count is evenly divisible by this number.
 */
static constexpr size_t mnemonic_seed_multiple = 4;

/**
 * Represents a mnemonic word list.
 */
using word_list = string_list;

/**
 * Create a new mnenomic (list of words) from provided entropy and a dictionary
 * selection. The mnemonic can later be converted to a seed for use in wallet
 * creation. Entropy byte count must be evenly divisible by 4.
 */
BI_API word_list create_mnemonic(data_slice entropy,
    const dictionary &lexicon=language::en);

/**
 * Checks a mnemonic against a dictionary to determine if the
 * words are spelled correctly and the checksum matches.
 * The words must have been created using mnemonic encoding.
 */
BI_API bool validate_mnemonic(const word_list& words,
    const dictionary &lexicon);

/**
 * Checks that a mnemonic is valid in at least one of the provided languages.
 */
BI_API bool validate_mnemonic(const word_list& mnemonic,
    const dictionary_list& lexicons=language::all);

/**
 * Convert a mnemonic with no passphrase to a wallet-generation seed.
 */
BI_API long_hash decode_mnemonic(const word_list& mnemonic);

#ifdef WITH_ICU

/**
 * Convert a mnemonic and passphrase to a wallet-generation seed.
 * Any passphrase can be used and will change the resulting seed.
 */
BI_API long_hash decode_mnemonic(const word_list& mnemonic,
    std::string const& passphrase);

#endif

} // namespace wallet
} // namespace kth

#endif
