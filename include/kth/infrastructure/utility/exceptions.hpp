// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
#ifndef KTH_INFRASTRUCTURE_EXCEPTIONS_HPP
#define KTH_INFRASTRUCTURE_EXCEPTIONS_HPP

#include <exception>

#include <bitcoin/infrastructure/define.hpp>

namespace kth {

class BI_API end_of_stream
    : std::exception
{};

}

#endif
