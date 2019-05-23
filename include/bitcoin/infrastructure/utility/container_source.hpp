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
#ifndef KNUTH_INFRASTRUCTURE_CONTAINER_SOURCE_HPP
#define KNUTH_INFRASTRUCTURE_CONTAINER_SOURCE_HPP

#include <algorithm>
#include <cstddef>
#include <cstdint>

#include <boost/iostreams/stream.hpp>

#include <bitcoin/infrastructure/define.hpp>
#include <bitcoin/infrastructure/utility/data.hpp>
#include <bitcoin/infrastructure/utility/limits.hpp>

namespace libbitcoin {

// modified from boost.iostreams example
// boost.org/doc/libs/1_55_0/libs/iostreams/doc/tutorial/container_source.html
template <typename Container, typename SourceType, typename CharType>
class BI_API container_source {
public:
    using char_type = CharType;
    using category = boost::iostreams::source_tag;

    explicit
    container_source(const Container& container)
        : container_(container), position_(0)
    {
        static_assert(sizeof(SourceType) == sizeof(CharType), "invalid size");
    }

    std::streamsize read(char_type* buffer, std::streamsize size) {
        auto amount = safe_subtract(container_.size(), position_);
        auto result = std::min(size, static_cast<std::streamsize>(amount));

        // TODO: use ios eof symbol (template-based).
        if (result <= 0) {
            return -1;
        }

        auto const value = static_cast<typename Container::size_type>(result);
        std::copy_n(container_.begin() + position_, value, buffer);
        position_ += value;
        return result;
    }

private:
    const Container& container_;
    typename Container::size_type position_;
};

template <typename Container>
using byte_source = container_source<Container, uint8_t, char>;

template <typename Container>
using stream_source = boost::iostreams::stream<byte_source<Container>>;

using data_source = stream_source<data_chunk>;

} // namespace libbitcoin

#endif

