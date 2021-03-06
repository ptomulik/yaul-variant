// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <yaul/variant/variant_fwd.hpp>
#include <yaul/variant/detail/variant_which.hpp>
#include <type_traits>

using yaul::detail::variant::variant_which;
using yaul::detail::variant::variant_which_t;
using yaul::variant;
using std::is_same;

static_assert(is_same< typename variant_which< variant<int> >::type, signed char>::value, "");
static_assert(is_same< variant_which_t< variant<int> >, signed char>::value, "");

struct S {};
static_assert(is_same< typename variant_which< variant<int,S> >::type, signed char>::value, "");
static_assert(is_same< variant_which_t< variant<int,S> >, signed char>::value, "");

int main()
{
  return 0;
}
