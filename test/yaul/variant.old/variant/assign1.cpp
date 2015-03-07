// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <yaul/variant/variant.hpp>
#include <yaul/variant/test_config.hpp>
#include <type_traits>

// play with assign operators

struct S00 { };
static_assert( std::is_nothrow_assignable<S00,S00&>::value, "");
static_assert( std::is_nothrow_assignable<S00,S00 const&>::value, "");
static_assert( std::is_nothrow_assignable<S00,S00&&>::value, "");
static_assert( std::is_nothrow_assignable<yaul::variant<S00>,S00&>::value, "");
static_assert( std::is_nothrow_assignable<yaul::variant<S00>,S00 const&>::value, "");
static_assert( std::is_nothrow_assignable<yaul::variant<S00>,S00&&>::value, "");

struct S11 
{
  S11& operator=(S11&) = delete;
  S11& operator=(S11 const&) = default;   S11(S11 const&) = default;
  S11& operator=(S11&&) = default;        S11(S11&&) = default;
};
static_assert(!std::is_nothrow_assignable<S11,S11&>::value, "");
static_assert( std::is_nothrow_assignable<S11,S11 const&>::value, "");
static_assert( std::is_nothrow_assignable<S11,S11&&>::value, "");
static_assert(!std::is_nothrow_assignable<yaul::variant<S11>,S11&>::value, "");
static_assert( std::is_nothrow_assignable<yaul::variant<S11>,S11 const&>::value, "");
static_assert( std::is_nothrow_assignable<yaul::variant<S11>,S11&&>::value, "");

struct S12 
{
  S12& operator=(S12&) = default;       S12(S12&) = default;
  S12& operator=(S12 const&) = delete;
  S12& operator=(S12&&) = default;      S12(S12&&) = default;
};
static_assert( std::is_nothrow_assignable<S12,S12&>::value, "");
static_assert(!std::is_nothrow_assignable<S12,S12 const&>::value, "");
static_assert( std::is_nothrow_assignable<S12,S12&&>::value, "");
static_assert( std::is_nothrow_assignable<yaul::variant<S12>,S12&>::value, "");
static_assert(!std::is_nothrow_assignable<yaul::variant<S12>,S12 const&>::value, "");
static_assert( std::is_nothrow_assignable<yaul::variant<S12>,S12&&>::value, "");

void test__foo__01()
{
  YAUL_VARIANT_CHECK(true);
}

int main()
{
  test__foo__01();
  return YAUL_VARIANT_TEST_EXIT_CODE;
}
