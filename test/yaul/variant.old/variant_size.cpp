// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <yaul/variant/variant_size.hpp>
#include <type_traits>

using yaul::variant_size;
using yaul::variant;

static_assert(variant_size<variant<int> >::value == 1ul, "");
static_assert(variant_size<variant<int,char> >::value == 2ul, "");
static_assert(variant_size<variant<int,char,float> >::value == 3ul, "");

int main()
{
  return 0;
}
