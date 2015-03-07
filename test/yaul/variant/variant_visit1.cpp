// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <yaul/variant/variant.hpp>
#include <yaul/variant/test_config.hpp>

void test__visit__01()
{
  static int last;
  struct Visitor
  {
    typedef void result_type;
    result_type operator()(int&) & noexcept             { last = 11; }
    result_type operator()(int const&) & noexcept       { last = 12; }
    result_type operator()(int&&) & noexcept            { last = 13; }
    result_type operator()(int&) const & noexcept       { last = 21; }
    result_type operator()(int const&) const & noexcept { last = 22; }
    result_type operator()(int&&) const & noexcept      { last = 23; }
    result_type operator()(int&) && noexcept            { last = 31; }
    result_type operator()(int const&) && noexcept      { last = 32; }
    result_type operator()(int&&) && noexcept           { last = 33; }
  };
  using Variant = yaul::variant<int>;


  Visitor visitor;
  Variant var{10};

  last = 0;

  var.apply_visitor(visitor);
  YAUL_VARIANT_CHECK_EQUALS(last, 11);

  const_cast<const Variant&>(var).apply_visitor(visitor);
  YAUL_VARIANT_CHECK_EQUALS(last, 12);

  Variant{2}.apply_visitor(visitor);
  YAUL_VARIANT_CHECK_EQUALS(last, 13);

  var.apply_visitor(static_cast<const Visitor&>(visitor));
  YAUL_VARIANT_CHECK_EQUALS(last, 21);

  const_cast<const Variant&>(var).apply_visitor(static_cast<const Visitor&>(visitor));
  YAUL_VARIANT_CHECK_EQUALS(last, 22);

  Variant{2}.apply_visitor(static_cast<const Visitor&>(visitor));
  YAUL_VARIANT_CHECK_EQUALS(last, 23);

  var.apply_visitor(Visitor());
  YAUL_VARIANT_CHECK_EQUALS(last, 31);

  const_cast<const Variant&>(var).apply_visitor(Visitor{});
  YAUL_VARIANT_CHECK_EQUALS(last, 32);

  Variant{2}.apply_visitor(Visitor{});
  YAUL_VARIANT_CHECK_EQUALS(last, 33);
}

void test__visit__02()
{
  struct Visitor
  {
    typedef int result_type;
    result_type operator()(int) const noexcept    { return 1; }
    result_type operator()(float) const noexcept  { return 2; }
    result_type operator()(char) const noexcept   { return 3; }
  };

  using Variant = yaul::variant<int, float, char>;

  //
  {
    Variant x1{1};
    const Variant x2{1};
    Visitor v1;
    const Visitor v2{};
    YAUL_VARIANT_CHECK_EQUALS(Variant{1}.apply_visitor(Visitor{}),      1);
    YAUL_VARIANT_CHECK_EQUALS(Variant{1}.apply_visitor(v1),             1);
    YAUL_VARIANT_CHECK_EQUALS(Variant{1}.apply_visitor(v2),             1);
    YAUL_VARIANT_CHECK_EQUALS(x1.apply_visitor(Visitor{}),              1);
    YAUL_VARIANT_CHECK_EQUALS(x1.apply_visitor(v1),                     1);
    YAUL_VARIANT_CHECK_EQUALS(x1.apply_visitor(v2),                     1);
    YAUL_VARIANT_CHECK_EQUALS(x2.apply_visitor(Visitor{}),              1);
    YAUL_VARIANT_CHECK_EQUALS(x2.apply_visitor(v1),                     1);
    YAUL_VARIANT_CHECK_EQUALS(x2.apply_visitor(v2),                     1);
  }
  {
    Variant x1{1.23f};
    const Variant x2{1.23f};
    Visitor v1;
    const Visitor v2{};
    YAUL_VARIANT_CHECK_EQUALS(Variant{1.23f}.apply_visitor(Visitor{}),  2);
    YAUL_VARIANT_CHECK_EQUALS(Variant{1.23f}.apply_visitor(v1),         2);
    YAUL_VARIANT_CHECK_EQUALS(Variant{1.23f}.apply_visitor(v2),         2);
    YAUL_VARIANT_CHECK_EQUALS(x1.apply_visitor(Visitor{}),              2);
    YAUL_VARIANT_CHECK_EQUALS(x1.apply_visitor(v1),                     2);
    YAUL_VARIANT_CHECK_EQUALS(x1.apply_visitor(v2),                     2);
    YAUL_VARIANT_CHECK_EQUALS(x2.apply_visitor(Visitor{}),              2);
    YAUL_VARIANT_CHECK_EQUALS(x2.apply_visitor(v1),                     2);
    YAUL_VARIANT_CHECK_EQUALS(x2.apply_visitor(v2),                     2);
  }
  {
    Variant x1{'a'};
    const Variant x2{'a'};
    Visitor v1;
    const Visitor v2{};
    YAUL_VARIANT_CHECK_EQUALS(Variant{'a'}.apply_visitor(Visitor{}),    3);
    YAUL_VARIANT_CHECK_EQUALS(Variant{'a'}.apply_visitor(v1),           3);
    YAUL_VARIANT_CHECK_EQUALS(Variant{'a'}.apply_visitor(v2),           3);
    YAUL_VARIANT_CHECK_EQUALS(x1.apply_visitor(Visitor{}),              3);
    YAUL_VARIANT_CHECK_EQUALS(x1.apply_visitor(v1),                     3);
    YAUL_VARIANT_CHECK_EQUALS(x1.apply_visitor(v2),                     3);
    YAUL_VARIANT_CHECK_EQUALS(x2.apply_visitor(Visitor{}),              3);
    YAUL_VARIANT_CHECK_EQUALS(x2.apply_visitor(v1),                     3);
    YAUL_VARIANT_CHECK_EQUALS(x2.apply_visitor(v2),                     3);
  }
}

int main()
{
  test__visit__01();
  test__visit__02();
  return YAUL_VARIANT_TEST_EXIT_CODE;
}
