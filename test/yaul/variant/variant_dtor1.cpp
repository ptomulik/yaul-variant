// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <yaul/variant/variant.hpp>
#include <yaul/variant/test_config.hpp>
#include <type_traits>

//
// play around with variant destructor
//
void test__dtor__01()
{
  struct S
  {
    S(char& d) : d(d) { }
    ~S() { d = 'd'; }
    char& d;
  };

  char d;

  d = '?';
  {
    yaul::variant<S,int> v{S{d}};
    YAUL_VARIANT_CHECK_EQUALS(v.which(), 0);
  }
  YAUL_VARIANT_CHECK_EQUALS(d, 'd');

  d = '?';
  {
    yaul::variant<S,int> v{10};
    YAUL_VARIANT_CHECK_EQUALS(v.which(), 1);
  }
  YAUL_VARIANT_CHECK_EQUALS(d, '?');

  d = '?';
  {
    yaul::variant<int,S> v{S{d}};
    YAUL_VARIANT_CHECK_EQUALS(v.which(), 1);
  }
  YAUL_VARIANT_CHECK_EQUALS(d, 'd');
}

int main()
{
  test__dtor__01();
  return YAUL_VARIANT_TEST_EXIT_CODE;
}
