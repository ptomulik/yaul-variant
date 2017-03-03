// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <yaul/variant/detail/checked_delete.hpp>
#include <yaul/variant/test_config.hpp>


// it seems to be impossible to test real purpose of checked_delete,
// but we may at least test existence of the functions

struct S
{
  static int count;
  S() { ++count; }
  S(S const&) { ++count; }
  ~S() { --count; }
};

int S::count = 0;

using yaul::detail::variant::checked_delete;
using yaul::detail::variant::checked_array_delete;

int main()
{
  {
    S* s = new S();
    YAUL_VARIANT_CHECK_EQUALS(S::count, 1);
    checked_delete(s);
    YAUL_VARIANT_CHECK_EQUALS(S::count, 0);
  }

  {
    S* s = new S[2];
    YAUL_VARIANT_CHECK_EQUALS(S::count, 2);
    checked_array_delete(s);
    YAUL_VARIANT_CHECK_EQUALS(S::count, 0);
  }
  return YAUL_VARIANT_TEST_EXIT_CODE;
}
