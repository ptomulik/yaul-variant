// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <yaul/variant/detail/is_nonrecursive_trivially_destructible.hpp>
#include <yaul/variant/test_config.hpp>

using yaul::detail::variant::is_nonrecursive_trivially_destructible;


static_assert(is_nonrecursive_trivially_destructible<int>::value, "");
static_assert(is_nonrecursive_trivially_destructible<int const>::value, "");
static_assert(is_nonrecursive_trivially_destructible<int volatile>::value, "");
static_assert(is_nonrecursive_trivially_destructible<int const volatile>::value, "");
static_assert(is_nonrecursive_trivially_destructible<int&>::value, "");
static_assert(is_nonrecursive_trivially_destructible<int const&>::value, "");
static_assert(is_nonrecursive_trivially_destructible<int volatile&>::value, "");
static_assert(is_nonrecursive_trivially_destructible<int const volatile&>::value, "");
static_assert(is_nonrecursive_trivially_destructible<int&&>::value, "");
static_assert(is_nonrecursive_trivially_destructible<int const&&>::value, "");
static_assert(is_nonrecursive_trivially_destructible<int volatile&&>::value, "");
static_assert(is_nonrecursive_trivially_destructible<int const volatile&&>::value, "");
static_assert(is_nonrecursive_trivially_destructible<int*>::value, "");
static_assert(is_nonrecursive_trivially_destructible<int const*>::value, "");
static_assert(is_nonrecursive_trivially_destructible<int volatile*>::value, "");
static_assert(is_nonrecursive_trivially_destructible<int const volatile*>::value, "");

struct T {};
struct N { ~N(){} };
template<typename...> struct F{};

static_assert( is_nonrecursive_trivially_destructible<T>::value, "");
static_assert( is_nonrecursive_trivially_destructible< F<T> >::value, "");
static_assert( is_nonrecursive_trivially_destructible< F<N> >::value, "");
static_assert(!is_nonrecursive_trivially_destructible<N>::value, "");

#include <yaul/variant/variant.hpp>

using yaul::variant;
static_assert( is_nonrecursive_trivially_destructible< variant<T,int> >::value, "");
static_assert(!is_nonrecursive_trivially_destructible< variant<T,N> >::value, "");

#include <yaul/variant/recursive_variant.hpp>
using yaul::make_recursive_variant;
using yaul::recursive_variant_;
static_assert(!is_nonrecursive_trivially_destructible<make_recursive_variant<T,int,recursive_variant_>::type>::value, "");
static_assert(!is_nonrecursive_trivially_destructible<make_recursive_variant<T,int,F<recursive_variant_> >::type>::value, "");
static_assert( is_nonrecursive_trivially_destructible<make_recursive_variant<T,int,F<recursive_variant_>&>::type>::value, "");
static_assert( is_nonrecursive_trivially_destructible<make_recursive_variant<T,int,F<recursive_variant_> const&>::type>::value, "");
static_assert( is_nonrecursive_trivially_destructible<make_recursive_variant<T,int,F<recursive_variant_> volatile&>::type>::value, "");
static_assert( is_nonrecursive_trivially_destructible<make_recursive_variant<T,int,F<recursive_variant_> const volatile&>::type>::value, "");

int main()
{
  return YAUL_VARIANT_TEST_EXIT_CODE;
}
