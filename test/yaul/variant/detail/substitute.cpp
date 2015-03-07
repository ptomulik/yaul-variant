// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <yaul/variant/detail/substitute.hpp>
#include <yaul/variant/test_config.hpp>

void test__substitute__01()
{
  using namespace yaul::detail::variant;
  using std::is_same;

  // type and pointer substitution
  static_assert(is_same<substitute<int, char, double>::type, int>::value, "");
  static_assert(is_same<substitute<int, char, int>::type, char>::value, "");
  static_assert(is_same<substitute<int const, char, int>::type, char const>::value, "");
  static_assert(is_same<substitute<int volatile, char, int>::type, char volatile>::value, "");
  static_assert(is_same<substitute<int const volatile, char, int>::type, char const volatile>::value, "");
  static_assert(is_same<substitute<int&, char, int>::type, char&>::value, "");
  static_assert(is_same<substitute<int const&, char, int>::type, char const&>::value, "");
  static_assert(is_same<substitute<int volatile&, char, int>::type, char volatile&>::value, "");
  static_assert(is_same<substitute<int const volatile&, char, int>::type, char const volatile&>::value, "");
  static_assert(is_same<substitute<int&&, char, int>::type, char&&>::value, "");
  static_assert(is_same<substitute<int const&&, char, int>::type, char const&&>::value, "");
  static_assert(is_same<substitute<int volatile&&, char, int>::type, char volatile&&>::value, "");
  static_assert(is_same<substitute<int const volatile&&, char, int>::type, char const volatile&&>::value, "");
  static_assert(is_same<substitute<int*, char, int>::type, char*>::value, "");
  static_assert(is_same<substitute<int const*, char, int>::type, char const*>::value, "");
  static_assert(is_same<substitute<int volatile*, char, int>::type, char volatile*>::value, "");
  static_assert(is_same<substitute<int const volatile*, char, int>::type, char const volatile*>::value, "");
}

template<typename ...> struct F;
template<typename ...> struct G;

void test__substitute__02()
{
  using namespace yaul::detail::variant;
  using std::is_same;

  // template substitution
  static_assert(is_same<substitute<F<int, float, void>, char, double>::type, F<int,float,void> >::value, "");

  static_assert(is_same<substitute<F<int, float, void>, char, int>::type, F<char,float,void> >::value, "");
  static_assert(is_same<substitute<F<int, float, void> const, char, int>::type, F<char,float,void> const>::value, "");
  static_assert(is_same<substitute<F<int, float, void> volatile, char, int>::type, F<char,float,void> volatile>::value, "");
  static_assert(is_same<substitute<F<int, float, void> const volatile, char, int>::type, F<char,float,void> const volatile>::value, "");
  static_assert(is_same<substitute<F<int, float, void>&, char, int>::type, F<char,float,void>& >::value, "");
  static_assert(is_same<substitute<F<int, float, void> const&, char, int>::type, F<char,float,void> const&>::value, "");
  static_assert(is_same<substitute<F<int, float, void> volatile&, char, int>::type, F<char,float,void> volatile&>::value, "");
  static_assert(is_same<substitute<F<int, float, void> const volatile&, char, int>::type, F<char,float,void> const volatile&>::value, "");
  static_assert(is_same<substitute<F<int, float, void>&&, char, int>::type, F<char,float,void>&& >::value, "");
  static_assert(is_same<substitute<F<int, float, void> const&&, char, int>::type, F<char,float,void> const&&>::value, "");
  static_assert(is_same<substitute<F<int, float, void> volatile&&, char, int>::type, F<char,float,void> volatile&&>::value, "");
  static_assert(is_same<substitute<F<int, float, void> const volatile&&, char, int>::type, F<char,float,void> const volatile&&>::value, "");
  static_assert(is_same<substitute<F<int, float, void>*, char, int>::type, F<char,float,void>* >::value, "");
  static_assert(is_same<substitute<F<int, float, void> const*, char, int>::type, F<char,float,void> const*>::value, "");
  static_assert(is_same<substitute<F<int, float, void> volatile*, char, int>::type, F<char,float,void> volatile*>::value, "");
  static_assert(is_same<substitute<F<int, float, void> const volatile*, char, int>::type, F<char,float,void> const volatile*>::value, "");

  static_assert(is_same<substitute<F<int const, float, void>, char, int>::type, F<char const,float,void> >::value, "");
  static_assert(is_same<substitute<F<int const, float, void> const, char, int>::type, F<char const,float,void> const>::value, "");
  static_assert(is_same<substitute<F<int const, float, void> volatile, char, int>::type, F<char const,float,void> volatile>::value, "");
  static_assert(is_same<substitute<F<int const, float, void> const volatile, char, int>::type, F<char const,float,void> const volatile>::value, "");
  static_assert(is_same<substitute<F<int const, float, void>&, char, int>::type, F<char const,float,void>& >::value, "");
  static_assert(is_same<substitute<F<int const, float, void> const&, char, int>::type, F<char const,float,void> const&>::value, "");
  static_assert(is_same<substitute<F<int const, float, void> volatile&, char, int>::type, F<char const,float,void> volatile&>::value, "");
  static_assert(is_same<substitute<F<int const, float, void> const volatile&, char, int>::type, F<char const,float,void> const volatile&>::value, "");
  static_assert(is_same<substitute<F<int const, float, void>&&, char, int>::type, F<char const,float,void>&& >::value, "");
  static_assert(is_same<substitute<F<int const, float, void> const&&, char, int>::type, F<char const,float,void> const&&>::value, "");
  static_assert(is_same<substitute<F<int const, float, void> volatile&&, char, int>::type, F<char const,float,void> volatile&&>::value, "");
  static_assert(is_same<substitute<F<int const, float, void> const volatile&&, char, int>::type, F<char const,float,void> const volatile&&>::value, "");
  static_assert(is_same<substitute<F<int const, float, void>*, char, int>::type, F<char const,float,void>* >::value, "");
  static_assert(is_same<substitute<F<int const, float, void> const*, char, int>::type, F<char const,float,void> const*>::value, "");
  static_assert(is_same<substitute<F<int const, float, void> volatile*, char, int>::type, F<char const,float,void> volatile*>::value, "");
  static_assert(is_same<substitute<F<int const, float, void> const volatile*, char, int>::type, F<char const,float,void> const volatile*>::value, "");

  static_assert(is_same<substitute<F<int volatile, float, void>, char, int>::type, F<char volatile,float,void> >::value, "");
  static_assert(is_same<substitute<F<int volatile, float, void> const, char, int>::type, F<char volatile,float,void> const>::value, "");
  static_assert(is_same<substitute<F<int volatile, float, void> volatile, char, int>::type, F<char volatile,float,void> volatile>::value, "");
  static_assert(is_same<substitute<F<int volatile, float, void> const volatile, char, int>::type, F<char volatile,float,void> const volatile>::value, "");
  static_assert(is_same<substitute<F<int volatile, float, void>&, char, int>::type, F<char volatile,float,void>& >::value, "");
  static_assert(is_same<substitute<F<int volatile, float, void> const&, char, int>::type, F<char volatile,float,void> const&>::value, "");
  static_assert(is_same<substitute<F<int volatile, float, void> volatile&, char, int>::type, F<char volatile,float,void> volatile&>::value, "");
  static_assert(is_same<substitute<F<int volatile, float, void> const volatile&, char, int>::type, F<char volatile,float,void> const volatile&>::value, "");
  static_assert(is_same<substitute<F<int volatile, float, void>&&, char, int>::type, F<char volatile,float,void>&& >::value, "");
  static_assert(is_same<substitute<F<int volatile, float, void> const&&, char, int>::type, F<char volatile,float,void> const&&>::value, "");
  static_assert(is_same<substitute<F<int volatile, float, void> volatile&&, char, int>::type, F<char volatile,float,void> volatile&&>::value, "");
  static_assert(is_same<substitute<F<int volatile, float, void> const volatile&&, char, int>::type, F<char volatile,float,void> const volatile&&>::value, "");
  static_assert(is_same<substitute<F<int volatile, float, void>*, char, int>::type, F<char volatile,float,void>* >::value, "");
  static_assert(is_same<substitute<F<int volatile, float, void> const*, char, int>::type, F<char volatile,float,void> const*>::value, "");
  static_assert(is_same<substitute<F<int volatile, float, void> volatile*, char, int>::type, F<char volatile,float,void> volatile*>::value, "");
  static_assert(is_same<substitute<F<int volatile, float, void> const volatile*, char, int>::type, F<char volatile,float,void> const volatile*>::value, "");

  static_assert(is_same<substitute<F<int const volatile, float, void>, char, int>::type, F<char const volatile,float,void> >::value, "");
  static_assert(is_same<substitute<F<int const volatile, float, void> const, char, int>::type, F<char const volatile,float,void> const>::value, "");
  static_assert(is_same<substitute<F<int const volatile, float, void> volatile, char, int>::type, F<char const volatile,float,void> volatile>::value, "");
  static_assert(is_same<substitute<F<int const volatile, float, void> const volatile, char, int>::type, F<char const volatile,float,void> const volatile>::value, "");
  static_assert(is_same<substitute<F<int const volatile, float, void>&, char, int>::type, F<char const volatile,float,void>& >::value, "");
  static_assert(is_same<substitute<F<int const volatile, float, void> const&, char, int>::type, F<char const volatile,float,void> const&>::value, "");
  static_assert(is_same<substitute<F<int const volatile, float, void> volatile&, char, int>::type, F<char const volatile,float,void> volatile&>::value, "");
  static_assert(is_same<substitute<F<int const volatile, float, void> const volatile&, char, int>::type, F<char const volatile,float,void> const volatile&>::value, "");
  static_assert(is_same<substitute<F<int const volatile, float, void>&&, char, int>::type, F<char const volatile,float,void>&& >::value, "");
  static_assert(is_same<substitute<F<int const volatile, float, void> const&&, char, int>::type, F<char const volatile,float,void> const&&>::value, "");
  static_assert(is_same<substitute<F<int const volatile, float, void> volatile&&, char, int>::type, F<char const volatile,float,void> volatile&&>::value, "");
  static_assert(is_same<substitute<F<int const volatile, float, void> const volatile&&, char, int>::type, F<char const volatile,float,void> const volatile&&>::value, "");
  static_assert(is_same<substitute<F<int const volatile, float, void>*, char, int>::type, F<char const volatile,float,void>* >::value, "");
  static_assert(is_same<substitute<F<int const volatile, float, void> const*, char, int>::type, F<char const volatile,float,void> const*>::value, "");
  static_assert(is_same<substitute<F<int const volatile, float, void> volatile*, char, int>::type, F<char const volatile,float,void> volatile*>::value, "");
  static_assert(is_same<substitute<F<int const volatile, float, void> const volatile*, char, int>::type, F<char const volatile,float,void> const volatile*>::value, "");

  static_assert(is_same<substitute<F<int&, float, void>, char, int>::type, F<char&,float,void> >::value, "");
  static_assert(is_same<substitute<F<int&, float, void> const, char, int>::type, F<char&,float,void> const>::value, "");
  static_assert(is_same<substitute<F<int&, float, void> volatile, char, int>::type, F<char&,float,void> volatile>::value, "");
  static_assert(is_same<substitute<F<int&, float, void> const volatile, char, int>::type, F<char&,float,void> const volatile>::value, "");
  static_assert(is_same<substitute<F<int&, float, void>&, char, int>::type, F<char&,float,void>& >::value, "");
  static_assert(is_same<substitute<F<int&, float, void> const&, char, int>::type, F<char&,float,void> const&>::value, "");
  static_assert(is_same<substitute<F<int&, float, void> volatile&, char, int>::type, F<char&,float,void> volatile&>::value, "");
  static_assert(is_same<substitute<F<int&, float, void> const volatile&, char, int>::type, F<char&,float,void> const volatile&>::value, "");
  static_assert(is_same<substitute<F<int&, float, void>&&, char, int>::type, F<char&,float,void>&& >::value, "");
  static_assert(is_same<substitute<F<int&, float, void> const&&, char, int>::type, F<char&,float,void> const&&>::value, "");
  static_assert(is_same<substitute<F<int&, float, void> volatile&&, char, int>::type, F<char&,float,void> volatile&&>::value, "");
  static_assert(is_same<substitute<F<int&, float, void> const volatile&&, char, int>::type, F<char&,float,void> const volatile&&>::value, "");
  static_assert(is_same<substitute<F<int&, float, void>*, char, int>::type, F<char&,float,void>* >::value, "");
  static_assert(is_same<substitute<F<int&, float, void> const*, char, int>::type, F<char&,float,void> const*>::value, "");
  static_assert(is_same<substitute<F<int&, float, void> volatile*, char, int>::type, F<char&,float,void> volatile*>::value, "");
  static_assert(is_same<substitute<F<int&, float, void> const volatile*, char, int>::type, F<char&,float,void> const volatile*>::value, "");

  static_assert(is_same<substitute<F<int const&, float, void>, char, int>::type, F<char const&,float,void> >::value, "");
  static_assert(is_same<substitute<F<int const&, float, void> const, char, int>::type, F<char const&,float,void> const>::value, "");
  static_assert(is_same<substitute<F<int const&, float, void> volatile, char, int>::type, F<char const&,float,void> volatile>::value, "");
  static_assert(is_same<substitute<F<int const&, float, void> const volatile, char, int>::type, F<char const&,float,void> const volatile>::value, "");
  static_assert(is_same<substitute<F<int const&, float, void>&, char, int>::type, F<char const&,float,void>& >::value, "");
  static_assert(is_same<substitute<F<int const&, float, void> const&, char, int>::type, F<char const&,float,void> const&>::value, "");
  static_assert(is_same<substitute<F<int const&, float, void> volatile&, char, int>::type, F<char const&,float,void> volatile&>::value, "");
  static_assert(is_same<substitute<F<int const&, float, void> const volatile&, char, int>::type, F<char const&,float,void> const volatile&>::value, "");
  static_assert(is_same<substitute<F<int const&, float, void>&&, char, int>::type, F<char const&,float,void>&& >::value, "");
  static_assert(is_same<substitute<F<int const&, float, void> const&&, char, int>::type, F<char const&,float,void> const&&>::value, "");
  static_assert(is_same<substitute<F<int const&, float, void> volatile&&, char, int>::type, F<char const&,float,void> volatile&&>::value, "");
  static_assert(is_same<substitute<F<int const&, float, void> const volatile&&, char, int>::type, F<char const&,float,void> const volatile&&>::value, "");
  static_assert(is_same<substitute<F<int const&, float, void>*, char, int>::type, F<char const&,float,void>* >::value, "");
  static_assert(is_same<substitute<F<int const&, float, void> const*, char, int>::type, F<char const&,float,void> const*>::value, "");
  static_assert(is_same<substitute<F<int const&, float, void> volatile*, char, int>::type, F<char const&,float,void> volatile*>::value, "");
  static_assert(is_same<substitute<F<int const&, float, void> const volatile*, char, int>::type, F<char const&,float,void> const volatile*>::value, "");

  static_assert(is_same<substitute<F<int&&, float, void>, char, int>::type, F<char&&,float,void> >::value, "");
  static_assert(is_same<substitute<F<int&&, float, void> const, char, int>::type, F<char&&,float,void> const>::value, "");
  static_assert(is_same<substitute<F<int&&, float, void> volatile, char, int>::type, F<char&&,float,void> volatile>::value, "");
  static_assert(is_same<substitute<F<int&&, float, void> const volatile, char, int>::type, F<char&&,float,void> const volatile>::value, "");
  static_assert(is_same<substitute<F<int&&, float, void>&, char, int>::type, F<char&&,float,void>& >::value, "");
  static_assert(is_same<substitute<F<int&&, float, void> const&, char, int>::type, F<char&&,float,void> const&>::value, "");
  static_assert(is_same<substitute<F<int&&, float, void> volatile&, char, int>::type, F<char&&,float,void> volatile&>::value, "");
  static_assert(is_same<substitute<F<int&&, float, void> const volatile&, char, int>::type, F<char&&,float,void> const volatile&>::value, "");
  static_assert(is_same<substitute<F<int&&, float, void>&&, char, int>::type, F<char&&,float,void>&& >::value, "");
  static_assert(is_same<substitute<F<int&&, float, void> const&&, char, int>::type, F<char&&,float,void> const&&>::value, "");
  static_assert(is_same<substitute<F<int&&, float, void> volatile&&, char, int>::type, F<char&&,float,void> volatile&&>::value, "");
  static_assert(is_same<substitute<F<int&&, float, void> const volatile&&, char, int>::type, F<char&&,float,void> const volatile&&>::value, "");
  static_assert(is_same<substitute<F<int&&, float, void>*, char, int>::type, F<char&&,float,void>* >::value, "");
  static_assert(is_same<substitute<F<int&&, float, void> const*, char, int>::type, F<char&&,float,void> const*>::value, "");
  static_assert(is_same<substitute<F<int&&, float, void> volatile*, char, int>::type, F<char&&,float,void> volatile*>::value, "");
  static_assert(is_same<substitute<F<int&&, float, void> const volatile*, char, int>::type, F<char&&,float,void> const volatile*>::value, "");

  static_assert(is_same<substitute<F<int*, float, void>, char, int>::type, F<char*,float,void> >::value, "");
  static_assert(is_same<substitute<F<int*, float, void> const, char, int>::type, F<char*,float,void> const>::value, "");
  static_assert(is_same<substitute<F<int*, float, void> volatile, char, int>::type, F<char*,float,void> volatile>::value, "");
  static_assert(is_same<substitute<F<int*, float, void> const volatile, char, int>::type, F<char*,float,void> const volatile>::value, "");
  static_assert(is_same<substitute<F<int*, float, void>&, char, int>::type, F<char*,float,void>& >::value, "");
  static_assert(is_same<substitute<F<int*, float, void> const&, char, int>::type, F<char*,float,void> const&>::value, "");
  static_assert(is_same<substitute<F<int*, float, void> volatile&, char, int>::type, F<char*,float,void> volatile&>::value, "");
  static_assert(is_same<substitute<F<int*, float, void> const volatile&, char, int>::type, F<char*,float,void> const volatile&>::value, "");
  static_assert(is_same<substitute<F<int*, float, void>&&, char, int>::type, F<char*,float,void>&& >::value, "");
  static_assert(is_same<substitute<F<int*, float, void> const&&, char, int>::type, F<char*,float,void> const&&>::value, "");
  static_assert(is_same<substitute<F<int*, float, void> volatile&&, char, int>::type, F<char*,float,void> volatile&&>::value, "");
  static_assert(is_same<substitute<F<int*, float, void> const volatile&&, char, int>::type, F<char*,float,void> const volatile&&>::value, "");
  static_assert(is_same<substitute<F<int*, float, void>*, char, int>::type, F<char*,float,void>* >::value, "");
  static_assert(is_same<substitute<F<int*, float, void> const*, char, int>::type, F<char*,float,void> const*>::value, "");
  static_assert(is_same<substitute<F<int*, float, void> volatile*, char, int>::type, F<char*,float,void> volatile*>::value, "");
  static_assert(is_same<substitute<F<int*, float, void> const volatile*, char, int>::type, F<char*,float,void> const volatile*>::value, "");

  static_assert(is_same<substitute<F<int const*, float, void>, char, int>::type, F<char const*,float,void> >::value, "");
  static_assert(is_same<substitute<F<int const*, float, void> const, char, int>::type, F<char const*,float,void> const>::value, "");
  static_assert(is_same<substitute<F<int const*, float, void> volatile, char, int>::type, F<char const*,float,void> volatile>::value, "");
  static_assert(is_same<substitute<F<int const*, float, void> const volatile, char, int>::type, F<char const*,float,void> const volatile>::value, "");
  static_assert(is_same<substitute<F<int const*, float, void>&, char, int>::type, F<char const*,float,void>& >::value, "");
  static_assert(is_same<substitute<F<int const*, float, void> const&, char, int>::type, F<char const*,float,void> const&>::value, "");
  static_assert(is_same<substitute<F<int const*, float, void> volatile&, char, int>::type, F<char const*,float,void> volatile&>::value, "");
  static_assert(is_same<substitute<F<int const*, float, void> const volatile&, char, int>::type, F<char const*,float,void> const volatile&>::value, "");
  static_assert(is_same<substitute<F<int const*, float, void>&&, char, int>::type, F<char const*,float,void>&& >::value, "");
  static_assert(is_same<substitute<F<int const*, float, void> const&&, char, int>::type, F<char const*,float,void> const&&>::value, "");
  static_assert(is_same<substitute<F<int const*, float, void> volatile&&, char, int>::type, F<char const*,float,void> volatile&&>::value, "");
  static_assert(is_same<substitute<F<int const*, float, void> const volatile&&, char, int>::type, F<char const*,float,void> const volatile&&>::value, "");
  static_assert(is_same<substitute<F<int const*, float, void>*, char, int>::type, F<char const*,float,void>* >::value, "");
  static_assert(is_same<substitute<F<int const*, float, void> const*, char, int>::type, F<char const*,float,void> const*>::value, "");
  static_assert(is_same<substitute<F<int const*, float, void> volatile*, char, int>::type, F<char const*,float,void> volatile*>::value, "");
  static_assert(is_same<substitute<F<int const*, float, void> const volatile*, char, int>::type, F<char const*,float,void> const volatile*>::value, "");

  static_assert(is_same<substitute<F<int volatile*, float, void>, char, int>::type, F<char volatile*,float,void> >::value, "");
  static_assert(is_same<substitute<F<int volatile*, float, void> const, char, int>::type, F<char volatile*,float,void> const>::value, "");
  static_assert(is_same<substitute<F<int volatile*, float, void> volatile, char, int>::type, F<char volatile*,float,void> volatile>::value, "");
  static_assert(is_same<substitute<F<int volatile*, float, void> const volatile, char, int>::type, F<char volatile*,float,void> const volatile>::value, "");
  static_assert(is_same<substitute<F<int volatile*, float, void>&, char, int>::type, F<char volatile*,float,void>& >::value, "");
  static_assert(is_same<substitute<F<int volatile*, float, void> const&, char, int>::type, F<char volatile*,float,void> const&>::value, "");
  static_assert(is_same<substitute<F<int volatile*, float, void> volatile&, char, int>::type, F<char volatile*,float,void> volatile&>::value, "");
  static_assert(is_same<substitute<F<int volatile*, float, void> const volatile&, char, int>::type, F<char volatile*,float,void> const volatile&>::value, "");
  static_assert(is_same<substitute<F<int volatile*, float, void>&&, char, int>::type, F<char volatile*,float,void>&& >::value, "");
  static_assert(is_same<substitute<F<int volatile*, float, void> const&&, char, int>::type, F<char volatile*,float,void> const&&>::value, "");
  static_assert(is_same<substitute<F<int volatile*, float, void> volatile&&, char, int>::type, F<char volatile*,float,void> volatile&&>::value, "");
  static_assert(is_same<substitute<F<int volatile*, float, void> const volatile&&, char, int>::type, F<char volatile*,float,void> const volatile&&>::value, "");
  static_assert(is_same<substitute<F<int volatile*, float, void>*, char, int>::type, F<char volatile*,float,void>* >::value, "");
  static_assert(is_same<substitute<F<int volatile*, float, void> const*, char, int>::type, F<char volatile*,float,void> const*>::value, "");
  static_assert(is_same<substitute<F<int volatile*, float, void> volatile*, char, int>::type, F<char volatile*,float,void> volatile*>::value, "");
  static_assert(is_same<substitute<F<int volatile*, float, void> const volatile*, char, int>::type, F<char volatile*,float,void> const volatile*>::value, "");

  static_assert(is_same<substitute<F<int const volatile*, float, void>, char, int>::type, F<char const volatile*,float,void> >::value, "");
  static_assert(is_same<substitute<F<int const volatile*, float, void> const, char, int>::type, F<char const volatile*,float,void> const>::value, "");
  static_assert(is_same<substitute<F<int const volatile*, float, void> volatile, char, int>::type, F<char const volatile*,float,void> volatile>::value, "");
  static_assert(is_same<substitute<F<int const volatile*, float, void> const volatile, char, int>::type, F<char const volatile*,float,void> const volatile>::value, "");
  static_assert(is_same<substitute<F<int const volatile*, float, void>&, char, int>::type, F<char const volatile*,float,void>& >::value, "");
  static_assert(is_same<substitute<F<int const volatile*, float, void> const&, char, int>::type, F<char const volatile*,float,void> const&>::value, "");
  static_assert(is_same<substitute<F<int const volatile*, float, void> volatile&, char, int>::type, F<char const volatile*,float,void> volatile&>::value, "");
  static_assert(is_same<substitute<F<int const volatile*, float, void> const volatile&, char, int>::type, F<char const volatile*,float,void> const volatile&>::value, "");
  static_assert(is_same<substitute<F<int const volatile*, float, void>&&, char, int>::type, F<char const volatile*,float,void>&& >::value, "");
  static_assert(is_same<substitute<F<int const volatile*, float, void> const&&, char, int>::type, F<char const volatile*,float,void> const&&>::value, "");
  static_assert(is_same<substitute<F<int const volatile*, float, void> volatile&&, char, int>::type, F<char const volatile*,float,void> volatile&&>::value, "");
  static_assert(is_same<substitute<F<int const volatile*, float, void> const volatile&&, char, int>::type, F<char const volatile*,float,void> const volatile&&>::value, "");
  static_assert(is_same<substitute<F<int const volatile*, float, void>*, char, int>::type, F<char const volatile*,float,void>* >::value, "");
  static_assert(is_same<substitute<F<int const volatile*, float, void> const*, char, int>::type, F<char const volatile*,float,void> const*>::value, "");
  static_assert(is_same<substitute<F<int const volatile*, float, void> volatile*, char, int>::type, F<char const volatile*,float,void> volatile*>::value, "");
  static_assert(is_same<substitute<F<int const volatile*, float, void> const volatile*, char, int>::type, F<char const volatile*,float,void> const volatile*>::value, "");
}

void test__substitute__03()
{
  using namespace yaul::detail::variant;
  using std::is_same;

  struct T1;
  struct T2;

  // substitute T1 with T2
  static_assert(is_same<substitute<F<T1,double, F<char,T1> >, T2, T1>::type, F<T2, double, F<char,T2> > >::value, "");
  static_assert(is_same<substitute<F<T1 const, double, F<char,T1 volatile> >, T2, T1>::type, F<T2 const, double, F<char, T2 volatile> > >::value, "");
  static_assert(is_same<substitute<F<T1&,double, F<char,T1*> >, T2, T1>::type, F<T2&, double, F<char,T2*> > >::value, "");

  static_assert(is_same<substitute<F<T1,double, G<char,T1> >, T2, T1>::type, F<T2, double, G<char,T2> > >::value, "");
  static_assert(is_same<substitute<F<T1 const, double, G<char,T1 volatile> >, T2, T1>::type, F<T2 const, double, G<char, T2 volatile> > >::value, "");
  static_assert(is_same<substitute<F<T1&,double, G<char,T1*> >, T2, T1>::type, F<T2&, double, G<char,T2*> > >::value, "");
}

int main()
{
  test__substitute__01();
  test__substitute__02();
  test__substitute__03();
  return YAUL_VARIANT_TEST_EXIT_CODE;
}
