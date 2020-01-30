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
#ifndef KTH_INFRASTRUCTURE_COLLECTION_HPP
#define KTH_INFRASTRUCTURE_COLLECTION_HPP

#include <iostream>
#include <iterator>
#include <vector>

#include <bitcoin/infrastructure/define.hpp>

/* NOTE: don't declare 'using namespace foo' in headers. */

namespace libbitcoin {

#define BI_SENTENCE_DELIMITER " "

/**
 * Cast vector/enumerable elements into a new vector.
 * @param      <Source>  The source element type.
 * @param      <Target>  The target element type.
 * @param[in]  source    The enumeration of Source elements to cast.
 * @returns              A new enumeration with elements cast to Target.
 */
template <typename Source, typename Target>
std::vector<Target> cast(std::vector<Source> const& source);

/**
 * Obtain the sorted distinct elements of the list.
 * @param      <T>        The list element type.
 * @param[in]  list       The list.
 * @return                The sorted list reduced to its distinct elements.
 */
template <typename T>
std::vector<T>& distinct(std::vector<T>& list);

/**
 * Find the position of a pair in an ordered list.
 * @param      <Pair>  The type of list member elements.
 * @param[in]  list    The list to search.
 * @param[in]  key     The key to the element to find.
 * @return             The position or -1 if not found.
 */
template <typename Pair, typename Key>
int find_pair_position(std::vector<Pair const> const& list, Key& key);

/**
 * Find the position of an element in an ordered list.
 * @param      <T>        The type of list member elements.
 * @param[in]  list       The list to search.
 * @param[in]  value      The value of the element to find.
 * @return                The position or -1 if not found.
 */
template <typename T, typename Container>
int find_position(Container const& list, T const& value);

/**
 * Facilitate a list insertion sort by inserting into a sorted position.
 * @param      <T>          The type of list member elements.
 * @param      <Predicate>  The sort predicate function signature.
 * @param[in]  list         The list to modify.
 * @param[in]  element      The element to insert.
 * @param[in]  predicate    The sort predicate.
 * @return                  The vector iterator.
 */
template <typename T, typename Predicate>
typename std::vector<T>::iterator insert_sorted(std::vector<T>& list, T const& element, Predicate predicate);

/**
 * Move members of a source list to end of a target list. Source is cleared.
 * @param      <T>        The type of list member elements.
 * @param[in]  target     The target list.
 * @param[in]  source     The source list
 */
template <typename T>
void move_append(std::vector<T>& target, std::vector<T>& source);

/**
 * Pop an element from the stack and return its value.
 * @param      <T>         The stack element type.
 * @param[in]  stack       The stack.
 */
template <typename T>
T pop(std::vector<T>& stack);

} // namespace libbitcoin

namespace std {

/**
 * Make vectors of serializable elements serializable to std::ostream.
 * @param      <T>     The type of list member elements.
 * @param[in]  output  The output stream to serialize to.
 * @param[in]  list    The list to serialize.
 * @return             The output stream.
 */
template <typename T>
std::ostream& operator<<(std::ostream& output, std::vector<T> const& list);

} // namespace std

#include <bitcoin/infrastructure/impl/utility/collection.ipp>

#endif
