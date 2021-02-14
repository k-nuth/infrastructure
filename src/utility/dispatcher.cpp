// Copyright (c) 2016-2021 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <kth/infrastructure/utility/dispatcher.hpp>

#include <memory>
#include <string>

#include <kth/infrastructure/utility/threadpool.hpp>
#include <kth/infrastructure/utility/work.hpp>

namespace kth {

dispatcher::dispatcher(threadpool& pool, std::string const& name)
  : heap_(std::make_shared<work>(pool, name)), pool_(pool)
{
}

////size_t dispatcher::ordered_backlog()
////{
////    return heap_->ordered_backlog();
////}
////
////size_t dispatcher::unordered_backlog()
////{
////    return heap_->unordered_backlog();
////}
////
////size_t dispatcher::concurrent_backlog()
////{
////    return heap_->concurrent_backlog();
////}
////
////size_t dispatcher::combined_backlog()
////{
////    return heap_->combined_backlog();
////}

} // namespace kth
