// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <yaul/variant/recursive_variant_tag.hpp>
#include <yaul/variant/test_config.hpp>
#include <type_traits>

typedef yaul::recursive_variant_tag tag;
typedef yaul::recursive_variant_    tag_alias;

static_assert(std::is_same<yaul::recursive_variant_tag, yaul::recursive_variant_>::value, "");

int main()
{
  return YAUL_VARIANT_TEST_EXIT_CODE;
}
