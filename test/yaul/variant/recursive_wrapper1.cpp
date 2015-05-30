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
    static_assert(is_same<decltype(yaul::recursive_wrapper<int>{1}.get()), int&&>::value, "");
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

template<typename> struct F01;
template<typename> struct F02;

namespace yaul { namespace detail {
template< typename T >
  struct is_recursive_wrapper_impl<F02<T> >
    : std::integral_constant<bool, true>
    { };
} } // end namespace yaul::detail

void test__is_recursive_wrapper__01()
{
  
  static_assert(!yaul::is_recursive_wrapper<int>::value, "");
  static_assert(!yaul::is_recursive_wrapper<F01<int> >::value, "");
  static_assert( yaul::is_recursive_wrapper<F02<int> >::value, "");
  static_assert( yaul::is_recursive_wrapper<const F02<int> >::value, "");
  static_assert( yaul::is_recursive_wrapper<volatile F02<int> >::value, "");
  static_assert( yaul::is_recursive_wrapper<const volatile F02<int> >::value, "");
  static_assert( yaul::is_recursive_wrapper<yaul::recursive_wrapper<int> >::value, "");
  static_assert( yaul::is_recursive_wrapper<const yaul::recursive_wrapper<int> >::value, "");
  static_assert( yaul::is_recursive_wrapper<volatile yaul::recursive_wrapper<int> >::value, "");
  static_assert( yaul::is_recursive_wrapper<const volatile yaul::recursive_wrapper<int> >::value, "");
}

void test__unwrap_recursive_wrapper__01()
{
  static_assert(std::is_same<yaul::unwrap_recursive_wrapper<int>::type, int>::value, "");
  static_assert(std::is_same<yaul::unwrap_recursive_wrapper<F01<int> >::type, F01<int> >::value, "");
  static_assert(std::is_same<yaul::unwrap_recursive_wrapper<F02<int> >::type, int>::value, "");
  static_assert(std::is_same<yaul::unwrap_recursive_wrapper<const F02<int> >::type, const int>::value, "");
  static_assert(std::is_same<yaul::unwrap_recursive_wrapper<volatile F02<int> >::type, volatile int>::value, "");
  static_assert(std::is_same<yaul::unwrap_recursive_wrapper<const volatile F02<int> >::type, const volatile int>::value, "");
  static_assert(std::is_same<yaul::unwrap_recursive_wrapper<yaul::recursive_wrapper<int> >::type, int>::value, "");
  static_assert(std::is_same<yaul::unwrap_recursive_wrapper<const yaul::recursive_wrapper<int> >::type, const int>::value, "");
  static_assert(std::is_same<yaul::unwrap_recursive_wrapper<volatile yaul::recursive_wrapper<int> >::type, volatile int>::value, "");
  static_assert(std::is_same<yaul::unwrap_recursive_wrapper<const volatile yaul::recursive_wrapper<int> >::type, const volatile int>::value, "");
}

int main()
{
  test__recursive_wrapper__01();
  test__recursive_wrapper__02();
  test__is_recursive_wrapper__01();
  test__unwrap_recursive_wrapper__01();
  return YAUL_VARIANT_TEST_EXIT_CODE;
}
