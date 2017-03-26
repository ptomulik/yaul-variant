// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <yaul/variant/detail/variadic_union.hpp>
#include <yaul/variant/test_config.hpp>
#include <type_traits>
#include <utility>

using yaul::detail::variant::variadic_union;
using yaul::detail::variant::in_place_index_t;

constexpr in_place_index_t<0ul> _0{};
constexpr in_place_index_t<1ul> _1{};
constexpr in_place_index_t<2ul> _2{};
//constexpr in_place_index_t<3ul> _3{};

enum qual_t {
  q_lr,     // l-value reference
  q_lr_c,   // l-value reference to const
  q_lr_v,   // l-value reference to volatile
  q_lr_cv,  // l-value reference to const volatile
  q_rr,     // r-value reference
  q_rr_c,   // r-value reference to const
  q_rr_v,   // r-value reference to volatile
  q_rr_cv   // r-value reference to const volatile
};

// trivially destructible
struct S1
{
#ifndef YAUL_VARIANT_NO_CONSTEXPR_ON_NONCONST_FUNCTIONS

  constexpr qual_t qual()& noexcept { return q_lr; }
  constexpr qual_t qual() const& noexcept { return q_lr_c; }
  constexpr qual_t qual() volatile& noexcept { return q_lr_v; }
  constexpr qual_t qual() const volatile& noexcept { return q_lr_cv; }
  constexpr qual_t qual()&& noexcept { return q_rr; }
# ifndef YAUL_VARIANT_NO_RRCV_QUALIFIED_FUNCTIONS
  constexpr qual_t qual() const&& noexcept { return q_rr_c; }
  constexpr qual_t qual() volatile&& noexcept { return q_rr_v; }
  constexpr qual_t qual() const volatile&& noexcept { return q_rr_cv; }
# endif

#else

  qual_t qual()& noexcept { return q_lr; }
  constexpr qual_t qual() const& noexcept { return q_lr_c; }
  qual_t qual() volatile& noexcept { return q_lr_v; }
  constexpr qual_t qual() const volatile& noexcept { return q_lr_cv; }
  qual_t qual()&& noexcept { return q_rr; }
# ifndef YAUL_VARIANT_NO_RRCV_QUALIFIED_FUNCTIONS
  constexpr qual_t qual() const&& noexcept { return q_rr_c; }
  qual_t qual() volatile&& noexcept { return q_rr_v; }
  constexpr qual_t qual() const volatile&& noexcept { return q_rr_cv; }
# endif

#endif
};

// nontrivially destructible
struct S2
{
  static int count;
  ~S2() noexcept { --count; }
  S2() noexcept { ++count; }
  S2(const char*) { ++count; }   // intentionally non-noexcept

  qual_t qual()& noexcept { return q_lr; }
  qual_t qual() const& noexcept { return q_lr_c; }
  qual_t qual() volatile& noexcept { return q_lr_v; }
  qual_t qual() const volatile& noexcept { return q_lr_cv; }
  qual_t qual()&& noexcept { return q_rr; }
#ifndef YAUL_VARIANT_NO_RRCV_QUALIFIED_FUNCTIONS
  qual_t qual() const&& noexcept { return q_rr_c; }
  qual_t qual() volatile&& noexcept { return q_rr_v; }
  qual_t qual() const volatile&& noexcept { return q_rr_cv; }
#endif
};

int S2::count = 0;

// trivially destructible but has some non-constexpr c-tors
struct S3
{
  int i;
  S3(int i) noexcept : i(i) { }
  S3() noexcept : i(0) { }

  qual_t qual()& noexcept { return q_lr; }
  qual_t qual() const& noexcept { return q_lr_c; }
  qual_t qual() volatile& noexcept { return q_lr_v; }
  qual_t qual() const volatile& noexcept { return q_lr_cv; }
  qual_t qual()&& noexcept { return q_rr; }
#ifndef YAUL_VARIANT_NO_RRCV_QUALIFIED_FUNCTIONS
  qual_t qual() const&& noexcept { return q_rr_c; }
  qual_t qual() volatile&& noexcept { return q_rr_v; }
  qual_t qual() const volatile&& noexcept { return q_rr_cv; }
#endif
};

// has non-constexpr d-tor
struct S4
{
  ~S4() noexcept(false) {}
};

static_assert(!std::is_literal_type<S3>::value, "");
static_assert( std::is_trivially_destructible<S3>::value, "");

using U_i = variadic_union<int>;
using U_ic = variadic_union<int,char>;
static_assert(!std::is_default_constructible<U_i>::value, "");
static_assert( std::is_constructible<U_i, in_place_index_t<0ul> >::value, "");
static_assert( std::is_constructible<U_i, in_place_index_t<0ul>, int>::value, "");

// check noexcept-ness of certain expressions on U_i
static_assert(noexcept(U_i(_0)),"");
static_assert(noexcept(U_i(_0,1)),"");
static_assert(noexcept(std::declval<U_i&>().get(_0)),"");
static_assert(noexcept(std::declval<U_i const&>().get(_0)),"");
static_assert(noexcept(std::declval<U_i volatile&>().get(_0)),"");
static_assert(noexcept(std::declval<U_i const volatile&>().get(_0)),"");
static_assert(noexcept(std::declval<U_i&&>().get(_0)),"");
#ifndef YAUL_VARIANT_NO_RRCV_QUALIFIED_FUNCTIONS
static_assert(noexcept(std::declval<U_i const&&>().get(_0)),"");
static_assert(noexcept(std::declval<U_i volatile&&>().get(_0)),"");
static_assert(noexcept(std::declval<U_i const volatile&&>().get(_0)),"");
#endif
static_assert(noexcept(std::declval<U_i&>().destruct(_0)),"");
static_assert(noexcept(std::declval<U_i const&>().destruct(_0)),"");
//static_assert(noexcept(std::declval<U_i volatile&>().destruct(_0)),""); // FIXME: shouldn't it work?
//static_assert(noexcept(std::declval<U_i const volatile&>().destruct(_0)),""); // FIXME: shouldn't it work?
static_assert(noexcept(std::declval<U_i&&>().destruct(_0)),"");
#ifndef YAUL_VARIANT_NO_RRCV_QUALIFIED_FUNCTIONS
static_assert(noexcept(std::declval<U_i const&&>().destruct(_0)),"");
//static_assert(noexcept(std::declval<U_i volatile&&>().destruct(_0)),""); // FIXME: shouldn't it work?
//static_assert(noexcept(std::declval<U_i const volatile&&>().destruct(_0)),""); // FIXME: shouldn't it work?
#endif
static_assert(noexcept(std::declval<U_i&>().~U_i()),"");

// check noexcept-ness of certain expressions on U_ic
static_assert(noexcept(U_ic(_0)),"");
static_assert(noexcept(U_ic(_0,1)),"");
static_assert(noexcept(U_ic(_1,'a')),"");
static_assert(noexcept(std::declval<U_ic&>().get(_0)),"");
static_assert(noexcept(std::declval<U_ic&>().get(_1)),"");
static_assert(noexcept(std::declval<U_ic const&>().get(_0)),"");
static_assert(noexcept(std::declval<U_ic const&>().get(_1)),"");
static_assert(noexcept(std::declval<U_ic volatile&>().get(_0)),"");
static_assert(noexcept(std::declval<U_ic volatile&>().get(_1)),"");
static_assert(noexcept(std::declval<U_ic const volatile&>().get(_0)),"");
static_assert(noexcept(std::declval<U_ic const volatile&>().get(_1)),"");
static_assert(noexcept(std::declval<U_ic&&>().get(_0)),"");
static_assert(noexcept(std::declval<U_ic&&>().get(_1)),"");
#ifndef YAUL_VARIANT_NO_RRCV_QUALIFIED_FUNCTIONS
static_assert(noexcept(std::declval<U_ic const&&>().get(_0)),"");
static_assert(noexcept(std::declval<U_ic const&&>().get(_1)),"");
static_assert(noexcept(std::declval<U_ic volatile&&>().get(_0)),"");
static_assert(noexcept(std::declval<U_ic volatile&&>().get(_1)),"");
static_assert(noexcept(std::declval<U_ic const volatile&&>().get(_0)),"");
static_assert(noexcept(std::declval<U_ic const volatile&&>().get(_1)),"");
#endif
static_assert(noexcept(std::declval<U_ic&>().~U_ic()),"");

// check noexcept-ness of certain expressions on variadic_union<int, S2>
static_assert(noexcept(variadic_union<int, S2>(_0)),"");
static_assert(noexcept(variadic_union<int, S2>(_0,1)),"");
static_assert(noexcept(variadic_union<int, S2>(_1)),"");
static_assert(!noexcept(variadic_union<int, S2>(_1,"a")),"");
static_assert(noexcept(std::declval<variadic_union<int, S2>&>().get(_0)),"");
static_assert(noexcept(std::declval<variadic_union<int, S2>&>().get(_1)),"");
static_assert(noexcept(std::declval<variadic_union<int, S2> const&>().get(_0)),"");
static_assert(noexcept(std::declval<variadic_union<int, S2> const&>().get(_1)),"");
static_assert(noexcept(std::declval<variadic_union<int, S2> volatile&>().get(_0)),"");
static_assert(noexcept(std::declval<variadic_union<int, S2> volatile&>().get(_1)),"");
static_assert(noexcept(std::declval<variadic_union<int, S2> const volatile&>().get(_0)),"");
static_assert(noexcept(std::declval<variadic_union<int, S2> const volatile&>().get(_1)),"");
static_assert(noexcept(std::declval<variadic_union<int, S2>&&>().get(_0)),"");
static_assert(noexcept(std::declval<variadic_union<int, S2>&&>().get(_1)),"");
#ifndef YAUL_VARIANT_NO_RRCV_QUALIFIED_FUNCTIONS
static_assert(noexcept(std::declval<variadic_union<int, S2> const&&>().get(_0)),"");
static_assert(noexcept(std::declval<variadic_union<int, S2> const&&>().get(_1)),"");
static_assert(noexcept(std::declval<variadic_union<int, S2> volatile&&>().get(_0)),"");
static_assert(noexcept(std::declval<variadic_union<int, S2> volatile&&>().get(_1)),"");
static_assert(noexcept(std::declval<variadic_union<int, S2> const volatile&&>().get(_0)),"");
static_assert(noexcept(std::declval<variadic_union<int, S2> const volatile&&>().get(_1)),"");
#endif
static_assert(noexcept(std::declval<variadic_union<int, S2>&>().~variadic_union()),"");

// check noexcept-ness of certain expressions on variadic_union<int, S4>
static_assert( noexcept(std::declval<variadic_union<int,S4>&>().~variadic_union()), ""); // variadic_union has always trivial d-tor
static_assert( noexcept(std::declval<variadic_union<int,S4>&>().destruct(_0)), "");
static_assert(!noexcept(std::declval<variadic_union<int,S4>&>().destruct(_1)), "");

constexpr U_i const u_i_c_02{_0, 2};
constexpr U_ic const u_ic_c_02{_0, 2};
constexpr U_ic const u_ic_c_1a{_1, 'a'};

static_assert(u_i_c_02.get(_0) == 2, "");
static_assert(u_ic_c_02.get(_0) == 2, "");
static_assert(u_ic_c_1a.get(_1) == 'a', "");


constexpr U_i const u_i_rc_02{_0, 2};
constexpr U_ic const u_ic_rc_02{_0, 2};
constexpr U_ic const u_ic_rc_1a{_1, 'a'};

static_assert(std::move(u_i_rc_02).get(_0) == 2, "");
static_assert(std::move(u_ic_rc_02).get(_0) == 2, "");
static_assert(std::move(u_ic_rc_1a).get(_1) == 'a', "");

constexpr variadic_union<int, S1> u_is1_c_02{_0, 2};
constexpr variadic_union<int, S1> u_is1_c_1_{_0};

static_assert(u_is1_c_02.get(_0) == 2, "");
static_assert(u_is1_c_1_.get(_1).qual() == q_lr_c, "");

constexpr variadic_union<int, S1> u_is1_rc_02{_0, 2};
constexpr variadic_union<int, S1> u_is1_rc_1_{_0};

static_assert(std::move(u_is1_rc_02).get(_0) == 2, "");
#ifndef YAUL_VARIANT_NO_RRCV_QUALIFIED_FUNCTIONS
static_assert(std::move(u_is1_rc_1_).get(_1).qual() == q_rr_c, "");
#else
static_assert(std::move(u_is1_rc_1_).get(_1).qual() == q_lr_c, "");
#endif

void test__variadic_union__00()
{
  {
    variadic_union<int,char> u{_0}; // default c-tor 0
    u.get(_0) = 3;
    YAUL_VARIANT_CHECK(u.get(_0) == 3);
    u.get(_1) = 'z';
    YAUL_VARIANT_CHECK(u.get(_1) == 'z');
  }
  {
    variadic_union<int,char> u{_1}; // default c-tor 1
    u.get(_0) = 3;
    YAUL_VARIANT_CHECK(u.get(_0) == 3);
    u.get(_1) = 'z';
    YAUL_VARIANT_CHECK(u.get(_1) == 'z');
  }
}

void test__variadic_union__01()
{
  {
    variadic_union<int, S1> u(_0,2);
    YAUL_VARIANT_CHECK(u.get(_0) == 2);
  }
  {
    variadic_union<int, S1> u(_1);
    YAUL_VARIANT_CHECK(u.get(_1).qual() == q_lr);
    u.get(_0) = 2;
    YAUL_VARIANT_CHECK(u.get(_0) == 2);
  }
  {
    variadic_union<int, S1> const u(_0,2);
    YAUL_VARIANT_CHECK(u.get(_0) == 2);
  }
  {
    variadic_union<int, S1> const u(_1);
    YAUL_VARIANT_CHECK(u.get(_1).qual() == q_lr_c);
  }
  {
    variadic_union<int, S1> volatile u(_0,2);
    YAUL_VARIANT_CHECK(u.get(_0) == 2);
  }
  {
    variadic_union<int, S1> volatile u(_1);
    YAUL_VARIANT_CHECK(u.get(_1).qual() == q_lr_v);
    u.get(_0) = 2;
    YAUL_VARIANT_CHECK(u.get(_0) == 2);
  }
  {
    variadic_union<int, S1> const volatile u(_0,2);
    YAUL_VARIANT_CHECK(u.get(_0) == 2);
  }
  {
    variadic_union<int, S1> const volatile u(_1);
    YAUL_VARIANT_CHECK(u.get(_1).qual() == q_lr_cv);
  }
  {
    variadic_union<int, S1> u(_0,2);
    YAUL_VARIANT_CHECK(std::move(u).get(_0) == 2);
  }
  {
    variadic_union<int, S1> u(_1);
    YAUL_VARIANT_CHECK(std::move(u).get(_1).qual() == q_rr);
  }
#ifndef YAUL_VARIANT_NO_RRCV_QUALIFIED_FUNCTIONS
  {
    variadic_union<int, S1> const u(_0,2);
    YAUL_VARIANT_CHECK(std::move(u).get(_0) == 2);
  }
  {
    variadic_union<int, S1> const u(_1);
    YAUL_VARIANT_CHECK(std::move(u).get(_1).qual() == q_rr_c);
  }
  {
    variadic_union<int, S1> volatile u(_0,2);
    YAUL_VARIANT_CHECK(std::move(u).get(_0) == 2);
  }
  {
    variadic_union<int, S1> volatile u(_1);
    YAUL_VARIANT_CHECK(std::move(u).get(_1).qual() == q_rr_v);
  }
  {
    variadic_union<int, S1> const volatile u(_0, 2);
    YAUL_VARIANT_CHECK(std::move(u).get(_0) == 2);
  }
  {
    variadic_union<int, S1> const volatile u(_1);
    YAUL_VARIANT_CHECK(std::move(u).get(_1).qual() == q_rr_cv);
  }
#endif
}

void test__variadic_union__02()
{
  {
    int const count = S2::count;
    variadic_union<S1, S2> u(_0);
    YAUL_VARIANT_CHECK_EQUALS(S2::count, count);
    YAUL_VARIANT_CHECK(u.get(_0).qual() == q_lr);
    u.get(_1) = S2{};
    YAUL_VARIANT_CHECK_EQUALS(S2::count, count);
    YAUL_VARIANT_CHECK(u.get(_1).qual() == q_lr);
  }
  {
    int const count = S2::count;
    variadic_union<S1, S2> u(_1);
    YAUL_VARIANT_CHECK_EQUALS(S2::count, count + 1);
    YAUL_VARIANT_CHECK(u.get(_1).qual() == q_lr);
    u.destruct(_1);
    YAUL_VARIANT_CHECK_EQUALS(S2::count, count);
    u.get(_0) = S1{};
    YAUL_VARIANT_CHECK(u.get(_0).qual() == q_lr);
  }
  {
    variadic_union<S1, S2> const u(_0);
    YAUL_VARIANT_CHECK(u.get(_0).qual() == q_lr_c);
  }
  {
    variadic_union<S1, S2> const u(_1);
    YAUL_VARIANT_CHECK(u.get(_1).qual() == q_lr_c);
  }
  {
    variadic_union<S1, S2> volatile u(_0);
    YAUL_VARIANT_CHECK(u.get(_0).qual() == q_lr_v);
  }
  {
    variadic_union<S1, S2> volatile u(_1);
    YAUL_VARIANT_CHECK(u.get(_1).qual() == q_lr_v);
  }
  {
    variadic_union<S1, S2> const volatile u(_0);
    YAUL_VARIANT_CHECK(u.get(_0).qual() == q_lr_cv);
  }
  {
    variadic_union<S1, S2> const volatile u(_1);
    YAUL_VARIANT_CHECK(u.get(_1).qual() == q_lr_cv);
  }
  {
    variadic_union<S1, S2> u(_0);
    YAUL_VARIANT_CHECK(std::move(u).get(_0).qual() == q_rr);
    u.get(_1) = S2{};
    YAUL_VARIANT_CHECK(std::move(u).get(_1).qual() == q_rr);
  }
  {
    variadic_union<S1, S2> u(_1);
    YAUL_VARIANT_CHECK(std::move(u).get(_1).qual() == q_rr);
    u.get(_0) = S1{};
    YAUL_VARIANT_CHECK(std::move(u).get(_0).qual() == q_rr);
  }
#ifndef YAUL_VARIANT_NO_RRCV_QUALIFIED_FUNCTIONS
  {
    variadic_union<S1, S2> const u(_0);
    YAUL_VARIANT_CHECK(std::move(u).get(_0).qual() == q_rr_c);
  }
  {
    variadic_union<S1, S2> const u(_1);
    YAUL_VARIANT_CHECK(std::move(u).get(_1).qual() == q_rr_c);
  }
  {
    variadic_union<S1, S2> volatile u(_0);
    YAUL_VARIANT_CHECK(std::move(u).get(_0).qual() == q_rr_v);
  }
  {
    variadic_union<S1, S2> volatile u(_1);
    YAUL_VARIANT_CHECK(std::move(u).get(_1).qual() == q_rr_v);
  }
  {
    variadic_union<S1, S2> const volatile u(_0);
    YAUL_VARIANT_CHECK(std::move(u).get(_0).qual() == q_rr_cv);
  }
  {
    variadic_union<S1, S2> const volatile u(_1);
    YAUL_VARIANT_CHECK(std::move(u).get(_1).qual() == q_rr_cv);
  }
#endif
}

void test__variadic_union__03()
{
  // &
  {
    variadic_union<S1, S2, S3> u(_0);
    YAUL_VARIANT_CHECK(u.get(_0).qual() == q_lr);
    u.get(_1) = S2{};
    YAUL_VARIANT_CHECK(u.get(_1).qual() == q_lr);
    u.get(_2) = S3{};
    YAUL_VARIANT_CHECK(u.get(_2).qual() == q_lr);
  }
  {
    variadic_union<S1, S2, S3> u(_1);
    YAUL_VARIANT_CHECK(u.get(_1).qual() == q_lr);
    u.get(_0) = S1{};
    YAUL_VARIANT_CHECK(u.get(_0).qual() == q_lr);
    u.get(_2) = S3{};
    YAUL_VARIANT_CHECK(u.get(_2).qual() == q_lr);
  }
  {
    variadic_union<S1, S2, S3> u(_2);
    YAUL_VARIANT_CHECK(u.get(_2).qual() == q_lr);
    u.get(_0) = S1{};
    YAUL_VARIANT_CHECK(u.get(_0).qual() == q_lr);
    u.get(_1) = S2{};
    YAUL_VARIANT_CHECK(u.get(_1).qual() == q_lr);
  }
  // const&
  {
    variadic_union<S1, S2, S3> const u(_0);
    YAUL_VARIANT_CHECK(u.get(_0).qual() == q_lr_c);
  }
  {
    variadic_union<S1, S2, S3> const u(_1);
    YAUL_VARIANT_CHECK(u.get(_1).qual() == q_lr_c);
  }
  {
    variadic_union<S1, S2, S3> const u(_2);
    YAUL_VARIANT_CHECK(u.get(_2).qual() == q_lr_c);
  }
  // volatile&
  {
    variadic_union<S1, S2, S3> volatile u(_0);
    YAUL_VARIANT_CHECK(u.get(_0).qual() == q_lr_v);
  }
  {
    variadic_union<S1, S2, S3> volatile u(_1);
    YAUL_VARIANT_CHECK(u.get(_1).qual() == q_lr_v);
  }
  {
    variadic_union<S1, S2, S3> volatile u(_2);
    YAUL_VARIANT_CHECK(u.get(_2).qual() == q_lr_v);
  }
  // const volatile&
  {
    variadic_union<S1, S2, S3> const volatile u(_0);
    YAUL_VARIANT_CHECK(u.get(_0).qual() == q_lr_cv);
  }
  {
    variadic_union<S1, S2, S3> const volatile u(_1);
    YAUL_VARIANT_CHECK(u.get(_1).qual() == q_lr_cv);
  }
  {
    variadic_union<S1, S2, S3> const volatile u(_2);
    YAUL_VARIANT_CHECK(u.get(_2).qual() == q_lr_cv);
  }
  // &&
  {
    variadic_union<S1, S2, S3> u(_0);
    YAUL_VARIANT_CHECK(std::move(u).get(_0).qual() == q_rr);
    u.get(_1) = S2{};
    YAUL_VARIANT_CHECK(std::move(u).get(_1).qual() == q_rr);
    u.get(_2) = S3{};
    YAUL_VARIANT_CHECK(std::move(u).get(_2).qual() == q_rr);
  }
  {
    variadic_union<S1, S2, S3> u(_1);
    YAUL_VARIANT_CHECK(std::move(u).get(_1).qual() == q_rr);
    u.get(_0) = S1{};
    YAUL_VARIANT_CHECK(std::move(u).get(_0).qual() == q_rr);
    u.get(_2) = S3{};
    YAUL_VARIANT_CHECK(std::move(u).get(_2).qual() == q_rr);
  }
  {
    variadic_union<S1, S2, S3> u(_2);
    YAUL_VARIANT_CHECK(std::move(u).get(_2).qual() == q_rr);
    u.get(_0) = S1{};
    YAUL_VARIANT_CHECK(std::move(u).get(_0).qual() == q_rr);
    u.get(_1) = S2{};
    YAUL_VARIANT_CHECK(std::move(u).get(_1).qual() == q_rr);
  }
#ifndef YAUL_VARIANT_NO_RRCV_QUALIFIED_FUNCTIONS
  // const&&
  {
    variadic_union<S1, S2, S3> const u(_0);
    YAUL_VARIANT_CHECK(std::move(u).get(_0).qual() == q_rr_c);
  }
  {
    variadic_union<S1, S2, S3> const u(_1);
    YAUL_VARIANT_CHECK(std::move(u).get(_1).qual() == q_rr_c);
  }
  {
    variadic_union<S1, S2, S3> const u(_2);
    YAUL_VARIANT_CHECK(std::move(u).get(_2).qual() == q_rr_c);
  }
  // volatile&&
  {
    variadic_union<S1, S2, S3> volatile u(_0);
    YAUL_VARIANT_CHECK(std::move(u).get(_0).qual() == q_rr_v);
  }
  {
    variadic_union<S1, S2, S3> volatile u(_1);
    YAUL_VARIANT_CHECK(std::move(u).get(_1).qual() == q_rr_v);
  }
  {
    variadic_union<S1, S2, S3> volatile u(_2);
    YAUL_VARIANT_CHECK(std::move(u).get(_2).qual() == q_rr_v);
  }
  // const volatile&&
  {
    variadic_union<S1, S2, S3> const volatile u(_0);
    YAUL_VARIANT_CHECK(std::move(u).get(_0).qual() == q_rr_cv);
  }
  {
    variadic_union<S1, S2, S3> const volatile u(_1);
    YAUL_VARIANT_CHECK(std::move(u).get(_1).qual() == q_rr_cv);
  }
  {
    variadic_union<S1, S2, S3> const volatile u(_2);
    YAUL_VARIANT_CHECK(std::move(u).get(_2).qual() == q_rr_cv);
  }
#endif
}

int main()
{
  test__variadic_union__00();
  test__variadic_union__01();
  test__variadic_union__02();
  test__variadic_union__03();
  return YAUL_VARIANT_TEST_EXIT_CODE;
}
