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
#include <bitcoin/infrastructure/machine/number.hpp>

#include <cstdint>

namespace kth {
namespace machine {

uint8_t constexpr number::positive_0; // = 0;
uint8_t constexpr number::positive_1; //  = 1;
uint8_t constexpr number::positive_2; //  = 2;
uint8_t constexpr number::positive_3; //  = 3;
uint8_t constexpr number::positive_4; //  = 4;
uint8_t constexpr number::positive_5; //  = 5;
uint8_t constexpr number::positive_6; //  = 6;
uint8_t constexpr number::positive_7; //  = 7;
uint8_t constexpr number::positive_8; //  = 8;
uint8_t constexpr number::positive_9; //  = 9;
uint8_t constexpr number::positive_10; //  = 10;
uint8_t constexpr number::positive_11; //  = 11;
uint8_t constexpr number::positive_12; //  = 12;
uint8_t constexpr number::positive_13; //  = 13;
uint8_t constexpr number::positive_14; //  = 14;
uint8_t constexpr number::positive_15; //  = 15;
uint8_t constexpr number::positive_16; //  = 16;

uint8_t constexpr number::negative_mask; //  = 0x80;
uint8_t constexpr number::negative_1; //  = negative_mask | positive_1;
uint8_t constexpr number::negative_0; //  = negative_mask | positive_0;


// uint8_t constexpr number::positive_0 = 0;
// uint8_t constexpr number::positive_1 = 1;
// uint8_t constexpr number::positive_2 = 2;
// uint8_t constexpr number::positive_3 = 3;
// uint8_t constexpr number::positive_4 = 4;
// uint8_t constexpr number::positive_5 = 5;
// uint8_t constexpr number::positive_6 = 6;
// uint8_t constexpr number::positive_7 = 7;
// uint8_t constexpr number::positive_8 = 8;
// uint8_t constexpr number::positive_9 = 9;
// uint8_t constexpr number::positive_10 = 10;
// uint8_t constexpr number::positive_11 = 11;
// uint8_t constexpr number::positive_12 = 12;
// uint8_t constexpr number::positive_13 = 13;
// uint8_t constexpr number::positive_14 = 14;
// uint8_t constexpr number::positive_15 = 15;
// uint8_t constexpr number::positive_16 = 16;

// uint8_t constexpr number::negative_mask = 0x80;
// uint8_t constexpr number::negative_1 = negative_mask | positive_1;
// uint8_t constexpr number::negative_0 = negative_mask | positive_0;

} // namespace machine
} // namespace kth
