// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <yaul/variant/variant.hpp>
#include <yaul/variant/static_visitor.hpp>
#include <yaul/variant/test_config.hpp>
#include <type_traits>

//
// play with move constructibility
//

static_assert( std::is_nothrow_move_constructible<yaul::variant<int> >::value, "");
static_assert( std::is_nothrow_move_constructible<yaul::variant<int, float> >::value, "");

// trivial ctors
struct S00 { };
static_assert( std::is_nothrow_move_constructible<S00>::value, "");
static_assert( std::is_nothrow_move_constructible<yaul::variant<S00> >::value, "");

// trivial ctors with explicitly default'ed move ctor
struct S01 { S01(S01&&) = default; };
static_assert( std::is_nothrow_move_constructible<S01>::value, "");
static_assert( std::is_nothrow_move_constructible<yaul::variant<S01> >::value, "");
static_assert( std::is_nothrow_move_constructible<yaul::variant<S01,S00> >::value, "");

// noexcept non-trivial move ctor
struct S02 { S02(S02&&) noexcept {} };
static_assert( std::is_nothrow_move_constructible<S02>::value, "");
static_assert( std::is_nothrow_move_constructible<yaul::variant<S02> >::value, "");
static_assert( std::is_nothrow_move_constructible<yaul::variant<S02,S01,S00> >::value, "");

// non-trivial move ctor
struct S03 { S03(S03&&) {} };
static_assert( std::is_move_constructible<S03>::value, "");
static_assert(!std::is_nothrow_move_constructible<S03>::value, "");
static_assert( std::is_move_constructible<yaul::variant<S03> >::value, "");
static_assert(!std::is_nothrow_move_constructible<yaul::variant<S03> >::value, "");
static_assert( std::is_move_constructible<yaul::variant<S03,S02> >::value, "");
static_assert(!std::is_nothrow_move_constructible<yaul::variant<S03,S02> >::value, "");
static_assert( std::is_move_constructible<yaul::variant<S03,S02,S01> >::value, "");
static_assert(!std::is_nothrow_move_constructible<yaul::variant<S03,S02,S01> >::value, "");

// deleted move ctor
struct S10 { S10(S10&&) = delete; };
static_assert(!std::is_move_constructible<S10>::value, "");
static_assert(!std::is_move_constructible<yaul::variant<S10> >::value, "");
static_assert(!std::is_move_constructible<yaul::variant<S10,S02> >::value, "");
static_assert(!std::is_move_constructible<yaul::variant<S10,S02,S01> >::value, "");

void test__move_ctor__01()
{
  struct Visitor
    : yaul::static_visitor<int>
  { result_type operator()(int x) const noexcept { return x; } };

  yaul::variant<int> v{yaul::variant<int>{1}};

  YAUL_VARIANT_CHECK_EQUALS(v.which(), 0);
  YAUL_VARIANT_CHECK_EQUALS(v.apply_visitor(Visitor{}), 1);
}

void test__move_ctor__02()
{
  struct Visitor
    : yaul::static_visitor<float>
  {
    float operator()(int x) const noexcept { return static_cast<float>(x); } 
    float operator()(float x) const noexcept { return static_cast<float>(x); } 
  };

  yaul::variant<int,float> v{yaul::variant<int,float>{2.0f}};

  YAUL_VARIANT_CHECK_EQUALS(v.which(), 1);
  YAUL_VARIANT_CHECK_EQUALS(v.apply_visitor(Visitor{}), 2.0f);
}

void test__move_ctor__03()
{
  static int last;

  struct Visitor
    : yaul::static_visitor<float>
  {
    float operator()(int x) const noexcept { return static_cast<float>(x); } 
    float operator()(float x) const noexcept { return static_cast<float>(x); } 
  };

  struct S
  {
    S() = default;
    S(S&) noexcept        { last = 1; }
    S(const S&) noexcept  { last = 2; }
    S(S&&) noexcept       { last = 3; }
  };


  {
    last = -1;

    yaul::variant<S> v0;
    yaul::variant<S> v{std::move(v0)};
    YAUL_VARIANT_CHECK_EQUALS(last, 3);

    YAUL_VARIANT_CHECK_EQUALS(v.which(), 0);
  }
}

void test__move_ctor__04()
{
  static int last;

  struct Visitor
    : yaul::static_visitor<float>
  {
    float operator()(int x) const noexcept { return static_cast<float>(x); } 
    float operator()(float x) const noexcept { return static_cast<float>(x); } 
  };

  struct S
  {
    S() noexcept {}
    S(S&&) noexcept  { last = 3; }
  };
  {
    last = -1;

    yaul::variant<S> v0;
    yaul::variant<S> v{std::move(v0)};
    YAUL_VARIANT_CHECK_EQUALS(last, 3);

    YAUL_VARIANT_CHECK_EQUALS(v.which(), 0);
  }
}

int main()
{
  test__move_ctor__01();
  test__move_ctor__02();
  test__move_ctor__03();
  test__move_ctor__04();
  return YAUL_VARIANT_TEST_EXIT_CODE;
}
