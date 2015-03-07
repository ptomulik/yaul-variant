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
// play with copy constructibility
//

static_assert( std::is_nothrow_copy_constructible<yaul::variant<int> >::value, "");
static_assert( std::is_nothrow_copy_constructible<yaul::variant<int, float> >::value, "");

struct S00 { };
static_assert( std::is_nothrow_copy_constructible<S00>::value, "");
static_assert( std::is_nothrow_copy_constructible<yaul::variant<S00> >::value, "");

struct S01 { S01(S01 const&) = default; };
static_assert( std::is_nothrow_copy_constructible<S01>::value, "");
static_assert( std::is_nothrow_copy_constructible<yaul::variant<S01> >::value, "");
static_assert( std::is_nothrow_copy_constructible<yaul::variant<S01,S00> >::value, "");

struct S02 { S02(S02 const&) noexcept {} };
static_assert( std::is_nothrow_copy_constructible<S02>::value, "");
static_assert( std::is_nothrow_copy_constructible<yaul::variant<S02> >::value, "");
static_assert( std::is_nothrow_copy_constructible<yaul::variant<S02,S01,S00> >::value, "");

struct S03 { S03(S03 const&) {} };
static_assert( std::is_copy_constructible<S03>::value, "");
static_assert(!std::is_nothrow_copy_constructible<S03>::value, "");
static_assert( std::is_copy_constructible<yaul::variant<S03> >::value, "");
static_assert(!std::is_nothrow_copy_constructible<yaul::variant<S03> >::value, "");
static_assert( std::is_copy_constructible<yaul::variant<S03,S02> >::value, "");
static_assert(!std::is_nothrow_copy_constructible<yaul::variant<S03,S02> >::value, "");
static_assert( std::is_copy_constructible<yaul::variant<S03,S02,S01> >::value, "");
static_assert(!std::is_nothrow_copy_constructible<yaul::variant<S03,S02,S01> >::value, "");

struct S10 { S10(S10 const&) = delete; };
static_assert(!std::is_copy_constructible<S10>::value, "");
static_assert(!std::is_copy_constructible<yaul::variant<S10> >::value, "");
static_assert(!std::is_copy_constructible<yaul::variant<S10,S02> >::value, "");
static_assert(!std::is_copy_constructible<yaul::variant<S10,S02,S01> >::value, "");

struct S11 { S11(S11&) = delete; };
static_assert(!std::is_copy_constructible<S11>::value, "");
static_assert(!std::is_copy_constructible<yaul::variant<S11> >::value, "");
static_assert(!std::is_copy_constructible<yaul::variant<S11,S02> >::value, "");
static_assert(!std::is_copy_constructible<yaul::variant<S11,S02,S01> >::value, "");

struct S12 { S12(S12&) = delete; S12(S12 const&) = default; };
static_assert( std::is_nothrow_copy_constructible<S12>::value, "");
static_assert( std::is_nothrow_copy_constructible<yaul::variant<S12> >::value, "");
static_assert( std::is_nothrow_copy_constructible<yaul::variant<S12,S02> >::value, "");
static_assert( std::is_nothrow_copy_constructible<yaul::variant<S12,S02,S01> >::value, "");

struct S31
{
  S31(S31&) = default;
  S31(S31 const &) = delete;
  S31(S31&&) = delete;
};
static_assert( std::is_constructible<S31, S31&>::value, "");
static_assert(!std::is_constructible<S31, S31 const&>::value, "");
static_assert(!std::is_constructible<S31, S31&&>::value, "");
static_assert( std::is_constructible<yaul::variant<S31>, yaul::variant<S31>&>::value, "");
static_assert(!std::is_constructible<yaul::variant<S31>, yaul::variant<S31> const&>::value, "");
static_assert(!std::is_constructible<yaul::variant<S31>, yaul::variant<S31>&&>::value, "");

struct S32
{
  S32(S32&) = delete;
  S32(S32 const &) = default;
  S32(S32&&) = delete;
};
static_assert(!std::is_constructible<S32, S32&>::value, "");
static_assert( std::is_constructible<S32, S32 const&>::value, "");
static_assert(!std::is_constructible<S32, S32&&>::value, "");
static_assert(!std::is_constructible<yaul::variant<S32>, yaul::variant<S32>&>::value, "");
static_assert( std::is_constructible<yaul::variant<S32>, yaul::variant<S32> const&>::value, "");
// FIXME: this is somehow broken...
//static_assert(!std::is_constructible<yaul::variant<S32>, yaul::variant<S32>&&>::value, "");

struct S33
{
  S33(S33&) = delete;
  S33(S33 const &) = delete;
  S33(S33&&) = default;
};
static_assert(!std::is_constructible<S33, S33&>::value, "");
static_assert(!std::is_constructible<S33, S33 const&>::value, "");
static_assert( std::is_constructible<S33, S33&&>::value, "");
static_assert(!std::is_constructible<yaul::variant<S33>, yaul::variant<S33>&>::value, "");
static_assert(!std::is_constructible<yaul::variant<S33>, yaul::variant<S33> const&>::value, "");
static_assert( std::is_constructible<yaul::variant<S33>, yaul::variant<S33>&&>::value, "");

void test__copy_ctor__01()
{
  struct Visitor
    : yaul::static_visitor<int>
  { result_type operator()(int x) const noexcept { return x; } };

  yaul::variant<int> v1{1};
  yaul::variant<int> v2{v1};

  YAUL_VARIANT_CHECK_EQUALS(v1.which(), 0);
  YAUL_VARIANT_CHECK_EQUALS(v2.which(), 0);
  
  YAUL_VARIANT_CHECK_EQUALS(v1.apply_visitor(Visitor{}), 1);
  YAUL_VARIANT_CHECK_EQUALS(v2.apply_visitor(Visitor{}), 1);
}

void test__copy_ctor__02()
{
  struct Visitor
    : yaul::static_visitor<float>
  {
    float operator()(int x) const noexcept { return static_cast<float>(x); } 
    float operator()(float x) const noexcept { return static_cast<float>(x); } 
  };

  yaul::variant<int,float> v1{2.0f};
  yaul::variant<int,float> v2{v1};

  YAUL_VARIANT_CHECK_EQUALS(v1.which(), 1);
  YAUL_VARIANT_CHECK_EQUALS(v2.which(), 1);
  
  YAUL_VARIANT_CHECK_EQUALS(v1.apply_visitor(Visitor{}), 2.0f);
  YAUL_VARIANT_CHECK_EQUALS(v2.apply_visitor(Visitor{}), 2.0f);
}

void test__copy_ctor__03()
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
  };


  {
    last = -1;

    yaul::variant<S> v1;
    YAUL_VARIANT_CHECK_EQUALS(last, -1);

    yaul::variant<S> v2{v1};
    YAUL_VARIANT_CHECK_EQUALS(last, 1);

    YAUL_VARIANT_CHECK_EQUALS(v1.which(), 0);
    YAUL_VARIANT_CHECK_EQUALS(v2.which(), 0);
  }
}

void test__copy_ctor__04()
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
    S(const S&) noexcept  { last = 2; }
  };

  {
    last = -1;

    yaul::variant<S> v1;
    YAUL_VARIANT_CHECK_EQUALS(last, -1);

    yaul::variant<S> v2{v1};
    YAUL_VARIANT_CHECK_EQUALS(last, 2);

    YAUL_VARIANT_CHECK_EQUALS(v1.which(), 0);
    YAUL_VARIANT_CHECK_EQUALS(v2.which(), 0);
  }
}

int main()
{
  test__copy_ctor__01();
  test__copy_ctor__02();
  test__copy_ctor__03();
  test__copy_ctor__04();
  return YAUL_VARIANT_TEST_EXIT_CODE;
}
