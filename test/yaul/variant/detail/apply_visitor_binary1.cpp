// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <yaul/variant/detail/apply_visitor_binary.hpp>
#include <yaul/variant/variant.hpp>
#include <yaul/variant/test_config.hpp>
#include <type_traits>

struct V01
{
  static int  ii;
  static char cc;

  typedef int result_type; 

  template< typename T1, typename T2 >
  int operator()(T1&&, T2&&) noexcept { return -1; }

  int operator()(char& c, int& i) & noexcept                    { cc = c; ii = i; return 0x11121; }
  int operator()(char& c, int const& i) & noexcept              { cc = c; ii = i; return 0x11122; }
  int operator()(char& c, int&& i) & noexcept                   { cc = c; ii = i; return 0x11123; }

  int operator()(char const& c, int& i) & noexcept              { cc = c; ii = i; return 0x11221; }
  int operator()(char const& c, int const& i) & noexcept        { cc = c; ii = i; return 0x11222; }
  int operator()(char const& c, int&& i) & noexcept             { cc = c; ii = i; return 0x11223; }

  int operator()(char&& c, int& i) & noexcept                   { cc = c; ii = i; return 0x11321; }
  int operator()(char&& c, int const& i) & noexcept             { cc = c; ii = i; return 0x11322; }
  int operator()(char&& c, int&& i) & noexcept                  { cc = c; ii = i; return 0x11323; }

  int operator()(char& c, int& i) const & noexcept              { cc = c; ii = i; return 0x21121; }
  int operator()(char& c, int const& i) const & noexcept        { cc = c; ii = i; return 0x21122; }
  int operator()(char& c, int&& i) const & noexcept             { cc = c; ii = i; return 0x21123; }

  int operator()(char const& c, int& i) const & noexcept        { cc = c; ii = i; return 0x21221; }
  int operator()(char const& c, int const& i) const & noexcept  { cc = c; ii = i; return 0x21222; }
  int operator()(char const& c, int&& i) const & noexcept       { cc = c; ii = i; return 0x21223; }

  int operator()(char&& c, int& i) const & noexcept             { cc = c; ii = i; return 0x21321; }
  int operator()(char&& c, int const& i) const & noexcept       { cc = c; ii = i; return 0x21322; }
  int operator()(char&& c, int&& i) const& noexcept             { cc = c; ii = i; return 0x21323; }

  int operator()(char& c, int& i) && noexcept                   { cc = c; ii = i; return 0x31121; }
  int operator()(char& c, int const& i) && noexcept             { cc = c; ii = i; return 0x31122; }
  int operator()(char& c, int&& i) && noexcept                  { cc = c; ii = i; return 0x31123; }

  int operator()(char const& c, int& i) && noexcept             { cc = c; ii = i; return 0x31221; }
  int operator()(char const& c, int const& i) && noexcept       { cc = c; ii = i; return 0x31222; }
  int operator()(char const& c, int&& i) && noexcept            { cc = c; ii = i; return 0x31223; }

  int operator()(char&& c, int& i) && noexcept                  { cc = c; ii = i; return 0x31321; }
  int operator()(char&& c, int const& i) && noexcept            { cc = c; ii = i; return 0x31322; }
  int operator()(char&& c, int&& i) && noexcept                 { cc = c; ii = i; return 0x31323; }
};

int V01::ii;
char V01::cc;

void test__binary_visitor_unwrap__01()
{
  using namespace yaul::detail::variant;
  using std::is_same;

  // V01&
  {
    V01 v;
    {
      int i{123};
      static_assert(is_same<decltype(binary_visitor_unwrap(v,i)), binary_visitor_unwrapper<V01&,int&> >::value, "");

      {
        char c{'a'};
        V01::ii = 0;
        V01::cc = '\0';
        YAUL_VARIANT_CHECK_EQUALS(binary_visitor_unwrap(v,i)(c), 0x11121);
        YAUL_VARIANT_CHECK_EQUALS(V01::ii, 123);
        YAUL_VARIANT_CHECK_EQUALS(V01::cc, 'a');
      }
      {
        char const c{'a'};
        V01::ii = 0;
        V01::cc = '\0';
        YAUL_VARIANT_CHECK_EQUALS(binary_visitor_unwrap(v,i)(c), 0x11221);
        YAUL_VARIANT_CHECK_EQUALS(V01::ii, 123);
        YAUL_VARIANT_CHECK_EQUALS(V01::cc, 'a');
      }
      {
        V01::ii = 0;
        V01::cc = '\0';
        YAUL_VARIANT_CHECK_EQUALS(binary_visitor_unwrap(v,i)('a'), 0x11321);
        YAUL_VARIANT_CHECK_EQUALS(V01::ii, 123);
        YAUL_VARIANT_CHECK_EQUALS(V01::cc, 'a');
      }
    }
    {
      int const i{123};
      static_assert(is_same<decltype(binary_visitor_unwrap(v,i)), binary_visitor_unwrapper<V01&,int const&> >::value, "");

      {
        char c{'a'};
        V01::ii = 0;
        V01::cc = '\0';
        YAUL_VARIANT_CHECK_EQUALS(binary_visitor_unwrap(v,i)(c), 0x11122);
        YAUL_VARIANT_CHECK_EQUALS(V01::ii, 123);
        YAUL_VARIANT_CHECK_EQUALS(V01::cc, 'a');
      }
      {
        char const c{'a'};
        V01::ii = 0;
        V01::cc = '\0';
        YAUL_VARIANT_CHECK_EQUALS(binary_visitor_unwrap(v,i)(c), 0x11222);
        YAUL_VARIANT_CHECK_EQUALS(V01::ii, 123);
        YAUL_VARIANT_CHECK_EQUALS(V01::cc, 'a');
      }
      {
        V01::ii = 0;
        V01::cc = '\0';
        YAUL_VARIANT_CHECK_EQUALS(binary_visitor_unwrap(v,i)('a'), 0x11322);
        YAUL_VARIANT_CHECK_EQUALS(V01::ii, 123);
        YAUL_VARIANT_CHECK_EQUALS(V01::cc, 'a');
      }
    }
    {
      static_assert(is_same<decltype(binary_visitor_unwrap(v,123)), binary_visitor_unwrapper<V01&,int&&> >::value, "");
      {
        char c{'a'};
        V01::ii = 0;
        V01::cc = '\0';
        YAUL_VARIANT_CHECK_EQUALS(binary_visitor_unwrap(v,123)(c), 0x11123);
        YAUL_VARIANT_CHECK_EQUALS(V01::ii, 123);
        YAUL_VARIANT_CHECK_EQUALS(V01::cc, 'a');
      }
      {
        char const c{'a'};
        V01::ii = 0;
        V01::cc = '\0';
        YAUL_VARIANT_CHECK_EQUALS(binary_visitor_unwrap(v,123)(c), 0x11223);
        YAUL_VARIANT_CHECK_EQUALS(V01::ii, 123);
        YAUL_VARIANT_CHECK_EQUALS(V01::cc, 'a');
      }
      {
        V01::ii = 0;
        V01::cc = '\0';
        YAUL_VARIANT_CHECK_EQUALS(binary_visitor_unwrap(v,123)('a'), 0x11323);
        YAUL_VARIANT_CHECK_EQUALS(V01::ii, 123);
        YAUL_VARIANT_CHECK_EQUALS(V01::cc, 'a');
      }
    }
  }

  // 
  // V01 const&
  //
  {
    V01 const v{};
    {
      int i{123};
      static_assert(is_same<decltype(binary_visitor_unwrap(v,i)), binary_visitor_unwrapper<V01 const&,int&> >::value, "");

      {
        char c{'a'};
        V01::ii = 0;
        V01::cc = '\0';
        YAUL_VARIANT_CHECK_EQUALS(binary_visitor_unwrap(v,i)(c), 0x21121);
        YAUL_VARIANT_CHECK_EQUALS(V01::ii, 123);
        YAUL_VARIANT_CHECK_EQUALS(V01::cc, 'a');
      }
      {
        char const c{'a'};
        V01::ii = 0;
        V01::cc = '\0';
        YAUL_VARIANT_CHECK_EQUALS(binary_visitor_unwrap(v,i)(c), 0x21221);
        YAUL_VARIANT_CHECK_EQUALS(V01::ii, 123);
        YAUL_VARIANT_CHECK_EQUALS(V01::cc, 'a');
      }
      {
        V01::ii = 0;
        V01::cc = '\0';
        YAUL_VARIANT_CHECK_EQUALS(binary_visitor_unwrap(v,i)('a'), 0x21321);
        YAUL_VARIANT_CHECK_EQUALS(V01::ii, 123);
        YAUL_VARIANT_CHECK_EQUALS(V01::cc, 'a');
      }
    }
    {
      int const i{123};
      static_assert(is_same<decltype(binary_visitor_unwrap(v,i)), binary_visitor_unwrapper<V01 const&,int const&> >::value, "");

      {
        char c{'a'};
        V01::ii = 0;
        V01::cc = '\0';
        YAUL_VARIANT_CHECK_EQUALS(binary_visitor_unwrap(v,i)(c), 0x21122);
        YAUL_VARIANT_CHECK_EQUALS(V01::ii, 123);
        YAUL_VARIANT_CHECK_EQUALS(V01::cc, 'a');
      }
      {
        char const c{'a'};
        V01::ii = 0;
        V01::cc = '\0';
        YAUL_VARIANT_CHECK_EQUALS(binary_visitor_unwrap(v,i)(c), 0x21222);
        YAUL_VARIANT_CHECK_EQUALS(V01::ii, 123);
        YAUL_VARIANT_CHECK_EQUALS(V01::cc, 'a');
      }
      {
        V01::ii = 0;
        V01::cc = '\0';
        YAUL_VARIANT_CHECK_EQUALS(binary_visitor_unwrap(v,i)('a'), 0x21322);
        YAUL_VARIANT_CHECK_EQUALS(V01::ii, 123);
        YAUL_VARIANT_CHECK_EQUALS(V01::cc, 'a');
      }
    }
    {
      static_assert(is_same<decltype(binary_visitor_unwrap(v,0)), binary_visitor_unwrapper<V01 const&,int&&> >::value, "");

      {
        char c{'a'};
        V01::ii = 0;
        V01::cc = '\0';
        YAUL_VARIANT_CHECK_EQUALS(binary_visitor_unwrap(v,123)(c), 0x21123);
        YAUL_VARIANT_CHECK_EQUALS(V01::ii, 123);
        YAUL_VARIANT_CHECK_EQUALS(V01::cc, 'a');
      }
      {
        char const c{'a'};
        V01::ii = 0;
        V01::cc = '\0';
        YAUL_VARIANT_CHECK_EQUALS(binary_visitor_unwrap(v,123)(c), 0x21223);
        YAUL_VARIANT_CHECK_EQUALS(V01::ii, 123);
        YAUL_VARIANT_CHECK_EQUALS(V01::cc, 'a');
      }
      {
        V01::ii = 0;
        V01::cc = '\0';
        YAUL_VARIANT_CHECK_EQUALS(binary_visitor_unwrap(v,123)('a'), 0x21323);
        YAUL_VARIANT_CHECK_EQUALS(V01::ii, 123);
        YAUL_VARIANT_CHECK_EQUALS(V01::cc, 'a');
      }
    }
  }

  //
  // V01&&
  //
  {
    {
      int i{123};
      static_assert(is_same<decltype(binary_visitor_unwrap(V01{},i)), binary_visitor_unwrapper<V01&&,int&> >::value, "");
      {
        char c{'a'};
        V01::ii = 0;
        V01::cc = '\0';
        YAUL_VARIANT_CHECK_EQUALS(binary_visitor_unwrap(V01{},i)(c), 0x31121);
        YAUL_VARIANT_CHECK_EQUALS(V01::ii, 123);
        YAUL_VARIANT_CHECK_EQUALS(V01::cc, 'a');
      }
      {
        char const c{'a'};
        V01::ii = 0;
        V01::cc = '\0';
        YAUL_VARIANT_CHECK_EQUALS(binary_visitor_unwrap(V01{},i)(c), 0x31221);
        YAUL_VARIANT_CHECK_EQUALS(V01::ii, 123);
        YAUL_VARIANT_CHECK_EQUALS(V01::cc, 'a');
      }
      {
        V01::ii = 0;
        V01::cc = '\0';
        YAUL_VARIANT_CHECK_EQUALS(binary_visitor_unwrap(V01{},i)('a'), 0x31321);
        YAUL_VARIANT_CHECK_EQUALS(V01::ii, 123);
        YAUL_VARIANT_CHECK_EQUALS(V01::cc, 'a');
      }
    }
    {
      int const i{123};
      static_assert(is_same<decltype(binary_visitor_unwrap(V01{},i)), binary_visitor_unwrapper<V01&&,int const&> >::value, "");
      {
        char c{'a'};
        V01::ii = 0;
        V01::cc = '\0';
        YAUL_VARIANT_CHECK_EQUALS(binary_visitor_unwrap(V01{},i)(c), 0x31122);
        YAUL_VARIANT_CHECK_EQUALS(V01::ii, 123);
        YAUL_VARIANT_CHECK_EQUALS(V01::cc, 'a');
      }
      {
        char const c{'a'};
        V01::ii = 0;
        V01::cc = '\0';
        YAUL_VARIANT_CHECK_EQUALS(binary_visitor_unwrap(V01{},i)(c), 0x31222);
        YAUL_VARIANT_CHECK_EQUALS(V01::ii, 123);
        YAUL_VARIANT_CHECK_EQUALS(V01::cc, 'a');
      }
      {
        V01::ii = 0;
        V01::cc = '\0';
        YAUL_VARIANT_CHECK_EQUALS(binary_visitor_unwrap(V01{},i)('a'), 0x31322);
        YAUL_VARIANT_CHECK_EQUALS(V01::ii, 123);
        YAUL_VARIANT_CHECK_EQUALS(V01::cc, 'a');
      }
    }
    {
      static_assert(is_same<decltype(binary_visitor_unwrap(V01{},123)), binary_visitor_unwrapper<V01&&,int&&> >::value, "");
      {
        char c{'a'};
        V01::ii = 0;
        V01::cc = '\0';
        YAUL_VARIANT_CHECK_EQUALS(binary_visitor_unwrap(V01{},123)(c), 0x31123);
        YAUL_VARIANT_CHECK_EQUALS(V01::ii, 123);
        YAUL_VARIANT_CHECK_EQUALS(V01::cc, 'a');
      }
      {
        char const c{'a'};
        V01::ii = 0;
        V01::cc = '\0';
        YAUL_VARIANT_CHECK_EQUALS(binary_visitor_unwrap(V01{},123)(c), 0x31223);
        YAUL_VARIANT_CHECK_EQUALS(V01::ii, 123);
        YAUL_VARIANT_CHECK_EQUALS(V01::cc, 'a');
      }
      {
        V01::ii = 0;
        V01::cc = '\0';
        YAUL_VARIANT_CHECK_EQUALS(binary_visitor_unwrap(V01{},123)('a'), 0x31323);
        YAUL_VARIANT_CHECK_EQUALS(V01::ii, 123);
        YAUL_VARIANT_CHECK_EQUALS(V01::cc, 'a');
      }
    }
  }
}

void  test__binary_visitor_wrap__01()
{
  using namespace yaul::detail::variant;
  using std::is_same;

  typedef yaul::variant<char> X1;

  //
  // V01&
  //
  {
    V01 v;
    // X1&
    {
      X1 x1{'a'};
      static_assert(is_same<decltype(binary_visitor_wrap(v,x1)), binary_visitor_wrapper<V01&,X1&> >::value, "");
      {
        int i{123};
        V01::ii = 0;
        V01::cc = '\0';
        YAUL_VARIANT_CHECK_EQUALS(binary_visitor_wrap(v,x1)(i), 0x11121);
        YAUL_VARIANT_CHECK_EQUALS(V01::ii, 123);
        YAUL_VARIANT_CHECK_EQUALS(V01::cc, 'a');
      }
      {
        int const i{123};
        V01::ii = 0;
        V01::cc = '\0';
        YAUL_VARIANT_CHECK_EQUALS(binary_visitor_wrap(v,x1)(i), 0x11122);
        YAUL_VARIANT_CHECK_EQUALS(V01::ii, 123);
        YAUL_VARIANT_CHECK_EQUALS(V01::cc, 'a');
      }
      {
        V01::ii = 0;
        V01::cc = '\0';
        YAUL_VARIANT_CHECK_EQUALS(binary_visitor_wrap(v,x1)(123), 0x11123);
        YAUL_VARIANT_CHECK_EQUALS(V01::ii, 123);
        YAUL_VARIANT_CHECK_EQUALS(V01::cc, 'a');
      }
    }
    // X1 const&
    {
      X1 const x1{'a'};
      static_assert(is_same<decltype(binary_visitor_wrap(v,x1)), binary_visitor_wrapper<V01&,X1 const&> >::value, "");
      {
        int i{123};
        V01::ii = 0;
        V01::cc = '\0';
        YAUL_VARIANT_CHECK_EQUALS(binary_visitor_wrap(v,x1)(i), 0x11221);
        YAUL_VARIANT_CHECK_EQUALS(V01::ii, 123);
        YAUL_VARIANT_CHECK_EQUALS(V01::cc, 'a');
      }
      {
        int const i{123};
        V01::ii = 0;
        V01::cc = '\0';
        YAUL_VARIANT_CHECK_EQUALS(binary_visitor_wrap(v,x1)(i), 0x11222);
        YAUL_VARIANT_CHECK_EQUALS(V01::ii, 123);
        YAUL_VARIANT_CHECK_EQUALS(V01::cc, 'a');
      }
      {
        V01::ii = 0;
        V01::cc = '\0';
        YAUL_VARIANT_CHECK_EQUALS(binary_visitor_wrap(v,x1)(123), 0x11223);
        YAUL_VARIANT_CHECK_EQUALS(V01::ii, 123);
        YAUL_VARIANT_CHECK_EQUALS(V01::cc, 'a');
      }
    }
    // X1&&
    {
      static_assert(is_same<decltype(binary_visitor_wrap(v,X1{'a'})), binary_visitor_wrapper<V01&,X1&&> >::value, "");
      {
        int i{123};
        V01::ii = 0;
        V01::cc = '\0';
        YAUL_VARIANT_CHECK_EQUALS(binary_visitor_wrap(v,X1{'a'})(i), 0x11321);
        YAUL_VARIANT_CHECK_EQUALS(V01::ii, 123);
        YAUL_VARIANT_CHECK_EQUALS(V01::cc, 'a');
      }
      {
        int const i{123};
        V01::ii = 0;
        V01::cc = '\0';
        YAUL_VARIANT_CHECK_EQUALS(binary_visitor_wrap(v,X1{'a'})(i), 0x11322);
        YAUL_VARIANT_CHECK_EQUALS(V01::ii, 123);
        YAUL_VARIANT_CHECK_EQUALS(V01::cc, 'a');
      }
      {
        V01::ii = 0;
        V01::cc = '\0';
        YAUL_VARIANT_CHECK_EQUALS(binary_visitor_wrap(v,X1{'a'})(123), 0x11323);
        YAUL_VARIANT_CHECK_EQUALS(V01::ii, 123);
        YAUL_VARIANT_CHECK_EQUALS(V01::cc, 'a');
      }
    }
  }

  //
  // V01 const&
  //
  {
    V01 const v{};
    // X1&
    {
      X1 x1{'a'};
      static_assert(is_same<decltype(binary_visitor_wrap(v,x1)), binary_visitor_wrapper<V01 const&,X1&> >::value, "");
      {
        int i{123};
        V01::ii = 0;
        V01::cc = '\0';
        YAUL_VARIANT_CHECK_EQUALS(binary_visitor_wrap(v,x1)(i), 0x21121);
        YAUL_VARIANT_CHECK_EQUALS(V01::ii, 123);
        YAUL_VARIANT_CHECK_EQUALS(V01::cc, 'a');
      }
      {
        int const i{123};
        V01::ii = 0;
        V01::cc = '\0';
        YAUL_VARIANT_CHECK_EQUALS(binary_visitor_wrap(v,x1)(i), 0x21122);
        YAUL_VARIANT_CHECK_EQUALS(V01::ii, 123);
        YAUL_VARIANT_CHECK_EQUALS(V01::cc, 'a');
      }
      {
        V01::ii = 0;
        V01::cc = '\0';
        YAUL_VARIANT_CHECK_EQUALS(binary_visitor_wrap(v,x1)(123), 0x21123);
        YAUL_VARIANT_CHECK_EQUALS(V01::ii, 123);
        YAUL_VARIANT_CHECK_EQUALS(V01::cc, 'a');
      }
    }
    // X1 const&
    {
      X1 const x1{'a'};
      static_assert(is_same<decltype(binary_visitor_wrap(v,x1)), binary_visitor_wrapper<V01 const&,X1 const&> >::value, "");
      {
        int i{123};
        V01::ii = 0;
        V01::cc = '\0';
        YAUL_VARIANT_CHECK_EQUALS(binary_visitor_wrap(v,x1)(i), 0x21221);
        YAUL_VARIANT_CHECK_EQUALS(V01::ii, 123);
        YAUL_VARIANT_CHECK_EQUALS(V01::cc, 'a');
      }
      {
        int const i{123};
        V01::ii = 0;
        V01::cc = '\0';
        YAUL_VARIANT_CHECK_EQUALS(binary_visitor_wrap(v,x1)(i), 0x21222);
        YAUL_VARIANT_CHECK_EQUALS(V01::ii, 123);
        YAUL_VARIANT_CHECK_EQUALS(V01::cc, 'a');
      }
      {
        V01::ii = 0;
        V01::cc = '\0';
        YAUL_VARIANT_CHECK_EQUALS(binary_visitor_wrap(v,x1)(123), 0x21223);
        YAUL_VARIANT_CHECK_EQUALS(V01::ii, 123);
        YAUL_VARIANT_CHECK_EQUALS(V01::cc, 'a');
      }
    }
    // X1&&
    {
      static_assert(is_same<decltype(binary_visitor_wrap(v,X1{'a'})), binary_visitor_wrapper<V01 const&,X1&&> >::value, "");
      {
        int i{123};
        V01::ii = 0;
        V01::cc = '\0';
        YAUL_VARIANT_CHECK_EQUALS(binary_visitor_wrap(v,X1{'a'})(i), 0x21321);
        YAUL_VARIANT_CHECK_EQUALS(V01::ii, 123);
        YAUL_VARIANT_CHECK_EQUALS(V01::cc, 'a');
      }
      {
        int const i{123};
        V01::ii = 0;
        V01::cc = '\0';
        YAUL_VARIANT_CHECK_EQUALS(binary_visitor_wrap(v,X1{'a'})(i), 0x21322);
        YAUL_VARIANT_CHECK_EQUALS(V01::ii, 123);
        YAUL_VARIANT_CHECK_EQUALS(V01::cc, 'a');
      }
      {
        V01::ii = 0;
        V01::cc = '\0';
        YAUL_VARIANT_CHECK_EQUALS(binary_visitor_wrap(v,X1{'a'})(123), 0x21323);
        YAUL_VARIANT_CHECK_EQUALS(V01::ii, 123);
        YAUL_VARIANT_CHECK_EQUALS(V01::cc, 'a');
      }
    }
  }

  //
  // V01&&
  //
  {
    // X1&
    {
      X1 x1{'a'};
      static_assert(is_same<decltype(binary_visitor_wrap(V01{},x1)), binary_visitor_wrapper<V01&&,X1&> >::value, "");
      {
        int i{123};
        V01::ii = 0;
        V01::cc = '\0';
        YAUL_VARIANT_CHECK_EQUALS(binary_visitor_wrap(V01{},x1)(i), 0x31121);
        YAUL_VARIANT_CHECK_EQUALS(V01::ii, 123);
        YAUL_VARIANT_CHECK_EQUALS(V01::cc, 'a');
      }
      {
        int const i{123};
        V01::ii = 0;
        V01::cc = '\0';
        YAUL_VARIANT_CHECK_EQUALS(binary_visitor_wrap(V01{},x1)(i), 0x31122);
        YAUL_VARIANT_CHECK_EQUALS(V01::ii, 123);
        YAUL_VARIANT_CHECK_EQUALS(V01::cc, 'a');
      }
      {
        V01::ii = 0;
        V01::cc = '\0';
        YAUL_VARIANT_CHECK_EQUALS(binary_visitor_wrap(V01{},x1)(123), 0x31123);
        YAUL_VARIANT_CHECK_EQUALS(V01::ii, 123);
        YAUL_VARIANT_CHECK_EQUALS(V01::cc, 'a');
      }
    }
    // X1 const&
    {
      X1 const x1{'a'};
      static_assert(is_same<decltype(binary_visitor_wrap(V01{},x1)), binary_visitor_wrapper<V01&&,X1 const&> >::value, "");
      {
        int i{123};
        V01::ii = 0;
        V01::cc = '\0';
        YAUL_VARIANT_CHECK_EQUALS(binary_visitor_wrap(V01{},x1)(i), 0x31221);
        YAUL_VARIANT_CHECK_EQUALS(V01::ii, 123);
        YAUL_VARIANT_CHECK_EQUALS(V01::cc, 'a');
      }
      {
        int const i{123};
        V01::ii = 0;
        V01::cc = '\0';
        YAUL_VARIANT_CHECK_EQUALS(binary_visitor_wrap(V01{},x1)(i), 0x31222);
        YAUL_VARIANT_CHECK_EQUALS(V01::ii, 123);
        YAUL_VARIANT_CHECK_EQUALS(V01::cc, 'a');
      }
      {
        V01::ii = 0;
        V01::cc = '\0';
        YAUL_VARIANT_CHECK_EQUALS(binary_visitor_wrap(V01{},x1)(123), 0x31223);
        YAUL_VARIANT_CHECK_EQUALS(V01::ii, 123);
        YAUL_VARIANT_CHECK_EQUALS(V01::cc, 'a');
      }
    }
    // X1&&
    {
      static_assert(is_same<decltype(binary_visitor_wrap(V01{},X1{'a'})), binary_visitor_wrapper<V01&&,X1&&> >::value, "");
      {
        int i{123};
        V01::ii = 0;
        V01::cc = '\0';
        YAUL_VARIANT_CHECK_EQUALS(binary_visitor_wrap(V01{},X1{'a'})(i), 0x31321);
        YAUL_VARIANT_CHECK_EQUALS(V01::ii, 123);
        YAUL_VARIANT_CHECK_EQUALS(V01::cc, 'a');
      }
      {
        int const i{123};
        V01::ii = 0;
        V01::cc = '\0';
        YAUL_VARIANT_CHECK_EQUALS(binary_visitor_wrap(V01{},X1{'a'})(i), 0x31322);
        YAUL_VARIANT_CHECK_EQUALS(V01::ii, 123);
        YAUL_VARIANT_CHECK_EQUALS(V01::cc, 'a');
      }
      {
        V01::ii = 0;
        V01::cc = '\0';
        YAUL_VARIANT_CHECK_EQUALS(binary_visitor_wrap(V01{},X1{'a'})(123), 0x31323);
        YAUL_VARIANT_CHECK_EQUALS(V01::ii, 123);
        YAUL_VARIANT_CHECK_EQUALS(V01::cc, 'a');
      }
    }
  }
}

struct V02
{
  static int  i1;
  static int  i2;
  static char c1;
  static char c2;

  typedef int result_type; 

  template< typename T1, typename T2 >
  int operator()(T1&&, T2&&) const noexcept { return -1; }

  int operator()(char a1, char a2) const noexcept { c1 = a1; c2 = a2; return 0x11; }
  int operator()(char a1, int a2) const noexcept  { c1 = a1; i2 = a2; return 0x12; }
  int operator()(int a1, char a2) const noexcept  { i1 = a1; c2 = a2; return 0x21; }
  int operator()(int a1, int a2) const noexcept   { i1 = a1; i2 = a2; return 0x22; }
};

int V02::i1;
int V02::i2;
char V02::c1;
char V02::c2;

void  test__binary_visitor_wrap__02()
{
  using namespace yaul::detail::variant;
  using std::is_same;
  using yaul::variant;

  {
    V02::c1 = '\0';
    V02::c2 = '\0';
    YAUL_VARIANT_CHECK_EQUALS(binary_visitor_wrap(V02{}, variant<int,char,double>{'a'})('b'), 0x11);
    YAUL_VARIANT_CHECK_EQUALS(V02::c1, 'a');
    YAUL_VARIANT_CHECK_EQUALS(V02::c2, 'b');
  }
  {
    V02::i1 = 0;
    V02::c2 = '\0';
    YAUL_VARIANT_CHECK_EQUALS(binary_visitor_wrap(V02{}, variant<int,char,double>{123})('b'), 0x21);
    YAUL_VARIANT_CHECK_EQUALS(V02::i1, 123);
    YAUL_VARIANT_CHECK_EQUALS(V02::c2, 'b');
  }
}

void test__apply_visitor__01()
{
  using namespace yaul::detail::variant;
  using std::is_same;

  typedef yaul::variant<char,double> X1;
  typedef yaul::variant<double, int> X2;

  //
  // V01&
  //
  {
    V01 v;
    // X1&
    {
      X1 x1{'a'};
      // X2&
      {
        X2 x2{123};
        V01::cc = '\0';
        V01::ii = 0;
        YAUL_VARIANT_CHECK_EQUALS(apply_visitor(v, x1, x2), 0x11121);
        YAUL_VARIANT_CHECK_EQUALS(V01::cc, 'a');
        YAUL_VARIANT_CHECK_EQUALS(V01::ii, 123);
      }
      // X2 const&
      {
        X2 const x2{123};
        V01::cc = '\0';
        V01::ii = 0;
        YAUL_VARIANT_CHECK_EQUALS(apply_visitor(v, x1, x2), 0x11122);
        YAUL_VARIANT_CHECK_EQUALS(V01::cc, 'a');
        YAUL_VARIANT_CHECK_EQUALS(V01::ii, 123);
      }
      // X2&&
      {
        V01::cc = '\0';
        V01::ii = 0;
        YAUL_VARIANT_CHECK_EQUALS(apply_visitor(v, x1, X2{123}), 0x11123);
        YAUL_VARIANT_CHECK_EQUALS(V01::cc, 'a');
        YAUL_VARIANT_CHECK_EQUALS(V01::ii, 123);
      }
    }
    // X1 const&
    {
      X1 const x1{'a'};
      // X2&
      {
        X2 x2{123};
        V01::cc = '\0';
        V01::ii = 0;
        YAUL_VARIANT_CHECK_EQUALS(apply_visitor(v, x1, x2), 0x11221);
        YAUL_VARIANT_CHECK_EQUALS(V01::cc, 'a');
        YAUL_VARIANT_CHECK_EQUALS(V01::ii, 123);
      }
      // X2 const&
      {
        X2 const x2{123};
        V01::cc = '\0';
        V01::ii = 0;
        YAUL_VARIANT_CHECK_EQUALS(apply_visitor(v, x1, x2), 0x11222);
        YAUL_VARIANT_CHECK_EQUALS(V01::cc, 'a');
        YAUL_VARIANT_CHECK_EQUALS(V01::ii, 123);
      }
      // X2&&
      {
        V01::cc = '\0';
        V01::ii = 0;
        YAUL_VARIANT_CHECK_EQUALS(apply_visitor(v, x1, X2{123}), 0x11223);
        YAUL_VARIANT_CHECK_EQUALS(V01::cc, 'a');
        YAUL_VARIANT_CHECK_EQUALS(V01::ii, 123);
      }
    }
    // X1&&
    {
      {
        X2 x2{123};
        V01::cc = '\0';
        V01::ii = 0;
        YAUL_VARIANT_CHECK_EQUALS(apply_visitor(v, X1{'a'}, x2), 0x11321);
        YAUL_VARIANT_CHECK_EQUALS(V01::cc, 'a');
        YAUL_VARIANT_CHECK_EQUALS(V01::ii, 123);
      }
      // X2 const&
      {
        X2 const x2{123};
        V01::cc = '\0';
        V01::ii = 0;
        YAUL_VARIANT_CHECK_EQUALS(apply_visitor(v, X1{'a'}, x2), 0x11322);
        YAUL_VARIANT_CHECK_EQUALS(V01::cc, 'a');
        YAUL_VARIANT_CHECK_EQUALS(V01::ii, 123);
      }
      // X2&&
      {
        V01::cc = '\0';
        V01::ii = 0;
        YAUL_VARIANT_CHECK_EQUALS(apply_visitor(v, X1{'a'}, X2{123}), 0x11323);
        YAUL_VARIANT_CHECK_EQUALS(V01::cc, 'a');
        YAUL_VARIANT_CHECK_EQUALS(V01::ii, 123);
      }
    }
  }

  //
  // V01 const&
  //
  {
    V01 const v{};
    // X1&
    {
      X1 x1{'a'};
      // X2&
      {
        X2 x2{123};
        V01::cc = '\0';
        V01::ii = 0;
        YAUL_VARIANT_CHECK_EQUALS(apply_visitor(v, x1, x2), 0x21121);
        YAUL_VARIANT_CHECK_EQUALS(V01::cc, 'a');
        YAUL_VARIANT_CHECK_EQUALS(V01::ii, 123);
      }
      // X2 const&
      {
        X2 const x2{123};
        V01::cc = '\0';
        V01::ii = 0;
        YAUL_VARIANT_CHECK_EQUALS(apply_visitor(v, x1, x2), 0x21122);
        YAUL_VARIANT_CHECK_EQUALS(V01::cc, 'a');
        YAUL_VARIANT_CHECK_EQUALS(V01::ii, 123);
      }
      // X2&&
      {
        V01::cc = '\0';
        V01::ii = 0;
        YAUL_VARIANT_CHECK_EQUALS(apply_visitor(v, x1, X2{123}), 0x21123);
        YAUL_VARIANT_CHECK_EQUALS(V01::cc, 'a');
        YAUL_VARIANT_CHECK_EQUALS(V01::ii, 123);
      }
    }
    // X1 const&
    {
      X1 const x1{'a'};
      // X2&
      {
        X2 x2{123};
        V01::cc = '\0';
        V01::ii = 0;
        YAUL_VARIANT_CHECK_EQUALS(apply_visitor(v, x1, x2), 0x21221);
        YAUL_VARIANT_CHECK_EQUALS(V01::cc, 'a');
        YAUL_VARIANT_CHECK_EQUALS(V01::ii, 123);
      }
      // X2 const&
      {
        X2 const x2{123};
        V01::cc = '\0';
        V01::ii = 0;
        YAUL_VARIANT_CHECK_EQUALS(apply_visitor(v, x1, x2), 0x21222);
        YAUL_VARIANT_CHECK_EQUALS(V01::cc, 'a');
        YAUL_VARIANT_CHECK_EQUALS(V01::ii, 123);
      }
      // X2&&
      {
        V01::cc = '\0';
        V01::ii = 0;
        YAUL_VARIANT_CHECK_EQUALS(apply_visitor(v, x1, X2{123}), 0x21223);
        YAUL_VARIANT_CHECK_EQUALS(V01::cc, 'a');
        YAUL_VARIANT_CHECK_EQUALS(V01::ii, 123);
      }
    }
    // X1&&
    {
      {
        X2 x2{123};
        V01::cc = '\0';
        V01::ii = 0;
        YAUL_VARIANT_CHECK_EQUALS(apply_visitor(v, X1{'a'}, x2), 0x21321);
        YAUL_VARIANT_CHECK_EQUALS(V01::cc, 'a');
        YAUL_VARIANT_CHECK_EQUALS(V01::ii, 123);
      }
      // X2 const&
      {
        X2 const x2{123};
        V01::cc = '\0';
        V01::ii = 0;
        YAUL_VARIANT_CHECK_EQUALS(apply_visitor(v, X1{'a'}, x2), 0x21322);
        YAUL_VARIANT_CHECK_EQUALS(V01::cc, 'a');
        YAUL_VARIANT_CHECK_EQUALS(V01::ii, 123);
      }
      // X2&&
      {
        V01::cc = '\0';
        V01::ii = 0;
        YAUL_VARIANT_CHECK_EQUALS(apply_visitor(v, X1{'a'}, X2{123}), 0x21323);
        YAUL_VARIANT_CHECK_EQUALS(V01::cc, 'a');
        YAUL_VARIANT_CHECK_EQUALS(V01::ii, 123);
      }
    }
  }

  //
  // V01&&
  //
  {
    // X1&
    {
      X1 x1{'a'};
      // X2&
      {
        X2 x2{123};
        V01::cc = '\0';
        V01::ii = 0;
        YAUL_VARIANT_CHECK_EQUALS(apply_visitor(V01{}, x1, x2), 0x31121);
        YAUL_VARIANT_CHECK_EQUALS(V01::cc, 'a');
        YAUL_VARIANT_CHECK_EQUALS(V01::ii, 123);
      }
      // X2 const&
      {
        X2 const x2{123};
        V01::cc = '\0';
        V01::ii = 0;
        YAUL_VARIANT_CHECK_EQUALS(apply_visitor(V01{}, x1, x2), 0x31122);
        YAUL_VARIANT_CHECK_EQUALS(V01::cc, 'a');
        YAUL_VARIANT_CHECK_EQUALS(V01::ii, 123);
      }
      // X2&&
      {
        V01::cc = '\0';
        V01::ii = 0;
        YAUL_VARIANT_CHECK_EQUALS(apply_visitor(V01{}, x1, X2{123}), 0x31123);
        YAUL_VARIANT_CHECK_EQUALS(V01::cc, 'a');
        YAUL_VARIANT_CHECK_EQUALS(V01::ii, 123);
      }
    }
    // X1 const&
    {
      X1 const x1{'a'};
      // X2&
      {
        X2 x2{123};
        V01::cc = '\0';
        V01::ii = 0;
        YAUL_VARIANT_CHECK_EQUALS(apply_visitor(V01{}, x1, x2), 0x31221);
        YAUL_VARIANT_CHECK_EQUALS(V01::cc, 'a');
        YAUL_VARIANT_CHECK_EQUALS(V01::ii, 123);
      }
      // X2 const&
      {
        X2 const x2{123};
        V01::cc = '\0';
        V01::ii = 0;
        YAUL_VARIANT_CHECK_EQUALS(apply_visitor(V01{}, x1, x2), 0x31222);
        YAUL_VARIANT_CHECK_EQUALS(V01::cc, 'a');
        YAUL_VARIANT_CHECK_EQUALS(V01::ii, 123);
      }
      // X2&&
      {
        V01::cc = '\0';
        V01::ii = 0;
        YAUL_VARIANT_CHECK_EQUALS(apply_visitor(V01{}, x1, X2{123}), 0x31223);
        YAUL_VARIANT_CHECK_EQUALS(V01::cc, 'a');
        YAUL_VARIANT_CHECK_EQUALS(V01::ii, 123);
      }
    }
    // X1&&
    {
      {
        X2 x2{123};
        V01::cc = '\0';
        V01::ii = 0;
        YAUL_VARIANT_CHECK_EQUALS(apply_visitor(V01{}, X1{'a'}, x2), 0x31321);
        YAUL_VARIANT_CHECK_EQUALS(V01::cc, 'a');
        YAUL_VARIANT_CHECK_EQUALS(V01::ii, 123);
      }
      // X2 const&
      {
        X2 const x2{123};
        V01::cc = '\0';
        V01::ii = 0;
        YAUL_VARIANT_CHECK_EQUALS(apply_visitor(V01{}, X1{'a'}, x2), 0x31322);
        YAUL_VARIANT_CHECK_EQUALS(V01::cc, 'a');
        YAUL_VARIANT_CHECK_EQUALS(V01::ii, 123);
      }
      // X2&&
      {
        V01::cc = '\0';
        V01::ii = 0;
        YAUL_VARIANT_CHECK_EQUALS(apply_visitor(V01{}, X1{'a'}, X2{123}), 0x31323);
        YAUL_VARIANT_CHECK_EQUALS(V01::cc, 'a');
        YAUL_VARIANT_CHECK_EQUALS(V01::ii, 123);
      }
    }
  }
}

int main()
{
  test__binary_visitor_unwrap__01();
  test__binary_visitor_wrap__01();
  test__binary_visitor_wrap__02();
  test__apply_visitor__01();
  return YAUL_VARIANT_TEST_EXIT_CODE;
}
