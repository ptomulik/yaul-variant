// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <yaul/variant/detail/all.hpp>
#include <yaul/variant/recursive_wrapper_fwd.hpp>
#include <yaul/variant/test_config.hpp>
#include <type_traits>

using yaul::detail::variant::all;
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

static_assert(all<is<int>, variant<int> >::value == true,"");
static_assert(all<is<int>, variant<char, int, void> >::value == false,"");
static_assert(all<is<int>, variant<char, float, int> >::value == false,"");
static_assert(all<is<int>, variant<char> >::value == false,"");
static_assert(all<is<int>, variant<char,float> >::value == false,"");
static_assert(all<is<int>, variant<char, recursive_wrapper<int> > >::value == false, "");

#include <yaul/variant/detail/recursive_variant_fwd.hpp>
using yaul::detail::variant::recursive_variant;
static_assert(all<is<int>, variant<char, recursive_variant<int> > >::value == false, "");

#include <yaul/variant/recursive_variant.hpp>
#include <tuple>

void test__recursive_variant__01()
{
  {
    typedef make_recursive_variant<char, int, std::tuple<recursive_variant_> >::type V;
    static_assert(all<is_fundamental, V>::value == false, "");
  }
  {
    typedef variant<char, int, float> V;
    static_assert(all<is_fundamental, V>::value == true, "");
  }
}

int main()
{
  return YAUL_VARIANT_TEST_EXIT_CODE;
}
