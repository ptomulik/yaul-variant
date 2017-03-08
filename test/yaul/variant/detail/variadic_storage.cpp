// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <yaul/variant/detail/variadic_storage.hpp>
#include <yaul/variant/test_config.hpp>
#include <type_traits>

using yaul::detail::variant::variadic_storage;
using yaul::detail::variant::in_place_index_t;

constexpr const in_place_index_t<0ul> _0{};

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

using S_S1 = variadic_storage<S1>;
constexpr const S_S1 s_s1{_0};

static_assert( std::is_trivially_destructible<S_S1>::value, "");
static_assert(!std::is_default_constructible<S_S1>::value, "");
static_assert(s_s1.index() == 0, "");

struct S2
{
  static int count;
   S2() { ++count; }
  ~S2() { --count; }
};
int S2::count = 0;

void test__variadic_storage__with_S1()
{
  {
    variadic_storage<S1> s{_0};
    YAUL_VARIANT_CHECK_EQUALS(s.index(), 0);
  }
}

void test__variadic_storage__with_S2()
{
  const int count = S2::count;
  {
    variadic_storage<S2> s{_0};
    YAUL_VARIANT_CHECK_EQUALS(s.index(), 0);
    YAUL_VARIANT_CHECK_EQUALS(S2::count, count+1);
  }
  YAUL_VARIANT_CHECK_EQUALS(S2::count, count);
}

void test__variadic_storage__with_S1S2()
{
  const int count = S2::count;
  {
    variadic_storage<S1,S2> s{_0};
    YAUL_VARIANT_CHECK_EQUALS(s.index(), 0);
    YAUL_VARIANT_CHECK_EQUALS(S2::count, count);
  }
  YAUL_VARIANT_CHECK_EQUALS(S2::count, count);
}

int main()
{
  test__variadic_storage__with_S1();
  test__variadic_storage__with_S1S2();
  return YAUL_VARIANT_TEST_EXIT_CODE;
}
