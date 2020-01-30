// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
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
