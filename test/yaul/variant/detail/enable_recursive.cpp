// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <yaul/variant/detail/enable_recursive.hpp>
#include <yaul/variant/test_config.hpp>


template <typename...> struct V; // emulates yaul::variant<...>
template <typename...> struct F; // emulates any template, e.g. std::vector

void test__enable_recursive__01()
{
  using namespace yaul::detail::variant;
  using yaul::detail::variant::recursive_variant;
  using yaul::recursive_variant_;
  //using yaul::recursive_wrapper;
  using std::is_same;

  typedef V<int, char, recursive_variant_> R;
  static_assert(is_same<enable_recursive<int, R>::type, int>::value, "");

  static_assert(is_same<enable_recursive<recursive_variant_, R>::type, recursive_variant<R> >::value, "");
  static_assert(is_same<enable_recursive<recursive_variant_ const, R>::type, recursive_variant<R> const>::value, "");
  static_assert(is_same<enable_recursive<recursive_variant_ volatile, R>::type, recursive_variant<R> volatile>::value, "");
  static_assert(is_same<enable_recursive<recursive_variant_ const volatile, R>::type, recursive_variant<R> const volatile>::value, "");

  static_assert(is_same<enable_recursive<recursive_variant_&, R>::type, R& >::value, "");
  static_assert(is_same<enable_recursive<recursive_variant_ const&, R>::type, R const&>::value, "");
  static_assert(is_same<enable_recursive<recursive_variant_ volatile&, R>::type, R volatile&>::value, "");
  static_assert(is_same<enable_recursive<recursive_variant_ const volatile&, R>::type, R const volatile&>::value, "");

  static_assert(is_same<enable_recursive<recursive_variant_&&, R>::type, R&& >::value, "");
  static_assert(is_same<enable_recursive<recursive_variant_ const&&, R>::type, R const&&>::value, "");
  static_assert(is_same<enable_recursive<recursive_variant_ volatile&&, R>::type, R volatile&&>::value, "");
  static_assert(is_same<enable_recursive<recursive_variant_ const volatile&&, R>::type, R const volatile&&>::value, "");

  static_assert(is_same<enable_recursive<recursive_variant_*, R>::type, R* >::value, "");
  static_assert(is_same<enable_recursive<recursive_variant_ const*, R>::type, R const*>::value, "");
  static_assert(is_same<enable_recursive<recursive_variant_ volatile*, R>::type, R volatile*>::value, "");
  static_assert(is_same<enable_recursive<recursive_variant_ const volatile*, R>::type, R const volatile*>::value, "");

  static_assert(is_same<enable_recursive<R, R>::type, recursive_variant<V<int, char, V<int, char, recursive_variant_> > > >::value, "");
  static_assert(is_same<enable_recursive<R, R>::type, recursive_variant<V<int, char, V<int, char, recursive_variant_> > > >::value, "");
  static_assert(is_same<enable_recursive<F<recursive_variant_>, R>::type, recursive_variant<F<V<int, char, recursive_variant_> > > >::value, "");
}

int main()
{
  test__enable_recursive__01();
  return YAUL_VARIANT_TEST_EXIT_CODE;
}
