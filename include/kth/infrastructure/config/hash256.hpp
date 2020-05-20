// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_INFRASTUCTURE_CONFIG_HASH256_HPP
#define KTH_INFRASTUCTURE_CONFIG_HASH256_HPP

#include <iostream>
#include <string>

#include <kth/infrastructure/define.hpp>
#include <kth/infrastructure/math/hash.hpp>

namespace kth {
namespace config {

/**
 * Serialization helper for a bitcoin 256 bit hash.
 */
class BI_API hash256
{
public:
    /**
     * A list of bitcoin 256 bit hashes.
     * This must provide operator<< for ostream in order to be used as a
     * boost::program_options default_value.
     */
    using list = std::vector<hash256>;

    hash256() = default;

    hash256(hash256 const& x) = default;

    /**
     * Initialization constructor.
     * @param[in]  hexcode  The hash value in string hexidecimal form.
     */
    explicit
    hash256(std::string const& hexcode);

    /**
     * Initialization constructor.
     * @param[in]  value  The hash value to initialize with.
     */
    explicit
    hash256(hash_digest const& value);

    /**
     * Get the hash as a string.
     * @return The hash in the string hexidecimal form.
     */
    std::string to_string() const;

    /**
     * Override the equality operator.
     * @param[in]  other  The other object with which to compare.
     */
    bool operator==(const hash256& x) const;

    /**
     * Cast to internal type.
     * @return  This object's value cast to internal type.
     */
    // implicit
    operator hash_digest const&() const;    //NOLINT

    /**
     * Define stream in. Throws if input is invalid.
     * @param[in]   input     The input stream to read the value from.
     * @param[out]  argument  The object to receive the read value.
     * @return                The input stream reference.
     */
    friend 
    std::istream& operator>>(std::istream& input, hash256& argument);

    /**
     * Define stream out.
     * @param[in]   output    The output stream to write the value to.
     * @param[out]  argument  The object from which to obtain the value.
     * @return                The output stream reference.
     */
    friend 
    std::ostream& operator<<(std::ostream& output, const hash256& argument);

private:
    hash_digest value_{null_hash};
};

} // namespace config
} // namespace kth

#endif
