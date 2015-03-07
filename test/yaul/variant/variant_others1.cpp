// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <yaul/variant/variant.hpp>
#include <yaul/variant/test_config.hpp>
#include <typeindex>

void test__empty__01()
{
  yaul::variant<int,char,float> v;
  YAUL_VARIANT_CHECK(!v.empty());
  v = 10;
  YAUL_VARIANT_CHECK(!v.empty());
}

void test__type__01()
{
  yaul::variant<int,char,float> v;
  YAUL_VARIANT_CHECK(std::type_index(v.type()) == std::type_index(typeid(int)));
  v = 'a';
  YAUL_VARIANT_CHECK(std::type_index(v.type()) == std::type_index(typeid(char)));
  v = 1.234f;
  YAUL_VARIANT_CHECK(std::type_index(v.type()) == std::type_index(typeid(float)));
}

int main()
{
  test__empty__01();
  test__type__01();
  return YAUL_VARIANT_TEST_EXIT_CODE;
}
