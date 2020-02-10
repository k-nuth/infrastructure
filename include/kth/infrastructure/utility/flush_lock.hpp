// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
#ifndef KTH_INFRASTRUCTURE_CRASH_LOCK_HPP
#define KTH_INFRASTRUCTURE_CRASH_LOCK_HPP

#include <memory>

#include <boost/filesystem.hpp>

#include <kth/infrastructure/define.hpp>
#include <kth/infrastructure/unicode/file_lock.hpp>

namespace kth {

/// This class is not thread safe.
/// Guard a resource that may be corrupted due to an interrupted write.
class BI_API flush_lock
{
public:
    using path = boost::filesystem::path;

    explicit
    flush_lock(path const& file);

    bool try_lock();
    bool lock_shared();
    bool unlock_shared();

private:
    static bool create(std::string const& file);
    static bool exists(std::string const& file);
    static bool destroy(std::string const& file);

    bool locked_;
    std::string const file_;
};

} // namespace kth

#endif
