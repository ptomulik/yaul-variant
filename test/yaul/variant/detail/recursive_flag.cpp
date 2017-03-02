// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <yaul/variant/detail/recursive_flag.hpp>
#include <yaul/variant/test_config.hpp>
#include <type_traits>

using yaul::detail::variant::recursive_flag;
using yaul::detail::variant::remove_recursive_flag;

static_assert(std::is_same<remove_recursive_flag<int>::type, int>::value, "");
static_assert(std::is_same<remove_recursive_flag<recursive_flag<int> >::type, int>::value, "");

// CV-qualifiers are not interesting
static_assert(std::is_same<remove_recursive_flag<recursive_flag<int> const>::type, recursive_flag<int> const>::value, "");
static_assert(std::is_same<remove_recursive_flag<recursive_flag<int> volatile>::type, recursive_flag<int> volatile>::value, "");
static_assert(std::is_same<remove_recursive_flag<recursive_flag<int> const volatile>::type, recursive_flag<int> const volatile>::value, "");

int main()
{
  return YAUL_VARIANT_TEST_EXIT_CODE;
}
