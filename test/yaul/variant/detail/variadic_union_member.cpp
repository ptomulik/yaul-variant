// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <yaul/variant/detail/variadic_union_member.hpp>
#include <yaul/variant/test_config.hpp>

using yaul::detail::variant::variadic_union_member;
using yaul::detail::variant::in_place_index_t;

constexpr in_place_index_t<0ul> _0{};

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

// nontrivially destructible
struct S2
{
  static int count;
   S2() noexcept { ++ count; }
  ~S2() noexcept { -- count; }

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

using M_S2 = variadic_union_member<S2>;
static_assert( std::is_trivially_destructible< M_S2 >::value, "");
static_assert(!std::is_default_constructible< M_S2 >::value, "");
static_assert( std::is_constructible< M_S2, in_place_index_t<0ul> >::value, "");

struct U_S2
{
   M_S2 m;
   U_S2() noexcept : m(_0) { }
  ~U_S2() noexcept { m.destruct(); }
};



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
  //
  // Test with U_S2 (wrapper around M_S2)
  //
  int const count = S2::count;
  {
    U_S2 u;
    YAUL_VARIANT_CHECK(u.m.get().qual() == q_lr);
    YAUL_VARIANT_CHECK_EQUALS(S2::count, count+1); // ctor invoked
  }
  YAUL_VARIANT_CHECK_EQUALS(S2::count, count); // dtor invoked
  {
    U_S2 const u;
    YAUL_VARIANT_CHECK(u.m.get().qual() == q_lr_c);
    YAUL_VARIANT_CHECK_EQUALS(S2::count, count+1); // ctor invoked
  }
  YAUL_VARIANT_CHECK_EQUALS(S2::count, count); // dtor invoked
  {
    U_S2 volatile u;
    YAUL_VARIANT_CHECK(u.m.get().qual() == q_lr_v);
    YAUL_VARIANT_CHECK_EQUALS(S2::count, count+1); // ctor invoked
  }
  YAUL_VARIANT_CHECK_EQUALS(S2::count, count); // dtor invoked
  {
    U_S2 const volatile u;
    YAUL_VARIANT_CHECK(u.m.get().qual() == q_lr_cv);
    YAUL_VARIANT_CHECK_EQUALS(S2::count, count+1); // ctor invoked
  }
  YAUL_VARIANT_CHECK_EQUALS(S2::count, count); // dtor invoked
  {
    U_S2 u;
    YAUL_VARIANT_CHECK(std::move(u).m.get().qual() == q_rr);
    YAUL_VARIANT_CHECK_EQUALS(S2::count, count+1); // ctor invoked
  }
  YAUL_VARIANT_CHECK_EQUALS(S2::count, count); // dtor invoked
#ifndef YAUL_VARIANT_NO_RRCV_QUALIFIED_FUNCTIONS
  {
    U_S2 const u;
    YAUL_VARIANT_CHECK(std::move(u).m.get().qual() == q_rr_c); // ctor invoked
    YAUL_VARIANT_CHECK_EQUALS(S2::count, count+1);
  }
  YAUL_VARIANT_CHECK_EQUALS(S2::count, count); // dtor invoked
  {
    U_S2 volatile u;
    YAUL_VARIANT_CHECK(std::move(u).m.get().qual() == q_rr_v); // ctor invoked
    YAUL_VARIANT_CHECK_EQUALS(S2::count, count+1);
  }
  YAUL_VARIANT_CHECK_EQUALS(S2::count, count); // dtor invoked
  {
    U_S2 const volatile u;
    YAUL_VARIANT_CHECK(std::move(u).m.get().qual() == q_rr_cv); // ctor invoked
    YAUL_VARIANT_CHECK_EQUALS(S2::count, count+1);
  }
  YAUL_VARIANT_CHECK_EQUALS(S2::count, count); // dtor invoked
#endif
}


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

int main()
{
  test__variadic_union_member__with_S1();
  test__variadic_union_member__with_S2();
  test__variadic_union_member__with_S3();
  return YAUL_VARIANT_TEST_EXIT_CODE;
}
