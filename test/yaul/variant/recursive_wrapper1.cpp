// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <yaul/variant/recursive_wrapper.hpp>
#include <yaul/variant/variant.hpp>
#include <yaul/variant/apply_visitor.hpp>
#include <yaul/variant/test_config.hpp>
#include <type_traits>

void test__recursive_wrapper__01()
{
  using std::is_same;

  {
    yaul::recursive_wrapper<int> w{1};
    static_assert(is_same<decltype(w.get()), int&>::value, "");
    YAUL_VARIANT_CHECK_EQUALS(w.get(), 1);
  }
  {
    static_assert(is_same<decltype(yaul::recursive_wrapper<int>{1}.get()), int&>::value, "");
    YAUL_VARIANT_CHECK_EQUALS(yaul::recursive_wrapper<int>{1}.get(), 1);
  }
  {
    yaul::recursive_wrapper<int> w;
    w = 1;
    yaul::recursive_wrapper<int> w2{w};
    yaul::recursive_wrapper<int> w3{std::move(w)};

    YAUL_VARIANT_CHECK_EQUALS(w3.get(), 1);
    w3 = 2;
    YAUL_VARIANT_CHECK_EQUALS(w3.get(), 2);
  }
}

struct S02;

typedef yaul::variant<int, yaul::recursive_wrapper<S02> > X02;

struct S02
{
  X02 left;
  X02 right;
  S02( const X02& lhs, const X02& rhs )
    : left(lhs), right(rhs)
  { }
};

struct V02
{
  typedef int result_type; 
  int operator()(int i) const { return i; }
  int operator()(S02 const& x) const { return yaul::apply_visitor(*this, x.left) + yaul::apply_visitor(*this, x.right); }
};

void test__recursive_wrapper__02()
{
  {
    X02 l{1};
    X02 r{2};
    X02 x{S02{l,r}};

    YAUL_VARIANT_CHECK_EQUALS(yaul::apply_visitor(V02{}, x), 3);
    x = X02{4}; 
    YAUL_VARIANT_CHECK_EQUALS(yaul::apply_visitor(V02{}, x), 4);
  }

}

int main()
{
  test__recursive_wrapper__01();
  test__recursive_wrapper__02();
  return YAUL_VARIANT_TEST_EXIT_CODE;
}
