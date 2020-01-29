/**
 * Copyright (c) 2016-2020 Knuth Project.
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
#include <bitcoin/infrastructure/utility/deadline.hpp>

#include <functional>

#include <bitcoin/infrastructure/error.hpp>
#include <bitcoin/infrastructure/utility/asio.hpp>
#include <bitcoin/infrastructure/utility/thread.hpp>
#include <bitcoin/infrastructure/utility/threadpool.hpp>
#include <utility>

namespace libbitcoin {

using std::placeholders::_1;

// The timer closure captures an instance of this class and the callback.
// Deadline is guaranteed to call handler exactly once unless canceled/reset.

deadline::deadline(threadpool& pool)
    : duration_(asio::seconds(0))
    , timer_(pool.service())
    /*, CONSTRUCT_TRACK(deadline)*/
{}

deadline::deadline(threadpool& pool, asio::duration duration)
    : duration_(duration)
    , timer_(pool.service())
    /*, CONSTRUCT_TRACK(deadline)*/
{}

void deadline::start(handler handle) {
    start(std::move(handle), duration_);
}

void deadline::start(handler handle, asio::duration duration) {
    auto const timer_handler = std::bind(&deadline::handle_timer, shared_from_this(), _1, handle);

    // Critical Section
    ///////////////////////////////////////////////////////////////////////////
    unique_lock lock(mutex_);

    // Handling socket error codes creates exception safety.
    boost_code ignore;
    timer_.cancel(ignore);
    timer_.expires_from_now(duration);

    // async_wait will not invoke the handler within this function.
    timer_.async_wait(timer_handler);
    ///////////////////////////////////////////////////////////////////////////
}

// Cancellation calls handle_timer with asio::error::operation_aborted.
// We do not handle the cancelation result code, which will return success
// in the case of a race in which the timer is already canceled.
void deadline::stop() {
    // Critical Section
    ///////////////////////////////////////////////////////////////////////////
    unique_lock lock(mutex_);

    // Handling socket error codes creates exception safety.
    boost_code ignore;
    timer_.cancel(ignore);
    ///////////////////////////////////////////////////////////////////////////
}

// If the timer expires the callback is fired with a success code.
// If the timer fails the callback is fired with the normalized error code.
// If the timer is canceled no call is made.
void deadline::handle_timer(const boost_code& ec, handler const& handle) const {
    if ( ! ec) {
        handle(error::success);
    } else if (ec != asio::error::operation_aborted) {
        handle(error::boost_to_error_code(ec));
    }
}

} // namespace libbitcoin
