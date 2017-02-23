// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <yaul/variant/detail/all_trivially_destructible.hpp>
#include <yaul/variant/variant_fwd.hpp>
#include <yaul/variant/recursive_variant.hpp>
#include <yaul/variant/detail/recursive_flag.hpp>
#include <yaul/variant/test_config.hpp>

using yaul::detail::variant::all_trivially_destructible;
using yaul::detail::variant::recursive_flag;
using yaul::recursive_variant_;
using yaul::variant;
using yaul::make_recursive_variant;

// primitive types
static_assert( all_trivially_destructible< variant<int> >::value, "");
static_assert( all_trivially_destructible< variant<int*> >::value, "");
static_assert( all_trivially_destructible< variant<int const*> >::value, "");
static_assert( all_trivially_destructible< variant<int&> >::value, "");
static_assert( all_trivially_destructible< variant<int const&> >::value, "");
static_assert( all_trivially_destructible< variant<int&&> >::value, "");

static_assert( all_trivially_destructible< variant<int,char> >::value, "");

static_assert( all_trivially_destructible< variant<int*,char> >::value, "");
static_assert( all_trivially_destructible< variant<int,char*> >::value, "");
static_assert( all_trivially_destructible< variant<int*,char*> >::value, "");
static_assert( all_trivially_destructible< variant<int const*,char const*> >::value, "");

static_assert( all_trivially_destructible< variant<int&,char> >::value, "");
static_assert( all_trivially_destructible< variant<int,char&> >::value, "");
static_assert( all_trivially_destructible< variant<int&,char&> >::value, "");
static_assert( all_trivially_destructible< variant<int const&,char const&> >::value, "");

static_assert( all_trivially_destructible< variant<int&&,char> >::value, "");
static_assert( all_trivially_destructible< variant<int,char&&> >::value, "");
static_assert( all_trivially_destructible< variant<int&&,char&&> >::value, "");

// custom structures
struct T {};
struct N { ~N(); };
template<typename...> struct F {};

static_assert( all_trivially_destructible< variant<int,T,char> >::value, "");
static_assert(!all_trivially_destructible< variant<int,N,char> >::value, "");
static_assert( all_trivially_destructible< variant<int,T&,char> >::value, "");
static_assert( all_trivially_destructible< variant<int,N&,char> >::value, "");
static_assert( all_trivially_destructible< variant<int,T*,char> >::value, "");
static_assert( all_trivially_destructible< variant<int,N*,char> >::value, "");

// handling recursive_flag
static_assert( all_trivially_destructible< variant<recursive_flag<int>,T,char> >::value, "");
static_assert( all_trivially_destructible< variant<recursive_flag<T>,T,char> >::value, "");
static_assert(!all_trivially_destructible< variant<recursive_flag<N>,T,char> >::value, "");

//
// handling recursive wrappers
//

// Reference/pointer recursion..
static_assert( all_trivially_destructible< variant<recursive_flag<int>,T,recursive_variant_&> >::value, "");
static_assert( all_trivially_destructible< variant<recursive_flag<int>,T,recursive_variant_ const&> >::value, "");
static_assert( all_trivially_destructible< variant<recursive_flag<int>,T,recursive_variant_ volatile&> >::value, "");
static_assert( all_trivially_destructible< variant<recursive_flag<int>,T,recursive_variant_ const volatile&> >::value, "");

static_assert( all_trivially_destructible< variant<recursive_flag<int>,T,recursive_variant_&&> >::value, "");
static_assert( all_trivially_destructible< variant<recursive_flag<int>,T,recursive_variant_ const&&> >::value, "");
static_assert( all_trivially_destructible< variant<recursive_flag<int>,T,recursive_variant_ volatile&&> >::value, "");
static_assert( all_trivially_destructible< variant<recursive_flag<int>,T,recursive_variant_ const volatile&&> >::value, "");

static_assert( all_trivially_destructible< variant<recursive_flag<int>,T,recursive_variant_*> >::value, "");
static_assert( all_trivially_destructible< variant<recursive_flag<int>,T,recursive_variant_ const*> >::value, "");
static_assert( all_trivially_destructible< variant<recursive_flag<int>,T,recursive_variant_ volatile*> >::value, "");
static_assert( all_trivially_destructible< variant<recursive_flag<int>,T,recursive_variant_ const volatile*> >::value, "");

static_assert( all_trivially_destructible< make_recursive_variant<int,T,F<recursive_variant_>& >::type >::value, "");
static_assert( all_trivially_destructible< make_recursive_variant<int,T,F<recursive_variant_> const& >::type >::value, "");
static_assert( all_trivially_destructible< make_recursive_variant<int,T,F<recursive_variant_> volatile& >::type >::value, "");
static_assert( all_trivially_destructible< make_recursive_variant<int,T,F<recursive_variant_> const volatile& >::type >::value, "");

static_assert( all_trivially_destructible< make_recursive_variant<int,T,F<recursive_variant_>&& >::type >::value, "");
static_assert( all_trivially_destructible< make_recursive_variant<int,T,F<recursive_variant_> const&& >::type >::value, "");
static_assert( all_trivially_destructible< make_recursive_variant<int,T,F<recursive_variant_> volatile&& >::type >::value, "");
static_assert( all_trivially_destructible< make_recursive_variant<int,T,F<recursive_variant_> const volatile&& >::type >::value, "");

static_assert( all_trivially_destructible< make_recursive_variant<int,T,F<recursive_variant_>* >::type >::value, "");
static_assert( all_trivially_destructible< make_recursive_variant<int,T,F<recursive_variant_> const* >::type >::value, "");
static_assert( all_trivially_destructible< make_recursive_variant<int,T,F<recursive_variant_> volatile* >::type >::value, "");
static_assert( all_trivially_destructible< make_recursive_variant<int,T,F<recursive_variant_> const volatile* >::type >::value, "");

// Value recursion
static_assert(!all_trivially_destructible< variant<recursive_flag<int>,T,recursive_variant_> >::value, "");
static_assert(!all_trivially_destructible< variant<recursive_flag<int>,T,recursive_variant_ const> >::value, "");
static_assert(!all_trivially_destructible< variant<recursive_flag<int>,T,recursive_variant_ volatile> >::value, "");
static_assert(!all_trivially_destructible< variant<recursive_flag<int>,T,recursive_variant_ const volatile> >::value, "");

static_assert(!all_trivially_destructible< make_recursive_variant<int,T,recursive_variant_>::type >::value, "");
static_assert(!all_trivially_destructible< make_recursive_variant<int,T,recursive_variant_ const>::type >::value, "");
static_assert(!all_trivially_destructible< make_recursive_variant<int,T,recursive_variant_ volatile>::type >::value, "");
static_assert(!all_trivially_destructible< make_recursive_variant<int,T,recursive_variant_ const volatile>::type >::value, "");

static_assert(!all_trivially_destructible< make_recursive_variant<int,T,F<recursive_variant_> >::type >::value, "");
static_assert(!all_trivially_destructible< make_recursive_variant<int,T,F<recursive_variant_ const> >::type >::value, "");
static_assert(!all_trivially_destructible< make_recursive_variant<int,T,F<recursive_variant_ volatile> >::type >::value, "");
static_assert(!all_trivially_destructible< make_recursive_variant<int,T,F<recursive_variant_ const volatile> >::type >::value, "");

int main()
{
  return YAUL_VARIANT_TEST_EXIT_CODE;
}
