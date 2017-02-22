// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <yaul/variant/variant.hpp>
#include <yaul/variant/test_config.hpp>

//
// play with constexprness of the variant
//
void test__constexpr__01()
{
  //constexpr yaul::variant<int> v;
  //YAUL_VARIANT_CHECK_EQUALS(v.which(), 0);
}

int main()
{
  test__constexpr__01();
  return YAUL_VARIANT_TEST_EXIT_CODE;
}
