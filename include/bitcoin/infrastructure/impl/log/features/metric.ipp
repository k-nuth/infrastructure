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
#ifndef KNUTH_INFRASTRUCTURE_LOG_FEATURES_METRIC_IPP
#define KNUTH_INFRASTRUCTURE_LOG_FEATURES_METRIC_IPP

namespace libbitcoin {
namespace log {
namespace features {

template <typename BaseType>
metric_feature<BaseType>::metric_feature()
  : BaseType(), metric_attribute_(metric_type())
{
    BaseType::add_attribute_unlocked(attributes::metric_type::get_name(),
        metric_attribute_);
}

template <typename BaseType>
metric_feature<BaseType>::metric_feature(const metric_feature& x)
  : BaseType(static_cast<const BaseType&>(x)),
    metric_attribute_(x.metric_attribute_)
{
    BaseType::attributes()[attributes::metric_type::get_name()] = metric_attribute_;
}

template <typename BaseType>
template <typename Arguments>
metric_feature<BaseType>::metric_feature(Arguments const& arguments)
  : BaseType(arguments),
    metric_attribute_(arguments[keywords::metric || metric_type()])
{
    BaseType::add_attribute_unlocked(attributes::metric_type::get_name(),
        metric_attribute_);
}

template <typename BaseType>
typename metric_feature<BaseType>::metric_type
    metric_feature<BaseType>::metric() const
{
    BOOST_LOG_EXPR_IF_MT(boost::log::aux::shared_lock_guard<
        const threading_model> lock(this->get_threading_model());)

    return metric_attribute_.get();
}

template <typename BaseType>
void metric_feature<BaseType>::metric(const metric_type& value)
{
    BOOST_LOG_EXPR_IF_MT(boost::log::aux::exclusive_lock_guard<threading_model>
        lock(this->get_threading_model());)

    metric_attribute_.set(value);
}

template <typename BaseType>
const typename metric_feature<BaseType>::metric_attribute&
    metric_feature<BaseType>::get_metric_attribute() const
{
    return metric_attribute_;
}

template <typename BaseType>
template <typename Arguments>
boost::log::record metric_feature<BaseType>::open_record_unlocked(
    Arguments const& arguments)
{
    return open_record_with_metric_unlocked(arguments,
        arguments[keywords::metric | boost::parameter::void_()]);
}

template <typename BaseType>
void metric_feature<BaseType>::swap_unlocked(metric_feature& x)
{
    BaseType::swap_unlocked(static_cast<BaseType&>(x));
    metric_attribute_.swap(x.metric_attribute_);
}

template <typename BaseType>
template <typename Arguments, typename Value>
boost::log::record metric_feature<BaseType>::open_record_with_metric_unlocked(
    Arguments const& arguments, const Value& value)
{
    metric_attribute_.set(value);
    return BaseType::open_record_unlocked(arguments);
}

template <typename BaseType>
template <typename Arguments>
boost::log::record metric_feature<BaseType>::open_record_with_metric_unlocked(
    Arguments const& arguments, boost::parameter::void_ /*unused*/)
{
    return BaseType::open_record_unlocked(arguments);
}

} // namespace features
} // namespace log
} // namespace libbitcoin

#endif
