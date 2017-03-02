// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <yaul/variant/detail/substitute.hpp>
#include <yaul/variant/test_config.hpp>

using namespace yaul::detail::variant;
using std::is_same;

struct T;
struct T1;
struct T2;
template<typename ...> struct F;
template<typename ...> struct G;

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

// substituting types in a template with another type
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

static_assert(is_same<substitute<F<int volatile&, float, void>, char, int>::type, F<char volatile&,float,void> >::value, "");
static_assert(is_same<substitute<F<int volatile&, float, void> const, char, int>::type, F<char volatile&,float,void> const>::value, "");
static_assert(is_same<substitute<F<int volatile&, float, void> volatile, char, int>::type, F<char volatile&,float,void> volatile>::value, "");
static_assert(is_same<substitute<F<int volatile&, float, void> const volatile, char, int>::type, F<char volatile&,float,void> const volatile>::value, "");
static_assert(is_same<substitute<F<int volatile&, float, void>&, char, int>::type, F<char volatile&,float,void>& >::value, "");
static_assert(is_same<substitute<F<int volatile&, float, void> const&, char, int>::type, F<char volatile&,float,void> const&>::value, "");
static_assert(is_same<substitute<F<int volatile&, float, void> volatile&, char, int>::type, F<char volatile&,float,void> volatile&>::value, "");
static_assert(is_same<substitute<F<int volatile&, float, void> const volatile&, char, int>::type, F<char volatile&,float,void> const volatile&>::value, "");
static_assert(is_same<substitute<F<int volatile&, float, void>&&, char, int>::type, F<char volatile&,float,void>&& >::value, "");
static_assert(is_same<substitute<F<int volatile&, float, void> const&&, char, int>::type, F<char volatile&,float,void> const&&>::value, "");
static_assert(is_same<substitute<F<int volatile&, float, void> volatile&&, char, int>::type, F<char volatile&,float,void> volatile&&>::value, "");
static_assert(is_same<substitute<F<int volatile&, float, void> const volatile&&, char, int>::type, F<char volatile&,float,void> const volatile&&>::value, "");
static_assert(is_same<substitute<F<int volatile&, float, void>*, char, int>::type, F<char volatile&,float,void>* >::value, "");
static_assert(is_same<substitute<F<int volatile&, float, void> const*, char, int>::type, F<char volatile&,float,void> const*>::value, "");
static_assert(is_same<substitute<F<int volatile&, float, void> volatile*, char, int>::type, F<char volatile&,float,void> volatile*>::value, "");
static_assert(is_same<substitute<F<int volatile&, float, void> const volatile*, char, int>::type, F<char volatile&,float,void> const volatile*>::value, "");

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

// substitute T1 with T2
static_assert(is_same<substitute<F<T1,double, F<char,T1> >, T2, T1>::type, F<T2, double, F<char,T2> > >::value, "");
static_assert(is_same<substitute<F<T1 const, double, F<char,T1 volatile> >, T2, T1>::type, F<T2 const, double, F<char, T2 volatile> > >::value, "");
static_assert(is_same<substitute<F<T1&,double, F<char,T1*> >, T2, T1>::type, F<T2&, double, F<char,T2*> > >::value, "");

static_assert(is_same<substitute<F<T1,double, G<char,T1> >, T2, T1>::type, F<T2, double, G<char,T2> > >::value, "");
static_assert(is_same<substitute<F<T1 const, double, G<char,T1 volatile> >, T2, T1>::type, F<T2 const, double, G<char, T2 volatile> > >::value, "");
static_assert(is_same<substitute<F<T1&,double, G<char,T1*> >, T2, T1>::type, F<T2&, double, G<char,T2*> > >::value, "");

// T, F<T>, T
static_assert(is_same< substitute<T, F<T>, T>::type, F<T> >::value, "");
static_assert(is_same< substitute<T const, F<T>, T>::type, F<T> const>::value, "");
static_assert(is_same< substitute<T volatile, F<T>, T>::type, F<T> volatile>::value, "");
static_assert(is_same< substitute<T const volatile, F<T>, T>::type, F<T> const volatile>::value, "");

static_assert(is_same< substitute<T, F<T const>, T>::type, F<T const> >::value, "");
static_assert(is_same< substitute<T const, F<T const>, T>::type, F<T const> const>::value, "");
static_assert(is_same< substitute<T volatile, F<T const>, T>::type, F<T const> volatile>::value, "");
static_assert(is_same< substitute<T const volatile, F<T const>, T>::type, F<T const> const volatile>::value, "");

static_assert(is_same< substitute<T, F<T volatile>, T>::type, F<T volatile> >::value, "");
static_assert(is_same< substitute<T const, F<T volatile>, T>::type, F<T volatile> const>::value, "");
static_assert(is_same< substitute<T volatile, F<T volatile>, T>::type, F<T volatile> volatile>::value, "");
static_assert(is_same< substitute<T const volatile, F<T volatile>, T>::type, F<T volatile> const volatile>::value, "");

static_assert(is_same< substitute<T, F<T const volatile>, T>::type, F<T const volatile> >::value, "");
static_assert(is_same< substitute<T const, F<T const volatile>, T>::type, F<T const volatile> const>::value, "");
static_assert(is_same< substitute<T volatile, F<T const volatile>, T>::type, F<T const volatile> volatile>::value, "");
static_assert(is_same< substitute<T const volatile, F<T const volatile>, T>::type, F<T const volatile> const volatile>::value, "");

// T&, F<T>, T
static_assert(is_same< substitute<T&, F<T>, T>::type, F<T>& >::value, "");
static_assert(is_same< substitute<T const&, F<T>, T>::type, F<T> const&>::value, "");
static_assert(is_same< substitute<T volatile&, F<T>, T>::type, F<T> volatile&>::value, "");
static_assert(is_same< substitute<T const volatile&, F<T>, T>::type, F<T> const volatile&>::value, "");

static_assert(is_same< substitute<T&, F<T const>, T>::type, F<T const>& >::value, "");
static_assert(is_same< substitute<T const&, F<T const>, T>::type, F<T const> const&>::value, "");
static_assert(is_same< substitute<T volatile&, F<T const>, T>::type, F<T const> volatile&>::value, "");
static_assert(is_same< substitute<T const volatile&, F<T const>, T>::type, F<T const> const volatile&>::value, "");

static_assert(is_same< substitute<T&, F<T volatile>, T>::type, F<T volatile>& >::value, "");
static_assert(is_same< substitute<T const&, F<T volatile>, T>::type, F<T volatile> const&>::value, "");
static_assert(is_same< substitute<T volatile&, F<T volatile>, T>::type, F<T volatile> volatile&>::value, "");
static_assert(is_same< substitute<T const volatile&, F<T volatile>, T>::type, F<T volatile> const volatile&>::value, "");

static_assert(is_same< substitute<T&, F<T const volatile>, T>::type, F<T const volatile>& >::value, "");
static_assert(is_same< substitute<T const&, F<T const volatile>, T>::type, F<T const volatile> const&>::value, "");
static_assert(is_same< substitute<T volatile&, F<T const volatile>, T>::type, F<T const volatile> volatile&>::value, "");
static_assert(is_same< substitute<T const volatile&, F<T const volatile>, T>::type, F<T const volatile> const volatile&>::value, "");

// T&&, F<T>, T
static_assert(is_same< substitute<T&&, F<T>, T>::type, F<T>&& >::value, "");
static_assert(is_same< substitute<T const&&, F<T>, T>::type, F<T> const&&>::value, "");
static_assert(is_same< substitute<T volatile&&, F<T>, T>::type, F<T> volatile&&>::value, "");
static_assert(is_same< substitute<T const volatile&&, F<T>, T>::type, F<T> const volatile&&>::value, "");

static_assert(is_same< substitute<T&&, F<T const>, T>::type, F<T const>&& >::value, "");
static_assert(is_same< substitute<T const&&, F<T const>, T>::type, F<T const> const&&>::value, "");
static_assert(is_same< substitute<T volatile&&, F<T const>, T>::type, F<T const> volatile&&>::value, "");
static_assert(is_same< substitute<T const volatile&&, F<T const>, T>::type, F<T const> const volatile&&>::value, "");

static_assert(is_same< substitute<T&&, F<T volatile>, T>::type, F<T volatile>&& >::value, "");
static_assert(is_same< substitute<T const&&, F<T volatile>, T>::type, F<T volatile> const&&>::value, "");
static_assert(is_same< substitute<T volatile&&, F<T volatile>, T>::type, F<T volatile> volatile&&>::value, "");
static_assert(is_same< substitute<T const volatile&&, F<T volatile>, T>::type, F<T volatile> const volatile&&>::value, "");

static_assert(is_same< substitute<T&&, F<T const volatile>, T>::type, F<T const volatile>&& >::value, "");
static_assert(is_same< substitute<T const&&, F<T const volatile>, T>::type, F<T const volatile> const&&>::value, "");
static_assert(is_same< substitute<T volatile&&, F<T const volatile>, T>::type, F<T const volatile> volatile&&>::value, "");
static_assert(is_same< substitute<T const volatile&&, F<T const volatile>, T>::type, F<T const volatile> const volatile&&>::value, "");

// T*, F<T>, T
static_assert(is_same< substitute<T*, F<T>, T>::type, F<T>* >::value, "");
static_assert(is_same< substitute<T const*, F<T>, T>::type, F<T> const*>::value, "");
static_assert(is_same< substitute<T volatile*, F<T>, T>::type, F<T> volatile*>::value, "");
static_assert(is_same< substitute<T const volatile*, F<T>, T>::type, F<T> const volatile*>::value, "");

static_assert(is_same< substitute<T*, F<T const>, T>::type, F<T const>* >::value, "");
static_assert(is_same< substitute<T const*, F<T const>, T>::type, F<T const> const*>::value, "");
static_assert(is_same< substitute<T volatile*, F<T const>, T>::type, F<T const> volatile*>::value, "");
static_assert(is_same< substitute<T const volatile*, F<T const>, T>::type, F<T const> const volatile*>::value, "");

static_assert(is_same< substitute<T*, F<T volatile>, T>::type, F<T volatile>* >::value, "");
static_assert(is_same< substitute<T const*, F<T volatile>, T>::type, F<T volatile> const*>::value, "");
static_assert(is_same< substitute<T volatile*, F<T volatile>, T>::type, F<T volatile> volatile*>::value, "");
static_assert(is_same< substitute<T const volatile*, F<T volatile>, T>::type, F<T volatile> const volatile*>::value, "");

static_assert(is_same< substitute<T*, F<T const volatile>, T>::type, F<T const volatile>* >::value, "");
static_assert(is_same< substitute<T const*, F<T const volatile>, T>::type, F<T const volatile> const*>::value, "");
static_assert(is_same< substitute<T volatile*, F<T const volatile>, T>::type, F<T const volatile> volatile*>::value, "");
static_assert(is_same< substitute<T const volatile*, F<T const volatile>, T>::type, F<T const volatile> const volatile*>::value, "");

// T&, F<T&>, T
static_assert(is_same< substitute<T&, F<T&>, T>::type, F<T&>& >::value, "");
static_assert(is_same< substitute<T const&, F<T&>, T>::type, F<T&> const&>::value, "");
static_assert(is_same< substitute<T volatile&, F<T&>, T>::type, F<T&> volatile&>::value, "");
static_assert(is_same< substitute<T const volatile&, F<T&>, T>::type, F<T&> const volatile&>::value, "");

static_assert(is_same< substitute<T&, F<T const&>, T>::type, F<T const&>& >::value, "");
static_assert(is_same< substitute<T const&, F<T const&>, T>::type, F<T const&> const&>::value, "");
static_assert(is_same< substitute<T volatile&, F<T const&>, T>::type, F<T const&> volatile&>::value, "");
static_assert(is_same< substitute<T const volatile&, F<T const&>, T>::type, F<T const&> const volatile&>::value, "");

static_assert(is_same< substitute<T&, F<T volatile&>, T>::type, F<T volatile&>& >::value, "");
static_assert(is_same< substitute<T const&, F<T volatile&>, T>::type, F<T volatile&> const&>::value, "");
static_assert(is_same< substitute<T volatile&, F<T volatile&>, T>::type, F<T volatile&> volatile&>::value, "");
static_assert(is_same< substitute<T const volatile&, F<T volatile&>, T>::type, F<T volatile&> const volatile&>::value, "");

static_assert(is_same< substitute<T&, F<T const volatile&>, T>::type, F<T const volatile&>& >::value, "");
static_assert(is_same< substitute<T const&, F<T const volatile&>, T>::type, F<T const volatile&> const&>::value, "");
static_assert(is_same< substitute<T volatile&, F<T const volatile&>, T>::type, F<T const volatile&> volatile&>::value, "");
static_assert(is_same< substitute<T const volatile&, F<T const volatile&>, T>::type, F<T const volatile&> const volatile&>::value, "");

// T&&, F<T&&>, T
static_assert(is_same< substitute<T&&, F<T&&>, T>::type, F<T&&>&& >::value, "");
static_assert(is_same< substitute<T const&&, F<T&&>, T>::type, F<T&&> const&&>::value, "");
static_assert(is_same< substitute<T volatile&&, F<T&&>, T>::type, F<T&&> volatile&&>::value, "");
static_assert(is_same< substitute<T const volatile&&, F<T&&>, T>::type, F<T&&> const volatile&&>::value, "");

static_assert(is_same< substitute<T&&, F<T const&&>, T>::type, F<T const&&>&& >::value, "");
static_assert(is_same< substitute<T const&&, F<T const&&>, T>::type, F<T const&&> const&&>::value, "");
static_assert(is_same< substitute<T volatile&&, F<T const&&>, T>::type, F<T const&&> volatile&&>::value, "");
static_assert(is_same< substitute<T const volatile&&, F<T const&&>, T>::type, F<T const&&> const volatile&&>::value, "");

static_assert(is_same< substitute<T&&, F<T volatile&&>, T>::type, F<T volatile&&>&& >::value, "");
static_assert(is_same< substitute<T const&&, F<T volatile&&>, T>::type, F<T volatile&&> const&&>::value, "");
static_assert(is_same< substitute<T volatile&&, F<T volatile&&>, T>::type, F<T volatile&&> volatile&&>::value, "");
static_assert(is_same< substitute<T const volatile&&, F<T volatile&&>, T>::type, F<T volatile&&> const volatile&&>::value, "");

static_assert(is_same< substitute<T&&, F<T const volatile&&>, T>::type, F<T const volatile&&>&& >::value, "");
static_assert(is_same< substitute<T const&&, F<T const volatile&&>, T>::type, F<T const volatile&&> const&&>::value, "");
static_assert(is_same< substitute<T volatile&&, F<T const volatile&&>, T>::type, F<T const volatile&&> volatile&&>::value, "");
static_assert(is_same< substitute<T const volatile&&, F<T const volatile&&>, T>::type, F<T const volatile&&> const volatile&&>::value, "");

// T*, F<T*>, T
static_assert(is_same< substitute<T*, F<T*>, T>::type, F<T*>* >::value, "");
static_assert(is_same< substitute<T const*, F<T*>, T>::type, F<T*> const*>::value, "");
static_assert(is_same< substitute<T volatile*, F<T*>, T>::type, F<T*> volatile*>::value, "");
static_assert(is_same< substitute<T const volatile*, F<T*>, T>::type, F<T*> const volatile*>::value, "");

static_assert(is_same< substitute<T*, F<T const*>, T>::type, F<T const*>* >::value, "");
static_assert(is_same< substitute<T const*, F<T const*>, T>::type, F<T const*> const*>::value, "");
static_assert(is_same< substitute<T volatile*, F<T const*>, T>::type, F<T const*> volatile*>::value, "");
static_assert(is_same< substitute<T const volatile*, F<T const*>, T>::type, F<T const*> const volatile*>::value, "");

static_assert(is_same< substitute<T*, F<T volatile*>, T>::type, F<T volatile*>* >::value, "");
static_assert(is_same< substitute<T const*, F<T volatile*>, T>::type, F<T volatile*> const*>::value, "");
static_assert(is_same< substitute<T volatile*, F<T volatile*>, T>::type, F<T volatile*> volatile*>::value, "");
static_assert(is_same< substitute<T const volatile*, F<T volatile*>, T>::type, F<T volatile*> const volatile*>::value, "");

static_assert(is_same< substitute<T*, F<T const volatile*>, T>::type, F<T const volatile*>* >::value, "");
static_assert(is_same< substitute<T const*, F<T const volatile*>, T>::type, F<T const volatile*> const*>::value, "");
static_assert(is_same< substitute<T volatile*, F<T const volatile*>, T>::type, F<T const volatile*> volatile*>::value, "");
static_assert(is_same< substitute<T const volatile*, F<T const volatile*>, T>::type, F<T const volatile*> const volatile*>::value, "");

int main()
{
  return YAUL_VARIANT_TEST_EXIT_CODE;
}
