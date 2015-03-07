// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <yaul/variant/variant_type.hpp>
#include <type_traits>

using yaul::variant_type;
using yaul::variant;
using std::is_same;

static_assert(is_same<typename variant_type<0ul,variant<int> >::type, int>::value, "");
static_assert(is_same<typename variant_type<0ul,variant<int,char> >::type, int>::value, "");
static_assert(is_same<typename variant_type<1ul,variant<int,char> >::type, char>::value, "");

int main()
{
  return 0;
}
