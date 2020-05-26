// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <sstream>
#include <boost/program_options.hpp>
#include <boost/test/unit_test.hpp>
#include <kth/infrastructure.hpp>

using namespace kth;
using namespace kth::infrastructure::config;
using namespace boost::program_options;

BOOST_AUTO_TEST_SUITE(endpoint_tests)

// ------------------------------------------------------------------------- //

BOOST_AUTO_TEST_SUITE(endpoint__construct)

BOOST_AUTO_TEST_CASE(endpoint__construct__empty__throws_invalid_option)
{
    BOOST_REQUIRE_THROW(endpoint url(""), invalid_option_value);
}

BOOST_AUTO_TEST_CASE(endpoint__construct__no_host__throws_invalid_option_value)
{
    BOOST_REQUIRE_THROW(endpoint host("tcp://"), invalid_option_value);
}

BOOST_AUTO_TEST_CASE(endpoint__construct__port_only__throws_invalid_option_value)
{
    BOOST_REQUIRE_THROW(endpoint host(":42"), invalid_option_value);
}

BOOST_AUTO_TEST_CASE(endpoint__construct__default__localhost)
{
    endpoint host;
    BOOST_REQUIRE_EQUAL(host.scheme(), "");
    BOOST_REQUIRE_EQUAL(host.host(), "localhost");
    BOOST_REQUIRE_EQUAL(host.port(), 0u);
}

BOOST_AUTO_TEST_CASE(endpoint__construct__host__expected_values)
{
    endpoint host("foo");
    BOOST_REQUIRE_EQUAL(host.scheme(), "");
    BOOST_REQUIRE_EQUAL(host.host(), "foo");
    BOOST_REQUIRE_EQUAL(host.port(), 0u);
}

BOOST_AUTO_TEST_CASE(endpoint__construct__host_port__expected_values)
{
    endpoint endpoint("foo.bar:42");
    BOOST_REQUIRE_EQUAL(endpoint.scheme(), "");
    BOOST_REQUIRE_EQUAL(endpoint.host(), "foo.bar");
    BOOST_REQUIRE_EQUAL(endpoint.port(), 42u);
}

BOOST_AUTO_TEST_CASE(endpoint__construct__scheme_host_port__expected_values)
{
    endpoint host("tcp://foo.bar:42");
    BOOST_REQUIRE_EQUAL(host.scheme(), "tcp");
    BOOST_REQUIRE_EQUAL(host.host(), "foo.bar");
    BOOST_REQUIRE_EQUAL(host.port(), 42u);
}

BOOST_AUTO_TEST_CASE(endpoint__construct__scheme_host__expected_values)
{
    endpoint host("tcp://foo.bar");
    BOOST_REQUIRE_EQUAL(host.scheme(), "tcp");
    BOOST_REQUIRE_EQUAL(host.host(), "foo.bar");
    BOOST_REQUIRE_EQUAL(host.port(), 0u);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()
