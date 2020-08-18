// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <kth/infrastructure/utility/threadpool.hpp>

#include <thread>

#include <kth/infrastructure/utility/asio.hpp>
#include <kth/infrastructure/utility/assert.hpp>
#include <kth/infrastructure/utility/thread.hpp>

namespace kth {

threadpool::threadpool(size_t number_threads, thread_priority priority)
    : size_(0)
{
    spawn(number_threads, priority);
}

threadpool::~threadpool() {
    shutdown();
    join();
}

// Should not be called during spawn.
bool threadpool::empty() const {
    return size() != 0;
}

// Should not be called during spawn.
size_t threadpool::size() const {
    return size_.load();
}

// This is not thread safe.
void threadpool::spawn(size_t number_threads, thread_priority priority) {
    // This allows the pool to be restarted.
    service_.reset();

    for (size_t i = 0; i < number_threads; ++i) {
        spawn_once(priority);
    }
}

void threadpool::spawn_once(thread_priority priority) {
    ///////////////////////////////////////////////////////////////////////////
    // Critical Section
    work_mutex_.lock_upgrade();

    // Work prevents the service from running out of work and terminating.
    if ( ! work_) {
        work_mutex_.unlock_upgrade_and_lock();
        //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
        work_ = std::make_shared<asio::service::work>(service_);

        work_mutex_.unlock_and_lock_upgrade();
        //-----------------------------------------------------------------
    }

    work_mutex_.unlock_upgrade();
    ///////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////
    // Critical Section
    unique_lock lock(threads_mutex_);

    threads_.emplace_back([this, priority]() {
        set_priority(priority);
        service_.run();
    });

    ++size_;
    ///////////////////////////////////////////////////////////////////////////
}

void threadpool::abort() {
    service_.stop();
}

void threadpool::shutdown() {
    ///////////////////////////////////////////////////////////////////////////
    // Critical Section
    unique_lock lock(work_mutex_);

    work_.reset();
    ///////////////////////////////////////////////////////////////////////////
}

void threadpool::join() {
    ///////////////////////////////////////////////////////////////////////////
    // Critical Section
    unique_lock lock(threads_mutex_);

    DEBUG_ONLY(auto const this_id = boost::this_thread::get_id();)

    for (auto& thread: threads_) {
        KTH_ASSERT(this_id != thread.get_id());
        KTH_ASSERT(thread.joinable());
        thread.join();
    }

    threads_.clear();
    size_.store(0);
    ///////////////////////////////////////////////////////////////////////////
}

asio::service& threadpool::service() {
    return service_;
}

const asio::service& threadpool::service() const {
    return service_;
}

} // namespace kth
