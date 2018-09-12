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
#ifndef BITPRIM_INFRASTRUCTURE_COMPAT_HPP
#define BITPRIM_INFRASTRUCTURE_COMPAT_HPP

#include <cstdint>
#include <limits>

// CTP_Nov2013 implements noexcept but unfortunately VC12 and CTP_Nov2013
// both identify as _MSC_VER = 1800, otherwise we could include CTP_Nov2013.
#if defined(_MSC_VER) && (_MSC_VER <= 1800)
    #define BI_NOEXCEPT _NOEXCEPT
    #define BI_CONSTEXPR const
    #define BI_CONSTFUNC inline
    #define BI_CONSTCTOR
#else
    #define BI_NOEXCEPT noexcept
    #define BI_CONSTEXPR constexpr
    #define BI_CONSTFUNC constexpr
    #define BI_CONSTCTOR constexpr
#endif

// TODO: prefix names with BI_
#ifdef _MSC_VER
    #define MIN_INT64 INT64_MIN
    #define MAX_INT64 INT64_MAX
    #define MIN_INT32 INT32_MIN
    #define MAX_INT32 INT32_MAX
    #define MAX_UINT64 UINT64_MAX
    #define MAX_UINT32 UINT32_MAX
    #define MAX_UINT16 UINT16_MAX
    #define MAX_UINT8 UINT8_MAX
    #define BI_MAX_SIZE SIZE_MAX
#else
    #define MIN_INT64 std::numeric_limits<int64_t>::min()
    #define MAX_INT64 std::numeric_limits<int64_t>::max()
    #define MIN_INT32 std::numeric_limits<int32_t>::min()
    #define MAX_INT32 std::numeric_limits<int32_t>::max()
    #define MAX_UINT64 std::numeric_limits<uint64_t>::max()
    #define MAX_UINT32 std::numeric_limits<uint32_t>::max()
    #define MAX_UINT16 std::numeric_limits<uint16_t>::max()
    #define MAX_UINT8 std::numeric_limits<uint8_t>::max()
    #define BI_MAX_SIZE std::numeric_limits<size_t>::max()
#endif

#endif
