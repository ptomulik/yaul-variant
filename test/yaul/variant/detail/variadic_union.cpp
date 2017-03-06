// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <yaul/variant/detail/variadic_union.hpp>
#include <yaul/variant/test_config.hpp>
#include <type_traits>

using yaul::detail::variant::variadic_element;
using yaul::detail::variant::variadic_union_member;
using yaul::detail::variant::variadic_union;
using yaul::detail::variant::in_place_index_t;

constexpr in_place_index_t<0ul> _0{};
constexpr in_place_index_t<1ul> _1{};
//constexpr in_place_index_t<2ul> _2{};
//constexpr in_place_index_t<3ul> _3{};

using M_int = variadic_union_member<int>;
static_assert( std::is_trivially_destructible< M_int >::value, "");
static_assert(!std::is_default_constructible< M_int >::value, "");
static_assert( std::is_constructible< M_int, in_place_index_t<0ul> >::value, "");
static_assert( std::is_constructible< M_int, in_place_index_t<0ul>, int >::value, "");

// check some constant expressions
constexpr M_int const m_int_c_2{_0, 2};
static_assert( m_int_c_2.get() == 2, "");

#ifndef YAUL_VARIANT_NO_RRCV_QUALIFIED_FUNCTIONS
constexpr M_int const m_int_rc_2{_0, 2};
static_assert( std::move(m_int_rc_2).get() == 2, "");
#endif // YAUL_VARIANT_NO_RRCV_QUALIFIED_FUNCTIONS

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

using M_S1 = variadic_union_member<S1>;
static_assert( std::is_trivially_destructible< M_S1 >::value, "");
static_assert(!std::is_default_constructible< M_S1 >::value, "");
static_assert( std::is_constructible< M_S1, in_place_index_t<0ul> >::value, "");

constexpr M_S1 const m_s1_lc{_0};
static_assert( m_s1_lc.get().qual() == q_lr_c, "");

constexpr M_S1 const m_s1_rc{_0};
#ifndef YAUL_VARIANT_NO_RRCV_QUALIFIED_FUNCTIONS
static_assert( std::move(m_s1_rc).get().qual() == q_rr_c, "");
#else
static_assert( std::move(m_s1_rc).get().qual() == q_lr_c, "");
#endif

void test__variadic_union_member__with_S1()
{
  {
    M_S1 m{_0};
    YAUL_VARIANT_CHECK(m.get().qual() == q_lr);
  }
  {
    M_S1 const m{_0};
    YAUL_VARIANT_CHECK(m.get().qual() == q_lr_c);
  }
  {
    M_S1 volatile m{_0};
    YAUL_VARIANT_CHECK(m.get().qual() == q_lr_v);
  }
  {
    M_S1 const volatile m{_0};
    YAUL_VARIANT_CHECK(m.get().qual() == q_lr_cv);
  }
  {
    M_S1 m{_0};
    YAUL_VARIANT_CHECK(std::move(m).get().qual() == q_rr);
  }
#ifndef YAUL_VARIANT_NO_RRCV_QUALIFIED_FUNCTIONS
  {
    M_S1 const m{_0};
    YAUL_VARIANT_CHECK(std::move(m).get().qual() == q_rr_c);
  }
  {
    M_S1 volatile m{_0};
    YAUL_VARIANT_CHECK(std::move(m).get().qual() == q_rr_v);
  }
  {
    M_S1 const volatile m{_0};
    YAUL_VARIANT_CHECK(std::move(m).get().qual() == q_rr_cv);
  }
#endif
}



// nontrivially destructible
struct S2
{
  ~S2() {}

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
using M_S2 = variadic_union_member<S2>;
static_assert( std::is_trivially_destructible< M_S2 >::value, "");
static_assert(!std::is_default_constructible< M_S2 >::value, "");
static_assert( std::is_constructible< M_S2, in_place_index_t<0ul> >::value, "");

void test__variadic_union_member__with_S2()
{
  {
    M_S2 m{_0};
    YAUL_VARIANT_CHECK(m.get().qual() == q_lr);
  }
  {
    M_S2 const m{_0};
    YAUL_VARIANT_CHECK(m.get().qual() == q_lr_c);
  }
  {
    M_S2 volatile m{_0};
    YAUL_VARIANT_CHECK(m.get().qual() == q_lr_v);
  }
  {
    M_S2 const volatile m{_0};
    YAUL_VARIANT_CHECK(m.get().qual() == q_lr_cv);
  }
  {
    M_S2 m{_0};
    YAUL_VARIANT_CHECK(std::move(m).get().qual() == q_rr);
  }
#ifndef YAUL_VARIANT_NO_RRCV_QUALIFIED_FUNCTIONS
  {
    M_S2 const m{_0};
    YAUL_VARIANT_CHECK(std::move(m).get().qual() == q_rr_c);
  }
  {
    M_S2 volatile m{_0};
    YAUL_VARIANT_CHECK(std::move(m).get().qual() == q_rr_v);
  }
  {
    M_S2 const volatile m{_0};
    YAUL_VARIANT_CHECK(std::move(m).get().qual() == q_rr_cv);
  }
#endif
}


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
static_assert(!std::is_literal_type<S3>::value, "");
static_assert( std::is_trivially_destructible<S3>::value, "");

using M_S3 = variadic_union_member<S3>;
static_assert( std::is_trivially_destructible< M_S3 >::value, "");
static_assert(!std::is_default_constructible< M_S3 >::value, "");
static_assert( std::is_constructible< M_S3, in_place_index_t<0ul> >::value, "");

void test__variadic_union_member__with_S3()
{
  {
    M_S3 m{_0};
    YAUL_VARIANT_CHECK(m.get().qual() == q_lr);
  }
  {
    M_S3 const m{_0};
    YAUL_VARIANT_CHECK(m.get().qual() == q_lr_c);
  }
  {
    M_S3 volatile m{_0};
    YAUL_VARIANT_CHECK(m.get().qual() == q_lr_v);
  }
  {
    M_S3 const volatile m{_0};
    YAUL_VARIANT_CHECK(m.get().qual() == q_lr_cv);
  }
  {
    M_S3 m{_0};
    YAUL_VARIANT_CHECK(std::move(m).get().qual() == q_rr);
  }
#ifndef YAUL_VARIANT_NO_RRCV_QUALIFIED_FUNCTIONS
  {
    M_S3 const m{_0};
    YAUL_VARIANT_CHECK(std::move(m).get().qual() == q_rr_c);
  }
  {
    M_S3 volatile m{_0};
    YAUL_VARIANT_CHECK(std::move(m).get().qual() == q_rr_v);
  }
  {
    M_S3 const volatile m{_0};
    YAUL_VARIANT_CHECK(std::move(m).get().qual() == q_rr_cv);
  }
#endif

  {
    M_S3 m{_0,2};
    YAUL_VARIANT_CHECK(m.get().i == 2);
    YAUL_VARIANT_CHECK(m.get().qual() == q_lr);
  }
  {
    M_S3 const m{_0,2};
    YAUL_VARIANT_CHECK(m.get().i == 2);
    YAUL_VARIANT_CHECK(m.get().qual() == q_lr_c);
  }
  {
    M_S3 volatile m{_0,2};
    YAUL_VARIANT_CHECK(m.get().i == 2);
    YAUL_VARIANT_CHECK(m.get().qual() == q_lr_v);
  }
  {
    M_S3 const volatile m{_0,2};
    YAUL_VARIANT_CHECK(m.get().i == 2);
    YAUL_VARIANT_CHECK(m.get().qual() == q_lr_cv);
  }
  {
    M_S3 m{_0,2};
    YAUL_VARIANT_CHECK(std::move(m).get().i == 2);
    YAUL_VARIANT_CHECK(std::move(m).get().qual() == q_rr);
  }
#ifndef YAUL_VARIANT_NO_RRCV_QUALIFIED_FUNCTIONS
  {
    M_S3 const m{_0,2};
    YAUL_VARIANT_CHECK(std::move(m).get().i == 2);
    YAUL_VARIANT_CHECK(std::move(m).get().qual() == q_rr_c);
  }
  {
    M_S3 volatile m{_0,2};
    YAUL_VARIANT_CHECK(std::move(m).get().i == 2);
    YAUL_VARIANT_CHECK(std::move(m).get().qual() == q_rr_v);
  }
  {
    M_S3 const volatile m{_0,2};
    YAUL_VARIANT_CHECK(std::move(m).get().i == 2);
    YAUL_VARIANT_CHECK(std::move(m).get().qual() == q_rr_cv);
  }
#endif
}

static_assert(std::is_same<variadic_element<0ul, int>::type, int>::value, "");
static_assert(std::is_same<variadic_element<0ul, int, char>::type, int>::value, "");
static_assert(std::is_same<variadic_element<1ul, int, char>::type, char>::value, "");

using U_i = variadic_union<int>;
using U_ic = variadic_union<int,char>;
static_assert(!std::is_default_constructible<U_i>::value, "");
static_assert( std::is_constructible<U_i, in_place_index_t<0ul> >::value, "");
static_assert( std::is_constructible<U_i, in_place_index_t<0ul>, int>::value, "");

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
    variadic_union<int, S1> u(_1);
    YAUL_VARIANT_CHECK(u.get(_1).qual() == q_lr);
    u.get(_0) = 2;
    YAUL_VARIANT_CHECK(u.get(_0) == 2);
  }
  {
    variadic_union<int, S1> const u(_1);
    YAUL_VARIANT_CHECK(u.get(_1).qual() == q_lr_c);
  }
  {
    variadic_union<int, S1> volatile u(_1);
    YAUL_VARIANT_CHECK(u.get(_1).qual() == q_lr_v);
    u.get(_0) = 2;
    YAUL_VARIANT_CHECK(u.get(_0) == 2);
  }
  {
    variadic_union<int, S1> const volatile u(_1);
    YAUL_VARIANT_CHECK(u.get(_1).qual() == q_lr_cv);
  }
  {
    variadic_union<int, S1> u(_1);
    YAUL_VARIANT_CHECK(std::move(u).get(_1).qual() == q_rr);
  }
#ifndef YAUL_VARIANT_NO_RRCV_QUALIFIED_FUNCTIONS
  {
    variadic_union<int, S1> const u(_1);
    YAUL_VARIANT_CHECK(std::move(u).get(_1).qual() == q_rr_c);
  }
  {
    variadic_union<int, S1> volatile u(_1);
    YAUL_VARIANT_CHECK(std::move(u).get(_1).qual() == q_rr_v);
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
    variadic_union<S1, S2> u(_1);
    YAUL_VARIANT_CHECK(u.get(_1).qual() == q_lr);
    u.get(_0) = S1{};
    YAUL_VARIANT_CHECK(u.get(_0).qual() == q_lr);
  }
  {
    variadic_union<S1, S2> const u(_1);
    YAUL_VARIANT_CHECK(u.get(_1).qual() == q_lr_c);
    // const!!
    //u.get(_0) = S1{};
    //YAUL_VARIANT_CHECK(u.get(_0).qual() == q_lr_c);
  }
  {
    variadic_union<S1, S2> volatile u(_1);
    YAUL_VARIANT_CHECK(u.get(_1).qual() == q_lr_v);
    // volatile!
    // S1 s;
    // u.get(_0) = s;
    // YAUL_VARIANT_CHECK(u.get(_0).qual() == q_lr_v);
  }
  {
    variadic_union<S1, S2> const volatile u(_1);
    YAUL_VARIANT_CHECK(u.get(_1).qual() == q_lr_cv);
    // const!
    //u.get(_0) = S1{};
    //YAUL_VARIANT_CHECK(u.get(_0).qual() == q_lr_cv);
  }
  {
    variadic_union<S1, S2> u(_1);
    YAUL_VARIANT_CHECK(std::move(u).get(_1).qual() == q_rr);
    u.get(_0) = S1{};
    YAUL_VARIANT_CHECK(std::move(u).get(_0).qual() == q_rr);
  }
#ifndef YAUL_VARIANT_NO_RRCV_QUALIFIED_FUNCTIONS
  {
    variadic_union<S1, S2> const u(_1);
    YAUL_VARIANT_CHECK(std::move(u).get(_1).qual() == q_rr_c);
    // const!
    //u.get(_0) = S1{};
    //YAUL_VARIANT_CHECK(std::move(u).get(_0).qual() == q_rr_c);
  }
  {
    variadic_union<S1, S2> volatile u(_1);
    YAUL_VARIANT_CHECK(std::move(u).get(_1).qual() == q_rr_v);
    // volatile!
    // u.get(_0) = S1{};
    // YAUL_VARIANT_CHECK(std::move(u).get(_0).qual() == q_rr_v);
  }
  {
    variadic_union<S1, S2> const volatile u(_1);
    YAUL_VARIANT_CHECK(std::move(u).get(_1).qual() == q_rr_cv);
    // const!
    //u.get(_0) = S1{};
    //YAUL_VARIANT_CHECK(std::move(u).get(_0).qual() == q_rr_cv);
  }
#endif
}

int main()
{
  test__variadic_union_member__with_S1();
  test__variadic_union_member__with_S2();
  test__variadic_union_member__with_S3();
  test__variadic_union__00();
  test__variadic_union__01();
  test__variadic_union__02();
  return YAUL_VARIANT_TEST_EXIT_CODE;
}
