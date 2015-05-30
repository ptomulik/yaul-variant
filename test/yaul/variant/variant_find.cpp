// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <yaul/variant/variant_find.hpp>
#include <yaul/variant/recursive_wrapper_fwd.hpp>
#include <yaul/variant/test_config.hpp>

using yaul::variant_find;
using yaul::variant;
using yaul::recursive_wrapper;

static_assert(variant_find<int, variant<int> >::value == 0ul,"");
static_assert(variant_find<int, variant<char, int, void> >::value == 1ul,"");
static_assert(variant_find<int, variant<char, float, int> >::value == 2ul,"");
static_assert(variant_find<int, variant<char> >::value == 1ul,"");
static_assert(variant_find<int, variant<char,float> >::value == 2ul,"");
static_assert(variant_find<int, variant<char, recursive_wrapper<int> > >::value == 1ul, "");

#include <yaul/variant/detail/recursive_variant_fwd.hpp>
using yaul::detail::variant::recursive_variant;
static_assert(variant_find<int, variant<char, recursive_variant<int> > >::value == 1ul, "");

#include <yaul/variant/recursive_variant.hpp>
#include <tuple>
using yaul::make_recursive_variant;
using yaul::recursive_variant_;
static_assert(variant_find<char, make_recursive_variant<char, int, std::tuple<recursive_variant_> >::type>::value == 0ul, "");
static_assert(variant_find<int, make_recursive_variant<char, int, std::tuple<recursive_variant_> >::type>::value == 1ul, "");
static_assert(variant_find<std::tuple<recursive_variant_>, make_recursive_variant<char, int, std::tuple<recursive_variant_> >::type>::value == 2ul, "");

int main()
{
  return YAUL_VARIANT_TEST_EXIT_CODE;
}
