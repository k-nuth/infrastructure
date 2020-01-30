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
#ifndef KNUTH_INFRASTRUCTURE_LOG_FEATURES_COUNTER_HPP
#define KNUTH_INFRASTRUCTURE_LOG_FEATURES_COUNTER_HPP

#include <boost/log/sources/features.hpp>
#include <boost/log/sources/threading_models.hpp>
#include <boost/log/utility/strictest_lock.hpp>

namespace kth {
namespace log {

namespace attributes {

BOOST_LOG_ATTRIBUTE_KEYWORD(counter, "Counter", int64_t)

} // namespace attributes

namespace features {

template <typename BaseType>
class counter_feature : public BaseType
{
public:
    using char_type = typename BaseType::char_type;
    using threading_model = typename BaseType::threading_model;

public:
    counter_feature() = default;
    counter_feature(const counter_feature& x);

    template <typename Arguments>
    explicit
    counter_feature(Arguments const& arguments);

    using open_record_lock = typename boost::log::strictest_lock<
        boost::lock_guard<threading_model>,
        typename BaseType::open_record_lock,
        typename BaseType::add_attribute_lock,
        typename BaseType::remove_attribute_lock
    >::type;

protected:
    template <typename Arguments>
    boost::log::record open_record_unlocked(Arguments const& arguments);

private:
    template <typename Value>
    boost::log::attribute_set::iterator add_counter_unlocked(
        boost::log::attribute_set& set, const Value& value);

    boost::log::attribute_set::iterator add_counter_unlocked(
        boost::log::attribute_set& set, boost::parameter::void_ /*unused*/);
};

struct counter
{
    template <typename BaseType>
    struct apply
    {
        using type = counter_feature<BaseType>;
    };
};

} // namespace features

namespace keywords {

BOOST_PARAMETER_KEYWORD(tag, counter)

} // namespace keywords

} // namespace log
} // namespace kth

#include <bitcoin/infrastructure/impl/log/features/counter.ipp>

#endif
