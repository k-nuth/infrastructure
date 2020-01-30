// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
#include <bitcoin/infrastructure/utility/monitor.hpp>

#include <cstddef>
#include <string>
#include <utility>
////#include <bitcoin/infrastructure/log/sources.hpp>

// libbitcoin defines the log and tracking but does not use them.
// These are defined in bc so that they can be used in network and blockchain.

namespace libbitcoin {

monitor::monitor(count_ptr counter, std::string&& name)
  : counter_(std::move(counter)), name_(std::move(name))
{
    trace(++(*counter_), "+");
}

monitor::~monitor()
{
    trace(--(*counter_), "-");
}

} // namespace libbitcoin
