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
#ifndef BITPRIM_INFRASTRUCTURE_LOG_FEATURES_METRIC_HPP
#define BITPRIM_INFRASTRUCTURE_LOG_FEATURES_METRIC_HPP

#include <boost/log/sources/features.hpp>
#include <boost/log/sources/threading_models.hpp>
#include <boost/log/utility/strictest_lock.hpp>

namespace libbitcoin {
namespace log {

namespace attributes {

BOOST_LOG_ATTRIBUTE_KEYWORD(metric, "Metric", std::string)

} // namespace attributes

namespace features {

template<typename BaseType>
class metric_feature
  : public BaseType
{
public:
    using char_type = typename BaseType::char_type;
    using threading_model = typename BaseType::threading_model;

    using metric_type = std::string;
    using metric_attribute = boost::log::attributes::mutable_constant<metric_type>;

    using open_record_lock = typename boost::log::strictest_lock<boost::lock_guard<threading_model> >::type;

    typedef typename boost::log::strictest_lock<
        typename BaseType::swap_lock,
        boost::log::aux::exclusive_lock_guard<threading_model>
    >::type swap_lock;

public:
    metric_feature();
    metric_feature(const metric_feature& other);

    template<typename Arguments>
    metric_feature(const Arguments& arguments);

    metric_type metric() const;
    void metric(const metric_type& value);

protected:
    const metric_attribute& get_metric_attribute() const;

    template<typename Arguments>
    boost::log::record open_record_unlocked(const Arguments& arguments);

    void swap_unlocked(metric_feature& other);

private:
    template<typename Arguments, typename Value>
    boost::log::record open_record_with_metric_unlocked(
        const Arguments& arguments, const Value& value);

    template<typename Arguments>
    boost::log::record open_record_with_metric_unlocked(
        const Arguments& arguments, boost::parameter::void_);

private:
    metric_attribute metric_attribute_;
};

struct metric
{
    template<typename BaseType>
    struct apply
    {
        using type = metric_feature<BaseType>;
    };
};

} // namespace features

namespace keywords {

BOOST_PARAMETER_KEYWORD(tag, metric)

} // namespace keywords

} // namespace log
} // namespace libbitcoin

#include <bitcoin/infrastructure/impl/log/features/metric.ipp>

#endif
