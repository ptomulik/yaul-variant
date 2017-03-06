// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <yaul/variant/detail/variadic_element.hpp>
#include <yaul/variant/test_config.hpp>

using yaul::detail::variant::variadic_element;

static_assert(std::is_same<variadic_element<0ul, int>::type, int>::value, "");
static_assert(std::is_same<variadic_element<0ul, int, char>::type, int>::value, "");
static_assert(std::is_same<variadic_element<1ul, int, char>::type, char>::value, "");

// Also, it must be usable for SFINAE
template<std::size_t Np>
struct S
{
  // SFINAEd-out for I > 2
  template<std::size_t I = Np>
  constexpr static typename variadic_element<I, int, float, double>::type
  cast(int i) noexcept
  { return static_cast<typename variadic_element<I, int, float, double>::type>(i); }

  constexpr static
  int orig(int i) noexcept
  { return i; }
};

#include <type_traits>

static_assert(S<0ul>::cast(2) == 2, "");
static_assert(S<1ul>::cast(2) == 2.0f, "");
static_assert(S<2ul>::cast(2) == 2.0, "");
static_assert(std::is_same<decltype(S<0ul>::cast(2)),int>::value, "");
static_assert(std::is_same<decltype(S<1ul>::cast(2)),float>::value, "");
static_assert(std::is_same<decltype(S<2ul>::cast(2)),double>::value, "");
// For I>2, S<I>::cast() is SFINAEd-out
static_assert(S<3ul>::orig(2) == 2, "");
static_assert(std::is_same<decltype(S<3ul>::orig(2)),int>::value, "");

int main()
{
  return YAUL_VARIANT_TEST_EXIT_CODE;
}
