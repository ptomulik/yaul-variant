// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <yaul/variant/variant_contains.hpp>
#include <yaul/variant/test_config.hpp>

using yaul::variant_contains;
using yaul::variant;

static_assert( variant_contains<int, variant<int> >::value,"");
static_assert( variant_contains<int, variant<char, int, void> >::value,"");
static_assert( variant_contains<int, variant<char, float, int> >::value,"");
static_assert(!variant_contains<int, variant<char> >::value,"");
static_assert(!variant_contains<int, variant<char,float> >::value,"");

int main()
{
  return YAUL_VARIANT_TEST_EXIT_CODE;
}
