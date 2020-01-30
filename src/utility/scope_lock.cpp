// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
#include <bitcoin/infrastructure/utility/scope_lock.hpp>

#include <memory>

#include <bitcoin/infrastructure/utility/thread.hpp>

namespace libbitcoin {

scope_lock::scope_lock(shared_mutex& mutex)
  : mutex_(mutex)
{
    mutex_.lock();
}

scope_lock::~scope_lock()
{
    mutex_.unlock();
}

} // namespace libbitcoin
