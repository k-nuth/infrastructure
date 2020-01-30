// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
#ifndef KTH_INFRASTUCTURE_MESSAGE_MESSAGES_HPP
#define KTH_INFRASTUCTURE_MESSAGE_MESSAGES_HPP

// #include <algorithm>
// #include <cstdint>
// #include <cstddef>

#include <bitcoin/infrastructure/define.hpp>
#include <bitcoin/infrastructure/utility/container_sink.hpp>
#include <bitcoin/infrastructure/utility/data.hpp>
#include <bitcoin/infrastructure/utility/limits.hpp>

namespace libbitcoin {
namespace message {

BI_API size_t variable_uint_size(uint64_t value);

} // namespace message
} // namespace libbitcoin

#endif
