// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <yaul/variant/detail/variadic_index.hpp>
#include <yaul/variant/test_config.hpp>
#include <type_traits>

using yaul::detail::variant::variadic_index;
using yaul::detail::variant::variadic_index_t;

static_assert(std::is_same<variadic_index<>::type, signed char>::value, "");
static_assert(std::is_same<variadic_index<int>::type, signed char>::value, "");
static_assert(std::is_same<variadic_index<int,char>::type, signed char>::value, "");

static_assert(std::is_same<variadic_index_t<>, signed char>::value, "");
static_assert(std::is_same<variadic_index_t<int>, signed char>::value, "");
static_assert(std::is_same<variadic_index_t<int,char>, signed char>::value, "");

int main()
{
  return YAUL_VARIANT_TEST_EXIT_CODE;
}
