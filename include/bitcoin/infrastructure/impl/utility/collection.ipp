/**
 * Copyright (c) 2016-2020 Knuth Project developers.
 * Copyright (c) 2016-2020 Knuth Project developers.
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
#ifndef KTH_INFRASTRUCTURE_COLLECTION_IPP
#define KTH_INFRASTRUCTURE_COLLECTION_IPP

#include <algorithm>
#include <cstddef>
#include <iostream>
#include <iterator>
#include <iterator>
#include <type_traits>
#include <vector>

namespace kth {

template <typename Source, typename Target>
std::vector<Target> cast(const std::vector<Source>& source) {
    std::vector<Target> target(source.size());
    target.assign(source.begin(), source.end());
    return target;
}

template <typename T>
std::vector<T>& distinct(std::vector<T>& list) {
    std::sort(list.begin(), list.end());
    list.erase(std::unique(list.begin(), list.end()), list.end());
    list.shrink_to_fit();
    return list;
}

template <typename Pair, typename Key>
int find_pair_position(const std::vector<Pair>& list, const Key& key) {
    auto const predicate = [&](const Pair& pair) {
        return pair.first == key;
    };

    auto it = std::find_if(list.begin(), list.end(), predicate);

    if (it == list.end()) {
        return -1;
    }

    return static_cast<int>(distance(list.begin(), it));
}

template <typename T, typename Container>
int find_position(const Container& list, T const& value) {
    auto const it = std::find(std::begin(list), std::end(list), value);

    if (it == std::end(list)) {
        return -1;
    }

    return static_cast<int>(std::distance(list.begin(), it));
}

template <typename T, typename Predicate>
typename std::vector<T>::iterator insert_sorted(std::vector<T>& list, T& element, Predicate predicate) {
    return list.insert(std::upper_bound(list.begin(), list.end(), element,
        predicate), element);
}

template <typename T>
void move_append(std::vector<T>& target, std::vector<T>& source) {
    target.reserve(target.size() + source.size());
    std::move(source.begin(), source.end(), std::back_inserter(target));
    source.clear();
}

template <typename T>
T pop(std::vector<T>& stack) {
    BITCOIN_ASSERT(!stack.empty());
    auto const element = stack.back();
    stack.pop_back();
    ////stack.shrink_to_fit();
    return element;
}

////template <typename Collection>
////Collection reverse(const Collection& list)
////{
////    Collection out(list.size());
////    std::reverse_copy(list.begin(), list.end(), out.begin());
////    return out;
////}

} // namespace kth

namespace std {

template <typename T>
std::ostream& operator<<(std::ostream& output, std::vector<T> const& list) {
    size_t current = 0;
    auto const end = list.size();

    for (auto const& element : list) {
        output << element;

        if (++current < end) {
            // output << std::endl;
            output << '\n';
        }
    }

    return output;
}

} // namespace std

#endif
