// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <yaul/variant/detail/variadic_storage.hpp>
#include <yaul/variant/test_config.hpp>

using yaul::detail::variant::variadic_storage;
using yaul::detail::variant::in_place_index_t;

constexpr const in_place_index_t<0ul> _0{};

struct S1
{
};

struct S2
{
  static int count;
   S2() { ++count; }
  ~S2() { --count; }
};
int S2::count = 0;

void test__variadic_storage__with_S2()
{
  const int count = S2::count;
  {
    variadic_storage<S2> s{_0};
    YAUL_VARIANT_CHECK_EQUALS(s.index(), 0);
    YAUL_VARIANT_CHECK_EQUALS(S2::count, count+1);
  }
  YAUL_VARIANT_CHECK_EQUALS(S2::count, count);
}

void test__variadic_storage__with_S1S2()
{
  const int count = S2::count;
  {
    variadic_storage<S1,S2> s{_0};
    YAUL_VARIANT_CHECK_EQUALS(s.index(), 0);
    YAUL_VARIANT_CHECK_EQUALS(S2::count, count);
  }
  YAUL_VARIANT_CHECK_EQUALS(S2::count, count);
}

int main()
{
  test__variadic_storage__with_S1S2();
  return YAUL_VARIANT_TEST_EXIT_CODE;
}
