// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_INFRASTRUCTURE_DEADLINE_HPP
#define KTH_INFRASTRUCTURE_DEADLINE_HPP

#include <memory>

#include <kth/infrastructure/define.hpp>
#include <kth/infrastructure/error.hpp>
#include <kth/infrastructure/utility/asio.hpp>
#include <kth/infrastructure/utility/assert.hpp>
#include <kth/infrastructure/utility/enable_shared_from_base.hpp>
#include <kth/infrastructure/utility/noncopyable.hpp>
#include <kth/infrastructure/utility/thread.hpp>
#include <kth/infrastructure/utility/threadpool.hpp>
////#include <kth/infrastructure/utility/track.hpp>

namespace kth {

/**
 * Class wrapper for boost::asio::deadline_timer, thread safe.
 * This simplifies invocation, eliminates boost-specific error handling and
 * makes timer firing and cancellation conditions safer.
 */
class KI_API deadline
    : public enable_shared_from_base<deadline>
    , noncopyable
    /*, track<deadline>*/
{
public:
    using ptr = std::shared_ptr<deadline>;
    using handler = std::function<void (code const &)>;

    /**
     * Construct a deadline timer with a zero duration.
     * @param[in]  pool      The thread pool used by the timer.
     */
    explicit
    deadline(threadpool& pool);

    /**
     * Construct a deadline timer.
     * @param[in]  pool      The thread pool used by the timer.
     * @param[in]  duration  The default time period from start to expiration.
     */
    deadline(threadpool& pool, asio::duration duration);

    /**
     * Start or restart the timer.
     * The handler will not be invoked within the scope of this call.
     * Use expired(ec) in handler to test for expiration.
     * @param[in]  handle  Callback invoked upon expire or cancel.
     */
    void start(handler handle);

    /**
     * Start or restart the timer.
     * The handler will not be invoked within the scope of this call.
     * Use expired(ec) in handler to test for expiration.
     * @param[in]  handle    Callback invoked upon expire or cancel.
     * @param[in]  duration  The time period from start to expiration.
     */
    void start(handler handle, asio::duration duration);

    /**
     * Cancel the timer. The handler will be invoked.
     */
    void stop();

private:
    void handle_timer(const boost_code& ec, const handler& handle) const;

    asio::timer timer_;
    asio::duration duration_;
    mutable shared_mutex mutex_;
};

} // namespace kth

#endif
