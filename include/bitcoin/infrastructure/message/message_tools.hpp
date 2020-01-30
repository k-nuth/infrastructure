// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
#ifndef KTH_INFRASTRUCTURE_MESSAGE_TOOLS_HPP_
#define KTH_INFRASTRUCTURE_MESSAGE_TOOLS_HPP_

#include <cstddef>
#include <cstdint>

#include <bitcoin/infrastructure/define.hpp>

namespace libbitcoin { 
namespace message {

BI_API size_t variable_uint_size(uint64_t value);

} // namespace message
} // namespace libbitcoin

#endif // KTH_INFRASTRUCTURE_MESSAGE_TOOLS_HPP_
