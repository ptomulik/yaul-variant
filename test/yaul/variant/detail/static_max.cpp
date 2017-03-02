// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <yaul/variant/detail/static_max.hpp>

using namespace yaul::detail::variant;

static_assert(static_max<1ul>::value == 1ul, "");
static_assert(static_max<2ul>::value == 2ul, "");
static_assert(static_max<0ul,2ul>::value == 2ul, "");
static_assert(static_max<0ul,2ul,1ul>::value == 2ul, "");
static_assert(static_max<0ul,6ul,4ul,8ul>::value == 8ul, "");

#include <type_traits>
static_assert(std::is_same<static_max<0ul,3ul>::type,std::integral_constant<std::size_t, 3ul> >::value, "");

int main()
{
  return 0;
}
