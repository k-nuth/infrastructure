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
#ifndef BITPRIM_INFRASTRUCTURE_COMPAT_H
#define BITPRIM_INFRASTRUCTURE_COMPAT_H

#ifdef _MSC_VER
    /* There is no <endian.h> for MSVC but it is always little endian. */
    #ifndef __LITTLE_ENDIAN__
        # undef __BIG_ENDIAN__
        # define __LITTLE_ENDIAN__
    #endif
#endif

#ifdef _MSC_VER
    #define BI_C_INLINE __inline
#else
    #define BI_C_INLINE inline
#endif

#endif
