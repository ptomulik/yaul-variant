// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <yaul/variant/${unit}.hpp>
#include <yaul/variant/test_config.hpp>

void test__foo__01()
{
  YAUL_VARIANT_CHECK(true);
}

int main()
{
  test__foo__01();
  return YAUL_VARIANT_TEST_EXIT_CODE;
}
