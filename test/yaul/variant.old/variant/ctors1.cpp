// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
// 
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <yaul/variant/variant.hpp>
#include <yaul/variant/test_config.hpp>
#include <type_traits>

//
// play a little bit with default-constructibility
//
struct S0 { S0() = delete; }; // non-default-constructible
static_assert( std::is_nothrow_default_constructible<yaul::variant<int,S0> >::value, "");
static_assert(!std::is_default_constructible<yaul::variant<S0,int> >::value, "");

struct S1 { S1() {} };        // default-constructible but not nothrow
static_assert( std::is_nothrow_default_constructible<yaul::variant<int,S1> >::value, "");
static_assert( std::is_default_constructible<yaul::variant<S1,int> >::value, "");
static_assert(!std::is_nothrow_default_constructible<yaul::variant<S1,int> >::value, "");

struct S2 { };
static_assert( std::is_nothrow_default_constructible<yaul::variant<S2> >::value, "");
static_assert( std::is_nothrow_default_constructible<yaul::variant<S2, int> >::value, "");
static_assert( std::is_nothrow_default_constructible<yaul::variant<S2, S1> >::value, "");
static_assert(!std::is_nothrow_default_constructible<yaul::variant<S1, S2> >::value, "");

// non-default-construtible type S in type list, but not on a first position
yaul::variant<int, S0> v0;
yaul::variant<int, S1> v1;

int main() { return YAUL_VARIANT_TEST_EXIT_CODE; }
