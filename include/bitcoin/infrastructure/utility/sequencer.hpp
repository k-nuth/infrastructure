/**
 * Copyright (c) 2016-2019 Knuth Project.
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
#ifndef KNUTH_INFRASTRUCTURE_SEQUENCER_HPP
#define KNUTH_INFRASTRUCTURE_SEQUENCER_HPP

#include <functional>
#include <memory>
#include <queue>

#include <bitcoin/infrastructure/utility/asio.hpp>
#include <bitcoin/infrastructure/utility/enable_shared_from_base.hpp>
#include <bitcoin/infrastructure/utility/thread.hpp>
////#include <bitcoin/infrastructure/utility/track.hpp>

namespace libbitcoin {

class sequencer
    : public enable_shared_from_base<sequencer>
    /*, track<sequencer>*/
{
public:
    using ptr = std::shared_ptr<sequencer>;
    using action = std::function<void ()>;

    explicit
    sequencer(asio::service& service);

    ~sequencer();

    void lock(action&& handler);
    void unlock();

private:
    // This is thread safe.
    asio::service& service_;

    // These are protected by mutex.
    bool executing_;
    std::queue<action> actions_;
    mutable shared_mutex mutex_;
};

} // namespace libbitcoin

#endif
