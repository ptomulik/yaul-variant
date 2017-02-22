// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <yaul/variant/get.hpp>
#include <yaul/variant/variant.hpp>
#include <yaul/variant/test_config.hpp>


// test yaul::get on ordinary variants

void test__relaxed_get__01()
{
  //
  // relaxed_get(&v) --> pointer version
  //

  using yaul::relaxed_get;
  typedef yaul::variant<int,char> V;

  // V*
  {
    V v;
    {
      v = 123;
      {
        int* i = relaxed_get<int>(&v);
        YAUL_VARIANT_CHECK(i != nullptr);
        YAUL_VARIANT_CHECK_EQUALS(*i, 123);
      }
      {
        char* c = relaxed_get<char>(&v);
        YAUL_VARIANT_CHECK(c == nullptr);
      }
      YAUL_VARIANT_CHECK(relaxed_get<float>(&v) == nullptr);

      v = 'a';
      {
        int* i = relaxed_get<int>(&v);
        YAUL_VARIANT_CHECK(i == nullptr);
      }
      {
        char* c = relaxed_get<char>(&v);
        YAUL_VARIANT_CHECK(c != nullptr);
        YAUL_VARIANT_CHECK_EQUALS(*c, 'a');
      }
      YAUL_VARIANT_CHECK(relaxed_get<float>(&v) == nullptr);
    }
  }

  // V const*
  {
    {
      V const v{123};
      {
        int const* i = relaxed_get<int>(&v);
        YAUL_VARIANT_CHECK(i != nullptr);
        YAUL_VARIANT_CHECK_EQUALS(*i, 123);
      }
      {
        char const* c = relaxed_get<char>(&v);
        YAUL_VARIANT_CHECK(c == nullptr);
      }
      YAUL_VARIANT_CHECK(relaxed_get<float>(&v) == nullptr);
    }
    {
      V const v{'a'};
      {
        int const* i = relaxed_get<int>(&v);
        YAUL_VARIANT_CHECK(i == nullptr);
      }
      {
        char const* c = relaxed_get<char>(&v);
        YAUL_VARIANT_CHECK(c != nullptr);
        YAUL_VARIANT_CHECK_EQUALS(*c, 'a');
      }
      YAUL_VARIANT_CHECK(relaxed_get<float>(&v) == nullptr);
    }
  }
}

void test__relaxed_get__02()
{
  //
  // relaxed_get(v) --> reference version
  //

  using yaul::relaxed_get;
  typedef yaul::variant<int,char> V;

  // V&
  {
    V v;
    v = 123;
    {
      int& i = relaxed_get<int>(v);
      YAUL_VARIANT_CHECK_EQUALS(i, 123);
    }
    YAUL_VARIANT_CHECK_THROWS(relaxed_get<char>(v), yaul::bad_get);

    v = 'a';
    {
      char& c = relaxed_get<char>(v);
      YAUL_VARIANT_CHECK_EQUALS(c, 'a');
    }
    YAUL_VARIANT_CHECK_THROWS(relaxed_get<int>(v), yaul::bad_get);
  }
  // V const&
  {
    {
      V const v{123};
      {
        int const& i = relaxed_get<int>(v);
        YAUL_VARIANT_CHECK_EQUALS(i, 123);
      }
      YAUL_VARIANT_CHECK_THROWS(relaxed_get<char>(v), yaul::bad_get);
    }
    {
      V const v{'a'};
      {
        char const& c = relaxed_get<char>(v);
        YAUL_VARIANT_CHECK_EQUALS(c, 'a');
      }
      YAUL_VARIANT_CHECK_THROWS(relaxed_get<int>(v), yaul::bad_get);
    }
  }

  // V&&
  {
    {
      {
        int&& i = relaxed_get<int>(V{123});
        YAUL_VARIANT_CHECK_EQUALS(i, 123);
      }
      YAUL_VARIANT_CHECK_THROWS(relaxed_get<char>(V{123}), yaul::bad_get);
    }
    {
      {
        char&& c = relaxed_get<char>(V{'a'});
        YAUL_VARIANT_CHECK_EQUALS(c, 'a');
      }
      YAUL_VARIANT_CHECK_THROWS(relaxed_get<int>(V{'a'}), yaul::bad_get);
    }
  }
}

void test__strict_get__01()
{
  //
  // strict_get(&v) --> pointer version
  //

  using yaul::strict_get;
  typedef yaul::variant<int,char> V;

  // V*
  {
    V v;
    {
      v = 123;
      {
        int* i = strict_get<int>(&v);
        YAUL_VARIANT_CHECK(i != nullptr);
        YAUL_VARIANT_CHECK_EQUALS(*i, 123);
      }
      {
        char* c = strict_get<char>(&v);
        YAUL_VARIANT_CHECK(c == nullptr);
      }

      v = 'a';
      {
        int* i = strict_get<int>(&v);
        YAUL_VARIANT_CHECK(i == nullptr);
      }
      {
        char* c = strict_get<char>(&v);
        YAUL_VARIANT_CHECK(c != nullptr);
        YAUL_VARIANT_CHECK_EQUALS(*c, 'a');
      }
    }
  }

  // V const*
  {
    {
      V const v{123};
      {
        int const* i = strict_get<int>(&v);
        YAUL_VARIANT_CHECK(i != nullptr);
        YAUL_VARIANT_CHECK_EQUALS(*i, 123);
      }
      {
        char const* c = strict_get<char>(&v);
        YAUL_VARIANT_CHECK(c == nullptr);
      }
    }
    {
      V const v{'a'};
      {
        int const* i = strict_get<int>(&v);
        YAUL_VARIANT_CHECK(i == nullptr);
      }
      {
        char const* c = strict_get<char>(&v);
        YAUL_VARIANT_CHECK(c != nullptr);
        YAUL_VARIANT_CHECK_EQUALS(*c, 'a');
      }
    }
  }
}

void test__strict_get__02()
{
  //
  // strict_get(v) --> reference version
  //

  using yaul::strict_get;
  typedef yaul::variant<int,char> V;

  // V&
  {
    V v;
    v = 123;
    {
      int& i = strict_get<int>(v);
      YAUL_VARIANT_CHECK_EQUALS(i, 123);
    }
    YAUL_VARIANT_CHECK_THROWS(strict_get<char>(v), yaul::bad_get);

    v = 'a';
    {
      char& c = strict_get<char>(v);
      YAUL_VARIANT_CHECK_EQUALS(c, 'a');
    }
    YAUL_VARIANT_CHECK_THROWS(strict_get<int>(v), yaul::bad_get);
  }
  // V const&
  {
    {
      V const v{123};
      {
        int const& i = strict_get<int>(v);
        YAUL_VARIANT_CHECK_EQUALS(i, 123);
      }
      YAUL_VARIANT_CHECK_THROWS(strict_get<char>(v), yaul::bad_get);
    }
    {
      V const v{'a'};
      {
        char const& c = strict_get<char>(v);
        YAUL_VARIANT_CHECK_EQUALS(c, 'a');
      }
      YAUL_VARIANT_CHECK_THROWS(strict_get<int>(v), yaul::bad_get);
    }
  }

  // V&&
  {
    {
      {
        int&& i = strict_get<int>(V{123});
        YAUL_VARIANT_CHECK_EQUALS(i, 123);
      }
      YAUL_VARIANT_CHECK_THROWS(strict_get<char>(V{123}), yaul::bad_get);
    }
    {
      {
        char&& c = strict_get<char>(V{'a'});
        YAUL_VARIANT_CHECK_EQUALS(c, 'a');
      }
      YAUL_VARIANT_CHECK_THROWS(strict_get<int>(V{'a'}), yaul::bad_get);
    }
  }
}

void test__get__01()
{
  //
  // get(&v) --> pointer version
  //

  using yaul::get;
  typedef yaul::variant<int,char> V;

  // V*
  {
    V v;
    {
      v = 123;
      {
        int* i = get<int>(&v);
        YAUL_VARIANT_CHECK(i != nullptr);
        YAUL_VARIANT_CHECK_EQUALS(*i, 123);
      }
      {
        char* c = get<char>(&v);
        YAUL_VARIANT_CHECK(c == nullptr);
      }

      v = 'a';
      {
        int* i = get<int>(&v);
        YAUL_VARIANT_CHECK(i == nullptr);
      }
      {
        char* c = get<char>(&v);
        YAUL_VARIANT_CHECK(c != nullptr);
        YAUL_VARIANT_CHECK_EQUALS(*c, 'a');
      }
    }
  }

  // V const*
  {
    {
      V const v{123};
      {
        int const* i = get<int>(&v);
        YAUL_VARIANT_CHECK(i != nullptr);
        YAUL_VARIANT_CHECK_EQUALS(*i, 123);
      }
      {
        char const* c = get<char>(&v);
        YAUL_VARIANT_CHECK(c == nullptr);
      }
    }
    {
      V const v{'a'};
      {
        int const* i = get<int>(&v);
        YAUL_VARIANT_CHECK(i == nullptr);
      }
      {
        char const* c = get<char>(&v);
        YAUL_VARIANT_CHECK(c != nullptr);
        YAUL_VARIANT_CHECK_EQUALS(*c, 'a');
      }
    }
  }
}

void test__get__02()
{
  //
  // get(v) --> reference version
  //

  using yaul::get;
  typedef yaul::variant<int,char> V;

  // V&
  {
    V v;
    v = 123;
    {
      int& i = get<int>(v);
      YAUL_VARIANT_CHECK_EQUALS(i, 123);
    }
    YAUL_VARIANT_CHECK_THROWS(get<char>(v), yaul::bad_get);

    v = 'a';
    {
      char& c = get<char>(v);
      YAUL_VARIANT_CHECK_EQUALS(c, 'a');
    }
    YAUL_VARIANT_CHECK_THROWS(get<int>(v), yaul::bad_get);
  }
  // V const&
  {
    {
      V const v{123};
      {
        int const& i = get<int>(v);
        YAUL_VARIANT_CHECK_EQUALS(i, 123);
      }
      YAUL_VARIANT_CHECK_THROWS(get<char>(v), yaul::bad_get);
    }
    {
      V const v{'a'};
      {
        char const& c = get<char>(v);
        YAUL_VARIANT_CHECK_EQUALS(c, 'a');
      }
      YAUL_VARIANT_CHECK_THROWS(get<int>(v), yaul::bad_get);
    }
  }

  // V&&
  {
    {
      {
        int&& i = get<int>(V{123});
        YAUL_VARIANT_CHECK_EQUALS(i, 123);
      }
      YAUL_VARIANT_CHECK_THROWS(get<char>(V{123}), yaul::bad_get);
    }
    {
      {
        char&& c = get<char>(V{'a'});
        YAUL_VARIANT_CHECK_EQUALS(c, 'a');
      }
      YAUL_VARIANT_CHECK_THROWS(get<int>(V{'a'}), yaul::bad_get);
    }
  }
}


int main()
{
//  test__relaxed_get__01();
//  test__relaxed_get__02();
  test__strict_get__01();
  test__strict_get__02();
  test__get__01();
  test__get__02();
  return YAUL_VARIANT_TEST_EXIT_CODE;
}
