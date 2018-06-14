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
#ifndef LIBBITCOIN_INFRASTRUCTURE_DEFINE_HPP
#define LIBBITCOIN_INFRASTRUCTURE_DEFINE_HPP

#include <bitcoin/infrastructure/compat.hpp>
// Create bc namespace alias.
namespace libbitcoin {
} // namespace libbitcoin

namespace bc = libbitcoin;

// See http://gcc.gnu.org/wiki/Visibility

// Generic helper definitions for shared library support
#if defined _MSC_VER || defined __CYGWIN__
    #define BI_HELPER_DLL_IMPORT __declspec(dllimport)
    #define BI_HELPER_DLL_EXPORT __declspec(dllexport)
    #define BI_HELPER_DLL_LOCAL
#else
    #if __GNUC__ >= 4
        #define BI_HELPER_DLL_IMPORT __attribute__ ((visibility ("default")))
        #define BI_HELPER_DLL_EXPORT __attribute__ ((visibility ("default")))
        #define BI_HELPER_DLL_LOCAL  __attribute__ ((visibility ("internal")))
    #else
        #define BI_HELPER_DLL_IMPORT
        #define BI_HELPER_DLL_EXPORT
        #define BI_HELPER_DLL_LOCAL
    #endif
#endif

// Now we use the generic helper definitions above to define BI_API
// and BI_INTERNAL. BI_API is used for the public API symbols. It either DLL
// imports or DLL exports (or does nothing for static build) BI_INTERNAL is
// used for non-api symbols.

#if defined BI_STATIC
    #define BI_API
    #define BI_INTERNAL
#elif defined BI_DLL
    #define BI_API      BI_HELPER_DLL_EXPORT
    #define BI_INTERNAL BI_HELPER_DLL_LOCAL
#else
    #define BI_API      BI_HELPER_DLL_IMPORT
    #define BI_INTERNAL BI_HELPER_DLL_LOCAL
#endif

// Tag to deprecate functions and methods.
// Gives a compiler warning when they are used.
#if defined _MSC_VER || defined __CYGWIN__
    #define BI_DEPRECATED __declspec(deprecated)
#else
    #if __GNUC__ >= 4
        #define BI_DEPRECATED __attribute__((deprecated))
    #else
        #define BI_DEPRECATED
    #endif
#endif

// Avoid namespace conflict between boost::placeholders and std::placeholders.
#define BOOST_BIND_NO_PLACEHOLDERS

// Define so we can have better visibility of lcov exclusion ranges.
#define LCOV_EXCL_START(text)
#define LCOV_EXCL_STOP()

#endif
