// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
#include <bitcoin/infrastructure/utility/interprocess_lock.hpp>

#include <memory>
#include <string>

#include <boost/filesystem.hpp>

#include <bitcoin/infrastructure/unicode/file_lock.hpp>
#include <bitcoin/infrastructure/unicode/ofstream.hpp>

namespace kth {

// static
bool interprocess_lock::create(std::string const& file)
{
    bc::ofstream stream(file);
    return stream.good();
}

// static
bool interprocess_lock::destroy(std::string const& file)
{
    return boost::filesystem::remove(file);
    ////std::remove(file.c_str());
}

interprocess_lock::interprocess_lock(path const& file)
  : file_(file.string())
{
}

interprocess_lock::~interprocess_lock()
{
    unlock();
}

// Lock is not idempotent, returns false if already locked.
// This succeeds if no other process has exclusive or sharable ownership.
bool interprocess_lock::lock()
{
    if ( ! create(file_)) {
        return false;
}

    lock_ = std::make_shared<lock_file>(file_);
    return lock_->try_lock();
}

// Unlock is idempotent, returns true if unlocked on return.
// This may leave the lock file behind, which is not a problem.
bool interprocess_lock::unlock()
{
    if ( ! lock_) {
        return true;
}

    lock_.reset();
    return destroy(file_);
}

} // namespace kth
