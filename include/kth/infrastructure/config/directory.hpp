// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_INFRASTUCTURE_CONFIG_DIRECTORY_HPP
#define KTH_INFRASTUCTURE_CONFIG_DIRECTORY_HPP

#include <filesystem>
#include <string>

// #include <boost/filesystem.hpp>

#include <kth/infrastructure/define.hpp>

namespace kth::infrastructure::config {

static 
std::filesystem::path config_default_path() {
    const std::filesystem::path folder;
    return folder;
}

//// Declare config_default_path() via KI_DECLARE_CONFIG_DEFAULT_PATH(relative).
//#define CONFIG_DEFAULT_PATH(directory, subdirectory) \
//    static std::filesystem::path config_default_path() \
//    { \
//        const std::filesystem::path folder(directory); \
//        return folder / subdirectory; \
//    }
//
//// The SYSCONFDIR symbol must be defined at compile for the project.
//// Therefore this must be compiled directly into the relevant project(s).
//#ifdef _MSC_VER
//    #define KI_DECLARE_CONFIG_DEFAULT_PATH(relative) \
//        CONFIG_DEFAULT_PATH(kth::infrastructure::config::windows_config_directory(), relative)
//#else
//    #define KI_DECLARE_CONFIG_DEFAULT_PATH(relative) \
//        CONFIG_DEFAULT_PATH(SYSCONFDIR, relative)
//#endif
//
///**
// * Get the windows configuration directory.
// * @return Path or empty string if unable to retrieve.
// */
//KI_API std::string windows_config_directory();

} // namespace kth::infrastructure::config

#endif
