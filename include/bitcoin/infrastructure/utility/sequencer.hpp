// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
#ifndef KTH_INFRASTRUCTURE_SEQUENCER_HPP
#define KTH_INFRASTRUCTURE_SEQUENCER_HPP

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
