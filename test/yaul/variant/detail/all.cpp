// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <yaul/variant/detail/all.hpp>
#include <yaul/variant/test_config.hpp>

using yaul::detail::variant::all;

static_assert( all<>::value, "");
static_assert( all<true>::value, "");
static_assert(!all<false>::value, "");
static_assert(!all<true, false>::value, "");
static_assert(!all<false, true>::value, "");
static_assert(!all<false, false>::value, "");

static_assert( all<true>::value, "");
static_assert( all<true, true>::value, "");
static_assert( all<true, true, true>::value, "");

int main()
{
  return YAUL_VARIANT_TEST_EXIT_CODE;
}
