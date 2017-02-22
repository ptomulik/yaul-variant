// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <yaul/variant/detail/apply_visitor_binary.hpp>
#include <yaul/variant/variant.hpp>
#include <yaul/variant/test_config.hpp>

struct V01
{
  typedef void result_type;
  template<typename T1, typename T2>
  result_type operator()(T1&&, T2&&) const noexcept { }
};

void test__noexcept__01()
{
  typedef yaul::variant<char, double> X1;
  typedef yaul::variant<double, int> X2;
  // V01&
  {
    V01 v;
    // X1&
    {
      X1 x1{'a'};
      // X2&
      {
        X2 x2{123};
        static_assert(noexcept(yaul::apply_visitor(v,x1,x2)), "");
      }
      {
        X2 const x2{123};
        static_assert(noexcept(yaul::apply_visitor(v,x1,x2)), "");
      }
      // X2&&
      {
        static_assert(noexcept(yaul::apply_visitor(v,x1,X2{123})), "");
      }
    }
    // X1 const&
    {
      X1 const x1{'a'};
      // X2&
      {
        X2 x2{123};
        static_assert(noexcept(yaul::apply_visitor(v,x1,x2)), "");
      }
      {
        X2 const x2{123};
        static_assert(noexcept(yaul::apply_visitor(v,x1,x2)), "");
      }
      // X2&&
      {
        static_assert(noexcept(yaul::apply_visitor(v,x1,X2{123})), "");
      }
    }
    // X1&&
    {
      // X2&
      {
        X2 x2{123};
        static_assert(noexcept(yaul::apply_visitor(v,X1{'a'},x2)), "");
      }
      {
        X2 const x2{123};
        static_assert(noexcept(yaul::apply_visitor(v,X1{'a'},x2)), "");
      }
      // X2&&
      {
        static_assert(noexcept(yaul::apply_visitor(v,X1{'a'},X2{123})), "");
      }
    }
  }
  // V01 const&
  {
    V01 const v{};
    // X1&
    {
      X1 x1{'a'};
      // X2&
      {
        X2 x2{123};
        static_assert(noexcept(yaul::apply_visitor(v,x1,x2)), "");
      }
      {
        X2 const x2{123};
        static_assert(noexcept(yaul::apply_visitor(v,x1,x2)), "");
      }
      // X2&&
      {
        static_assert(noexcept(yaul::apply_visitor(v,x1,X2{123})), "");
      }
    }
    // X1 const&
    {
      X1 const x1{'a'};
      // X2&
      {
        X2 x2{123};
        static_assert(noexcept(yaul::apply_visitor(v,x1,x2)), "");
      }
      {
        X2 const x2{123};
        static_assert(noexcept(yaul::apply_visitor(v,x1,x2)), "");
      }
      // X2&&
      {
        static_assert(noexcept(yaul::apply_visitor(v,x1,X2{123})), "");
      }
    }
    // X1&&
    {
      // X2&
      {
        X2 x2{123};
        static_assert(noexcept(yaul::apply_visitor(v,X1{'a'},x2)), "");
      }
      {
        X2 const x2{123};
        static_assert(noexcept(yaul::apply_visitor(v,X1{'a'},x2)), "");
      }
      // X2&&
      {
        static_assert(noexcept(yaul::apply_visitor(v,X1{'a'},X2{123})), "");
      }
    }
  }
  // V01&&
  {
    // X1&
    {
      X1 x1{'a'};
      // X2&
      {
        X2 x2{123};
        static_assert(noexcept(yaul::apply_visitor(V01{},x1,x2)), "");
      }
      {
        X2 const x2{123};
        static_assert(noexcept(yaul::apply_visitor(V01{},x1,x2)), "");
      }
      // X2&&
      {
        static_assert(noexcept(yaul::apply_visitor(V01{},x1,X2{123})), "");
      }
    }
    // X1 const&
    {
      X1 const x1{'a'};
      // X2&
      {
        X2 x2{123};
        static_assert(noexcept(yaul::apply_visitor(V01{},x1,x2)), "");
      }
      {
        X2 const x2{123};
        static_assert(noexcept(yaul::apply_visitor(V01{},x1,x2)), "");
      }
      // X2&&
      {
        static_assert(noexcept(yaul::apply_visitor(V01{},x1,X2{123})), "");
      }
    }
    // X1&&
    {
      // X2&
      {
        X2 x2{123};
        static_assert(noexcept(yaul::apply_visitor(V01{},X1{'a'},x2)), "");
      }
      {
        X2 const x2{123};
        static_assert(noexcept(yaul::apply_visitor(V01{},X1{'a'},x2)), "");
      }
      // X2&&
      {
        static_assert(noexcept(yaul::apply_visitor(V01{},X1{'a'},X2{123})), "");
      }
    }
  }
}

// is_nothrow_move_constructible<R03>::value is true
struct R02
{
  R02() = default;
  R02(R02&) = default;
  R02(R02 const&) {} // no nonexcept clause here
  R02(R02&&) = default;
};

struct V02
{
  typedef R02 result_type;
  template<typename T1, typename T2>
  result_type operator()(T1&&, T2&&) const noexcept { return R02{}; }
};

void test__noexcept__02()
{
  typedef yaul::variant<char, double> X1;
  typedef yaul::variant<double, int> X2;
  // V02&
  {
    V02 v;
    // X1&
    {
      X1 x1{'a'};
      // X2&
      {
        X2 x2{123};
        static_assert(noexcept(yaul::apply_visitor(v,x1,x2)), "");
      }
      {
        X2 const x2{123};
        static_assert(noexcept(yaul::apply_visitor(v,x1,x2)), "");
      }
      // X2&&
      {
        static_assert(noexcept(yaul::apply_visitor(v,x1,X2{123})), "");
      }
    }
    // X1 const&
    {
      X1 const x1{'a'};
      // X2&
      {
        X2 x2{123};
        static_assert(noexcept(yaul::apply_visitor(v,x1,x2)), "");
      }
      {
        X2 const x2{123};
        static_assert(noexcept(yaul::apply_visitor(v,x1,x2)), "");
      }
      // X2&&
      {
        static_assert(noexcept(yaul::apply_visitor(v,x1,X2{123})), "");
      }
    }
    // X1&&
    {
      // X2&
      {
        X2 x2{123};
        static_assert(noexcept(yaul::apply_visitor(v,X1{'a'},x2)), "");
      }
      {
        X2 const x2{123};
        static_assert(noexcept(yaul::apply_visitor(v,X1{'a'},x2)), "");
      }
      // X2&&
      {
        static_assert(noexcept(yaul::apply_visitor(v,X1{'a'},X2{123})), "");
      }
    }
  }
  // V02 const&
  {
    V02 const v{};
    // X1&
    {
      X1 x1{'a'};
      // X2&
      {
        X2 x2{123};
        static_assert(noexcept(yaul::apply_visitor(v,x1,x2)), "");
      }
      {
        X2 const x2{123};
        static_assert(noexcept(yaul::apply_visitor(v,x1,x2)), "");
      }
      // X2&&
      {
        static_assert(noexcept(yaul::apply_visitor(v,x1,X2{123})), "");
      }
    }
    // X1 const&
    {
      X1 const x1{'a'};
      // X2&
      {
        X2 x2{123};
        static_assert(noexcept(yaul::apply_visitor(v,x1,x2)), "");
      }
      {
        X2 const x2{123};
        static_assert(noexcept(yaul::apply_visitor(v,x1,x2)), "");
      }
      // X2&&
      {
        static_assert(noexcept(yaul::apply_visitor(v,x1,X2{123})), "");
      }
    }
    // X1&&
    {
      // X2&
      {
        X2 x2{123};
        static_assert(noexcept(yaul::apply_visitor(v,X1{'a'},x2)), "");
      }
      {
        X2 const x2{123};
        static_assert(noexcept(yaul::apply_visitor(v,X1{'a'},x2)), "");
      }
      // X2&&
      {
        static_assert(noexcept(yaul::apply_visitor(v,X1{'a'},X2{123})), "");
      }
    }
  }
  // V02&&
  {
    // X1&
    {
      X1 x1{'a'};
      // X2&
      {
        X2 x2{123};
        static_assert(noexcept(yaul::apply_visitor(V02{},x1,x2)), "");
      }
      {
        X2 const x2{123};
        static_assert(noexcept(yaul::apply_visitor(V02{},x1,x2)), "");
      }
      // X2&&
      {
        static_assert(noexcept(yaul::apply_visitor(V02{},x1,X2{123})), "");
      }
    }
    // X1 const&
    {
      X1 const x1{'a'};
      // X2&
      {
        X2 x2{123};
        static_assert(noexcept(yaul::apply_visitor(V02{},x1,x2)), "");
      }
      {
        X2 const x2{123};
        static_assert(noexcept(yaul::apply_visitor(V02{},x1,x2)), "");
      }
      // X2&&
      {
        static_assert(noexcept(yaul::apply_visitor(V02{},x1,X2{123})), "");
      }
    }
    // X1&&
    {
      // X2&
      {
        X2 x2{123};
        static_assert(noexcept(yaul::apply_visitor(V02{},X1{'a'},x2)), "");
      }
      {
        X2 const x2{123};
        static_assert(noexcept(yaul::apply_visitor(V02{},X1{'a'},x2)), "");
      }
      // X2&&
      {
        static_assert(noexcept(yaul::apply_visitor(V02{},X1{'a'},X2{123})), "");
      }
    }
  }
}

struct R03
{
  R03() = default;
  // all the move/copy operations without noexcept clause
  R03(R03&) = default;
  R03(R03 const&) = default;
  R03(R03&&) {}
  R03& operator=(R03&) = default;
  R03& operator=(R03 const&) = default;
  R03& operator=(R03&&) = default;
};

struct V03
{
  typedef R03 result_type;
  template<typename T1, typename T2>
  result_type operator()(T1&&, T2&&) const noexcept { return R03{}; }
};

void test__noexcept__03()
{
// FIXME: elaborate what's going on there...
//
// How the missing noexcept in R03(R03&&) propagates to apply_visitor():
//
// GCC <= 4.9:  does not propagate unless we use the "--no-elide-constructors"
// GCC >= 5.1:  propagates independently on the flag
// CLANG 3.5:   propagates unconditionally (seems to...)
//
// What about others?
//
// This seems to be connected to copy-elision vs. noexcept.
//
// See:
//
// https://gcc.gnu.org/ml/gcc-bugs/2012-04/msg01453.html
// http://en.cppreference.com/w/cpp/language/copy_elision
#if defined(__clang__) || (defined(__GNUC__) && (__GNUC__ >= 5) && (__GNUC_MINOR__ >= 1))
  typedef yaul::variant<char, double> X1;
  typedef yaul::variant<double, int> X2;

  {
    typedef yaul::variant<int> X3;
    V03 v;
    X3 x1{1}, x2{2};
    static_assert(!noexcept(yaul::apply_visitor(v,x1,x2)), "");
  }

  // V03&
  {
    V03 v;
    // X1&
    {
      X1 x1{'a'};
      // X2&
      {
        X2 x2{123};
        static_assert(!noexcept(yaul::apply_visitor(v,x1,x2)), "");
      }
      {
        X2 const x2{123};
        static_assert(!noexcept(yaul::apply_visitor(v,x1,x2)), "");
      }
      // X2&&
      {
        static_assert(!noexcept(yaul::apply_visitor(v,x1,X2{123})), "");
      }
    }
    // X1 const&
    {
      X1 const x1{'a'};
      // X2&
      {
        X2 x2{123};
        static_assert(!noexcept(yaul::apply_visitor(v,x1,x2)), "");
      }
      {
        X2 const x2{123};
        static_assert(!noexcept(yaul::apply_visitor(v,x1,x2)), "");
      }
      // X2&&
      {
        static_assert(!noexcept(yaul::apply_visitor(v,x1,X2{123})), "");
      }
    }
    // X1&&
    {
      // X2&
      {
        X2 x2{123};
        static_assert(!noexcept(yaul::apply_visitor(v,X1{'a'},x2)), "");
      }
      {
        X2 const x2{123};
        static_assert(!noexcept(yaul::apply_visitor(v,X1{'a'},x2)), "");
      }
      // X2&&
      {
        static_assert(!noexcept(yaul::apply_visitor(v,X1{'a'},X2{123})), "");
      }
    }
  }
  // V03 const&
  {
    V03 const v{};
    // X1&
    {
      X1 x1{'a'};
      // X2&
      {
        X2 x2{123};
        static_assert(!noexcept(yaul::apply_visitor(v,x1,x2)), "");
      }
      {
        X2 const x2{123};
        static_assert(!noexcept(yaul::apply_visitor(v,x1,x2)), "");
      }
      // X2&&
      {
        static_assert(!noexcept(yaul::apply_visitor(v,x1,X2{123})), "");
      }
    }
    // X1 const&
    {
      X1 const x1{'a'};
      // X2&
      {
        X2 x2{123};
        static_assert(!noexcept(yaul::apply_visitor(v,x1,x2)), "");
      }
      {
        X2 const x2{123};
        static_assert(!noexcept(yaul::apply_visitor(v,x1,x2)), "");
      }
      // X2&&
      {
        static_assert(!noexcept(yaul::apply_visitor(v,x1,X2{123})), "");
      }
    }
    // X1&&
    {
      // X2&
      {
        X2 x2{123};
        static_assert(!noexcept(yaul::apply_visitor(v,X1{'a'},x2)), "");
      }
      {
        X2 const x2{123};
        static_assert(!noexcept(yaul::apply_visitor(v,X1{'a'},x2)), "");
      }
      // X2&&
      {
        static_assert(!noexcept(yaul::apply_visitor(v,X1{'a'},X2{123})), "");
      }
    }
  }
  // V03&&
  {
    // X1&
    {
      X1 x1{'a'};
      // X2&
      {
        X2 x2{123};
        static_assert(!noexcept(yaul::apply_visitor(V03{},x1,x2)), "");
      }
      {
        X2 const x2{123};
        static_assert(!noexcept(yaul::apply_visitor(V03{},x1,x2)), "");
      }
      // X2&&
      {
        static_assert(!noexcept(yaul::apply_visitor(V03{},x1,X2{123})), "");
      }
    }
    // X1 const&
    {
      X1 const x1{'a'};
      // X2&
      {
        X2 x2{123};
        static_assert(!noexcept(yaul::apply_visitor(V03{},x1,x2)), "");
      }
      {
        X2 const x2{123};
        static_assert(!noexcept(yaul::apply_visitor(V03{},x1,x2)), "");
      }
      // X2&&
      {
        static_assert(!noexcept(yaul::apply_visitor(V03{},x1,X2{123})), "");
      }
    }
    // X1&&
    {
      // X2&
      {
        X2 x2{123};
        static_assert(!noexcept(yaul::apply_visitor(V03{},X1{'a'},x2)), "");
      }
      {
        X2 const x2{123};
        static_assert(!noexcept(yaul::apply_visitor(V03{},X1{'a'},x2)), "");
      }
      // X2&&
      {
        static_assert(!noexcept(yaul::apply_visitor(V03{},X1{'a'},X2{123})), "");
      }
    }
  }
#endif
}

struct V04
{
  typedef void result_type;
  template<typename T1, typename T2>
  result_type operator()(T1&&, T2&&) const noexcept { }
  result_type operator()(char, int) const { } // no noexcept clause
};

void test__noexcept__04()
{
  {
    typedef yaul::variant<char, double> X1;
    typedef yaul::variant<double, int> X2;

    // (X1, X2) -> touches the throwing specialization of operator()(char, int)
    static_assert(!noexcept(yaul::apply_visitor(V04{}, X1{'a'}, X2{123})), "");
    static_assert(!noexcept(yaul::apply_visitor(V04{}, X1{1.23}, X2{1.23})), "");

    // (X2, X1) -> touches only the noexcept operator()(T1&&, T2&&)
    static_assert(noexcept(yaul::apply_visitor(V04{}, X2{123}, X1{'a'})), "");
    static_assert(noexcept(yaul::apply_visitor(V04{}, X2{1.23}, X1{1.23})), "");
  }
}

int main()
{
  test__noexcept__01();
  test__noexcept__02();
  test__noexcept__03();
  test__noexcept__04();
  return YAUL_VARIANT_TEST_EXIT_CODE;
}
