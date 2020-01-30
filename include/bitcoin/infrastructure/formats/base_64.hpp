// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
#ifndef KTH_INFRASTUCTURE_BASE_64_HPP
#define KTH_INFRASTUCTURE_BASE_64_HPP

#include <string>

#include <bitcoin/infrastructure/define.hpp>
#include <bitcoin/infrastructure/utility/data.hpp>

namespace libbitcoin {

/**
 * Encode data as base64.
 * @return the base64 encoded string.
 */
BI_API std::string encode_base64(data_slice unencoded);

/**
 * Attempt to decode base64 data.
 * @return false if the input contains non-base64 characters.
 */
BI_API bool decode_base64(data_chunk& out, std::string const& in);

} // namespace libbitcoin

#endif

