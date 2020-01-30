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
#ifndef KNUTH_INFRASTRUCTURE_SOCKET_HPP
#define KNUTH_INFRASTRUCTURE_SOCKET_HPP

#include <memory>

#include <bitcoin/infrastructure/config/authority.hpp>
#include <bitcoin/infrastructure/define.hpp>
#include <bitcoin/infrastructure/error.hpp>
#include <bitcoin/infrastructure/utility/asio.hpp>
#include <bitcoin/infrastructure/utility/noncopyable.hpp>
#include <bitcoin/infrastructure/utility/thread.hpp>
#include <bitcoin/infrastructure/utility/threadpool.hpp>

namespace kth {

/// This class is thread safe but the socket may not be used concurrently.
class BI_API socket
    : noncopyable
    /*, public track<socket>*/
{
public:
    using ptr = std::shared_ptr<socket>;

    /// Construct an instance.
    explicit
    socket(threadpool& thread);

    /// Obtain the authority of the remote endpoint.
    config::authority authority() const;

    /// The underlying socket.
    asio::socket& get();

    /// Signal cancel of all outstanding work on the socket.
    void stop();

private:
    // This is thread safe.
    threadpool& thread_;

    // This is protected by mutex.
    asio::socket socket_;
    mutable shared_mutex mutex_;
};

} // namespace libbitcoin

#endif
