// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
#ifndef KTH_INFRASTUCTURE_CONFIG_SODIUM_HPP
#define KTH_INFRASTUCTURE_CONFIG_SODIUM_HPP

#include <iostream>
#include <string>
#include <vector>

#include <bitcoin/infrastructure/define.hpp>
#include <bitcoin/infrastructure/math/hash.hpp>
#include <bitcoin/infrastructure/utility/data.hpp>

namespace kth {
namespace config {

/**
 * Serialization helper for base58 sodium keys.
 */
class BI_API sodium
{
public:
    /**
     * A list of base85 values.
     * This must provide operator<< for ostream in order to be used as a
     * boost::program_options default_value.
     */
    using list = std::vector<sodium>;

    /**
     * Default constructor.
     */
    sodium();

    /**
     * Initialization constructor.
     * @param[in]  base85  The value to initialize with.
     */
    explicit
    sodium(std::string const& base85);

    /**
     * Initialization constructor.
     * @param[in]  value  The value to initialize with.
     */
    explicit
    sodium(hash_digest const& value);

    /**
     * Copy constructor.
     * @param[in]  other  The object to copy into self on construct.
     */
    sodium(sodium const& x);

    /**
     * Getter.
     * @return True if the key is initialized.
     */
    // implicit
    operator bool const() const;    //NOLINT

    /**
     * Overload cast to internal type.
     * @return  This object's value cast to internal type.
     */
    explicit
    operator hash_digest const&() const;

    /**
     * Overload cast to generic data reference.
     * @return  This object's value cast to generic data.
     */
    explicit
    operator data_slice() const;

    /**
     * Get the key as a base85 encoded (z85) string.
     * @return The encoded key.
     */
    std::string to_string() const;

    /**
     * Overload stream in. Throws if input is invalid.
     * @param[in]   input     The input stream to read the value from.
     * @param[out]  argument  The object to receive the read value.
     * @return                The input stream reference.
     */
    friend 
    std::istream& operator>>(std::istream& input, sodium& argument);

    /**
     * Overload stream out.
     * @param[in]   output    The output stream to write the value to.
     * @param[out]  argument  The object from which to obtain the value.
     * @return                The output stream reference.
     */
    friend 
    std::ostream& operator<<(std::ostream& output, const sodium& argument);

private:

    /**
     * The state of this object.
     */
    hash_digest value_;
};

} // namespace config
} // namespace kth

#endif