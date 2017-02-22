// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <yaul/variant/detail/find_if.hpp>
#include <yaul/variant/recursive_wrapper_fwd.hpp>
#include <yaul/variant/test_config.hpp>
#include <type_traits>

using yaul::detail::variant::find_if;
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

static_assert(find_if<is<int>, variant<int> >::value == 0ul,"");
static_assert(find_if<is<int>, variant<char, int, void> >::value == 1ul,"");
static_assert(find_if<is<int>, variant<char, float, int> >::value == 2ul,"");
static_assert(find_if<is<int>, variant<char> >::value == 1ul,"");
static_assert(find_if<is<int>, variant<char,float> >::value == 2ul,"");
static_assert(find_if<is<int>, variant<char, recursive_wrapper<int> > >::value == 1ul, "");

#include <yaul/variant/detail/recursive_variant_fwd.hpp>
using yaul::detail::variant::recursive_variant;
static_assert(find_if<is<int>, variant<char, recursive_variant<int> > >::value == 1ul, "");

#include <yaul/variant/recursive_variant.hpp>
#include <tuple>

void test__recursive_variant__01()
{
  typedef make_recursive_variant<char, int, std::tuple<recursive_variant_> >::type V;
  static_assert(find_if<is<char>, V>::value == 0ul, "");
  static_assert(find_if<is<int>, V>::value == 1ul, "");
  static_assert(find_if<is<std::tuple<V> >, V>::value == 2ul, "");
}

int main()
{
  return YAUL_VARIANT_TEST_EXIT_CODE;
}
