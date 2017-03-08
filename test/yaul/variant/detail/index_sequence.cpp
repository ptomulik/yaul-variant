// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <yaul/variant/detail/index_sequence.hpp>
#include <yaul/variant/test_config.hpp>
#include <type_traits>

using yaul::detail::variant::index_sequence;
using yaul::detail::variant::make_index_sequence;

static_assert(std::is_same<make_index_sequence<0>::type, index_sequence<> >::value, "");
static_assert(std::is_same<make_index_sequence<1>::type, index_sequence<0> >::value, "");
static_assert(std::is_same<make_index_sequence<2>::type, index_sequence<0,1> >::value, "");
static_assert(std::is_same<make_index_sequence<3>::type, index_sequence<0,1,2> >::value, "");
static_assert(std::is_same<make_index_sequence<4>::type, index_sequence<0,1,2,3> >::value, "");
static_assert(std::is_same<make_index_sequence<5>::type, index_sequence<0,1,2,3,4> >::value, "");

int main()
{
  return YAUL_VARIANT_TEST_EXIT_CODE;
}
