// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <yaul/variant/variant.hpp>
#include <yaul/variant/test_config.hpp>
#include <type_traits>

// test assignments from bounded types

void test__assign__01()
{
  struct S { int x; };

  {
    yaul::variant<double,S> v;
    YAUL_VARIANT_CHECK_EQUALS(v.which(), 0);
    S s{10};
    v = s;
    YAUL_VARIANT_CHECK_EQUALS(v.which(), 1);
  }

  {
    yaul::variant<double,S> v;
    YAUL_VARIANT_CHECK_EQUALS(v.which(), 0);
    S const s{10};
    v = s;
    YAUL_VARIANT_CHECK_EQUALS(v.which(), 1);
  }

  {
    yaul::variant<double,S> v;
    YAUL_VARIANT_CHECK_EQUALS(v.which(), 0);
    v = S{10};
    YAUL_VARIANT_CHECK_EQUALS(v.which(), 1);
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
    S& operator=(S&) = delete;
    S& operator=(S const&) = delete;
    S& operator=(S&&) = delete;
  };
  {
    yaul::variant<S,double> v;
    YAUL_VARIANT_CHECK_EQUALS(v.which(), 0);
  }
  {
    yaul::variant<double,S> v;
    YAUL_VARIANT_CHECK_EQUALS(v.which(), 0);
  }
  {
    S s;
    yaul::variant<double,S> v{s};
    YAUL_VARIANT_CHECK_EQUALS(v.which(), 1);
  }
  {
    S const s{};
    yaul::variant<double,S> v{s};
    YAUL_VARIANT_CHECK_EQUALS(v.which(), 1);
  }
  {
    yaul::variant<double,S> v{S{}};
    YAUL_VARIANT_CHECK_EQUALS(v.which(), 1);
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
    S& operator=(S&) = default;
    S& operator=(S const&) = delete;
    S& operator=(S&&) = delete;
  };

  S ss;

  {
    yaul::variant<S,double> v;
    YAUL_VARIANT_CHECK_EQUALS(v.which(), 0);
    v = ss;
    YAUL_VARIANT_CHECK_EQUALS(v.which(), 0);
  }
  {
    yaul::variant<double,S> v;
    YAUL_VARIANT_CHECK_EQUALS(v.which(), 0);
    v = ss;
    YAUL_VARIANT_CHECK_EQUALS(v.which(), 1);
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
    S& operator=(S const&) = default;
    S& operator=(S&&) = delete;
  };

  S const ss{};

  {
    yaul::variant<S,double> v;
    YAUL_VARIANT_CHECK_EQUALS(v.which(), 0);
    v = ss;
    YAUL_VARIANT_CHECK_EQUALS(v.which(), 0);
  }
  {
    yaul::variant<double,S> v;
    YAUL_VARIANT_CHECK_EQUALS(v.which(), 0);
    v = ss;
    YAUL_VARIANT_CHECK_EQUALS(v.which(), 1);
  }
}

void test__assign__05()
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
    yaul::variant<S,double> v;
    YAUL_VARIANT_CHECK_EQUALS(v.which(), 0);
    v = S{};
    YAUL_VARIANT_CHECK_EQUALS(v.which(), 0);
  }
  {
    yaul::variant<double,S> v;
    YAUL_VARIANT_CHECK_EQUALS(v.which(), 0);
    v = S{};
    YAUL_VARIANT_CHECK_EQUALS(v.which(), 1);
  }
}

void test__assign__06()
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
    yaul::variant<S,int> v;
    YAUL_VARIANT_CHECK_EQUALS(v.which(), 0);
    v = s;
    YAUL_VARIANT_CHECK_EQUALS(v.which(), 0);
    YAUL_VARIANT_CHECK_EQUALS(last, 1);
  }

  {
    S const s;
    yaul::variant<S,int> v;
    YAUL_VARIANT_CHECK_EQUALS(v.which(), 0);
    v = s;
    YAUL_VARIANT_CHECK_EQUALS(v.which(), 0);
    YAUL_VARIANT_CHECK_EQUALS(last, 2);
  }

  {
    yaul::variant<S,int> v;
    YAUL_VARIANT_CHECK_EQUALS(v.which(), 0);
    v = S{};
    YAUL_VARIANT_CHECK_EQUALS(v.which(), 0);
    YAUL_VARIANT_CHECK_EQUALS(last, 3);
  }

  {
    S s;
    yaul::variant<int,S> v;
    YAUL_VARIANT_CHECK_EQUALS(v.which(), 0);
    v = s;
    YAUL_VARIANT_CHECK_EQUALS(v.which(), 1);
    YAUL_VARIANT_CHECK_EQUALS(last, -1);
  }

  {
    S const s;
    yaul::variant<int,S> v;
    YAUL_VARIANT_CHECK_EQUALS(v.which(), 0);
    v = s;
    YAUL_VARIANT_CHECK_EQUALS(v.which(), 1);
    YAUL_VARIANT_CHECK_EQUALS(last, -2);
  }

  {
    yaul::variant<int,S> v;
    YAUL_VARIANT_CHECK_EQUALS(v.which(), 0);
    v = S{};
    YAUL_VARIANT_CHECK_EQUALS(v.which(), 1);
    YAUL_VARIANT_CHECK_EQUALS(last, -3);
  }
}

int main()
{
  test__assign__01();
  test__assign__02();
  test__assign__03();
  test__assign__04();
  test__assign__05();
  test__assign__06();
  return YAUL_VARIANT_TEST_EXIT_CODE;
}
