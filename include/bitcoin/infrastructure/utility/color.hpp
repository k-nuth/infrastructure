// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
#ifndef KTH_INFRASTRUCTURE_COLOR_HPP
#define KTH_INFRASTRUCTURE_COLOR_HPP

#include <cstdint>

#include <bitcoin/infrastructure/compat.hpp>
#include <bitcoin/infrastructure/define.hpp>

namespace libbitcoin {

struct BI_API color {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
    uint8_t alpha;
};

} // namespace libbitcoin

#endif
