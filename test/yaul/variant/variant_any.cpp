// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <yaul/variant/variant_any.hpp>
#include <yaul/variant/recursive_wrapper_fwd.hpp>
#include <yaul/variant/test_config.hpp>
#include <type_traits>

using yaul::variant_any;
using yaul::variant;
using yaul::recursive_wrapper;
using yaul::make_recursive_variant;
using yaul::recursive_variant_;

// Predicate - matches int
template<typename T1>
struct is {
  template<typename T2>
    struct apply : std::is_same<T1,T2>
  { };
};

struct is_fundamental
{
  template<typename T>
    using apply = std::is_fundamental<T>;
};

static_assert( variant_any<is<int>, variant<int> >::value,"");
static_assert( variant_any<is<int>, variant<char, int, void> >::value,"");
static_assert( variant_any<is<int>, variant<char, float, int> >::value,"");
static_assert(!variant_any<is<int>, variant<char> >::value,"");
static_assert(!variant_any<is<int>, variant<char,float> >::value,"");
static_assert( variant_any<is<int>, variant<char, recursive_wrapper<int> > >::value, "");

#include <yaul/variant/detail/recursive_variant_fwd.hpp>
using yaul::detail::variant::recursive_variant;
static_assert(variant_any<is<int>, variant<char, recursive_variant<int> > >::value, "");

#include <yaul/variant/recursive_variant.hpp>
#include <tuple>

void test__recursive_variant__01()
{
  {
    typedef make_recursive_variant<char, int, std::tuple<recursive_variant_> >::type V;
    static_assert( variant_any<is<char>, V>::value, "");
    static_assert( variant_any<is<int>, V>::value, "");
    static_assert( variant_any<is<std::tuple<V> >, V>::value, "");
    static_assert(!variant_any<is<float>, V>::value, "");
    static_assert( variant_any<is_fundamental, V>::value, "");
  }
  {
    struct A { int a; };
    struct B { int b; };
    typedef variant<A, B> V;
    static_assert(!variant_any<is_fundamental, V>::value, "");
  }
}

int main()
{
  return YAUL_VARIANT_TEST_EXIT_CODE;
}
