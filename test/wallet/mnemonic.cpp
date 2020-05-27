// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "mnemonic.hpp"

#include <boost/test/unit_test.hpp>
#include <kth/infrastructure.hpp>

using namespace kth;
using namespace kth::infrastructure::wallet;

BOOST_AUTO_TEST_SUITE(mnemonic_tests)

BOOST_AUTO_TEST_CASE(mnemonic__decode_mnemonic__no_passphrase)
{
    for (auto const& vector: mnemonic_no_passphrase)
    {
        auto const words = split(vector.mnemonic, ",");
        BOOST_REQUIRE(validate_mnemonic(words, vector.language));
        auto const seed = decode_mnemonic(words);
        BOOST_REQUIRE_EQUAL(encode_base16(seed), vector.seed);
    }
}

#ifdef WITH_ICU

BOOST_AUTO_TEST_CASE(mnemonic__decode_mnemonic__trezor)
{
    for (auto const& vector: mnemonic_trezor_vectors)
    {
        auto const words = split(vector.mnemonic, ",");
        BOOST_REQUIRE(validate_mnemonic(words));
        auto const seed = decode_mnemonic(words, vector.passphrase);
        BOOST_REQUIRE_EQUAL(encode_base16(seed), vector.seed);
    }
}

BOOST_AUTO_TEST_CASE(mnemonic__decode_mnemonic__bx)
{
    for (auto const& vector: mnemonic_bx_to_seed_vectors)
    {
        auto const words = split(vector.mnemonic, ",");
        BOOST_REQUIRE(validate_mnemonic(words));
        auto const seed = decode_mnemonic(words, vector.passphrase);
        BOOST_REQUIRE_EQUAL(encode_base16(seed), vector.seed);
    }
}

#endif

BOOST_AUTO_TEST_CASE(mnemonic__create_mnemonic__trezor)
{
    for (const mnemonic_result& vector: mnemonic_trezor_vectors)
    {
        data_chunk entropy;
        decode_base16(entropy, vector.entropy);
        auto const mnemonic = create_mnemonic(entropy, vector.language);
        BOOST_REQUIRE(mnemonic.size() > 0);
        BOOST_REQUIRE_EQUAL(join(mnemonic, ","), vector.mnemonic);
        BOOST_REQUIRE(validate_mnemonic(mnemonic));
    }
}

BOOST_AUTO_TEST_CASE(mnemonic__create_mnemonic__bx)
{
    for (const mnemonic_result& vector: mnemonic_bx_new_vectors)
    {
        data_chunk entropy;
        decode_base16(entropy, vector.entropy);
        auto const mnemonic = create_mnemonic(entropy, vector.language);
        BOOST_REQUIRE(mnemonic.size() > 0);
        BOOST_REQUIRE_EQUAL(join(mnemonic, ","), vector.mnemonic);
        BOOST_REQUIRE(validate_mnemonic(mnemonic));
    }
}

BOOST_AUTO_TEST_CASE(mnemonic__validate_mnemonic__invalid)
{
    for (auto const& mnemonic: invalid_mnemonic_tests)
    {
        auto const words = split(mnemonic, ",");
        BOOST_REQUIRE(!validate_mnemonic(words));
    }
}

BOOST_AUTO_TEST_CASE(mnemonic__create_mnemonic__tiny)
{
    data_chunk const entropy(4, 0xa9);
    auto const mnemonic = create_mnemonic(entropy);
    BOOST_REQUIRE_EQUAL(mnemonic.size(), 3u);
    BOOST_REQUIRE(validate_mnemonic(mnemonic));
}

BOOST_AUTO_TEST_CASE(mnemonic__create_mnemonic__giant)
{
    data_chunk const entropy(1024, 0xa9);
    auto const mnemonic = create_mnemonic(entropy);
    BOOST_REQUIRE_EQUAL(mnemonic.size(), 768u);
    BOOST_REQUIRE(validate_mnemonic(mnemonic));
}

BOOST_AUTO_TEST_CASE(mnemonic__dictionary__en_es__no_intersection)
{
    auto const& english = language::en;
    auto const& spanish = language::es;
    size_t intersection = 0;
    for (auto const es: spanish)
    {
        std::string test(es);
        auto const it = std::find(english.begin(), english.end(), test);
        if (it != std::end(english))
            intersection++;
    }

    BOOST_REQUIRE_EQUAL(intersection, 0u);
}

BOOST_AUTO_TEST_CASE(mnemonic__dictionary__en_it__no_intersection)
{
    auto const& english = language::en;
    auto const& italian = language::it;
    size_t intersection = 0;
    for (auto const it: italian)
    {
        std::string test(it);
        auto const iter = std::find(english.begin(), english.end(), test);
        if (iter != std::end(english))
            intersection++;
    }

    BOOST_REQUIRE_EQUAL(intersection, 0u);
}

BOOST_AUTO_TEST_CASE(mnemonic__dictionary__fr_es__no_intersection)
{
    auto const& french = language::fr;
    auto const& spanish = language::es;
    size_t intersection = 0;
    for (auto const es: spanish)
    {
        std::string test(es);
        auto const it = std::find(french.begin(), french.end(), test);
        if (it != std::end(french))
            intersection++;
    }

    BOOST_REQUIRE_EQUAL(intersection, 0u);
}

BOOST_AUTO_TEST_CASE(mnemonic__dictionary__it_es__no_intersection)
{
    auto const& italian = language::it;
    auto const& spanish = language::es;
    size_t intersection = 0;
    for (auto const es: spanish)
    {
        std::string test(es);
        auto const it = std::find(italian.begin(), italian.end(), test);
        if (it != std::end(italian))
            intersection++;
    }

    BOOST_REQUIRE_EQUAL(intersection, 0u);
}

BOOST_AUTO_TEST_CASE(mnemonic__dictionary__fr_it__no_intersection)
{
    auto const& french = language::fr;
    auto const& italian = language::it;
    size_t intersection = 0;
    for (auto const it: italian)
    {
        std::string test(it);
        auto const iter = std::find(french.begin(), french.end(), test);
        if (iter != std::end(french))
            intersection++;
    }

    BOOST_REQUIRE_EQUAL(intersection, 0u);
}

BOOST_AUTO_TEST_CASE(mnemonic__dictionary__cs_ru__no_intersection)
{
    auto const& czech = language::cs;
    auto const& russian = language::ru;
    size_t intersection = 0;
    for (auto const ru: russian)
    {
        std::string test(ru);
        auto const iter = std::find(czech.begin(), czech.end(), test);
        if (iter != std::end(czech))
            intersection++;
    }

    BOOST_REQUIRE_EQUAL(intersection, 0u);
}

BOOST_AUTO_TEST_CASE(mnemonic__dictionary__cs_uk__no_intersection)
{
    auto const& czech = language::cs;
    auto const& ukranian = language::uk;
    size_t intersection = 0;
    for (auto const uk: ukranian)
    {
        std::string test(uk);
        auto const iter = std::find(czech.begin(), czech.end(), test);
        if (iter != std::end(czech))
            intersection++;
    }

    BOOST_REQUIRE_EQUAL(intersection, 0u);
}

BOOST_AUTO_TEST_CASE(mnemonic__dictionary__zh_Hans_Hant__intersection)
{
    auto const& simplified = language::zh_Hans;
    auto const& traditional = language::zh_Hant;
    size_t intersection = 0;
    for (auto const hant: traditional)
    {
        std::string test(hant);
        auto const it = std::find(simplified.begin(), simplified.end(), test);
        if (it != std::end(simplified))
            intersection++;
    }

    BOOST_REQUIRE_EQUAL(intersection, 1275u);
}

BOOST_AUTO_TEST_SUITE_END()
