// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <yaul/variant/detail/variadic_storage.hpp>
#include <yaul/variant/test_config.hpp>
#include <type_traits>
#include <utility>

using yaul::detail::variant::variadic_storage;
using yaul::detail::variant::make_variadic_storage;
using yaul::detail::variant::make_variadic_storage_t;
using yaul::detail::variant::in_place_index_t;

struct fake_union
{
  template<std::size_t I>
  void destruct(in_place_index_t<I>) noexcept(I == 0)
  { }
};

constexpr const in_place_index_t<0ul> _0{};

static_assert( noexcept(yaul::detail::variant::variadic_union_destruct<0ul>(std::declval<fake_union&>())), "");
static_assert(!noexcept(yaul::detail::variant::variadic_union_destruct<1ul>(std::declval<fake_union&>())), "");

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

static_assert(std::is_same<make_variadic_storage<int,S1>::type, variadic_storage<true,int,S1> >::value, "");
static_assert(std::is_same<make_variadic_storage_t<int,S1>, make_variadic_storage<int,S1>::type>::value, "");

using S_S1 = make_variadic_storage_t<S1>;
constexpr const S_S1 s_s1{_0};

static_assert( std::is_trivially_destructible<S_S1>::value, "");
static_assert(!std::is_default_constructible<S_S1>::value, "");
static_assert(s_s1.index() == 0, "");

// check noexcept-ness of certain expressions involving make_variadic_storage_t<..,S1,...>.
static_assert( noexcept(std::declval<make_variadic_storage_t<S1>&>().~variadic_storage()), "");
static_assert( noexcept(std::declval<make_variadic_storage_t<int,S1>&>().~variadic_storage()), "");
static_assert( noexcept(std::declval<make_variadic_storage_t<int,S1,float>&>().~variadic_storage()), "");
static_assert( noexcept(std::declval<make_variadic_storage_t<int,S1>&>().assign<0ul>(0)), "");
static_assert( noexcept(std::declval<make_variadic_storage_t<int,S1>&>().assign<1ul>(std::declval<S1>())), "");
static_assert( noexcept(std::declval<make_variadic_storage_t<int,S1>&>().emplace<0ul>(0)), "");
static_assert( noexcept(std::declval<make_variadic_storage_t<int,S1>&>().emplace<1ul>(std::declval<S1>())), "");

struct S2
{
  static int count;
   S2() noexcept { ++count; }
  ~S2() noexcept { --count; }
};
int S2::count = 0;

static_assert(std::is_same<make_variadic_storage<int,S2>::type, variadic_storage<false,int,S2> >::value, "");

// check noexcept-ness of certain expressions involving make_variadic_storage_t<..,S2,...>.
static_assert( noexcept(std::declval<make_variadic_storage_t<S2>&>().~variadic_storage()), "");
static_assert( noexcept(std::declval<make_variadic_storage_t<int,S2>&>().~variadic_storage()), "");
static_assert( noexcept(std::declval<make_variadic_storage_t<int,S2,float>&>().~variadic_storage()), "");

struct S3
{
  ~S3() noexcept(false) { } // intentionally not-noexcept
};

// check noexcept-ness of certain expressions involving make_variadic_storage_t<..,S3,...>.
static_assert(!noexcept(std::declval<make_variadic_storage_t<S3>&>().~variadic_storage()), "");
static_assert(!noexcept(std::declval<make_variadic_storage_t<int,S3>&>().~variadic_storage()), "");
static_assert(!noexcept(std::declval<make_variadic_storage_t<int,S3,float>&>().~variadic_storage()), "");
// All the following hold because of potentially-throwing d-tor S3::~S3().
static_assert(!noexcept(std::declval<make_variadic_storage_t<int,S3,float>&>().assign<0ul>(0)), "");
static_assert(!noexcept(std::declval<make_variadic_storage_t<int,S3,float>&>().assign<1ul>(std::declval<S3 const&>())), "");
static_assert(!noexcept(std::declval<make_variadic_storage_t<int,S3,float>&>().assign<2ul>(1.2f)), "");
static_assert(!noexcept(std::declval<make_variadic_storage_t<int,S3,float>&>().emplace<0ul>(0)), "");
static_assert(!noexcept(std::declval<make_variadic_storage_t<int,S3,float>&>().emplace<1ul>(std::declval<S3 const&>())), "");
static_assert(!noexcept(std::declval<make_variadic_storage_t<int,S3,float>&>().emplace<2ul>(1.2f)), "");


struct S4
{
  S4() {}                                     // intentionally not-noexcept
  S4(S4 const&) {}                            // intentionally not-noexcept
  S4& operator=(S4 const&) { return *this; }  // intentionally not-noexcept
};

// check noexcept-ness of certain expressions involving make_variadic_storage_t<..,S4,...>.
static_assert( noexcept(std::declval<make_variadic_storage_t<int,S4,float>&>().assign<0ul>(0)), "");
static_assert(!noexcept(std::declval<make_variadic_storage_t<int,S4,float>&>().assign<1ul>(std::declval<S4 const&>())), "");
static_assert( noexcept(std::declval<make_variadic_storage_t<int,S4,float>&>().assign<2ul>(1.2f)), "");
static_assert( noexcept(std::declval<make_variadic_storage_t<int,S4,float>&>().emplace<0ul>(0)), "");
static_assert(!noexcept(std::declval<make_variadic_storage_t<int,S4,float>&>().emplace<1ul>(std::declval<S4 const&>())), "");
static_assert( noexcept(std::declval<make_variadic_storage_t<int,S4,float>&>().emplace<2ul>(1.2f)), "");

void test__variadic_storage__with_S1()
{
  {
    make_variadic_storage_t<S1> s{_0};
    YAUL_VARIANT_CHECK_EQUALS(s.index(), 0);
  }
}

void test__variadic_storage__with_S2()
{
  const int count = S2::count;
  {
    make_variadic_storage_t<S2> s{_0};
    YAUL_VARIANT_CHECK_EQUALS(s.index(), 0);
    YAUL_VARIANT_CHECK_EQUALS(S2::count, count+1);
  }
  YAUL_VARIANT_CHECK_EQUALS(S2::count, count);
}

void test__variadic_storage__with_S1S2()
{
  const int count = S2::count;
  {
    make_variadic_storage_t<S1,S2> s{_0};
    YAUL_VARIANT_CHECK_EQUALS(s.index(), 0);
    YAUL_VARIANT_CHECK_EQUALS(S2::count, count);
  }
  YAUL_VARIANT_CHECK_EQUALS(S2::count, count);
}

void test__variadic_storage__assign()
{
  {
    make_variadic_storage_t<int,char> s{_0,0};
    YAUL_VARIANT_CHECK_EQUALS(s.index(), 0);
    s.assign<1ul>('a');
    YAUL_VARIANT_CHECK_EQUALS(s.index(), 1);
  }
  {
    volatile make_variadic_storage_t<int,char> s{_0,0};
    YAUL_VARIANT_CHECK_EQUALS(s.index(), 0);
    s.assign<1ul>('a');
    YAUL_VARIANT_CHECK_EQUALS(s.index(), 1);
  }
}

void test__variadic_storage__emplace()
{
  {
    make_variadic_storage_t<int,char> s{_0,0};
    YAUL_VARIANT_CHECK_EQUALS(s.index(), 0);
    s.emplace<1ul>('a');
    YAUL_VARIANT_CHECK_EQUALS(s.index(), 1);
  }
  {
    volatile make_variadic_storage_t<int,char> s{_0,0};
    YAUL_VARIANT_CHECK_EQUALS(s.index(), 0);
    s.emplace<1ul>('a');
    YAUL_VARIANT_CHECK_EQUALS(s.index(), 1);
  }
}

int main()
{
  test__variadic_storage__with_S1();
  test__variadic_storage__with_S1S2();
  test__variadic_storage__assign();
  test__variadic_storage__emplace();
  return YAUL_VARIANT_TEST_EXIT_CODE;
}
