// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <yaul/variant/variant_find.hpp>
#include <yaul/variant/test_config.hpp>

using yaul::variant_find;
using yaul::variant;

static_assert(variant_find<int, variant<int> >::value == 0ul,"");
static_assert(variant_find<int, variant<char, int, void> >::value == 1ul,"");
static_assert(variant_find<int, variant<char, float, int> >::value == 2ul,"");
static_assert(variant_find<int, variant<char> >::value == 1ul,"");
static_assert(variant_find<int, variant<char,float> >::value == 2ul,"");

int main()
{
  return YAUL_VARIANT_TEST_EXIT_CODE;
}
