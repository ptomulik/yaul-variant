// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <yaul/variant/variant.hpp>
#include <yaul/variant/test_config.hpp>

struct CtorTester
  {
    int which;
    CtorTester()                  : which(0) { }
    CtorTester(CtorTester&)       : which(1) { }
    CtorTester(CtorTester const&) : which(2) { }
    CtorTester(CtorTester&&)      : which(3) { }
  };

void test__dflt_ctors__1()
{
  struct S1 {} ;
  struct S2 { S2() = delete; };
  {
    yaul::variant<int> v;
    YAUL_VARIANT_CHECK_EQUALS(v.which(), 0);
  }
  {
    yaul::variant<int, char, float> v;
    YAUL_VARIANT_CHECK_EQUALS(v.which(), 0);
  }
  {
    yaul::variant<S1, S2, int> v;
    YAUL_VARIANT_CHECK_EQUALS(v.which(), 0);
  }
  {
    yaul::variant<CtorTester, S1, S2> v;
    YAUL_VARIANT_CHECK_EQUALS(v.which(), 0);
    // YAUL_VARIANT_CHECK_EQUALS(yaul::get<0>(v).which, 0);
  }
}

void test__lref_ctors__1()
{
  struct S1 {};
  struct S2 { S2(S2&) = delete; S2() = default; };
  {
    int  i;
    int& r = i; 
    yaul::variant<int> v(r);
    YAUL_VARIANT_CHECK_EQUALS(v.which(), 0);
  }
  {
    int  i;
    int& r = i; 
    yaul::variant<char, int, float> v(r);
    YAUL_VARIANT_CHECK_EQUALS(v.which(), 1);
  }
  {
    S1 s;
    S1& r = s;
    yaul::variant<char, S1, S2> v(r);
    YAUL_VARIANT_CHECK_EQUALS(v.which(), 1);
  }
  {
    CtorTester s;
    CtorTester& r = s;
    yaul::variant<char, S1, S2, CtorTester> v(r);
    YAUL_VARIANT_CHECK_EQUALS(v.which(), 3);
    // YAUL_VARIANT_CHECK_EQUALS(yaul::get<3>(v).which, 1);
  }
}

void test__cref_ctors__1()
{
  struct S1 {};
  struct S2 { S2(S2 const&) = delete; S2() = default; };
  {
    int  i;
    int const& r = i; 
    yaul::variant<int> v(r);
    YAUL_VARIANT_CHECK_EQUALS(v.which(), 0);
  }
  {
    int  i;
    int const& r = i; 
    yaul::variant<char, int, float> v(r);
    YAUL_VARIANT_CHECK_EQUALS(v.which(), 1);
  }
  {
    S1 s;
    S1 const& r = s;
    yaul::variant<char, S1, S2> v(r);
    YAUL_VARIANT_CHECK_EQUALS(v.which(), 1);
  }
  {
    CtorTester s;
    CtorTester const& r = s;
    yaul::variant<char, S1, S2, CtorTester> v(r);
    YAUL_VARIANT_CHECK_EQUALS(v.which(), 3);
    // YAUL_VARIANT_CHECK_EQUALS(yaul::get<3>(v).which, 2);
  }
}

void test__rref_ctors__1()
{
  struct S1 {};
  struct S2 { S2(S2&&) = delete; S2() = default; };
  {
    yaul::variant<int> v(10);
    YAUL_VARIANT_CHECK_EQUALS(v.which(), 0);
  }
  {
    yaul::variant<char, int, float> v(10);
    YAUL_VARIANT_CHECK_EQUALS(v.which(), 1);
  }
  {
    yaul::variant<char, S1, S2> v{S1()};
    YAUL_VARIANT_CHECK_EQUALS(v.which(), 1);
  }
  {
    yaul::variant<char, S1, S2, CtorTester> v{CtorTester()};
    YAUL_VARIANT_CHECK_EQUALS(v.which(), 3);
    // YAUL_VARIANT_CHECK_EQUALS(yaul::get<3>().which, 3);
  }
}

void test__cref_assign__1()
{
  {
    int   _11   = 11; int const&  _11_r = _11;

    yaul::variant<int> v(10);
    YAUL_VARIANT_CHECK_EQUALS(v.which(), 0);
    v = _11_r;
    YAUL_VARIANT_CHECK_EQUALS(v.which(), 0);
  }
  {
    char  _b      = 'b';    char const&   _b_r      = _b;
    int   _11     = 11;     int const&    _11_r     = _11;
    float _1_23f  = 1.23f;  float const&  _1_23f_r  = _1_23f;
    yaul::variant<char, int, float> v('a');
    YAUL_VARIANT_CHECK_EQUALS(v.which(), 0);
    v = _b_r;
    YAUL_VARIANT_CHECK_EQUALS(v.which(), 0);
    v = _11_r;
    YAUL_VARIANT_CHECK_EQUALS(v.which(), 1);
    v = _1_23f_r;
    YAUL_VARIANT_CHECK_EQUALS(v.which(), 2);
  }
}

int main()
{
  // constructors
  test__dflt_ctors__1();
  test__lref_ctors__1();
  test__cref_ctors__1();
  test__rref_ctors__1();
  // assignment
  test__cref_assign__1();
  return YAUL_VARIANT_TEST_EXIT_CODE;
}
