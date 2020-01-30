// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
#ifndef KTH_INFRASTRUCTURE_RESUBSCRIBER_IPP
#define KTH_INFRASTRUCTURE_RESUBSCRIBER_IPP

#include <functional>
#include <memory>
#include <string>
#include <utility>

#include <bitcoin/infrastructure/utility/assert.hpp>
#include <bitcoin/infrastructure/utility/dispatcher.hpp>
#include <bitcoin/infrastructure/utility/thread.hpp>
#include <bitcoin/infrastructure/utility/threadpool.hpp>
////#include <bitcoin/infrastructure/utility/track.hpp>

namespace libbitcoin {

template <typename... Args>
resubscriber<Args...>::resubscriber(threadpool& pool,
    std::string const& class_name)
  : stopped_(true), dispatch_(pool, class_name)
    /*, track<resubscriber<Args...>>(class_name)*/
{
}

template <typename... Args>
resubscriber<Args...>::~resubscriber()
{
    BITCOIN_ASSERT_MSG(subscriptions_.empty(), "resubscriber not cleared");
}

template <typename... Args>
void resubscriber<Args...>::start()
{
    // Critical Section
    ///////////////////////////////////////////////////////////////////////////
    subscribe_mutex_.lock_upgrade();

    if (stopped_)
    {
        //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
        subscribe_mutex_.unlock_upgrade_and_lock();
        stopped_ = false;
        subscribe_mutex_.unlock();
        //---------------------------------------------------------------------
        return;
    }

    subscribe_mutex_.unlock_upgrade();
    ///////////////////////////////////////////////////////////////////////////
}

template <typename... Args>
void resubscriber<Args...>::stop()
{
    // Critical Section
    ///////////////////////////////////////////////////////////////////////////
    subscribe_mutex_.lock_upgrade();

    if ( ! stopped_)
    {
        //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
        subscribe_mutex_.unlock_upgrade_and_lock();
        stopped_ = true;
        subscribe_mutex_.unlock();
        //---------------------------------------------------------------------
        return;
    }

    subscribe_mutex_.unlock_upgrade();
    ///////////////////////////////////////////////////////////////////////////
}

template <typename... Args>
void resubscriber<Args...>::subscribe(handler&& notify, Args... stopped_args)
{
    // Critical Section
    ///////////////////////////////////////////////////////////////////////////
    subscribe_mutex_.lock_upgrade();

    if ( ! stopped_)
    {
        //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
        subscribe_mutex_.unlock_upgrade_and_lock();
        subscriptions_.push_back(std::forward<handler>(notify));
        subscribe_mutex_.unlock();
        //---------------------------------------------------------------------
        return;
    }

    subscribe_mutex_.unlock_upgrade();
    ///////////////////////////////////////////////////////////////////////////

    notify(stopped_args...);
}

template <typename... Args>
void resubscriber<Args...>::invoke(Args... args)
{
    do_invoke(args...);
}

template <typename... Args>
void resubscriber<Args...>::relay(Args... args)
{
    // This enqueues work while maintaining order.
    dispatch_.ordered(&resubscriber<Args...>::do_invoke,
        this->shared_from_this(), args...);
}

// private
template <typename... Args>
void resubscriber<Args...>::do_invoke(Args... args)
{
    // Critical Section (prevent concurrent handler execution)
    ///////////////////////////////////////////////////////////////////////////
    unique_lock lock(invoke_mutex_);

    // Critical Section (protect stop)
    ///////////////////////////////////////////////////////////////////////////
    subscribe_mutex_.lock();

    // Move subscribers from the member list to a temporary list.
    list subscriptions;
    std::swap(subscriptions, subscriptions_);

    subscribe_mutex_.unlock();
    ///////////////////////////////////////////////////////////////////////////

    // Subscriptions may be created while this loop is executing.
    // Invoke subscribers from temporary list and resubscribe as indicated.
    for (auto const& handler: subscriptions)
    {
        //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        // DEADLOCK RISK, handler must not return to invoke.
        //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        if (handler(args...))
        {
            // Critical Section
            ///////////////////////////////////////////////////////////////////
            subscribe_mutex_.lock_upgrade();

            if (stopped_)
            {
                subscribe_mutex_.unlock_upgrade();
                //-------------------------------------------------------------
                continue;
            }

            subscribe_mutex_.unlock_upgrade_and_lock();
            //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
            subscriptions_.push_back(handler);

            subscribe_mutex_.unlock();
            ///////////////////////////////////////////////////////////////////
        }
    }

    ///////////////////////////////////////////////////////////////////////////
}

} // namespace libbitcoin

#endif
