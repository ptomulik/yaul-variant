// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <yaul/variant/detail/all_trivially_destructible.hpp>
#include <yaul/variant/test_config.hpp>

using yaul::detail::variant::all_trivially_destructible;

struct S1 {};
struct S2 { ~S2() { } };

static_assert( all_trivially_destructible<>::value, "");
static_assert( all_trivially_destructible<int>::value, "");
static_assert( all_trivially_destructible<int, char>::value, "");
static_assert( all_trivially_destructible<int, char, float>::value, "");
static_assert( all_trivially_destructible<S1>::value, "");
static_assert( all_trivially_destructible<int, S1, char>::value, "");
static_assert(!all_trivially_destructible<S1, S2>::value, "");

int main()
{
  return YAUL_VARIANT_TEST_EXIT_CODE;
}
