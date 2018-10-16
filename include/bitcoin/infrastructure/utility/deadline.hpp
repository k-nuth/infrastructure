/**
 * Copyright (c) 2017-2018 Bitprim Inc.
 *
 * This file is part of Bitprim.
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
#ifndef BITPRIM_INFRASTRUCTURE_DEADLINE_HPP
#define BITPRIM_INFRASTRUCTURE_DEADLINE_HPP

#include <memory>

#include <bitcoin/infrastructure/define.hpp>
#include <bitcoin/infrastructure/error.hpp>
#include <bitcoin/infrastructure/utility/asio.hpp>
#include <bitcoin/infrastructure/utility/assert.hpp>
#include <bitcoin/infrastructure/utility/enable_shared_from_base.hpp>
#include <bitcoin/infrastructure/utility/noncopyable.hpp>
#include <bitcoin/infrastructure/utility/thread.hpp>
#include <bitcoin/infrastructure/utility/threadpool.hpp>
////#include <bitcoin/infrastructure/utility/track.hpp>

namespace libbitcoin {

/**
 * Class wrapper for boost::asio::deadline_timer, thread safe.
 * This simplifies invocation, eliminates boost-specific error handling and
 * makes timer firing and cancellation conditions safer.
 */
class BI_API deadline
    : public enable_shared_from_base<deadline>
    , noncopyable
    /*, track<deadline>*/
{
public:
    using ptr = std::shared_ptr<deadline>;
    using handler = std::function<void (const code &)>;

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
    void handle_timer(const boost_code& ec, handler handle) const;

    asio::timer timer_;
    asio::duration duration_;
    mutable shared_mutex mutex_;
};

} // namespace libbitcoin

#endif
