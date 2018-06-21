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
#include <bitcoin/infrastructure/utility/sequencer.hpp>

#include <utility>
#include <bitcoin/infrastructure/utility/asio.hpp>
#include <bitcoin/infrastructure/utility/assert.hpp>
#include <bitcoin/infrastructure/utility/thread.hpp>

namespace libbitcoin {

sequencer::sequencer(asio::service& service)
  : service_(service), executing_(false)
{
}

sequencer::~sequencer()
{
    BITCOIN_ASSERT_MSG(actions_.empty(), "sequencer not cleared");
}

// void sequencer::lock(action&& handler)
// {
//     auto post = false;

//     // Critical Section
//     ///////////////////////////////////////////////////////////////////////
//     mutex_.lock();

//     if (executing_)
//     {
//         actions_.push(std::move(handler));
//     }
//     else
//     {
//         post = true;
//         executing_ = true;
//     }

//     mutex_.unlock();
//     ///////////////////////////////////////////////////////////////////////

//     if (post)
//         service_.post(std::move(handler));
// }

void sequencer::lock(action&& handler)
{
    // Critical Section
    ///////////////////////////////////////////////////////////////////////
    {
    guard lock(mutex_);

    if (executing_)
    {
        actions_.push(std::move(handler));
        return;
    }

    executing_ = true;
    } 
    ///////////////////////////////////////////////////////////////////////

    service_.post(std::move(handler));
}
// void sequencer::unlock()
// {
//     action handler;

//     // Critical Section
//     ///////////////////////////////////////////////////////////////////////
//     mutex_.lock();

//     BITCOIN_ASSERT_MSG(executing_, "called unlock but sequence not locked");

//     if (actions_.empty())
//     {
//         executing_ = false;
//     }
//     else
//     {
//         executing_ = true;
//         std::swap(handler, actions_.front());
//         actions_.pop();
//     }

//     mutex_.unlock();
//     ///////////////////////////////////////////////////////////////////////

//     if (handler)
//         service_.post(std::move(handler));
// }

void sequencer::unlock()
{
    action handler;

    // Critical Section
    ///////////////////////////////////////////////////////////////////////
    {
    guard lock(mutex_);

    BITCOIN_ASSERT_MSG(executing_, "called unlock but sequence not locked");

    if (actions_.empty())
    {
        executing_ = false;
    }
    else
    {
        executing_ = true;
        std::swap(handler, actions_.front());
        actions_.pop();
    }

    }
    ///////////////////////////////////////////////////////////////////////

    if (handler)
        service_.post(std::move(handler));
}

} // namespace libbitcoin
