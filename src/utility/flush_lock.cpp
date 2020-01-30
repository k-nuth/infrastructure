// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
#include <bitcoin/infrastructure/utility/flush_lock.hpp>

#include <memory>

#include <boost/filesystem.hpp>

#include <bitcoin/infrastructure/unicode/file_lock.hpp>
#include <bitcoin/infrastructure/unicode/ifstream.hpp>
#include <bitcoin/infrastructure/unicode/ofstream.hpp>

namespace libbitcoin {

// static
bool flush_lock::create(std::string const& file)
{
    bc::ofstream stream(file);
    return stream.good();
}

// static
bool flush_lock::exists(std::string const& file)
{
    bc::ifstream stream(file);
    return stream.good();
    ////return boost::filesystem::exists(file);
}

// static
bool flush_lock::destroy(std::string const& file)
{
    return boost::filesystem::remove(file);
    ////std::remove(file.c_str());
}

flush_lock::flush_lock(path const& file)
  : file_(file.string()), locked_(false)
{
}

bool flush_lock::try_lock()
{
    return !exists(file_);
}

// Lock is idempotent, returns true if locked on return.
bool flush_lock::lock_shared()
{
    if (locked_) {
        return true;
}

    locked_ = create(file_);
    return locked_;
}

// Unlock is idempotent, returns true if unlocked on return.
bool flush_lock::unlock_shared()
{
    if ( ! locked_) {
        return true;
}

    locked_ = !destroy(file_);
    return !locked_;
}

} // namespace libbitcoin
