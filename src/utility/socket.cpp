// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
#include <bitcoin/infrastructure/utility/socket.hpp>

#include <memory>

#include <bitcoin/infrastructure/config/authority.hpp>
#include <bitcoin/infrastructure/utility/asio.hpp>
#include <bitcoin/infrastructure/utility/thread.hpp>
#include <bitcoin/infrastructure/utility/threadpool.hpp>

namespace libbitcoin {

socket::socket(threadpool& thread)
  : thread_(thread),
    socket_(thread_.service())
    /*, CONSTRUCT_TRACK(socket) */
{
}

config::authority socket::authority() const
{
    boost_code ec;

    ///////////////////////////////////////////////////////////////////////////
    // Critical Section.
    mutex_.lock_shared();

    auto const endpoint = socket_.remote_endpoint(ec);

    mutex_.unlock_shared();
    ///////////////////////////////////////////////////////////////////////////

    return ec ? config::authority() : config::authority(endpoint);
}

asio::socket& socket::get()
{
    ///////////////////////////////////////////////////////////////////////////
    // Critical Section.
    shared_lock lock(mutex_);

    return socket_;
    ///////////////////////////////////////////////////////////////////////////
}

void socket::stop()
{
    // Handling socket error codes creates exception safety.
    boost_code ignore;

    ///////////////////////////////////////////////////////////////////////////
    // Critical Section.
    unique_lock lock(mutex_);

    // Signal the end of oustanding async socket functions (read).
    socket_.shutdown(asio::socket::shutdown_both, ignore);

    // BUGBUG: this is documented to fail on Windows XP and Server 2003.
    // DO NOT CLOSE SOCKET, IT TERMINATES WORK IMMEDIATELY RESULTING IN LEAKS
    socket_.cancel(ignore);
    ///////////////////////////////////////////////////////////////////////////
}

} // namespace libbitcoin
