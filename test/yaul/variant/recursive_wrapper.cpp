// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <yaul/variant/recursive_wrapper.hpp>
#include <yaul/variant/test_config.hpp>
#include <type_traits>

using yaul::recursive_wrapper;

enum ctor_t {
  no_ctor,
  default_ctor,
  lref_ctor,
  lref_const_ctor,
  lref_volatile_ctor,
  lref_cv_ctor,
  rref_ctor,
  rref_const_ctor,
  rref_volatile_ctor,
  rref_cv_ctor,
  init_ctor
};

enum asgn_t {
  no_asgn,
  lref_asgn,
  lref_const_asgn,
  lref_volatile_asgn,
  lref_cv_asgn,
  rref_asgn,
  rref_const_asgn,
  rref_volatile_asgn,
  rref_cv_asgn
};

// helper metafunctions
template<typename T> struct disabled_ctor;
template<typename T> struct disabled_asgn;

struct S1
{
  ctor_t ctor;
  asgn_t asgn;
  int member;
  // ctors
  S1() : ctor(default_ctor), asgn(no_asgn), member{0} {}
  S1(S1& s) : ctor(lref_ctor), asgn(no_asgn), member(s.member) {}
  S1(S1 const& s) : ctor(lref_const_ctor), asgn(no_asgn), member(s.member) {}
  S1(S1 volatile& s) : ctor(lref_volatile_ctor), asgn(no_asgn), member(s.member) {}
  S1(S1 const volatile& s) : ctor(lref_cv_ctor), asgn(no_asgn), member(s.member) {}
  S1(S1&& s) : ctor(rref_ctor), asgn(no_asgn), member(std::move(s).member) {}
  S1(S1 const&& s) : ctor(rref_const_ctor), asgn(no_asgn), member(std::move(s).member) {}
  S1(S1 volatile&& s) : ctor(rref_volatile_ctor), asgn(no_asgn), member(std::move(s).member) {}
  S1(S1 const volatile&& s) : ctor(rref_cv_ctor), asgn(no_asgn), member(std::move(s).member) {}
  S1(int m) : ctor(init_ctor), asgn(no_asgn), member(m) { }
  // asgnment operators
  S1& operator=(S1& rhs) { member = rhs.member; asgn = lref_asgn; return *this; }
  S1& operator=(S1 const& rhs) { member = rhs.member; asgn = lref_const_asgn; return *this; }
  S1& operator=(S1 volatile& rhs) { member = rhs.member; asgn = lref_volatile_asgn; return *this; }
  S1& operator=(S1 const volatile& rhs) { member = rhs.member; asgn = lref_cv_asgn; return *this; }
  S1& operator=(S1&& rhs) { member = rhs.member; asgn = rref_asgn; return *this; }
  S1& operator=(S1 const&& rhs) { member = rhs.member; asgn = rref_const_asgn; return *this; }
  S1& operator=(S1 volatile&& rhs) { member = rhs.member; asgn = rref_volatile_asgn; return *this; }
  S1& operator=(S1 const volatile&& rhs) { member = rhs.member; asgn = rref_cv_asgn; return *this; }
};

template<> struct disabled_ctor<S1> { constexpr static ctor_t value = no_ctor; };
template<> struct disabled_asgn<S1> { constexpr static asgn_t value = no_asgn; };

struct S10 : S1
{
  using S1::S1;
  S10() = delete;
  S10(S10& s) : S1(s) {}
  S10(S10 const& s) : S1(s) {}
  S10(S10 volatile& s) : S1(s) {}
  S10(S10 const volatile& s) : S1(s) {}
  S10(S10&& s) : S1(std::move(s)) {}
  S10(S10 const&& s) : S1(std::move(s)) {}
  S10(S10 volatile&& s) : S1(std::move(s)) {}
  S10(S10 const volatile&& s) : S1(std::move(s)) {}

  S10& operator=(S10& rhs) { this->S1::operator=(rhs); return *this; }
  S10& operator=(S10 const& rhs) { this->S1::operator=(rhs); return *this; }
  S10& operator=(S10 volatile& rhs) { this->S1::operator=(rhs); return *this; }
  S10& operator=(S10 const volatile& rhs) { this->S1::operator=(rhs); return *this; }
  S10& operator=(S10&& rhs) { this->S1::operator=(std::move(rhs)); return *this; }
  S10& operator=(S10 const&& rhs) { this->S1::operator=(std::move(rhs)); return *this; }
  S10& operator=(S10 volatile&& rhs) { this->S1::operator=(std::move(rhs)); return *this; }
  S10& operator=(S10 const volatile&& rhs) { this->S1::operator=(std::move(rhs)); return *this; }
};

template<> struct disabled_ctor<S10> { constexpr static ctor_t value = default_ctor; };
template<> struct disabled_asgn<S10> { constexpr static asgn_t value = no_asgn; };

struct S11 : S1
{
  using S1::S1;
  S11() = default;
  S11(S11& s) = delete;
  S11(S11 const& s) : S1(s) {}
  S11(S11 volatile& s) : S1(s) {}
  S11(S11 const volatile& s) : S1(s) {}
  S11(S11&& s) : S1(std::move(s)) {}
  S11(S11 const&& s) : S1(std::move(s)) {}
  S11(S11 volatile&& s) : S1(std::move(s)) {}
  S11(S11 const volatile&& s) : S1(std::move(s)) {}

  S11& operator=(S11& rhs) = delete;
  S11& operator=(S11 const& rhs) { this->S1::operator=(rhs); return *this; }
  S11& operator=(S11 volatile& rhs) { this->S1::operator=(rhs); return *this; }
  S11& operator=(S11 const volatile& rhs) { this->S1::operator=(rhs); return *this; }
  S11& operator=(S11&& rhs) { this->S1::operator=(std::move(rhs)); return *this; }
  S11& operator=(S11 const&& rhs) { this->S1::operator=(std::move(rhs)); return *this; }
  S11& operator=(S11 volatile&& rhs) { this->S1::operator=(std::move(rhs)); return *this; }
  S11& operator=(S11 const volatile&& rhs) { this->S1::operator=(std::move(rhs)); return *this; }
};

template<> struct disabled_ctor<S11> { constexpr static ctor_t value = lref_ctor; };
template<> struct disabled_asgn<S11> { constexpr static asgn_t value = lref_asgn; };

struct S12 : S1
{
  using S1::S1;
  S12() = default;
  S12(S12& s) : S1(s) {}
  S12(S12 const& s) = delete;
  S12(S12 volatile& s) : S1(s) {}
  S12(S12 const volatile& s) : S1(s) {}
  S12(S12&& s) : S1(std::move(s)) {}
  S12(S12 const&& s) : S1(std::move(s)) {}
  S12(S12 volatile&& s) : S1(std::move(s)) {}
  S12(S12 const volatile&& s) : S1(std::move(s)) {}

  S12& operator=(S12& rhs) { this->S1::operator=(rhs); return *this; }
  S12& operator=(S12 const& rhs) = delete;
  S12& operator=(S12 volatile& rhs) { this->S1::operator=(rhs); return *this; }
  S12& operator=(S12 const volatile& rhs) { this->S1::operator=(rhs); return *this; }
  S12& operator=(S12&& rhs) { this->S1::operator=(std::move(rhs)); return *this; }
  S12& operator=(S12 const&& rhs) { this->S1::operator=(std::move(rhs)); return *this; }
  S12& operator=(S12 volatile&& rhs) { this->S1::operator=(std::move(rhs)); return *this; }
  S12& operator=(S12 const volatile&& rhs) { this->S1::operator=(std::move(rhs)); return *this; }
};

template<> struct disabled_ctor<S12> { constexpr static ctor_t value = lref_const_ctor; };
template<> struct disabled_asgn<S12> { constexpr static asgn_t value = lref_const_asgn; };

struct S13 : S1
{
  using S1::S1;
  S13() = default;
  S13(S13& s) : S1(s) {}
  S13(S13 const& s) : S1(s) {}
  S13(S13 volatile& s) = delete;
  S13(S13 const volatile& s) : S1(s) {}
  S13(S13&& s) : S1(std::move(s)) {}
  S13(S13 const&& s) : S1(std::move(s)) {}
  S13(S13 volatile&& s) : S1(std::move(s)) {}
  S13(S13 const volatile&& s) : S1(std::move(s)) {}

  S13& operator=(S13& rhs) { this->S1::operator=(rhs); return *this; }
  S13& operator=(S13 const& rhs) { this->S1::operator=(rhs); return *this; }
  S13& operator=(S13 volatile& rhs) = delete;
  S13& operator=(S13 const volatile& rhs) { this->S1::operator=(rhs); return *this; }
  S13& operator=(S13&& rhs) { this->S1::operator=(std::move(rhs)); return *this; }
  S13& operator=(S13 const&& rhs) { this->S1::operator=(std::move(rhs)); return *this; }
  S13& operator=(S13 volatile&& rhs) { this->S1::operator=(std::move(rhs)); return *this; }
  S13& operator=(S13 const volatile&& rhs) { this->S1::operator=(std::move(rhs)); return *this; }
};

template<> struct disabled_ctor<S13> { constexpr static ctor_t value = lref_volatile_ctor; };
template<> struct disabled_asgn<S13> { constexpr static asgn_t value = lref_volatile_asgn; };

struct S14 : S1
{
  using S1::S1;
  S14() = default;
  S14(S14& s) : S1(s) {}
  S14(S14 const& s) : S1(s) {}
  S14(S14 volatile& s) : S1(s) {}
  S14(S14 const volatile& s) = delete;
  S14(S14&& s) : S1(std::move(s)) {}
  S14(S14 const&& s) : S1(std::move(s)) {}
  S14(S14 volatile&& s) : S1(std::move(s)) {}
  S14(S14 const volatile&& s) : S1(std::move(s)) {}

  S14& operator=(S14& rhs) { this->S1::operator=(rhs); return *this; }
  S14& operator=(S14 const& rhs) { this->S1::operator=(rhs); return *this; }
  S14& operator=(S14 volatile& rhs) { this->S1::operator=(rhs); return *this; }
  S14& operator=(S14 const volatile& rhs) = delete;
  S14& operator=(S14&& rhs) { this->S1::operator=(std::move(rhs)); return *this; }
  S14& operator=(S14 const&& rhs) { this->S1::operator=(std::move(rhs)); return *this; }
  S14& operator=(S14 volatile&& rhs) { this->S1::operator=(std::move(rhs)); return *this; }
  S14& operator=(S14 const volatile&& rhs) { this->S1::operator=(std::move(rhs)); return *this; }
};

template<> struct disabled_ctor<S14> { constexpr static ctor_t value = lref_cv_ctor; };
template<> struct disabled_asgn<S14> { constexpr static asgn_t value = lref_cv_asgn; };

struct S15 : S1
{
  using S1::S1;
  S15() = default;
  S15(S15& s) : S1(s) {}
  S15(S15 const& s) : S1(s) {}
  S15(S15 volatile& s) : S1(s) {}
  S15(S15 const volatile& s) : S1(s) {}
  S15(S15&& s) = delete;
  S15(S15 const&& s) : S1(std::move(s)) {}
  S15(S15 volatile&& s) : S1(std::move(s)) {}
  S15(S15 const volatile&& s) : S1(std::move(s)) {}

  S15& operator=(S15& rhs) { this->S1::operator=(rhs); return *this; }
  S15& operator=(S15 const& rhs) { this->S1::operator=(rhs); return *this; }
  S15& operator=(S15 volatile& rhs) { this->S1::operator=(rhs); return *this; }
  S15& operator=(S15 const volatile& rhs) { this->S1::operator=(rhs); return *this; }
  S15& operator=(S15&& rhs) = delete;
  S15& operator=(S15 const&& rhs) { this->S1::operator=(std::move(rhs)); return *this; }
  S15& operator=(S15 volatile&& rhs) { this->S1::operator=(std::move(rhs)); return *this; }
  S15& operator=(S15 const volatile&& rhs) { this->S1::operator=(std::move(rhs)); return *this; }
};

template<> struct disabled_ctor<S15> { constexpr static ctor_t value = rref_ctor; };
template<> struct disabled_asgn<S15> { constexpr static asgn_t value = rref_asgn; };

struct S16 : S1
{
  using S1::S1;
  S16() = default;
  S16(S16& s) : S1(s) {}
  S16(S16 const& s) : S1(s) {}
  S16(S16 volatile& s) : S1(s) {}
  S16(S16 const volatile& s) : S1(s) {}
  S16(S16&& s) : S1(std::move(s)) {}
  S16(S16 const&& s) = delete;
  S16(S16 volatile&& s) : S1(std::move(s)) {}
  S16(S16 const volatile&& s) : S1(std::move(s)) {}

  S16& operator=(S16& rhs) { this->S1::operator=(rhs); return *this; }
  S16& operator=(S16 const& rhs) { this->S1::operator=(rhs); return *this; }
  S16& operator=(S16 volatile& rhs) { this->S1::operator=(rhs); return *this; }
  S16& operator=(S16 const volatile& rhs) { this->S1::operator=(rhs); return *this; }
  S16& operator=(S16&& rhs) { this->S1::operator=(std::move(rhs)); return *this; }
  S16& operator=(S16 const&& rhs) = delete;
  S16& operator=(S16 volatile&& rhs) { this->S1::operator=(std::move(rhs)); return *this; }
  S16& operator=(S16 const volatile&& rhs) { this->S1::operator=(std::move(rhs)); return *this; }
};

template<> struct disabled_ctor<S16> { constexpr static ctor_t value = rref_const_ctor; };
template<> struct disabled_asgn<S16> { constexpr static asgn_t value = rref_const_asgn; };

struct S17 : S1
{
  using S1::S1;
  S17() = default;
  S17(S17& s) : S1(s) {}
  S17(S17 const& s) : S1(s) {}
  S17(S17 volatile& s) : S1(s) {}
  S17(S17 const volatile& s) : S1(s) {}
  S17(S17&& s) : S1(std::move(s)) {}
  S17(S17 const&& s) : S1(std::move(s)) {}
  S17(S17 volatile&& s) = delete;
  S17(S17 const volatile&& s) : S1(std::move(s)) {}

  S17& operator=(S17& rhs) { this->S1::operator=(rhs); return *this; }
  S17& operator=(S17 const& rhs) { this->S1::operator=(rhs); return *this; }
  S17& operator=(S17 volatile& rhs) { this->S1::operator=(rhs); return *this; }
  S17& operator=(S17 const volatile& rhs) { this->S1::operator=(rhs); return *this; }
  S17& operator=(S17&& rhs) { this->S1::operator=(std::move(rhs)); return *this; }
  S17& operator=(S17 const&& rhs) { this->S1::operator=(std::move(rhs)); return *this; }
  S17& operator=(S17 volatile&& rhs) = delete;
  S17& operator=(S17 const volatile&& rhs) { this->S1::operator=(std::move(rhs)); return *this; }
};

template<> struct disabled_ctor<S17> { constexpr static ctor_t value = rref_volatile_ctor; };
template<> struct disabled_asgn<S17> { constexpr static asgn_t value = rref_volatile_asgn; };

struct S18 : S1
{
  using S1::S1;
  S18() = default;
  S18(S18& s) : S1(s) {}
  S18(S18 const& s) : S1(s) {}
  S18(S18 volatile& s) : S1(s) {}
  S18(S18 const volatile& s) : S1(s) {}
  S18(S18&& s) : S1(std::move(s)) {}
  S18(S18 const&& s) : S1(std::move(s)) {}
  S18(S18 volatile&& s) : S1(std::move(s)) {}
  S18(S18 const volatile&& s) = delete;

  S18& operator=(S18& rhs) { this->S1::operator=(rhs); return *this; }
  S18& operator=(S18 const& rhs) { this->S1::operator=(rhs); return *this; }
  S18& operator=(S18 volatile& rhs) { this->S1::operator=(rhs); return *this; }
  S18& operator=(S18 const volatile& rhs) { this->S1::operator=(rhs); return *this; }
  S18& operator=(S18&& rhs) { this->S1::operator=(std::move(rhs)); return *this; }
  S18& operator=(S18 const&& rhs) { this->S1::operator=(std::move(rhs)); return *this; }
  S18& operator=(S18 volatile&& rhs) { this->S1::operator=(std::move(rhs)); return *this; }
  S18& operator=(S18 const volatile&& rhs) = delete;
};

template<> struct disabled_ctor<S18> { constexpr static ctor_t value = rref_cv_ctor; };
template<> struct disabled_asgn<S18> { constexpr static asgn_t value = rref_cv_asgn; };

// First ensure that our test class S1 works as we expect
void test__S1__ctors()
{
  {
    S1 s;
    YAUL_VARIANT_CHECK(s.ctor == default_ctor);
    YAUL_VARIANT_CHECK(s.asgn == no_asgn);
  }
  {
    S1 s{5};
    S1 t(s);
    YAUL_VARIANT_CHECK(t.ctor == lref_ctor);
    YAUL_VARIANT_CHECK(t.asgn == no_asgn);
    YAUL_VARIANT_CHECK_EQUALS(t.member, 5);
  }
  {
    S1 const s{5};
    S1 t(s);
    YAUL_VARIANT_CHECK(t.ctor == lref_const_ctor);
    YAUL_VARIANT_CHECK(t.asgn == no_asgn);
    YAUL_VARIANT_CHECK_EQUALS(t.member, 5);
  }
  {
    S1 volatile s{5};
    S1 t(s);
    YAUL_VARIANT_CHECK(t.ctor == lref_volatile_ctor);
    YAUL_VARIANT_CHECK(t.asgn == no_asgn);
    YAUL_VARIANT_CHECK_EQUALS(t.member, 5);
  }
  {
    S1 const volatile s{5};
    S1 t(s);
    YAUL_VARIANT_CHECK(t.ctor == lref_cv_ctor);
    YAUL_VARIANT_CHECK(t.asgn == no_asgn);
    YAUL_VARIANT_CHECK_EQUALS(t.member, 5);
  }
  {
    S1&& s = S1{5};
    S1 t(std::move(s));
    YAUL_VARIANT_CHECK(t.ctor == rref_ctor);
    YAUL_VARIANT_CHECK(t.asgn == no_asgn);
    YAUL_VARIANT_CHECK_EQUALS(t.member, 5);
  }
  {
    S1 const&& s = S1{5};
    S1 t(std::move(s));
    YAUL_VARIANT_CHECK(t.ctor == rref_const_ctor);
    YAUL_VARIANT_CHECK_EQUALS(t.member, 5);
  }
  {
    S1 volatile&& s = S1{5};
    S1 t(std::move(s));
    YAUL_VARIANT_CHECK(t.ctor == rref_volatile_ctor);
    YAUL_VARIANT_CHECK(t.asgn == no_asgn);
    YAUL_VARIANT_CHECK_EQUALS(t.member, 5);
  }
  {
    S1 const volatile&& s = S1{5};
    S1 t(std::move(s));
    YAUL_VARIANT_CHECK(t.ctor == rref_cv_ctor);
    YAUL_VARIANT_CHECK(t.asgn == no_asgn);
    YAUL_VARIANT_CHECK_EQUALS(t.member, 5);
  }
  {
    S1 s{5};
    YAUL_VARIANT_CHECK(s.ctor == init_ctor);
    YAUL_VARIANT_CHECK(s.asgn == no_asgn);
    YAUL_VARIANT_CHECK_EQUALS(s.member, 5);
  }
}

void test__S1__asgns()
{
  {
    S1 s{5};
    S1 t;
    t = s;
    YAUL_VARIANT_CHECK(t.asgn == lref_asgn);
    YAUL_VARIANT_CHECK_EQUALS(t.member, 5);
  }
  {
    S1 const s{5};
    S1 t;
    t = s;
    YAUL_VARIANT_CHECK(t.asgn == lref_const_asgn);
    YAUL_VARIANT_CHECK_EQUALS(t.member, 5);
  }
  {
    S1 volatile s{5};
    S1 t;
    t = s;
    YAUL_VARIANT_CHECK(t.asgn == lref_volatile_asgn);
    YAUL_VARIANT_CHECK_EQUALS(t.member, 5);
  }
  {
    S1 const volatile s{5};
    S1 t;
    t = s;
    YAUL_VARIANT_CHECK(t.asgn == lref_cv_asgn);
    YAUL_VARIANT_CHECK_EQUALS(t.member, 5);
  }
  {
    S1&& s = S1{5};
    S1 t;
    t = std::move(s);
    YAUL_VARIANT_CHECK(t.asgn == rref_asgn);
    YAUL_VARIANT_CHECK_EQUALS(t.member, 5);
  }
  {
    S1 const&& s = S1{5};
    S1 t;
    t = std::move(s);
    YAUL_VARIANT_CHECK(t.asgn == rref_const_asgn);
    YAUL_VARIANT_CHECK_EQUALS(t.member, 5);
  }
  {
    S1 volatile&& s = S1{5};
    S1 t;
    t = std::move(s);
    YAUL_VARIANT_CHECK(t.asgn == rref_volatile_asgn);
    YAUL_VARIANT_CHECK_EQUALS(t.member, 5);
  }
  {
    S1 const volatile&& s = S1{5};
    S1 t;
    t = std::move(s);
    YAUL_VARIANT_CHECK(t.asgn == rref_cv_asgn);
    YAUL_VARIANT_CHECK_EQUALS(t.member, 5);
  }
}

template<typename T, ctor_t DisableCtor = disabled_ctor<T>::value>
struct test_recursive_wrapper_ctors
{
  // default_ctor
  template<ctor_t D = DisableCtor>
  static void
  test_default_ctor(typename std::enable_if<D != default_ctor, void*>::type = nullptr)
  {
    recursive_wrapper<T> w;
    YAUL_VARIANT_CHECK(w.get().ctor == default_ctor);
    YAUL_VARIANT_CHECK(w.get().asgn == no_asgn);
    YAUL_VARIANT_CHECK_EQUALS(w.get().member, 0);
  }
  template<ctor_t D = DisableCtor>
  static void
  test_default_ctor(typename std::enable_if<D == default_ctor, void*>::type = nullptr)
  {
  }

  // lref_ctor
  template<ctor_t D = DisableCtor>
  static void
  test_lref_ctor(typename std::enable_if<D != lref_ctor, void*>::type = nullptr)
  {
    {
      T s{5};
      recursive_wrapper<T> w{s};
      YAUL_VARIANT_CHECK(w.get().ctor == lref_ctor);
      YAUL_VARIANT_CHECK(w.get().asgn == no_asgn);
      YAUL_VARIANT_CHECK_EQUALS(w.get().member, 5);
    }
    {
      T s{5};
      recursive_wrapper<T> w1{s};
      recursive_wrapper<T> w2{w1};
      YAUL_VARIANT_CHECK(w2.get().ctor == lref_ctor);
      YAUL_VARIANT_CHECK(w2.get().asgn == no_asgn);
      YAUL_VARIANT_CHECK_EQUALS(w2.get().member, 5);
    }
  }
  template<ctor_t D = DisableCtor>
  static void
  test_lref_ctor(typename std::enable_if<D == lref_ctor, void*>::type = nullptr)
  {
  }

  // lref_const_ctor
  template<ctor_t D = DisableCtor>
  static void
  test_lref_const_ctor(typename std::enable_if<D != lref_const_ctor, void*>::type = nullptr)
  {
    {
      T const s{5};
      recursive_wrapper<T> w{s};
      YAUL_VARIANT_CHECK(w.get().ctor == lref_const_ctor);
      YAUL_VARIANT_CHECK(w.get().asgn == no_asgn);
      YAUL_VARIANT_CHECK_EQUALS(w.get().member, 5);
    }
    {
      T const s{5};
      recursive_wrapper<T> const w1{s};
      recursive_wrapper<T> w2{w1};
      YAUL_VARIANT_CHECK(w2.get().ctor == lref_const_ctor);
      YAUL_VARIANT_CHECK(w2.get().asgn == no_asgn);
      YAUL_VARIANT_CHECK_EQUALS(w2.get().member, 5);
    }
  }
  template<ctor_t D = DisableCtor>
  static void
  test_lref_const_ctor(typename std::enable_if<D == lref_const_ctor, void*>::type = nullptr)
  {
  }

  // lref_volatile_ctor
  template<ctor_t D = DisableCtor>
  static void
  test_lref_volatile_ctor(typename std::enable_if<D != lref_volatile_ctor, void*>::type = nullptr)
  {
    {
      T volatile s{5};
      recursive_wrapper<T> w{s};
      YAUL_VARIANT_CHECK(w.get().ctor == lref_volatile_ctor);
      YAUL_VARIANT_CHECK(w.get().asgn == no_asgn);
      YAUL_VARIANT_CHECK_EQUALS(w.get().member, 5);
    }
    {
      T volatile s{5};
      recursive_wrapper<T> volatile w1{s};
      recursive_wrapper<T> w2{w1};
      YAUL_VARIANT_CHECK(w2.get().ctor == lref_volatile_ctor);
      YAUL_VARIANT_CHECK(w2.get().asgn == no_asgn);
      YAUL_VARIANT_CHECK_EQUALS(w2.get().member, 5);
    }
  }
  template<ctor_t D = DisableCtor>
  static void
  test_lref_volatile_ctor(typename std::enable_if<D == lref_volatile_ctor, void*>::type = nullptr)
  {
  }

  // lref_cv_ctor
  template<ctor_t D = DisableCtor>
  static void
  test_lref_cv_ctor(typename std::enable_if<D != lref_cv_ctor, void*>::type = nullptr)
  {
    {
      T const volatile s{5};
      recursive_wrapper<T> w{s};
      YAUL_VARIANT_CHECK(w.get().ctor == lref_cv_ctor);
      YAUL_VARIANT_CHECK(w.get().asgn == no_asgn);
      YAUL_VARIANT_CHECK_EQUALS(w.get().member, 5);
    }
    {
      T const volatile s{5};
      recursive_wrapper<T> const volatile w1{s};
      recursive_wrapper<T> w2{w1};
      YAUL_VARIANT_CHECK(w2.get().ctor == lref_cv_ctor);
      YAUL_VARIANT_CHECK(w2.get().asgn == no_asgn);
      YAUL_VARIANT_CHECK_EQUALS(w2.get().member, 5);
    }
  }
  template<ctor_t D = DisableCtor>
  static void
  test_lref_cv_ctor(typename std::enable_if<D == lref_cv_ctor, void*>::type = nullptr)
  {
  }

  // rref_ctor
  template<ctor_t D = DisableCtor>
  static void
  test_rref_ctor(typename std::enable_if<D != rref_ctor, void*>::type = nullptr)
  {
    {
      T&& s = T{5};
      recursive_wrapper<T> w{std::move(s)};
      YAUL_VARIANT_CHECK(w.get().ctor == rref_ctor);
      YAUL_VARIANT_CHECK(w.get().asgn == no_asgn);
      YAUL_VARIANT_CHECK_EQUALS(w.get().member, 5);
    }
    {
      T&& s = T{5};
      recursive_wrapper<T>&& w1{std::move(s)};
      recursive_wrapper<T> w2{std::move(w1)};
      YAUL_VARIANT_CHECK(w2.get().ctor == rref_ctor);
      YAUL_VARIANT_CHECK(w2.get().asgn == no_asgn);
      YAUL_VARIANT_CHECK_EQUALS(w2.get().member, 5);
    }
  }
  template<ctor_t D = DisableCtor>
  static void
  test_rref_ctor(typename std::enable_if<D == rref_ctor, void*>::type = nullptr)
  {
  }

  // rref_const_ctor
  template<ctor_t D = DisableCtor>
  static void
  test_rref_const_ctor(typename std::enable_if<D != rref_const_ctor, void*>::type = nullptr)
  {
    {
      T const&& s = T{5};
      recursive_wrapper<T> w{std::move(s)};
      YAUL_VARIANT_CHECK(w.get().ctor == rref_const_ctor);
      YAUL_VARIANT_CHECK(w.get().asgn == no_asgn);
      YAUL_VARIANT_CHECK_EQUALS(w.get().member, 5);
    }
    {
      T const&& s = T{5};
      recursive_wrapper<T> const&& w1{std::move(s)};
      recursive_wrapper<T> w2{std::move(w1)};
      YAUL_VARIANT_CHECK(w2.get().ctor == rref_const_ctor);
      YAUL_VARIANT_CHECK(w2.get().asgn == no_asgn);
      YAUL_VARIANT_CHECK_EQUALS(w2.get().member, 5);
    }
  }
  template<ctor_t D = DisableCtor>
  static void
  test_rref_const_ctor(typename std::enable_if<D == rref_const_ctor, void*>::type = nullptr)
  {
  }

  // rref_volatile_ctor
  template<ctor_t D = DisableCtor>
  static void
  test_rref_volatile_ctor(typename std::enable_if<D != rref_volatile_ctor, void*>::type = nullptr)
  {
    {
      T volatile&& s = T{5};
      recursive_wrapper<T> w{std::move(s)};
      YAUL_VARIANT_CHECK(w.get().ctor == rref_volatile_ctor);
      YAUL_VARIANT_CHECK(w.get().asgn == no_asgn);
      YAUL_VARIANT_CHECK_EQUALS(w.get().member, 5);
    }
    {
      T volatile&& s = T{5};
      recursive_wrapper<T> volatile&& w1{std::move(s)};
      recursive_wrapper<T> w2{std::move(w1)};
      YAUL_VARIANT_CHECK(w2.get().ctor == rref_volatile_ctor);
      YAUL_VARIANT_CHECK(w2.get().asgn == no_asgn);
      YAUL_VARIANT_CHECK_EQUALS(w2.get().member, 5);
    }
  }
  template<ctor_t D = DisableCtor>
  static void
  test_rref_volatile_ctor(typename std::enable_if<D == rref_volatile_ctor, void*>::type = nullptr)
  {
  }

  // rref_cv_ctor
  template<ctor_t D = DisableCtor>
  static void
  test_rref_cv_ctor(typename std::enable_if<D != rref_cv_ctor, void*>::type = nullptr)
  {
    {
      T const volatile&& s = T{5};
      recursive_wrapper<T> w{std::move(s)};
      YAUL_VARIANT_CHECK(w.get().ctor == rref_cv_ctor);
      YAUL_VARIANT_CHECK(w.get().asgn == no_asgn);
      YAUL_VARIANT_CHECK_EQUALS(w.get().member, 5);
    }
    {
      T const volatile&& s = T{5};
      recursive_wrapper<T> const volatile&& w1{std::move(s)};
      recursive_wrapper<T> w2{std::move(w1)};
      YAUL_VARIANT_CHECK(w2.get().ctor == rref_cv_ctor);
      YAUL_VARIANT_CHECK(w2.get().asgn == no_asgn);
      YAUL_VARIANT_CHECK_EQUALS(w2.get().member, 5);
    }
  }
  template<ctor_t D = DisableCtor>
  static void
  test_rref_cv_ctor(typename std::enable_if<D == rref_cv_ctor, void*>::type = nullptr)
  {
  }

  static void
  test_all_ctors()
  {
    test_default_ctor();
    test_lref_ctor();
    test_lref_const_ctor();
    test_lref_volatile_ctor();
    test_lref_cv_ctor();
    test_rref_ctor();
#ifndef YAUL_VARIANT_NO_RREF_CV_QUALIFIED_MEMBERS
    test_rref_const_ctor();
    test_rref_volatile_ctor();
    test_rref_cv_ctor();
#endif
  }
};

template<typename T, asgn_t DisableAsgn = disabled_asgn<T>::value>
struct test_recursive_wrapper_asgns
{
  // lref_asgn
  template<asgn_t D = DisableAsgn>
  static void
  test_lref_asgn(typename std::enable_if<D != lref_asgn, void*>::type = nullptr)
  {
    {
      T s{5};
      recursive_wrapper<T> w{s};
      recursive_wrapper<T>* p;
      p = &(w = s);
      YAUL_VARIANT_CHECK(w.get().asgn == lref_asgn);
      YAUL_VARIANT_CHECK_EQUALS(w.get().member, 5);
      YAUL_VARIANT_CHECK(p == &w);
    }
    {
      T s{5};
      recursive_wrapper<T> w1{s};
      recursive_wrapper<T> w2;
      recursive_wrapper<T>* p;
      p = &(w2 = w1);
      YAUL_VARIANT_CHECK(w2.get().asgn == lref_asgn);
      YAUL_VARIANT_CHECK_EQUALS(w2.get().member, 5);
      YAUL_VARIANT_CHECK(p == &w2);
    }
  }
  template<asgn_t D = DisableAsgn>
  static void
  test_lref_asgn(typename std::enable_if<D == lref_asgn, void*>::type = nullptr)
  {
  }

  // lref_const_asgn
  template<asgn_t D = DisableAsgn>
  static void
  test_lref_const_asgn(typename std::enable_if<D != lref_const_asgn, void*>::type = nullptr)
  {
    {
      T const s{5};
      recursive_wrapper<T> w{s};
      recursive_wrapper<T>* p;
      p = &(w = s);
      YAUL_VARIANT_CHECK(w.get().asgn == lref_const_asgn);
      YAUL_VARIANT_CHECK_EQUALS(w.get().member, 5);
      YAUL_VARIANT_CHECK(p == &w);
    }
    {
      T const s{5};
      recursive_wrapper<T> const w1{s};
      recursive_wrapper<T> w2;
      recursive_wrapper<T>* p;
      p = &(w2 = w1);
      YAUL_VARIANT_CHECK(w2.get().asgn == lref_const_asgn);
      YAUL_VARIANT_CHECK_EQUALS(w2.get().member, 5);
      YAUL_VARIANT_CHECK(p == &w2);
    }
  }
  template<asgn_t D = DisableAsgn>
  static void
  test_lref_const_asgn(typename std::enable_if<D == lref_const_asgn, void*>::type = nullptr)
  {
  }

  // lref_volatile_asgn
  template<asgn_t D = DisableAsgn>
  static void
  test_lref_volatile_asgn(typename std::enable_if<D != lref_volatile_asgn, void*>::type = nullptr)
  {
    {
      T volatile s{5};
      recursive_wrapper<T> w{s};
      recursive_wrapper<T>* p;
      p = &(w = s);
      YAUL_VARIANT_CHECK(w.get().asgn == lref_volatile_asgn);
      YAUL_VARIANT_CHECK_EQUALS(w.get().member, 5);
      YAUL_VARIANT_CHECK(p == &w);
    }
    {
      T volatile s{5};
      recursive_wrapper<T> volatile w1{s};
      recursive_wrapper<T> w2;
      recursive_wrapper<T>* p;
      p = &(w2 = w1);
      YAUL_VARIANT_CHECK(w2.get().asgn == lref_volatile_asgn);
      YAUL_VARIANT_CHECK_EQUALS(w2.get().member, 5);
      YAUL_VARIANT_CHECK(p == &w2);
    }
  }
  template<asgn_t D = DisableAsgn>
  static void
  test_lref_volatile_asgn(typename std::enable_if<D == lref_volatile_asgn, void*>::type = nullptr)
  {
  }

  // lref_cv_asgn
  template<asgn_t D = DisableAsgn>
  static void
  test_lref_cv_asgn(typename std::enable_if<D != lref_cv_asgn, void*>::type = nullptr)
  {
    {
      T const volatile s{5};
      recursive_wrapper<T> w{s};
      recursive_wrapper<T>* p;
      p = &(w = s);
      YAUL_VARIANT_CHECK(w.get().asgn == lref_cv_asgn);
      YAUL_VARIANT_CHECK_EQUALS(w.get().member, 5);
      YAUL_VARIANT_CHECK(p == &w);
    }
    {
      T const volatile s{5};
      recursive_wrapper<T> const volatile w1{s};
      recursive_wrapper<T> w2;
      recursive_wrapper<T>* p;
      p = &(w2 = w1);
      YAUL_VARIANT_CHECK(w2.get().asgn == lref_cv_asgn);
      YAUL_VARIANT_CHECK_EQUALS(w2.get().member, 5);
      YAUL_VARIANT_CHECK(p == &w2);
    }
  }
  template<asgn_t D = DisableAsgn>
  static void
  test_lref_cv_asgn(typename std::enable_if<D == lref_cv_asgn, void*>::type = nullptr)
  {
  }

  // rref_asgn
  template<asgn_t D = DisableAsgn>
  static void
  test_rref_asgn(typename std::enable_if<D != rref_asgn, void*>::type = nullptr)
  {
    {
      T&& s = T{5};
      recursive_wrapper<T> w{std::move(s)};
      recursive_wrapper<T>* p;
      p = &(w = std::move(s));
      YAUL_VARIANT_CHECK(w.get().asgn == rref_asgn);
      YAUL_VARIANT_CHECK_EQUALS(w.get().member, 5);
      YAUL_VARIANT_CHECK(p == &w);
    }
    {
      T&& s = T{5};
      recursive_wrapper<T>&& w1{std::move(s)};
      recursive_wrapper<T> w2;
      recursive_wrapper<T>* p;
      p = &(w2 = std::move(w1));
      YAUL_VARIANT_CHECK(w2.get().asgn == rref_asgn);
      YAUL_VARIANT_CHECK_EQUALS(w2.get().member, 5);
      YAUL_VARIANT_CHECK(p == &w2);
    }
  }
  template<asgn_t D = DisableAsgn>
  static void
  test_rref_asgn(typename std::enable_if<D == rref_asgn, void*>::type = nullptr)
  {
  }

  // rref_const_asgn
  template<asgn_t D = DisableAsgn>
  static void
  test_rref_const_asgn(typename std::enable_if<D != rref_const_asgn, void*>::type = nullptr)
  {
    {
      T const&& s = T{5};
      recursive_wrapper<T> w{std::move(s)};
      recursive_wrapper<T>* p;
      p = &(w = std::move(s));
      YAUL_VARIANT_CHECK(w.get().asgn == rref_const_asgn);
      YAUL_VARIANT_CHECK_EQUALS(w.get().member, 5);
      YAUL_VARIANT_CHECK(p == &w);
    }
    {
      T const&& s = T{5};
      recursive_wrapper<T> const&& w1{std::move(s)};
      recursive_wrapper<T> w2;
      recursive_wrapper<T>* p;
      p = &(w2 = std::move(w1));
      YAUL_VARIANT_CHECK(w2.get().asgn == rref_const_asgn);
      YAUL_VARIANT_CHECK_EQUALS(w2.get().member, 5);
      YAUL_VARIANT_CHECK(p == &w2);
    }
  }
  template<asgn_t D = DisableAsgn>
  static void
  test_rref_const_asgn(typename std::enable_if<D == rref_const_asgn, void*>::type = nullptr)
  {
  }

  // rref_volatile_asgn
  template<asgn_t D = DisableAsgn>
  static void
  test_rref_volatile_asgn(typename std::enable_if<D != rref_volatile_asgn, void*>::type = nullptr)
  {
    {
      T volatile&& s = T{5};
      recursive_wrapper<T> w;
      recursive_wrapper<T>* p;
      p = &(w = std::move(s));
      YAUL_VARIANT_CHECK(w.get().asgn == rref_volatile_asgn);
      YAUL_VARIANT_CHECK_EQUALS(w.get().member, 5);
      YAUL_VARIANT_CHECK(p == &w);
    }
    {
      T volatile&& s = T{5};
      recursive_wrapper<T> volatile&& w1{std::move(s)};
      recursive_wrapper<T> w2;
      recursive_wrapper<T>* p;
      p = &(w2 = std::move(w1));
      YAUL_VARIANT_CHECK(w2.get().asgn == rref_volatile_asgn);
      YAUL_VARIANT_CHECK_EQUALS(w2.get().member, 5);
      YAUL_VARIANT_CHECK(p == &w2);
    }
  }
  template<asgn_t D = DisableAsgn>
  static void
  test_rref_volatile_asgn(typename std::enable_if<D == rref_volatile_asgn, void*>::type = nullptr)
  {
  }

  // rref_cv_asgn
  template<asgn_t D = DisableAsgn>
  static void
  test_rref_cv_asgn(typename std::enable_if<D != rref_cv_asgn, void*>::type = nullptr)
  {
    {
      T const volatile&& s = T{5};
      recursive_wrapper<T> w;
      recursive_wrapper<T>* p;
      p = &(w = std::move(s));
      YAUL_VARIANT_CHECK(w.get().asgn == rref_cv_asgn);
      YAUL_VARIANT_CHECK_EQUALS(w.get().member, 5);
      YAUL_VARIANT_CHECK(p == &w);
    }
    {
      T const volatile&& s = T{5};
      recursive_wrapper<T> const volatile&& w1{std::move(s)};
      recursive_wrapper<T> w2;
      recursive_wrapper<T>* p;
      p = &(w2 = std::move(w1));
      YAUL_VARIANT_CHECK(w2.get().asgn == rref_cv_asgn);
      YAUL_VARIANT_CHECK_EQUALS(w2.get().member, 5);
      YAUL_VARIANT_CHECK(p == &w2);
    }
  }
  template<asgn_t D = DisableAsgn>
  static void
  test_rref_cv_asgn(typename std::enable_if<D == rref_cv_asgn, void*>::type = nullptr)
  {
  }

  static void
  test_all_asgns()
  {
    test_lref_asgn();
    test_lref_const_asgn();
    test_lref_volatile_asgn();
    test_lref_cv_asgn();
    test_rref_asgn();
#ifndef YAUL_VARIANT_NO_RREF_CV_QUALIFIED_MEMBERS
    test_rref_const_asgn();
    test_rref_volatile_asgn();
    test_rref_cv_asgn();
#endif
  }
};

void test__recursive_wrapper__01()
{
  {
    recursive_wrapper<int> w{1};
    static_assert(std::is_same<decltype(w.get()), int&>::value, "");
    YAUL_VARIANT_CHECK_EQUALS(w.get(), 1);
  }
  {
    static_assert(std::is_same<decltype(recursive_wrapper<int>{1}.get()), int&&>::value, "");
    YAUL_VARIANT_CHECK_EQUALS(recursive_wrapper<int>{1}.get(), 1);
  }
  {
    recursive_wrapper<int> w;
    w = 1;
    recursive_wrapper<int> w2{w};
    recursive_wrapper<int> w3{std::move(w)};

    YAUL_VARIANT_CHECK_EQUALS(w3.get(), 1);
    w3 = 2;
    YAUL_VARIANT_CHECK_EQUALS(w3.get(), 2);
  }
}

void test__recursive_wrapper__swap()
{
  {
    recursive_wrapper<S1> r{S1{5}};
    recursive_wrapper<S1> s{S1{6}};

    S1* pr = &r.get();
    S1* ps = &s.get();

    yaul::swap(r,s);
    YAUL_VARIANT_CHECK_EQUALS(r.get().member, 6);
    YAUL_VARIANT_CHECK_EQUALS(s.get().member, 5);
    YAUL_VARIANT_CHECK_EQUALS(pr, &s.get());
    YAUL_VARIANT_CHECK_EQUALS(ps, &r.get());
    swap(r,s);
    YAUL_VARIANT_CHECK_EQUALS(r.get().member, 5);
    YAUL_VARIANT_CHECK_EQUALS(s.get().member, 6);
    YAUL_VARIANT_CHECK_EQUALS(pr, &r.get());
    YAUL_VARIANT_CHECK_EQUALS(ps, &s.get());
  }
}

int main()
{
  test__S1__ctors();
  test__S1__asgns();
  test__recursive_wrapper__01();

  test_recursive_wrapper_ctors<S1>::test_all_ctors();
  test_recursive_wrapper_ctors<S10>::test_all_ctors();
  test_recursive_wrapper_ctors<S11>::test_all_ctors();
  test_recursive_wrapper_ctors<S12>::test_all_ctors();
  test_recursive_wrapper_ctors<S13>::test_all_ctors();
  test_recursive_wrapper_ctors<S14>::test_all_ctors();
  test_recursive_wrapper_ctors<S15>::test_all_ctors();
  test_recursive_wrapper_ctors<S16>::test_all_ctors();
  test_recursive_wrapper_ctors<S17>::test_all_ctors();
  test_recursive_wrapper_ctors<S18>::test_all_ctors();

  test_recursive_wrapper_asgns<S1>::test_all_asgns();
  test_recursive_wrapper_asgns<S11>::test_all_asgns();
  test_recursive_wrapper_asgns<S12>::test_all_asgns();
  test_recursive_wrapper_asgns<S13>::test_all_asgns();
  test_recursive_wrapper_asgns<S14>::test_all_asgns();
  test_recursive_wrapper_asgns<S15>::test_all_asgns();
  test_recursive_wrapper_asgns<S16>::test_all_asgns();
  test_recursive_wrapper_asgns<S17>::test_all_asgns();
  test_recursive_wrapper_asgns<S18>::test_all_asgns();


//  test__recursive_wrapper__02();
  return YAUL_VARIANT_TEST_EXIT_CODE;
}
