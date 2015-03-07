// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <yaul/variant/detail/multivisitors_cpp11_based.hpp>
#include <yaul/variant/variant.hpp>
#include <yaul/variant/test_config.hpp>
#include <type_traits>
#include <tuple>

//
// first three functions to better understand how the std::forward_as_tuple works
//
void test__forward_as_tuple__01()
{
  using std::is_same;
  using std::tuple;
  using std::move;
  using std::get;
  using std::forward_as_tuple;
  static_assert(is_same<decltype(forward_as_tuple(1,'a')), tuple<int&&,char&&> >::value, "");
  {
    int i = 1;
    char c = 'a';
    static_assert(is_same<decltype(forward_as_tuple(i,c)), tuple<int&,char&> >::value, "");
    static_assert(noexcept(forward_as_tuple(i, c)), "");
    YAUL_VARIANT_CHECK_EQUALS(get<0>(forward_as_tuple(i,c)), 1);
    YAUL_VARIANT_CHECK_EQUALS(get<1>(forward_as_tuple(i,c)), 'a');
    get<0>(forward_as_tuple(i,c)) = 2;
    get<1>(forward_as_tuple(i,c)) = 'b';
    YAUL_VARIANT_CHECK_EQUALS(i, 2);
    YAUL_VARIANT_CHECK_EQUALS(c, 'b');
  }
  {
    int const i = 1;
    char c = 'a';
    static_assert(is_same<decltype(forward_as_tuple(i,c)), tuple<int const&,char&> >::value, "");
    static_assert(is_same<decltype(forward_as_tuple(i,move(c))), tuple<int const&,char&&> >::value, "");
    static_assert(noexcept(forward_as_tuple(i, move(c))), "");
  }
  {
    int i = 1;
    char c = 'a';
    int const& ri = i;
    char& rc = c;
    static_assert(is_same<decltype(forward_as_tuple(ri,rc)), tuple<int const&,char&> >::value, "");
    static_assert(is_same<decltype(forward_as_tuple(ri,move(rc))), tuple<int const&,char&&> >::value, "");
    static_assert(noexcept(forward_as_tuple(ri, move(rc))), "");
  }
}

void test__forward_as_tuple__02()
{
  using std::is_same;
  using std::tuple;
  using std::move;
  using std::get;
  using std::forward_as_tuple;
  struct S
  {
    int i;
    S() : i{0} { }
    S(int i) : i{i} { }
    S(S& s) : i{s.i} { }
    S(S const& s) : i{s.i} { }
    S(S&& s) : i{s.i} { }
  };
  {
    S s{1};
    static_assert(is_same<decltype(forward_as_tuple(s,2)), tuple<S&,int&&> >::value, "");
    static_assert(is_same<decltype(forward_as_tuple(std::move(s),2)), tuple<S&&,int&&> >::value, "");
    static_assert(is_same<decltype(forward_as_tuple(S{2},2)), tuple<S&&,int&&> >::value, "");
    // tuple only holds references, so even here we should achieve noexcept'ness
    static_assert(noexcept(forward_as_tuple(s,2)), ""); 
    // here we call the constructor so...
    static_assert(!noexcept(forward_as_tuple(S{2},2)), ""); 
    YAUL_VARIANT_CHECK_EQUALS(get<0>(forward_as_tuple(s,2)).i, 1);
    get<0>(forward_as_tuple(s,2)).i = 2;
    YAUL_VARIANT_CHECK_EQUALS(s.i, 2);
  }
}

void test__forward_as_tuple__03()
{
  using std::is_same;
  using std::tuple;
  using std::move;
  using std::get;
  using std::forward_as_tuple;
  struct S
  {
    int i;
    S() noexcept : i{0} { }
    S(int i) noexcept : i{i} { }
    S(S& s) noexcept : i{s.i} { }
    S(S const& s) noexcept : i{s.i} { }
    S(S&& s) noexcept : i{s.i} { }
  };
  {
    // here we call the constructor so...
    static_assert(noexcept(forward_as_tuple(S{2},2)), ""); 
  }
  {
    const yaul::variant<double, int, char> x{};
    static_assert(std::is_same<decltype(std::forward_as_tuple(x)), std::tuple<const yaul::variant<double, int, char>&> >::value, "");
    std::tuple<const yaul::variant<double, int, char>&> t{std::forward_as_tuple(x)};
    YAUL_VARIANT_CHECK_EQUALS(std::get<0>(t).which(), 0);
  }
}

void test__make_index_sequence__01()
{
  using namespace yaul::detail::variant;
  using std::is_same;
  static_assert(is_same<make_index_sequence<0>, index_sequence<> >::value, "");
  static_assert(is_same<make_index_sequence<1>, index_sequence<0> >::value, "");
  static_assert(is_same<make_index_sequence<2>, index_sequence<0,1> >::value, "");
  static_assert(is_same<make_index_sequence<3>, index_sequence<0,1,2> >::value, "");
}

void test__tuple_tail_fwd__01()
{
  using namespace yaul::detail::variant;
  using std::is_same;
  {
    using T = std::tuple<int,char>;
    T t{1,'a'};
    static_assert(is_same<decltype(tuple_tail_fwd(std::move(t))), std::tuple<char> >::value, "");
    static_assert(noexcept(tuple_tail_fwd(std::move(t))), "");
    YAUL_VARIANT_CHECK_EQUALS(std::get<0>(tuple_tail_fwd(std::move(t))), 'a');
  }
  {
    int i = 1;
    char c = 'a';
    using T = std::tuple<int&,char&>;
    T t{i,c};
    static_assert(is_same<decltype(tuple_tail_fwd(std::move(t))), std::tuple<char&> >::value, "");
    static_assert(noexcept(tuple_tail_fwd(std::move(t))), "");
    YAUL_VARIANT_CHECK_EQUALS(std::get<0>(tuple_tail_fwd(std::move(t))), 'a');
    std::get<0>(tuple_tail_fwd(std::move(t))) = 'b';
    YAUL_VARIANT_CHECK_EQUALS(c, 'b');
  }
  {
    int i = 1;
    double d = 2;
    static_assert(is_same<decltype(tuple_tail_fwd(std::forward_as_tuple(i,d,'a'))), std::tuple<double&,char&&> >::value, "");
    static_assert(noexcept(tuple_tail_fwd(std::forward_as_tuple(i,d,'a'))), "");
    YAUL_VARIANT_CHECK_EQUALS(std::get<1>(tuple_tail_fwd(std::forward_as_tuple(i,d,'a'))), 'a');
  }
}

void test__tuple_tail_fwd__02()
{
  using namespace yaul::detail::variant;
  struct S
  {
    int which;
    S() noexcept : which{0} { }
    S(S&) noexcept : which{1} { }
    S(S const&) noexcept : which{2} { }
    S(S&&) noexcept : which{3} { }
  };

  static_assert(noexcept(tuple_tail_fwd(std::forward_as_tuple(S{}))), "");
  static_assert(noexcept(tuple_tail_fwd(std::forward_as_tuple(1,S{}))), "");
  static_assert(noexcept(tuple_tail_fwd(std::forward_as_tuple('a',1,S{}))), "");

  {
    std::tuple<int,S> t;
    static_assert(noexcept(tuple_tail_fwd(std::move(t))), "");
  }
  {
    S s;
    std::tuple<int,S&> t{1,s};
    static_assert(noexcept(tuple_tail_fwd(std::move(t))), "");
  }
  {
    S const s;
    std::tuple<int,S const&> t{1,s};
    static_assert(noexcept(tuple_tail_fwd(std::move(t))), "");
  }
  {
    std::tuple<int,S&&> t{1,S{}};
    static_assert(noexcept(tuple_tail_fwd(std::move(std::move(t)))), "");
  }

  {
    S s;
    // this shall only pass-over references...
    YAUL_VARIANT_CHECK_EQUALS(std::get<2>(std::forward_as_tuple('a', 1, s)).which, 0);
    YAUL_VARIANT_CHECK_EQUALS(std::get<1>(tuple_tail_fwd(std::forward_as_tuple('a', 1, s))).which, 0);

    YAUL_VARIANT_CHECK_EQUALS(std::get<2>(std::forward_as_tuple('a',1,S{})).which, 0);
    YAUL_VARIANT_CHECK_EQUALS(std::get<1>(tuple_tail_fwd(std::forward_as_tuple('a',1,S{}))).which, 0);

    YAUL_VARIANT_CHECK_EQUALS(std::get<2>(std::forward_as_tuple('a',1,S{std::move(S{})})).which, 3);
    YAUL_VARIANT_CHECK_EQUALS(std::get<1>(tuple_tail_fwd(std::forward_as_tuple('a',1,S{std::move(S{})}))).which, 3);
  }
}

void test__tuple_tail_fwd__03()
{
  using namespace yaul::detail::variant;
  static int last;
  struct S
  {
    S()           { last  = -1; }
    S(S&)         { last += 0x100; }
    S(S const&)   { last += 0x010; }
    S(S&&)        { last += 0x001; }
  };

  static_assert(!noexcept(tuple_tail_fwd(std::forward_as_tuple(S{}))), "");
  static_assert(!noexcept(tuple_tail_fwd(std::forward_as_tuple(1,S{}))), "");
  static_assert(!noexcept(tuple_tail_fwd(std::forward_as_tuple('a',1,S{}))), "");

  {
    std::tuple<int,S> t;
    static_assert(noexcept(tuple_tail_fwd(std::move(t))), "");
    last = 0;
    tuple_tail_fwd(std::move(t));
    YAUL_VARIANT_CHECK_EQUALS(last, 0x001);
  }
  {
    S s;
    std::tuple<S&,int> t{s,1};
    static_assert(noexcept(tuple_tail_fwd(std::move(t))), "");
  }
  {
    S s;
    std::tuple<int,S&> t{1,s};
    static_assert(noexcept(tuple_tail_fwd(std::move(t))), "");
    last = 0;
    tuple_tail_fwd(std::move(t));
    YAUL_VARIANT_CHECK_EQUALS(last, 0x000);
  }
  {
    S const s;
    std::tuple<int,S const&> t{1,s};
    static_assert(noexcept(tuple_tail_fwd(std::move(t))), "");
    last = 0;
    tuple_tail_fwd(std::move(t));
    YAUL_VARIANT_CHECK_EQUALS(last, 0x000);
  }
  {
    std::tuple<int,S&&> t{1,S{}};
    static_assert(noexcept(tuple_tail_fwd(std::move(t))), "");
    last = 0;
    tuple_tail_fwd(std::move(t));
    YAUL_VARIANT_CHECK_EQUALS(last, 0x000);
  }
}

void test__multivisitor_rewrapper__01()
{
  struct V { typedef void result_type; };
  using namespace yaul::detail::variant;
  {
    V v;
    using T = std::tuple<>;
    static_assert(noexcept(multivisitor_rewrapper<V&, T, T>(v,T{},T{})), "");
    static_assert(noexcept(multivisitor_rewrapper<V&&, T, T>(V{},T{},T{})), "");
  }
  {
    V v;
    int i;
    char c;
    using T1 = std::tuple<int&, char&>;
    using T2 = std::tuple<>;
    static_assert(noexcept(multivisitor_rewrapper<V&, T1, T2>(v,std::forward_as_tuple(i,c),T2{})), "");
    static_assert(noexcept(multivisitor_rewrapper<V&&, T1, T2 >(V{},std::forward_as_tuple(i,c),T2{})), "");
  }
  {
    V v;
    using V1 = yaul::variant<double, int, char>;
    using T1 = std::tuple<V1&>;
    using T2 = std::tuple<>;
    V1 x{};
    multivisitor_rewrapper<V&, T1, T2> obj1(v, std::forward_as_tuple(x), T2{});
    multivisitor_rewrapper<V&&, T1, T2> obj2(V{}, std::forward_as_tuple(x), T2{});
  }
  {
    V v;
    using V1 = yaul::variant<double, int, char>;
    using V2 = yaul::variant<float, int>;
    using T1 = std::tuple<V1&,V2 const&>;
    using T2 = std::tuple<>;
    V1 x1{};
    V2 const x2{};
    multivisitor_rewrapper<V&, T1, T2> obj1(v, std::forward_as_tuple(x1,x2), T2{});
    multivisitor_rewrapper<V&&, T1, T2> obj2(V{}, std::forward_as_tuple(x1,x2), T2{});
  }
}


void test__make_multivisitor_rewrapper__01()
{
  struct V { typedef void result_type; };
  struct T1 { };
  struct T2 { };
  using namespace yaul::detail::variant;
  {
    T1 t1;
    static_assert(std::is_same<
        decltype(make_multivisitor_rewrapper(V{}, std::forward_as_tuple(t1,T2{}), std::forward_as_tuple())), 
        multivisitor_rewrapper<V&&, std::tuple<T1&,T2&&>, std::tuple<> >
    >::value, "");
    static_assert(noexcept(make_multivisitor_rewrapper(V{}, std::forward_as_tuple(t1, T2{}), std::forward_as_tuple())), "");
    make_multivisitor_rewrapper(V{}, std::forward_as_tuple(t1, T2{}), std::forward_as_tuple());
  }
  {
    V v;
    const yaul::variant<double, int, char> x{};
    make_multivisitor_rewrapper(v, std::forward_as_tuple(x), std::tuple<>{});
  }
}

int main()
{
  test__forward_as_tuple__01();
  test__forward_as_tuple__02();
  test__forward_as_tuple__03();
  test__make_index_sequence__01();
  test__tuple_tail_fwd__01();
  test__tuple_tail_fwd__02();
  test__tuple_tail_fwd__03();
  test__multivisitor_rewrapper__01();
  test__make_multivisitor_rewrapper__01();
  return YAUL_VARIANT_TEST_EXIT_CODE;
}
