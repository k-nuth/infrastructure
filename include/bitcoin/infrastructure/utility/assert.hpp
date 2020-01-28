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
#ifndef KNUTH_INFRASTRUCTURE_ASSERT_HPP
#define KNUTH_INFRASTRUCTURE_ASSERT_HPP

#ifdef NDEBUG
    #define BITCOIN_ASSERT(expression)
    #define BITCOIN_ASSERT_MSG(expression, text)
    #define DEBUG_ONLY(expression)
#else
    #include <cassert>
    #define BITCOIN_ASSERT(expression) assert(expression)
    #define BITCOIN_ASSERT_MSG(expression, text) assert((expression)&&(text))
    #define DEBUG_ONLY(expression) expression
#endif

// This is used to prevent bogus compiler warnings about unused variables.
#define UNUSED(expression) (void)(expression)

#endif
