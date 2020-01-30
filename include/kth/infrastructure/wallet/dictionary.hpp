// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
#ifndef KTH_INFRASTUCTURE_WALLET_DICTIONARY_HPP
#define KTH_INFRASTUCTURE_WALLET_DICTIONARY_HPP

#include <array>
#include <vector>

#include <bitcoin/infrastructure/compat.hpp>

namespace kth {
namespace wallet {

/**
 * A valid mnemonic dictionary has exactly this many words.
 */
static constexpr size_t dictionary_size = 2048;

/**
 * A dictionary for creating mnemonics.
 * The bip39 spec calls this a "wordlist".
 * This is a POD type, which means the compiler can write it directly
 * to static memory with no run-time overhead.
 */
using dictionary = std::array<char const*, dictionary_size>;

/**
 * A collection of candidate dictionaries for mnemonic validation.
 */
using dictionary_list = std::vector<const dictionary *>;

namespace language
{
    // Individual built-in languages:
    extern const dictionary en;
    extern const dictionary es;
    extern const dictionary ja;
    extern const dictionary it;
    extern const dictionary fr;
    extern const dictionary cs;
    extern const dictionary ru;
    extern const dictionary uk;
    extern const dictionary zh_Hans;
    extern const dictionary zh_Hant;

    // All built-in languages:
    extern const dictionary_list all;
}

} // namespace wallet
} // namespace kth

#endif