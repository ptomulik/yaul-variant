// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <yaul/variant/variant.hpp>
#include <yaul/variant/test_config.hpp>
#include <utility>

void test__dtor__01()
{
  using yaul::variant;

  struct S {};

  variant<S> v;
  static_assert(noexcept(v.~variant()), "");
}

void test__dtor__02()
{
  using yaul::variant;

  struct S { ~S() {} };

  variant<S> v;
  static_assert(noexcept(v.~variant()), "");
}

void test__dtor__03()
{
  using yaul::variant;

  struct S { ~S() noexcept(false) {} };

  variant<S> v;
  static_assert(!noexcept(v.~variant()), "");
}

void test__ctors__01()
{
  using yaul::variant;

  struct S { };

  static_assert(noexcept(variant<S>{}), "");
  // copy ctors
  {
    S s;
    static_assert(noexcept(variant<S>{s}), "");
  }
  {
    S const s{};
    static_assert(noexcept(variant<S>{s}), "");
  }
  {
    S s;
    static_assert(noexcept(variant<S>{std::move(s)}), "");
  }
}

void test__ctors__02()
{
  using yaul::variant;

  struct S
  {
    S() {}
    S(S&) = default;
    S(S const&) = default;
    S(S&&) = default;
  };

  static_assert(!noexcept(variant<S>{}), "");
  static_assert(!noexcept(variant<S,int>{}), "");
  static_assert( noexcept(variant<int,S>{}), ""); // S is at second position

  {
    S s;
    static_assert(noexcept(variant<S>{s}), "");
    static_assert(noexcept(variant<int,S>{s}), "");
    static_assert(noexcept(variant<S,int>{s}), "");
  }

  {
    S const s;
    static_assert(noexcept(variant<S>{s}), "");
    static_assert(noexcept(variant<int,S>{s}), "");
    static_assert(noexcept(variant<S,int>{s}), "");
  }

  {
    S s;
    static_assert(noexcept(variant<S>{std::move(s)}), "");
    static_assert(noexcept(variant<int,S>{std::move(s)}), "");
    static_assert(noexcept(variant<S,int>{std::move(s)}), "");
  }
}

void test__ctors__03()
{
  using yaul::variant;

  struct S
  {
    S() = default;
    S(S&) {}
    S(S const&) = default;
    S(S&&) = default;
  };

  static_assert( noexcept(variant<S>{}), "");
  static_assert( noexcept(variant<S,int>{}), "");
  static_assert( noexcept(variant<int,S>{}), ""); // S is at second position

  {
    S s;
    static_assert(!noexcept(variant<S>{s}), "");
    static_assert(!noexcept(variant<int,S>{s}), "");
    static_assert(!noexcept(variant<S,int>{s}), "");
  }

  {
    S const s{};
    static_assert(noexcept(variant<S>{s}), "");
    static_assert(noexcept(variant<int,S>{s}), "");
    static_assert(noexcept(variant<S,int>{s}), "");
  }

  {
    S s;
    static_assert(noexcept(variant<S>{std::move(s)}), "");
    static_assert(noexcept(variant<int,S>{std::move(s)}), "");
    static_assert(noexcept(variant<S,int>{std::move(s)}), "");
  }
}

void test__ctors__04()
{
  using yaul::variant;

  struct S
  {
    S() = default;
    S(S&) = default;
    S(S const&) {}
    S(S&&) = default;
  };

  static_assert( noexcept(variant<S>{}), "");
  static_assert( noexcept(variant<S,int>{}), "");
  static_assert( noexcept(variant<int,S>{}), ""); // S is at second position

  {
    S s;
    static_assert(noexcept(variant<S>{s}), "");
    static_assert(noexcept(variant<int,S>{s}), "");
    static_assert(noexcept(variant<S,int>{s}), "");
  }

  {
    S const s{};
    static_assert(!noexcept(variant<S>{s}), "");
    static_assert(!noexcept(variant<int,S>{s}), "");
    static_assert(!noexcept(variant<S,int>{s}), "");
  }

  {
    S s;
    static_assert(noexcept(variant<S>{std::move(s)}), "");
    static_assert(noexcept(variant<int,S>{std::move(s)}), "");
    static_assert(noexcept(variant<S,int>{std::move(s)}), "");
  }
}

void test__ctors__05()
{
  using yaul::variant;

  struct S
  {
    S() = default;
    S(S&) = default;
    S(S const&) = default;
    S(S&&) {}
  };

  static_assert( noexcept(variant<S>{}), "");
  static_assert( noexcept(variant<S,int>{}), "");
  static_assert( noexcept(variant<int,S>{}), ""); // S is at second position

  {
    S s;
    static_assert(noexcept(variant<S>{s}), "");
    static_assert(noexcept(variant<int,S>{s}), "");
    static_assert(noexcept(variant<S,int>{s}), "");
  }

  {
    S const s{};
    static_assert(noexcept(variant<S>{s}), "");
    static_assert(noexcept(variant<int,S>{s}), "");
    static_assert(noexcept(variant<S,int>{s}), "");
  }

  {
    S s;
    static_assert(!noexcept(variant<S>{std::move(s)}), "");
    static_assert(!noexcept(variant<int,S>{std::move(s)}), "");
    static_assert(!noexcept(variant<S,int>{std::move(s)}), "");
  }
}

void test__assign__01()
{
  using yaul::variant;

  struct S { };

  {
    S s;
    variant<float,S,int> v;
    static_assert(noexcept(v = s), "");
  }

  {
    S const s{};
    variant<float,S,int> v;
    static_assert(noexcept(v = s), "");
  }

  {
    S s;
    variant<float,S,int> v;
    static_assert(noexcept(v = std::move(s)), "");
  }

  {
    S s1;
    S const s2{};
    variant<S> v1, v2;
    variant<S> const v3;
    variant<S, int> v4;
    static_assert(noexcept(v1 = s1), "");
    static_assert(noexcept(v1 = s2), "");
    static_assert(noexcept(v1 = std::move(s1)), "");
    static_assert(noexcept(v1 = v2), "");
    static_assert(noexcept(v1 = v3), "");
    static_assert(noexcept(v1 = std::move(v1)), "");
    static_assert(noexcept(v4 = v1), "");
    static_assert(noexcept(v4 = v2), "");
    static_assert(noexcept(v4 = std::move(v1)), "");
  }

}

void test__assign__02()
{
  using yaul::variant;

  struct S
  {
    S() = default;
    S(S&) = default;
    S(S const&) = default;
    S(S&&) = default;
    S& operator=(S&) { return *this; }
    S& operator=(S const&) = default;
    S& operator=(S&&) = default;
  };

  {
    S s;
    variant<float,S,int> v;
    static_assert(!noexcept(v = s), "");
  }

  {
    S const s{};
    variant<float,S,int> v;
    static_assert(noexcept(v = s), "");
  }

  {
    S s;
    variant<float,S,int> v;
    static_assert(noexcept(v = std::move(s)), "");
  }

  {
    variant<float, S, int> v1;
    variant<float, S, int> v2;
    static_assert(!noexcept(v2 = v1), "");
  }

  {
    variant<float, S, int> const v1;
    variant<float, S, int> v2;
    static_assert(noexcept(v2 = v1), "");
  }

  {
    variant<float, S, int> v1;
    variant<float, S, int> v2;
    static_assert(noexcept(v2 = std::move(v1)), "");
  }

  {
    variant<float, S, int> v1;
    variant<S, int, float, S*> v2;
    static_assert(!noexcept(v2 = v1), "");
  }

  {
    variant<float, S, int> const v1;
    variant<S, int, float, S*> v2;
    static_assert(noexcept(v2 = v1), "");
  }

  {
    variant<float, S, int> v1;
    variant<float, S, int, S*> v2;
    static_assert(noexcept(v2 = std::move(v1)), "");
  }
}

void test__assign__03()
{
  using yaul::variant;

  struct S
  {
    S() = default;
    S(S&) = default;
    S(S const&) = default;
    S(S&&) = default;
    S& operator=(S&) = default;
    S& operator=(S const&) { return *this; }
    S& operator=(S&&) = default;
  };

  {
    S s;
    variant<float,S,int> v;
    static_assert(noexcept(v = s), "");
  }

  {
    S const s{};
    variant<float,S,int> v;
    static_assert(!noexcept(v = s), "");
  }

  {
    S s;
    variant<float,S,int> v;
    static_assert(noexcept(v = std::move(s)), "");
  }

  {
    variant<float, S, int> v1;
    variant<float, S, int> v2;
    static_assert(noexcept(v2 = v1), "");
  }

  {
    variant<float, S, int> const v1;
    variant<float, S, int> v2;
    static_assert(!noexcept(v2 = v1), "");
  }

  {
    variant<float, S, int> v1;
    variant<float, S, int> v2;
    static_assert(noexcept(v2 = std::move(v1)), "");
  }

  {
    variant<float, S, int> v1;
    variant<S, int, float, S*> v2;
    static_assert(noexcept(v2 = v1), "");
  }

  {
    variant<float, S, int> const v1;
    variant<S, int, float, S*> v2;
    static_assert(!noexcept(v2 = v1), "");
  }

  {
    variant<float, S, int> v1;
    variant<float, S, int, S*> v2;
    static_assert(noexcept(v2 = std::move(v1)), "");
  }
}

void test__assign__04()
{
  using yaul::variant;

  struct S
  {
    S() = default;
    S(S&) = default;
    S(S const&) = default;
    S(S&&) = default;
    S& operator=(S&) = default;
    S& operator=(S const&) = default;
    S& operator=(S&&) { return *this; }
  };

  {
    S s;
    variant<float,S,int> v;
    static_assert(noexcept(v = s), "");
  }

  {
    S const s{};
    variant<float,S,int> v;
    static_assert(noexcept(v = s), "");
  }

  {
    S s;
    variant<float,S,int> v;
    static_assert(!noexcept(v = std::move(s)), "");
  }

  {
    variant<float, S, int> v1;
    variant<float, S, int> v2;
    static_assert(noexcept(v2 = v1), "");
  }

  {
    variant<float, S, int> const v1;
    variant<float, S, int> v2;
    static_assert(noexcept(v2 = v1), "");
  }

  {
    variant<float, S, int> v1;
    variant<float, S, int> v2;
    static_assert(!noexcept(v2 = std::move(v1)), "");
  }

  {
    variant<float, S, int> v1;
    variant<S, int, float, S*> v2;
    static_assert(noexcept(v2 = v1), "");
  }

  {
    variant<float, S, int> const v1;
    variant<S, int, float, S*> v2;
    static_assert(noexcept(v2 = v1), "");
  }

  {
    variant<float, S, int> v1;
    variant<float, S, int, S*> v2;
    static_assert(!noexcept(v2 = std::move(v1)), "");
  }
}

int main()
{
  test__dtor__01();
  test__dtor__02();
  test__dtor__03();
  test__ctors__01();
  test__ctors__02();
  test__ctors__03();
  test__ctors__04();
  test__ctors__05();
  test__assign__01();
  test__assign__02();
  test__assign__03();
  test__assign__04();
  return YAUL_VARIANT_TEST_EXIT_CODE;
}
