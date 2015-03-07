// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <yaul/variant/variant.hpp>
#include <yaul/variant/test_config.hpp>
#include <type_traits>

//
// play with copy-construtibility
//

/////////////////////////////////////////////////////////////////////////////
// copy- and move-constructible
/////////////////////////////////////////////////////////////////////////////
struct S00 { };
static_assert( std::is_nothrow_constructible<yaul::variant<S00>,S00&>::value, "");
static_assert( std::is_nothrow_constructible<yaul::variant<S00>,S00 const&>::value, "");
static_assert( std::is_nothrow_constructible<yaul::variant<S00>, S00&&>::value, "");

struct S01
{
  static int counter1;
  static int counter2;
  static int counter3;
  S01() = default;
  S01(S01&) { ++counter1; }
  S01(S01 const&) { ++counter2; }
  S01(S01&&) { ++counter3; }
};
int S01::counter1 = 0;
int S01::counter2 = 0;
int S01::counter3 = 0;
static_assert( std::is_constructible<yaul::variant<S01>, S01&>::value, "");
static_assert( std::is_constructible<yaul::variant<S01>, S01 const&>::value, "");
static_assert( std::is_constructible<yaul::variant<S01>, S01&&>::value, "");
static_assert(!std::is_nothrow_constructible<yaul::variant<S01>, S01&>::value, "");
static_assert(!std::is_nothrow_constructible<yaul::variant<S01>, S01 const&>::value, "");
static_assert(!std::is_nothrow_constructible<yaul::variant<S01>, S01&&>::value, "");

void test__ctors__01()
{
  S01 s1;
  S01 const s2;

  S01::counter1 = 0;
  S01::counter2 = 0;
  S01::counter3 = 0;

  yaul::variant<S01> v1{s1};
  YAUL_VARIANT_CHECK_EQUALS(S01::counter1, 1);
  YAUL_VARIANT_CHECK_EQUALS(S01::counter2, 0);
  YAUL_VARIANT_CHECK_EQUALS(S01::counter3, 0);
  yaul::variant<S01> v2{s2};
  YAUL_VARIANT_CHECK_EQUALS(S01::counter1, 1);
  YAUL_VARIANT_CHECK_EQUALS(S01::counter2, 1);
  YAUL_VARIANT_CHECK_EQUALS(S01::counter3, 0);
  yaul::variant<S01> v3{S01()};
  YAUL_VARIANT_CHECK_EQUALS(S01::counter1, 1);
  YAUL_VARIANT_CHECK_EQUALS(S01::counter2, 1);
  YAUL_VARIANT_CHECK_EQUALS(S01::counter3, 1);
  (void)v1;
  (void)v2;
  (void)v3;
}

struct S02
{
  S02() = default;
  S02(S02&) noexcept { }
  S02(S02 const&) { }
  S02(S02&&) { }
};
static_assert( std::is_nothrow_constructible<yaul::variant<S02>, S02&>::value, "");
static_assert( std::is_constructible<yaul::variant<S02>, S02 const&>::value, "");
static_assert( std::is_constructible<yaul::variant<S02>, S02&&>::value, "");
static_assert(!std::is_nothrow_constructible<yaul::variant<S02>, S02 const&>::value, "");
static_assert(!std::is_nothrow_constructible<yaul::variant<S02>, S02&&>::value, "");

struct S03
{
  S03() = default;
  S03(S03&) { }
  S03(S03 const&) noexcept { }
  S03(S03&&) { }
};
static_assert( std::is_constructible<yaul::variant<S03>, S03&>::value, "");
static_assert( std::is_nothrow_constructible<yaul::variant<S03>, S03 const&>::value, "");
static_assert( std::is_constructible<yaul::variant<S03>, S03&&>::value, "");
static_assert(!std::is_nothrow_constructible<yaul::variant<S03>, S03&>::value, "");
static_assert(!std::is_nothrow_constructible<yaul::variant<S03>, S03&&>::value, "");

struct S04
{
  S04() = default;
  S04(S04&) { }
  S04(S04 const&) { }
  S04(S04&&) noexcept { }
};
static_assert( std::is_constructible<yaul::variant<S04>, S04&>::value, "");
static_assert( std::is_constructible<yaul::variant<S04>, S04 const&>::value, "");
static_assert( std::is_nothrow_constructible<yaul::variant<S04>, S04&&>::value, "");
static_assert(!std::is_nothrow_constructible<yaul::variant<S04>, S04&>::value, "");
static_assert(!std::is_nothrow_constructible<yaul::variant<S04>, S04 const&>::value, "");

/////////////////////////////////////////////////////////////////////////////
// non-copy-constructible (but move constructible)
/////////////////////////////////////////////////////////////////////////////
struct S10
{
  S10() = default;
  S10(S10 const&) = delete;
  S10(S10&&) = default; 
};

static_assert(!std::is_constructible<yaul::variant<S10>, S10&>::value, "");
static_assert(!std::is_constructible<yaul::variant<S10>, S10 const&>::value, "");
static_assert( std::is_nothrow_constructible<yaul::variant<S10>, S10&&>::value, "");


/////////////////////////////////////////////////////////////////////////////
// non-move-constructible
/////////////////////////////////////////////////////////////////////////////
struct S20
{
  S20() = default;
  S20(S20 const&) = default;
  S20(S20&&) = delete;
};
static_assert( std::is_nothrow_constructible<yaul::variant<S20>, S20&>::value, "");
static_assert( std::is_nothrow_constructible<yaul::variant<S20>, S20 const&>::value, "");
static_assert( std::is_nothrow_constructible<yaul::variant<S20>, S20&&>::value, ""); // this uses variant(S20 const&) c-tor

struct S21
{
  static int counter;
  S21() = default;
  S21(S21 const&) { ++counter; }
  S21(S21&&) = delete;
};
int S21::counter = 0;

static_assert( std::is_constructible<yaul::variant<S21>, S21&>::value, "");
static_assert( std::is_constructible<yaul::variant<S21>, S21 const&>::value, "");
static_assert( std::is_constructible<yaul::variant<S21>, S21&&>::value, ""); // this uses variant(S21 const&) c-tor
static_assert(!std::is_nothrow_constructible<yaul::variant<S21>, S21&>::value, "");
static_assert(!std::is_nothrow_constructible<yaul::variant<S21>, S21 const&>::value, "");
static_assert(!std::is_nothrow_constructible<yaul::variant<S21>, S21&&>::value, ""); // this uses variant(S21 const&) c-tor

void test__ctors__21()
{
  S21 s1;
  S21 const s2;

  S21::counter = 0;
  yaul::variant<S21> v1{S21()};
  YAUL_VARIANT_CHECK_EQUALS(S21::counter, 1);
  yaul::variant<S21> v2{s1};
  YAUL_VARIANT_CHECK_EQUALS(S21::counter, 2);
  yaul::variant<S21> v3{s2};
  YAUL_VARIANT_CHECK_EQUALS(S21::counter, 3);
  (void)v1;
  (void)v2;
  (void)v3;
}

/////////////////////////////////////////////////////////////////////////////
// non-copy- and non-move-constructible
/////////////////////////////////////////////////////////////////////////////
struct S30
{
  S30() = default;
  S30(S30 const&) = delete;
};
static_assert(!std::is_constructible<yaul::variant<S30>, S30&>::value, "");
static_assert(!std::is_constructible<yaul::variant<S30>, S30 const&>::value, "");
static_assert(!std::is_constructible<yaul::variant<S30>, S30&&>::value, "");

int main()
{
  test__ctors__01();
  test__ctors__21();
  return YAUL_VARIANT_TEST_EXIT_CODE;
}
