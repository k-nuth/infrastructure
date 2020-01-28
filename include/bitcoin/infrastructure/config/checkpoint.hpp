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
#ifndef LIBBITCOIN_INFRASTUCTURE_CONFIG_CHECKPOINT_HPP
#define LIBBITCOIN_INFRASTUCTURE_CONFIG_CHECKPOINT_HPP

#include <cstddef>
#include <iostream>
#include <string>
#include <vector>

#include <bitcoin/infrastructure/define.hpp>
#include <bitcoin/infrastructure/formats/base_16.hpp>

namespace libbitcoin {
namespace config {

/**
 * Serialization helper for a blockchain checkpoint.
 * This is a container for a {block hash, block height} tuple.
 */
class BI_API checkpoint {
public:
    using list = std::vector<checkpoint>;

    /**
     * Created a sorted copy of the list of checkpoints.
     * @param[in]  checks  The list of checkpoints.
     * @return             The sorted list of checkpoints.
     */
    static 
    list sort(list const& checks);

    /**
     * Confirm a checkpoint is in the range of a sorted list of checkpoints.
     * @param[in]  height  The height of checkpoint.
     * @param[in]  checks  The list of checkpoints.
     */
    static 
    bool covered(size_t height, list const& checks);

    /**
     * Validate a checkpoint against a set of checkpoints.
     * @param[in]  hash    The hash of the checkpoint.
     * @param[in]  height  The height of checkpoint.
     * @param[in]  checks  The set of checkpoints.
     */
    static 
    bool validate(hash_digest const& hash, size_t height, list const& checks);

    checkpoint();
    checkpoint(checkpoint const& x);

    /**
     * Initialization constructor.
     * The height is optional and will be set to zero if not provided.
     * @param[in]  value  The value of the hash[:height] form.
     */
    explicit
    checkpoint(std::string const& value);

    /**
     * Initialization constructor.
     * @param[in]  hash    The string block hash for the checkpoint.
     * @param[in]  height  The height of the hash.
     */
    checkpoint(std::string const& hash, size_t height);

    /**
     * Initialization constructor.
     * @param[in]  hash    The block hash for the checkpoint.
     * @param[in]  height  The height of the hash.
     */
    checkpoint(hash_digest const& hash, size_t height);

    hash_digest const& hash() const;
    size_t height() const;

    /**
     * Get the checkpoint as a string.
     * @return The ip address of the authority in the hash:height form.
     */
    std::string to_string() const;

    bool operator==(checkpoint const& x) const;

    friend 
    std::istream& operator>>(std::istream& input, checkpoint& argument);

    friend 
    std::ostream& operator<<(std::ostream& output, checkpoint const& argument);

private:
    hash_digest hash_;
    size_t height_{0};
};

} // namespace config
} // namespace libbitcoin

#endif
