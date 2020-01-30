/**
 * Copyright (c) 2016-2020 Knuth Project.
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
#ifndef KNUTH_INFRASTRUCTURE_MESSAGE_TOOLS_HPP_
#define KNUTH_INFRASTRUCTURE_MESSAGE_TOOLS_HPP_

#include <cstddef>
#include <cstdint>

#include <bitcoin/infrastructure/define.hpp>

namespace kth { 
namespace message {

BI_API size_t variable_uint_size(uint64_t value);

} // namespace message
} // namespace kth

#endif // KNUTH_INFRASTRUCTURE_MESSAGE_TOOLS_HPP_
