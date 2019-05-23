/**
 * Copyright (c) 2016-2019 Knuth Project.
 *
 * This file is part of Knuth Project.
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
#include <bitcoin/infrastructure/message/message_tools.hpp>

namespace libbitcoin { 
namespace message {

size_t variable_uint_size(uint64_t value) {
    if (value < 0xfd) {
        return 1;
    } 
    
    if (value <= 0xffff) {
        return 3;
    } 
    
    if (value <= 0xffffffff) {
        return 5;
    } 

    return 9;
    
}

} // namespace message
} // namespace libbitcoin
