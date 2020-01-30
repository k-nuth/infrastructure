// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
#ifndef KTH_INFRASTRUCTURE_INTERPROCESS_LOCK_HPP
#define KTH_INFRASTRUCTURE_INTERPROCESS_LOCK_HPP

#include <memory>
#include <string>

#include <boost/filesystem.hpp>

#include <bitcoin/infrastructure/define.hpp>
#include <bitcoin/infrastructure/unicode/file_lock.hpp>

namespace kth {

/// This class is not thread safe.
/// Guard a resource againt concurrent use by another instance of this app.
class BI_API interprocess_lock
{
public:
    using path = boost::filesystem::path;

    explicit
    interprocess_lock(path const& file);
    
    ~interprocess_lock();

    bool lock();
    bool unlock();

private:
    using lock_file = interprocess::file_lock;
    using lock_ptr = std::shared_ptr<lock_file>;

    static bool create(std::string const& file);
    static bool destroy(std::string const& file);

    lock_ptr lock_;
    std::string const file_;
};

} // namespace kth

#endif
