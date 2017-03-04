// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <yaul/variant/detail/enable_recursive.hpp>
#include <yaul/variant/test_config.hpp>


template <typename...> struct V; // emulates yaul::variant<...>
template <typename...> struct F; // emulates any template, e.g. std::vector

using yaul::detail::variant::enable_recursive;
using yaul::recursive_variant_tag;
using yaul::recursive_wrapper;
using std::is_same;

typedef V<int, char, recursive_variant_tag> R;
static_assert(is_same<enable_recursive<int, R>::type, int>::value, "");

static_assert(is_same<enable_recursive<recursive_variant_tag, R>::type, recursive_wrapper<R> >::value, "");
static_assert(is_same<enable_recursive<recursive_variant_tag const, R>::type, recursive_wrapper<R> const>::value, "");
static_assert(is_same<enable_recursive<recursive_variant_tag volatile, R>::type, recursive_wrapper<R> volatile>::value, "");
static_assert(is_same<enable_recursive<recursive_variant_tag const volatile, R>::type, recursive_wrapper<R> const volatile>::value, "");

static_assert(is_same<enable_recursive<recursive_variant_tag&, R>::type, R& >::value, "");
static_assert(is_same<enable_recursive<recursive_variant_tag const&, R>::type, R const&>::value, "");
static_assert(is_same<enable_recursive<recursive_variant_tag volatile&, R>::type, R volatile&>::value, "");
static_assert(is_same<enable_recursive<recursive_variant_tag const volatile&, R>::type, R const volatile&>::value, "");

static_assert(is_same<enable_recursive<recursive_variant_tag&&, R>::type, R&& >::value, "");
static_assert(is_same<enable_recursive<recursive_variant_tag const&&, R>::type, R const&&>::value, "");
static_assert(is_same<enable_recursive<recursive_variant_tag volatile&&, R>::type, R volatile&&>::value, "");
static_assert(is_same<enable_recursive<recursive_variant_tag const volatile&&, R>::type, R const volatile&&>::value, "");

static_assert(is_same<enable_recursive<recursive_variant_tag*, R>::type, R* >::value, "");
static_assert(is_same<enable_recursive<recursive_variant_tag const*, R>::type, R const*>::value, "");
static_assert(is_same<enable_recursive<recursive_variant_tag volatile*, R>::type, R volatile*>::value, "");
static_assert(is_same<enable_recursive<recursive_variant_tag const volatile*, R>::type, R const volatile*>::value, "");

static_assert(is_same<enable_recursive<R, R>::type, recursive_wrapper<V<int, char, V<int, char, recursive_variant_tag> > > >::value, "");
static_assert(is_same<enable_recursive<R, R>::type, recursive_wrapper<V<int, char, V<int, char, recursive_variant_tag> > > >::value, "");
static_assert(is_same<enable_recursive<F<recursive_variant_tag>, R>::type, recursive_wrapper<F<V<int, char, recursive_variant_tag> > > >::value, "");

int main()
{
  return YAUL_VARIANT_TEST_EXIT_CODE;
}
