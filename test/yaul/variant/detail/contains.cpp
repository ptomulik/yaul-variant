// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <yaul/variant/detail/contains.hpp>
#include <yaul/variant/recursive_wrapper_fwd.hpp>
#include <yaul/variant/test_config.hpp>
#include <type_traits>

using yaul::detail::variant::contains;
using yaul::variant;
using yaul::recursive_wrapper;
using yaul::make_recursive_variant;
using yaul::recursive_variant_;

// Predicate - matches int
static_assert( contains<int, variant<int> >::value,"");
static_assert( contains<int, variant<char, int, void> >::value,"");
static_assert( contains<int, variant<char, float, int> >::value,"");
static_assert(!contains<int, variant<char> >::value,"");
static_assert(!contains<int, variant<char,float> >::value,"");
static_assert( contains<int, variant<char, recursive_wrapper<int> > >::value, "");

#include <yaul/variant/detail/recursive_variant_fwd.hpp>
using yaul::detail::variant::recursive_variant;
static_assert(contains<int, variant<char, recursive_variant<int> > >::value, "");

#include <yaul/variant/recursive_variant.hpp>
#include <tuple>

void test__recursive_variant__01()
{
  {
    typedef make_recursive_variant<char, int, std::tuple<recursive_variant_> >::type V;
    static_assert( contains<char, V>::value, "");
    static_assert( contains<int, V>::value, "");
    static_assert( contains<std::tuple<V >, V>::value, "");
    static_assert(!contains<float, V>::value, "");
  }
}

int main()
{
  return YAUL_VARIANT_TEST_EXIT_CODE;
}
