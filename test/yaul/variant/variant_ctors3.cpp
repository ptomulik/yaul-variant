// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <yaul/variant/variant.hpp>
#include <yaul/variant/test_config.hpp>
#include <type_traits>
#include <utility>

//
// play with copy-/move- constructibility of identical variants
//

void test__ctors__01()
{
  {
    // variant(variant&)
    yaul::variant<int,char,double> v1{'a'};
    yaul::variant<int,char,double> v2{v1};
    YAUL_VARIANT_CHECK_EQUALS(v1.which(), 1);
    YAUL_VARIANT_CHECK_EQUALS(v2.which(), 1);
  }
  {
    // variant(variant const&)
    yaul::variant<int,char,double> const v1{'a'};
    yaul::variant<int,char,double> v2{v1};
    YAUL_VARIANT_CHECK_EQUALS(v1.which(), 1);
    YAUL_VARIANT_CHECK_EQUALS(v2.which(), 1);
  }
  {
    // variant(variant&&)
    yaul::variant<int,char,double> v1{'a'};
    yaul::variant<int,char,double> v2{std::move(v1)};
    YAUL_VARIANT_CHECK_EQUALS(v1.which(), 1);
    YAUL_VARIANT_CHECK_EQUALS(v2.which(), 1);
  }
}

void test__ctors__02()
{
  struct S
  {
    S() = default;
    S(S&) = default;
    S(S const&) = delete;
    S(S&&) = delete;
  };
  S s;
  {
    // variant(variant&)
    yaul::variant<S,int,double> v1{s};
    yaul::variant<S,int,double> v2{v1};
    YAUL_VARIANT_CHECK_EQUALS(v1.which(), 0);
    YAUL_VARIANT_CHECK_EQUALS(v2.which(), 0);
  }
  {
    // variant(variant&)
    yaul::variant<int,S,double> v1{s};
    yaul::variant<int,S,double> v2{v1};
    YAUL_VARIANT_CHECK_EQUALS(v1.which(), 1);
    YAUL_VARIANT_CHECK_EQUALS(v2.which(), 1);
  }
  {
    // variant(variant&)
    yaul::variant<int,double,S> v1{s};
    yaul::variant<int,double,S> v2{v1};
    YAUL_VARIANT_CHECK_EQUALS(v1.which(), 2);
    YAUL_VARIANT_CHECK_EQUALS(v2.which(), 2);
  }
}

void test__ctors__03()
{
  struct S
  {
    S() = default;
    S(S&) = delete;
    S(S const&) = default;
    S(S&&) = delete;
  };
  const S s{};
  {
    // variant(variant const&)
    yaul::variant<S,int,double> const v1{s};
    yaul::variant<S,int,double> v2{v1};
    YAUL_VARIANT_CHECK_EQUALS(v1.which(), 0);
    YAUL_VARIANT_CHECK_EQUALS(v2.which(), 0);
  }
  {
    // variant(variant const&)
    yaul::variant<int,S,double> const v1{s};
    yaul::variant<int,S,double> v2{v1};
    YAUL_VARIANT_CHECK_EQUALS(v1.which(), 1);
    YAUL_VARIANT_CHECK_EQUALS(v2.which(), 1);
  }
  {
    // variant(variant const&)
    yaul::variant<int,double,S> const v1{s};
    yaul::variant<int,double,S> v2{v1};
    YAUL_VARIANT_CHECK_EQUALS(v1.which(), 2);
    YAUL_VARIANT_CHECK_EQUALS(v2.which(), 2);
  }
}

void test__ctors__04()
{
  struct S
  {
    S() = default;
    S(S&) = delete;
    S(S const&) = delete;
    S(S&&) = default;
  };

  {
    // variant(variant const&)
    yaul::variant<S,int,double> v1{S{}};
    yaul::variant<S,int,double> v2{std::move(v1)};
    YAUL_VARIANT_CHECK_EQUALS(v1.which(), 0);
    YAUL_VARIANT_CHECK_EQUALS(v2.which(), 0);
  }
  {
    // variant(variant const&)
    yaul::variant<int,S,double> v1{S{}};
    yaul::variant<int,S,double> v2{std::move(v1)};
    YAUL_VARIANT_CHECK_EQUALS(v1.which(), 1);
    YAUL_VARIANT_CHECK_EQUALS(v2.which(), 1);
  }
  {
    // variant(variant const&)
    yaul::variant<int,double,S> v1{S{}};
    yaul::variant<int,double,S> v2{std::move(v1)};
    YAUL_VARIANT_CHECK_EQUALS(v1.which(), 2);
    YAUL_VARIANT_CHECK_EQUALS(v2.which(), 2);
  }
}

void test__ctors__05()
{
  static int counter;
  struct S
  {
    S() noexcept  { counter = 0x000; }
    S(S&)         { counter += 0x100; }
    S(S const&)   { counter += 0x010; }
    S(S&&)        { counter += 0x001; }
  };

  // variant(variant&)
  {
    yaul::variant<S, int, double> v1;
    YAUL_VARIANT_CHECK_EQUALS(counter, 0x000);
    YAUL_VARIANT_CHECK_EQUALS(v1.which(), 0);
    yaul::variant<S, int, double> v2{v1};
    YAUL_VARIANT_CHECK_EQUALS(counter, 0x100);
    YAUL_VARIANT_CHECK_EQUALS(v2.which(), 0);
  }

  {
    S s;
    yaul::variant<int, S, double> v1{s};
    YAUL_VARIANT_CHECK_EQUALS(counter, 0x100);
    YAUL_VARIANT_CHECK_EQUALS(v1.which(), 1);
    yaul::variant<int, S, double> v2{v1};
    YAUL_VARIANT_CHECK_EQUALS(counter, 0x200);
    YAUL_VARIANT_CHECK_EQUALS(v2.which(), 1);
  }

  {
    S s;
    yaul::variant<int, double, S> v1{s};
    YAUL_VARIANT_CHECK_EQUALS(counter, 0x100);
    YAUL_VARIANT_CHECK_EQUALS(v1.which(), 2);
    yaul::variant<int, double, S> v2{v1};
    YAUL_VARIANT_CHECK_EQUALS(counter, 0x200);
    YAUL_VARIANT_CHECK_EQUALS(v2.which(), 2);
  }

  // variant(variant const&)
  {
    yaul::variant<S, int, double> const v1;
    YAUL_VARIANT_CHECK_EQUALS(counter, 0x000);
    YAUL_VARIANT_CHECK_EQUALS(v1.which(), 0);
    yaul::variant<S, int, double> v2{v1};
    YAUL_VARIANT_CHECK_EQUALS(counter, 0x010);
    YAUL_VARIANT_CHECK_EQUALS(v2.which(), 0);
  }

  {
    S s;
    yaul::variant<int, S, double> const v1{s};
    YAUL_VARIANT_CHECK_EQUALS(counter, 0x100);
    YAUL_VARIANT_CHECK_EQUALS(v1.which(), 1);
    yaul::variant<int, S, double> v2{v1};
    YAUL_VARIANT_CHECK_EQUALS(counter, 0x110);
    YAUL_VARIANT_CHECK_EQUALS(v2.which(), 1);
  }

  {
    S s;
    yaul::variant<int, double, S> const v1{s};
    YAUL_VARIANT_CHECK_EQUALS(counter, 0x100);
    YAUL_VARIANT_CHECK_EQUALS(v1.which(), 2);
    yaul::variant<int, double, S> v2{v1};
    YAUL_VARIANT_CHECK_EQUALS(counter, 0x110);
    YAUL_VARIANT_CHECK_EQUALS(v2.which(), 2);
  }

  // variant(variant&&)
  {
    yaul::variant<S, int, double> v1;
    YAUL_VARIANT_CHECK_EQUALS(counter, 0x000);
    YAUL_VARIANT_CHECK_EQUALS(v1.which(), 0);
    yaul::variant<S, int, double> v2{std::move(v1)};
    YAUL_VARIANT_CHECK_EQUALS(counter, 0x001);
    YAUL_VARIANT_CHECK_EQUALS(v2.which(), 0);
  }

  {
    S s;
    yaul::variant<int, S, double> v1{s};
    YAUL_VARIANT_CHECK_EQUALS(counter, 0x100);
    YAUL_VARIANT_CHECK_EQUALS(v1.which(), 1);
    yaul::variant<int, S, double> v2{std::move(v1)};
    YAUL_VARIANT_CHECK_EQUALS(counter, 0x101);
    YAUL_VARIANT_CHECK_EQUALS(v2.which(), 1);
  }

  {
    S s;
    yaul::variant<int, double, S> v1{s};
    YAUL_VARIANT_CHECK_EQUALS(counter, 0x100);
    YAUL_VARIANT_CHECK_EQUALS(v1.which(), 2);
    yaul::variant<int, double, S> v2{std::move(v1)};
    YAUL_VARIANT_CHECK_EQUALS(counter, 0x101);
    YAUL_VARIANT_CHECK_EQUALS(v2.which(), 2);
  }
}

int main()
{
  test__ctors__01();
  test__ctors__02();
  test__ctors__03();
  test__ctors__04();
  test__ctors__05();
  return YAUL_VARIANT_TEST_EXIT_CODE;
}
