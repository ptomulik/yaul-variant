// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <yaul/variant/variant.hpp>
#include <yaul/variant/test_config.hpp>

void test__comp__01()
{
  yaul::variant<int,char> lhs{1}, rhs{1};

  static_assert(noexcept(lhs==rhs), "");
  static_assert(noexcept(lhs!=rhs), "");
  static_assert(noexcept(lhs<rhs), "");
  static_assert(noexcept(lhs>rhs), "");
  static_assert(noexcept(lhs<=rhs), "");
  static_assert(noexcept(lhs>=rhs), "");

  YAUL_VARIANT_CHECK(lhs == rhs);
  YAUL_VARIANT_CHECK(!(lhs != rhs));
  YAUL_VARIANT_CHECK(!(lhs < rhs));
  YAUL_VARIANT_CHECK(!(lhs > rhs));
  YAUL_VARIANT_CHECK(lhs <= rhs);
  YAUL_VARIANT_CHECK(lhs >= rhs);

  lhs = 2;
  YAUL_VARIANT_CHECK(!(lhs == rhs));
  YAUL_VARIANT_CHECK(lhs != rhs);
  YAUL_VARIANT_CHECK(!(lhs < rhs));
  YAUL_VARIANT_CHECK( (lhs > rhs));
  YAUL_VARIANT_CHECK(!(lhs <= rhs));
  YAUL_VARIANT_CHECK(lhs >= rhs);

  lhs = 1;
  rhs = 2;
  YAUL_VARIANT_CHECK(!(lhs == rhs));
  YAUL_VARIANT_CHECK(lhs != rhs);
  YAUL_VARIANT_CHECK( (lhs < rhs));
  YAUL_VARIANT_CHECK(!(lhs > rhs));
  YAUL_VARIANT_CHECK( (lhs <= rhs));
  YAUL_VARIANT_CHECK(!(lhs >= rhs));

  // lhs.which() < rhs.which()
  lhs = 97;
  rhs = 'a';
  YAUL_VARIANT_CHECK(lhs != rhs);
  YAUL_VARIANT_CHECK(lhs <  rhs);
  YAUL_VARIANT_CHECK(lhs <= rhs);
  YAUL_VARIANT_CHECK(!(lhs >  rhs));
  YAUL_VARIANT_CHECK(!(lhs >= rhs));

  // lhs.which() > rhs.which()
  lhs = 'a';
  rhs = 97;
  YAUL_VARIANT_CHECK(lhs != rhs);
  YAUL_VARIANT_CHECK(!(lhs <  rhs));
  YAUL_VARIANT_CHECK(!(lhs <= rhs));
  YAUL_VARIANT_CHECK(lhs >  rhs);
  YAUL_VARIANT_CHECK(lhs >= rhs);
}

int main()
{
  test__comp__01();
  return YAUL_VARIANT_TEST_EXIT_CODE;
}
