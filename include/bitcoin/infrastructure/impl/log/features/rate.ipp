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
#ifndef KNUTH_INFRASTRUCTURE_LOG_FEATURES_RATE_IPP
#define KNUTH_INFRASTRUCTURE_LOG_FEATURES_RATE_IPP

#include <boost/log/attributes.hpp>
#include <boost/scope_exit.hpp>

namespace kth {
namespace log {
namespace features {

template <typename BaseType>
rate_feature<BaseType>::rate_feature(const rate_feature& x)
    : BaseType(static_cast<const BaseType&>(x))
{}

template <typename BaseType>
template <typename Arguments>
rate_feature<BaseType>::rate_feature(Arguments const& arguments)
    : BaseType(arguments)
{}

template <typename BaseType>
template <typename Arguments>
boost::log::record rate_feature<BaseType>::open_record_unlocked(Arguments const& arguments) {
    auto& set = BaseType::attributes();
    auto tag = add_rate_unlocked(set,
        arguments[keywords::rate | boost::parameter::void_()]);

    BOOST_SCOPE_EXIT_TPL((&tag)(&set))
    {
        if (tag != set.end()) {
            set.erase(tag);
        }
    }
    BOOST_SCOPE_EXIT_END

    return BaseType::open_record_unlocked(arguments);
}

template <typename BaseType>
template <typename Value>
boost::log::attribute_set::iterator
    rate_feature<BaseType>::add_rate_unlocked(
    boost::log::attribute_set& set, const Value& value)
{
    auto tag = set.end();
    auto pair = BaseType::add_attribute_unlocked(attributes::rate_type::get_name(),
        boost::log::attributes::constant<float>(value));

    if (pair.second) {
        tag = pair.first;
    }

    return tag;
}

template <typename BaseType>
boost::log::attribute_set::iterator
rate_feature<BaseType>::add_rate_unlocked(boost::log::attribute_set& set, boost::parameter::void_ /*unused*/) {
    return set.end();
}

} // namespace features
} // namespace log
} // namespace kth

#endif
