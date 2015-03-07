// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <yaul/variant/variant.hpp>
#include <yaul/variant/test_config.hpp>

//
// play with default constructibility of bounded types
//
void test__ctors__01()
{
  // int is default constructible, so variant<int> should also be
  yaul::variant<int> v;
  YAUL_VARIANT_CHECK_EQUALS(v.which(), 0);
}

void test__ctors__02()
{
  // T0 is default constructible, so variant<T0> should also be
  struct T0 {};
  yaul::variant<T0> v;
  YAUL_VARIANT_CHECK_EQUALS(v.which(), 0);
}

void test__ctors__03()
{
  // T0 is default constructible, so variant<T0,T1> should also be (for any T1)
  struct T0 {};
  struct T1 { T1() = delete; };
  yaul::variant<T0,T1> v;
  YAUL_VARIANT_CHECK_EQUALS(v.which(), 0);
}

void test__ctors__04()
{
  // T0 is not default constructible, so variant<T0,T1> is also not default
  // constructible (for any T1); however, we should still be able to initialize
  // variant<T0,T1> from any of the bounded types.
  struct T0 { T0() = delete; T0(int) {} };
  struct T1 {};
  yaul::variant<T0,T1> v0{T0{0}};
  yaul::variant<T0,T1> v1{T1{}};
  YAUL_VARIANT_CHECK_EQUALS(v0.which(), 0);
  YAUL_VARIANT_CHECK_EQUALS(v1.which(), 1);
}

int main()
{
  test__ctors__01();
  test__ctors__02();
  test__ctors__03();
  test__ctors__04();
  return YAUL_VARIANT_TEST_EXIT_CODE;
}
