// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <yaul/variant/variant.hpp>
#include <yaul/variant/recursive_wrapper.hpp>
#include <yaul/variant/recursive_variant.hpp>
#include <yaul/variant/test_config.hpp>
#include <type_traits>
#include <utility>
#include <tuple>

using yaul::variant;
using yaul::make_recursive_variant;
using yaul::recursive_variant_;
using yaul::recursive_wrapper;

struct T { }; // trivially destructible
struct N { ~N() {} }; // non-trivially destructible
template<typename...> struct X{};

// these should be trivially destructible
static_assert( std::is_trivially_destructible<variant<int> >::value, "");
static_assert( std::is_trivially_destructible<variant<int, char, T> >::value, "");
static_assert( std::is_trivially_destructible<variant<int, char, X<N> > >::value, "");

// these should be non-trivially destructible
static_assert(!std::is_trivially_destructible<variant<N> >::value, "");
static_assert(!std::is_trivially_destructible<variant<int, char, N> >::value, "");

// recursive variants are not trivially destructible due to internal pointer management
static_assert(!std::is_trivially_destructible<make_recursive_variant<int, char, X<recursive_variant_> >::type>::value, "");
static_assert(!std::is_trivially_destructible<make_recursive_variant<T, char, recursive_variant_>::type>::value, "");
static_assert(!std::is_trivially_destructible<variant<int,char,recursive_wrapper<float> > >::value, "");
static_assert(!std::is_trivially_destructible<variant<int,char,recursive_wrapper<T> > >::value, "");
static_assert(!std::is_trivially_destructible<make_recursive_variant<N, char, recursive_variant_>::type>::value, "");

int main()
{
  return YAUL_VARIANT_TEST_EXIT_CODE;
}
