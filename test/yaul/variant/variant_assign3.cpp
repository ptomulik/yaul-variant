// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <yaul/variant/variant.hpp>
#include <yaul/variant/test_config.hpp>
#include <type_traits>

// test assignments from compatible (but not identical) variants

void test__assign__01()
{
  struct S { int x; };

  // operator=(variant&)
  {
    yaul::variant<double,S> v1{S{10}};
    YAUL_VARIANT_CHECK_EQUALS(v1.which(), 1);
    yaul::variant<double,int,S> v2;
    YAUL_VARIANT_CHECK_EQUALS(v2.which(), 0);
    v2 = v1;
    YAUL_VARIANT_CHECK_EQUALS(v2.which(), 2);
  }
  // operator=(variant const&)
  {
    yaul::variant<double,S> const v1{S{10}};
    YAUL_VARIANT_CHECK_EQUALS(v1.which(), 1);
    yaul::variant<double,int,S> v2;
    YAUL_VARIANT_CHECK_EQUALS(v2.which(), 0);
    v2 = v1;
    YAUL_VARIANT_CHECK_EQUALS(v2.which(), 2);
  }
  // operator=(variant&&)
  {
    yaul::variant<double,S> v1{S{10}};
    YAUL_VARIANT_CHECK_EQUALS(v1.which(), 1);
    yaul::variant<double,int,S> v2;
    YAUL_VARIANT_CHECK_EQUALS(v2.which(), 0);
    v2 = std::move(v1);
    YAUL_VARIANT_CHECK_EQUALS(v2.which(), 2);
  }
}

void test__assign__02()
{
  struct S
  {
    S() = default;
    S(S&) = default;
    S(S const&) = default;
    S(S&&) = default;
    S& operator=(S&) = default;
    S& operator=(S const&) = delete;
    S& operator=(S&&) = delete;
  };

  S ss;

  {
    yaul::variant<double,S> v1{ss};
    YAUL_VARIANT_CHECK_EQUALS(v1.which(), 1);
    yaul::variant<int,double,S> v2;
    YAUL_VARIANT_CHECK_EQUALS(v2.which(), 0);
    v2 = v1;
    YAUL_VARIANT_CHECK_EQUALS(v2.which(), 2);
  }
}

void test__assign__03()
{
  struct S
  {
    S() = default;
    S(S&) = default;
    S(S const&) = default;
    S(S&&) = default;
    S& operator=(S&) = delete;
    S& operator=(S const&) = default;
    S& operator=(S&&) = delete;
  };

  S const ss{};

  {
    yaul::variant<double,S> const v1{ss};
    YAUL_VARIANT_CHECK_EQUALS(v1.which(), 1);
    yaul::variant<int,double,S> v2;
    YAUL_VARIANT_CHECK_EQUALS(v2.which(), 0);
    v2 = v1;
    YAUL_VARIANT_CHECK_EQUALS(v2.which(), 2);
  }
}

void test__assign__04()
{
  struct S
  {
    S() = default;
    S(S&) = default;
    S(S const&) = default;
    S(S&&) = default;
    S& operator=(S&) = delete;
    S& operator=(S const&) = delete;
    S& operator=(S&&) = default;
  };

  {
    yaul::variant<double,S> v1{S{}};
    YAUL_VARIANT_CHECK_EQUALS(v1.which(), 1);
    yaul::variant<int,double,S> v2;
    YAUL_VARIANT_CHECK_EQUALS(v2.which(), 0);
    v2 = std::move(v1);
    YAUL_VARIANT_CHECK_EQUALS(v2.which(), 2);
  }
}

void test__assign__05()
{
  static int last;
  struct S
  {
    S() { last = 0; }
    S(S&) noexcept { last = -1; }
    S(S const&) noexcept { last = -2; }
    S(S&&) noexcept { last = -3; }
    S& operator=(S&) noexcept { last = 1; return *this;}
    S& operator=(S const&) noexcept { last = 2; return *this;}
    S& operator=(S&&) noexcept { last = 3; return *this;}
  };

  {
    S s;
    yaul::variant<int,S> v1{s};
    YAUL_VARIANT_CHECK_EQUALS(v1.which(), 1);
    yaul::variant<double,int,S> v2;
    YAUL_VARIANT_CHECK_EQUALS(v2.which(), 0);
    v2 = v1;
    YAUL_VARIANT_CHECK_EQUALS(v2.which(), 2);
    YAUL_VARIANT_CHECK_EQUALS(last, -1);
  }
  {
    S const s;
    yaul::variant<int,S> const v1{s};
    YAUL_VARIANT_CHECK_EQUALS(v1.which(), 1);
    yaul::variant<double,int,S> v2;
    YAUL_VARIANT_CHECK_EQUALS(v2.which(), 0);
    v2 = v1;
    YAUL_VARIANT_CHECK_EQUALS(v2.which(), 2);
    YAUL_VARIANT_CHECK_EQUALS(last, -2);
  }

  {
    yaul::variant<int,S> v1{S{}};
    YAUL_VARIANT_CHECK_EQUALS(v1.which(), 1);
    yaul::variant<double,int,S> v2;
    YAUL_VARIANT_CHECK_EQUALS(v2.which(), 0);
    v2 = std::move(v1);
    YAUL_VARIANT_CHECK_EQUALS(v2.which(), 2);
    YAUL_VARIANT_CHECK_EQUALS(last, -3);
  }

  {
    S s;
    yaul::variant<S,int> v1{s};
    YAUL_VARIANT_CHECK_EQUALS(v1.which(), 0);
    yaul::variant<S,double,int> v2;
    YAUL_VARIANT_CHECK_EQUALS(v2.which(), 0);
    v2 = v1;
    YAUL_VARIANT_CHECK_EQUALS(v2.which(), 0);
    YAUL_VARIANT_CHECK_EQUALS(last, 1);
  }
  {
    S const s;
    yaul::variant<S,int> const v1{s};
    YAUL_VARIANT_CHECK_EQUALS(v1.which(), 0);
    yaul::variant<S,double,int> v2;
    YAUL_VARIANT_CHECK_EQUALS(v2.which(), 0);
    v2 = v1;
    YAUL_VARIANT_CHECK_EQUALS(v2.which(), 0);
    YAUL_VARIANT_CHECK_EQUALS(last, 2);
  }

  {
    yaul::variant<S,int> v1{S{}};
    YAUL_VARIANT_CHECK_EQUALS(v1.which(), 0);
    yaul::variant<S,double,int> v2;
    YAUL_VARIANT_CHECK_EQUALS(v2.which(), 0);
    v2 = std::move(v1);
    YAUL_VARIANT_CHECK_EQUALS(v2.which(), 0);
    YAUL_VARIANT_CHECK_EQUALS(last, 3);
  }
}

int main()
{
  test__assign__01();
  test__assign__02();
  test__assign__03();
  test__assign__04();
  test__assign__05();
  return YAUL_VARIANT_TEST_EXIT_CODE;
}
