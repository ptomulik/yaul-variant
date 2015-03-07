// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <yaul/variant/variant.hpp>
#include <yaul/variant/test_config.hpp>
#include <type_traits>

//
// play with copy-/move- construtibility of bounded types
//

void test__ctors__01()
{
  yaul::variant<int> v{10};
  YAUL_VARIANT_CHECK_EQUALS(v.which(), 0);
}

void test__ctors__02()
{
  {
    yaul::variant<int,float,char> v{10};
    YAUL_VARIANT_CHECK_EQUALS(v.which(), 0);
  }
  {
    yaul::variant<int,float,char> v{10.0f};
    YAUL_VARIANT_CHECK_EQUALS(v.which(), 1);
  }
  {
    yaul::variant<int,float,char> v{'a'};
    YAUL_VARIANT_CHECK_EQUALS(v.which(), 2);
  }
}

void test__ctors__03()
{
  struct S
  {
    S() = delete;
    S(int) noexcept {}
  };

  {
    yaul::variant<S,int> v{S(1)};
    YAUL_VARIANT_CHECK_EQUALS(v.which(),0);
  }
  {
    S s{1};
    yaul::variant<S,int> v{s};
    YAUL_VARIANT_CHECK_EQUALS(v.which(),0);
  }
  {
    yaul::variant<int,S> v{S(1)};
    YAUL_VARIANT_CHECK_EQUALS(v.which(),1);
  }
  {
    S s{1};
    yaul::variant<int,S> v{s};
    YAUL_VARIANT_CHECK_EQUALS(v.which(),1);
  }
}

void test__ctors__04()
{
  struct S0
  {
    S0() = default;
    S0(S0&) = delete;
    S0(S0 const&) = delete;
    S0(S0&&) = delete;
  };

  {
    yaul::variant<S0,int> v;
    YAUL_VARIANT_CHECK_EQUALS(v.which(),0);
  }
  {
    yaul::variant<int,S0> v;
    YAUL_VARIANT_CHECK_EQUALS(v.which(),0);
  }
}

void test__ctors__05()
{
  struct S1
  {
    S1() = delete;
    S1(S1&) = default;
    S1(S1 const&) = delete;
    S1(S1&&) = delete;
    S1(int) {}
  };

  {
    S1 s{1};
    yaul::variant<S1,int> v{s};
    YAUL_VARIANT_CHECK_EQUALS(v.which(),0);
  }
  {
    S1 s{1};
    yaul::variant<int,S1> v{s};
    YAUL_VARIANT_CHECK_EQUALS(v.which(),1);
  }
}

void test__ctors__06()
{
  struct S2
  {
    S2() = delete;
    S2(S2&) = delete;
    S2(S2 const&) = default;
    S2(S2&&) = delete;
    S2(int) {}
  };

  {
    S2 const s{1};
    yaul::variant<S2,int> v{s};
    YAUL_VARIANT_CHECK_EQUALS(v.which(),0);
  }
  {
    S2 const s{1};
    yaul::variant<int,S2> v{s};
    YAUL_VARIANT_CHECK_EQUALS(v.which(),1);
  }
}

void test__ctors__07()
{
  struct S3
  {
    S3() = delete;
    S3(S3&) = delete;
    S3(S3 const&) = delete;
    S3(S3&&) = default;
    S3(int) {}
  };

  {
    yaul::variant<S3,int> v{S3{1}};
    YAUL_VARIANT_CHECK_EQUALS(v.which(),0);
  }
  {
    yaul::variant<int,S3> v{S3{1}};
    YAUL_VARIANT_CHECK_EQUALS(v.which(),1);
  }
}

int main()
{
  test__ctors__01();
  test__ctors__02();
  test__ctors__03();
  test__ctors__04();
  test__ctors__05();
  test__ctors__06();
  test__ctors__07();
  return YAUL_VARIANT_TEST_EXIT_CODE;
}
