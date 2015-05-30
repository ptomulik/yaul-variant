// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <yaul/variant/get.hpp>
#include <yaul/variant/recursive_variant.hpp>
#include <yaul/variant/test_config.hpp>
#include <tuple>


// test yaul::get on recursive variants

struct S01;

typedef yaul::variant<int, char, yaul::recursive_wrapper<S01> > X01;

struct S01
{
  X01 left;
  X01 right;

  S01(X01 const& l, X01 const& r)
    : left(l), right(r)
  { }

  bool operator==(S01 const& rhs) const noexcept
  { return left == rhs.left && right == rhs.right; }
};

typedef typename yaul::make_recursive_variant<
    int
  , char
  , std::tuple<
      yaul::recursive_variant_,
      yaul::recursive_variant_
    >
>::type X02;

typedef std::tuple<X02, X02> S02;

void test__relaxed_get__01()
{
  // X01&
  {
    {
      X01 x{123};
      int& i = yaul::relaxed_get<int>(x);
      YAUL_VARIANT_CHECK_EQUALS(i, 123);
      YAUL_VARIANT_CHECK_THROWS(yaul::relaxed_get<char>(x), yaul::bad_get);
      YAUL_VARIANT_CHECK_THROWS(yaul::relaxed_get<S01>(x), yaul::bad_get);
      YAUL_VARIANT_CHECK_THROWS(yaul::relaxed_get<float>(x), yaul::bad_get);
    }
    {
      X01 x{'a'};
      char& c = yaul::relaxed_get<char>(x);
      YAUL_VARIANT_CHECK_EQUALS(c, 'a');
      YAUL_VARIANT_CHECK_THROWS(yaul::relaxed_get<int>(x), yaul::bad_get);
      YAUL_VARIANT_CHECK_THROWS(yaul::relaxed_get<S01>(x), yaul::bad_get);
      YAUL_VARIANT_CHECK_THROWS(yaul::relaxed_get<float>(x), yaul::bad_get);
    }
    {
      X01 x{S01{X01{234}, X01{'d'}}};
      S01& s = yaul::relaxed_get<S01>(x);
      YAUL_VARIANT_CHECK(s.left == X01{234});
      s.left = X01{123};
      s.right = 'a';
      YAUL_VARIANT_CHECK(yaul::relaxed_get<S01>(x).left == X01{123});
      YAUL_VARIANT_CHECK(yaul::relaxed_get<S01>(x).right == X01{'a'});
      YAUL_VARIANT_CHECK_THROWS(yaul::relaxed_get<int>(x), yaul::bad_get);
      YAUL_VARIANT_CHECK_THROWS(yaul::relaxed_get<char>(x), yaul::bad_get);
      YAUL_VARIANT_CHECK_THROWS(yaul::relaxed_get<float>(x), yaul::bad_get);
    }
  }

  // X01 const&
  {
    {
      X01 const x{123};
      int const& i = yaul::relaxed_get<int>(x);
      YAUL_VARIANT_CHECK_EQUALS(i, 123);
      YAUL_VARIANT_CHECK_THROWS(yaul::relaxed_get<char>(x), yaul::bad_get);
      YAUL_VARIANT_CHECK_THROWS(yaul::relaxed_get<S01>(x), yaul::bad_get);
      YAUL_VARIANT_CHECK_THROWS(yaul::relaxed_get<float>(x), yaul::bad_get);
    }
    {
      X01 const x{'a'};
      char const& c = yaul::relaxed_get<char>(x);
      YAUL_VARIANT_CHECK_EQUALS(c, 'a');
      YAUL_VARIANT_CHECK_THROWS(yaul::relaxed_get<int>(x), yaul::bad_get);
      YAUL_VARIANT_CHECK_THROWS(yaul::relaxed_get<S01>(x), yaul::bad_get);
      YAUL_VARIANT_CHECK_THROWS(yaul::relaxed_get<float>(x), yaul::bad_get);
    }
    {
      X01 const x{S01{X01{234}, X01{'d'}}};
      S01 const& s = yaul::relaxed_get<S01>(x);
      YAUL_VARIANT_CHECK(s.left == X01{234});
      YAUL_VARIANT_CHECK(s.right == X01{'d'});
      YAUL_VARIANT_CHECK_THROWS(yaul::relaxed_get<int>(x), yaul::bad_get);
      YAUL_VARIANT_CHECK_THROWS(yaul::relaxed_get<char>(x), yaul::bad_get);
      YAUL_VARIANT_CHECK_THROWS(yaul::relaxed_get<float>(x), yaul::bad_get);
    }
  }

  // X01&&
  {
    {
      X01&& x{123};
      int&& i = yaul::relaxed_get<int>(std::move(x));
      YAUL_VARIANT_CHECK_EQUALS(i, 123);
      YAUL_VARIANT_CHECK_THROWS(yaul::relaxed_get<char>(std::move(x)), yaul::bad_get);
      YAUL_VARIANT_CHECK_THROWS(yaul::relaxed_get<S01>(std::move(x)), yaul::bad_get);
      YAUL_VARIANT_CHECK_THROWS(yaul::relaxed_get<float>(std::move(x)), yaul::bad_get);
    }
    {
      X01&& x{'a'};
      char&& c = yaul::relaxed_get<char>(std::move(x));
      YAUL_VARIANT_CHECK_EQUALS(c, 'a');
      YAUL_VARIANT_CHECK_THROWS(yaul::relaxed_get<int>(std::move(x)), yaul::bad_get);
      YAUL_VARIANT_CHECK_THROWS(yaul::relaxed_get<S01>(std::move(x)), yaul::bad_get);
      YAUL_VARIANT_CHECK_THROWS(yaul::relaxed_get<float>(std::move(x)), yaul::bad_get);
    }
    {
      X01&& x{S01{X01{234}, X01{'d'}}};
      S01&& s = yaul::relaxed_get<S01>(std::move(x));
      YAUL_VARIANT_CHECK(s.left == X01{234});
      YAUL_VARIANT_CHECK(s.right == X01{'d'});
      YAUL_VARIANT_CHECK_THROWS(yaul::relaxed_get<int>(std::move(x)), yaul::bad_get);
      YAUL_VARIANT_CHECK_THROWS(yaul::relaxed_get<char>(std::move(x)), yaul::bad_get);
      YAUL_VARIANT_CHECK_THROWS(yaul::relaxed_get<float>(std::move(x)), yaul::bad_get);
    }
  }

  // X01 const&&
  {
    {
      X01 const&& x{123};
      int const&& i = yaul::relaxed_get<int>(std::move(x));
      YAUL_VARIANT_CHECK_EQUALS(i, 123);
      YAUL_VARIANT_CHECK_THROWS(yaul::relaxed_get<char>(std::move(x)), yaul::bad_get);
      YAUL_VARIANT_CHECK_THROWS(yaul::relaxed_get<S01>(std::move(x)), yaul::bad_get);
      YAUL_VARIANT_CHECK_THROWS(yaul::relaxed_get<float>(std::move(x)), yaul::bad_get);
    }
    {
      X01 const&& x{'a'};
      char const&& c = yaul::relaxed_get<char>(std::move(x));
      YAUL_VARIANT_CHECK_EQUALS(c, 'a');
      YAUL_VARIANT_CHECK_THROWS(yaul::relaxed_get<int>(std::move(x)), yaul::bad_get);
      YAUL_VARIANT_CHECK_THROWS(yaul::relaxed_get<S01>(std::move(x)), yaul::bad_get);
      YAUL_VARIANT_CHECK_THROWS(yaul::relaxed_get<float>(std::move(x)), yaul::bad_get);
    }
    {
      X01 const&& x{S01{X01{234}, X01{'d'}}};
      S01 const&& s = yaul::relaxed_get<S01>(std::move(x));
      YAUL_VARIANT_CHECK(s.left == X01{234});
      YAUL_VARIANT_CHECK(s.right == X01{'d'});
      YAUL_VARIANT_CHECK_THROWS(yaul::relaxed_get<int>(std::move(x)), yaul::bad_get);
      YAUL_VARIANT_CHECK_THROWS(yaul::relaxed_get<char>(std::move(x)), yaul::bad_get);
      YAUL_VARIANT_CHECK_THROWS(yaul::relaxed_get<float>(std::move(x)), yaul::bad_get);
    }
  }
}

void test__relaxed_get__02()
{
  // X02&
  {
    {
      X02 x{123};
      int& i = yaul::relaxed_get<int>(x);
      YAUL_VARIANT_CHECK_EQUALS(i, 123);
      YAUL_VARIANT_CHECK_THROWS(yaul::relaxed_get<char>(x), yaul::bad_get);
      YAUL_VARIANT_CHECK_THROWS(yaul::relaxed_get<S02>(x), yaul::bad_get);
      YAUL_VARIANT_CHECK_THROWS(yaul::relaxed_get<float>(x), yaul::bad_get);
    }
    {
      X02 x{'a'};
      char& c = yaul::relaxed_get<char>(x);
      YAUL_VARIANT_CHECK_EQUALS(c, 'a');
      YAUL_VARIANT_CHECK_THROWS(yaul::relaxed_get<int>(x), yaul::bad_get);
      YAUL_VARIANT_CHECK_THROWS(yaul::relaxed_get<S02>(x), yaul::bad_get);
      YAUL_VARIANT_CHECK_THROWS(yaul::relaxed_get<float>(x), yaul::bad_get);
    }
    {
      X02 x{S02{X02{234}, X02{'d'}}};
      S02& s = yaul::relaxed_get<S02>(x);
      YAUL_VARIANT_CHECK(std::get<0>(s) == X02{234});
      std::get<0>(s) = X02{123};
      std::get<1>(s) = 'a';
      YAUL_VARIANT_CHECK(std::get<0>(yaul::relaxed_get<S02>(x)) == X02{123});
      YAUL_VARIANT_CHECK(std::get<1>(yaul::relaxed_get<S02>(x)) == X02{'a'});
      YAUL_VARIANT_CHECK_THROWS(yaul::relaxed_get<int>(x), yaul::bad_get);
      YAUL_VARIANT_CHECK_THROWS(yaul::relaxed_get<char>(x), yaul::bad_get);
      YAUL_VARIANT_CHECK_THROWS(yaul::relaxed_get<float>(x), yaul::bad_get);
    }
  }

  // X02 const&
  {
    {
      X02 const x{123};
      int const& i = yaul::relaxed_get<int>(x);
      YAUL_VARIANT_CHECK_EQUALS(i, 123);
      YAUL_VARIANT_CHECK_THROWS(yaul::relaxed_get<char>(x), yaul::bad_get);
      YAUL_VARIANT_CHECK_THROWS(yaul::relaxed_get<S02>(x), yaul::bad_get);
      YAUL_VARIANT_CHECK_THROWS(yaul::relaxed_get<float>(x), yaul::bad_get);
    }
    {
      X02 const x{'a'};
      char const& c = yaul::relaxed_get<char>(x);
      YAUL_VARIANT_CHECK_EQUALS(c, 'a');
      YAUL_VARIANT_CHECK_THROWS(yaul::relaxed_get<int>(x), yaul::bad_get);
      YAUL_VARIANT_CHECK_THROWS(yaul::relaxed_get<S02>(x), yaul::bad_get);
      YAUL_VARIANT_CHECK_THROWS(yaul::relaxed_get<float>(x), yaul::bad_get);
    }
    {
      X02 const x{S02{X02{234}, X02{'d'}}};
      S02 const& s = yaul::relaxed_get<S02>(x);
      YAUL_VARIANT_CHECK(std::get<0>(s) == X02{234});
      YAUL_VARIANT_CHECK(std::get<1>(s) == X02{'d'});
      YAUL_VARIANT_CHECK_THROWS(yaul::relaxed_get<int>(x), yaul::bad_get);
      YAUL_VARIANT_CHECK_THROWS(yaul::relaxed_get<char>(x), yaul::bad_get);
      YAUL_VARIANT_CHECK_THROWS(yaul::relaxed_get<float>(x), yaul::bad_get);
    }
  }

  // X02&&
  {
    {
      X02&& x{123};
      int&& i = yaul::relaxed_get<int>(std::move(x));
      YAUL_VARIANT_CHECK_EQUALS(i, 123);
      YAUL_VARIANT_CHECK_THROWS(yaul::relaxed_get<char>(std::move(x)), yaul::bad_get);
      YAUL_VARIANT_CHECK_THROWS(yaul::relaxed_get<S02>(std::move(x)), yaul::bad_get);
      YAUL_VARIANT_CHECK_THROWS(yaul::relaxed_get<float>(std::move(x)), yaul::bad_get);
    }
    {
      X02&& x{'a'};
      char&& c = yaul::relaxed_get<char>(std::move(x));
      YAUL_VARIANT_CHECK_EQUALS(c, 'a');
      YAUL_VARIANT_CHECK_THROWS(yaul::relaxed_get<int>(std::move(x)), yaul::bad_get);
      YAUL_VARIANT_CHECK_THROWS(yaul::relaxed_get<S02>(std::move(x)), yaul::bad_get);
      YAUL_VARIANT_CHECK_THROWS(yaul::relaxed_get<float>(std::move(x)), yaul::bad_get);
    }
    {
      X02&& x{S02{X02{234}, X02{'d'}}};
      S02&& s = yaul::relaxed_get<S02>(std::move(x));
      YAUL_VARIANT_CHECK(std::get<0>(std::move(s)) == X02{234});
      YAUL_VARIANT_CHECK(std::get<1>(std::move(s)) == X02{'d'});
      YAUL_VARIANT_CHECK_THROWS(yaul::relaxed_get<int>(std::move(x)), yaul::bad_get);
      YAUL_VARIANT_CHECK_THROWS(yaul::relaxed_get<char>(std::move(x)), yaul::bad_get);
      YAUL_VARIANT_CHECK_THROWS(yaul::relaxed_get<float>(std::move(x)), yaul::bad_get);
    }
  }

  // X02 const&&
  {
    {
      X02 const&& x{123};
      int const&& i = yaul::relaxed_get<int>(std::move(x));
      YAUL_VARIANT_CHECK_EQUALS(i, 123);
      YAUL_VARIANT_CHECK_THROWS(yaul::relaxed_get<char>(std::move(x)), yaul::bad_get);
      YAUL_VARIANT_CHECK_THROWS(yaul::relaxed_get<S02>(std::move(x)), yaul::bad_get);
      YAUL_VARIANT_CHECK_THROWS(yaul::relaxed_get<float>(std::move(x)), yaul::bad_get);
    }
    {
      X02 const&& x{'a'};
      char const&& c = yaul::relaxed_get<char>(std::move(x));
      YAUL_VARIANT_CHECK_EQUALS(c, 'a');
      YAUL_VARIANT_CHECK_THROWS(yaul::relaxed_get<int>(std::move(x)), yaul::bad_get);
      YAUL_VARIANT_CHECK_THROWS(yaul::relaxed_get<S02>(std::move(x)), yaul::bad_get);
      YAUL_VARIANT_CHECK_THROWS(yaul::relaxed_get<float>(std::move(x)), yaul::bad_get);
    }
    {
      X02 const&& x{S02{X02{234}, X02{'d'}}};
      S02 const&& s = yaul::relaxed_get<S02>(std::move(x));
      YAUL_VARIANT_CHECK(std::get<0>(std::move(s)) == X02{234});
      YAUL_VARIANT_CHECK(std::get<1>(std::move(s)) == X02{'d'});
      YAUL_VARIANT_CHECK_THROWS(yaul::relaxed_get<int>(std::move(x)), yaul::bad_get);
      YAUL_VARIANT_CHECK_THROWS(yaul::relaxed_get<char>(std::move(x)), yaul::bad_get);
      YAUL_VARIANT_CHECK_THROWS(yaul::relaxed_get<float>(std::move(x)), yaul::bad_get);
    }
  }
}


void test__strict_get__01()
{
  // X01&
  {
    {
      X01 x{123};
      int& i = yaul::strict_get<int>(x);
      YAUL_VARIANT_CHECK_EQUALS(i, 123);
      YAUL_VARIANT_CHECK_THROWS(yaul::strict_get<char>(x), yaul::bad_get);
      YAUL_VARIANT_CHECK_THROWS(yaul::strict_get<S01>(x), yaul::bad_get);
    }
    {
      X01 x{'a'};
      char& c = yaul::strict_get<char>(x);
      YAUL_VARIANT_CHECK_EQUALS(c, 'a');
      YAUL_VARIANT_CHECK_THROWS(yaul::strict_get<int>(x), yaul::bad_get);
      YAUL_VARIANT_CHECK_THROWS(yaul::strict_get<S01>(x), yaul::bad_get);
    }
    {
      X01 x{S01{X01{234}, X01{'d'}}};
      S01& s = yaul::strict_get<S01>(x);
      YAUL_VARIANT_CHECK(s.left == X01{234});
      s.left = X01{123};
      s.right = 'a';
      YAUL_VARIANT_CHECK(yaul::strict_get<S01>(x).left == X01{123});
      YAUL_VARIANT_CHECK(yaul::strict_get<S01>(x).right == X01{'a'});
      YAUL_VARIANT_CHECK_THROWS(yaul::strict_get<int>(x), yaul::bad_get);
      YAUL_VARIANT_CHECK_THROWS(yaul::strict_get<char>(x), yaul::bad_get);
    }
  }

  // X01 const&
  {
    {
      X01 const x{123};
      int const& i = yaul::strict_get<int>(x);
      YAUL_VARIANT_CHECK_EQUALS(i, 123);
      YAUL_VARIANT_CHECK_THROWS(yaul::strict_get<char>(x), yaul::bad_get);
      YAUL_VARIANT_CHECK_THROWS(yaul::strict_get<S01>(x), yaul::bad_get);
    }
    {
      X01 const x{'a'};
      char const& c = yaul::strict_get<char>(x);
      YAUL_VARIANT_CHECK_EQUALS(c, 'a');
      YAUL_VARIANT_CHECK_THROWS(yaul::strict_get<int>(x), yaul::bad_get);
      YAUL_VARIANT_CHECK_THROWS(yaul::strict_get<S01>(x), yaul::bad_get);
    }
    {
      X01 const x{S01{X01{234}, X01{'d'}}};
      S01 const& s = yaul::strict_get<S01>(x);
      YAUL_VARIANT_CHECK(s.left == X01{234});
      YAUL_VARIANT_CHECK(s.right == X01{'d'});
      YAUL_VARIANT_CHECK_THROWS(yaul::strict_get<int>(x), yaul::bad_get);
      YAUL_VARIANT_CHECK_THROWS(yaul::strict_get<char>(x), yaul::bad_get);
    }
  }

  // X01&&
  {
    {
      X01&& x{123};
      int&& i = yaul::strict_get<int>(std::move(x));
      YAUL_VARIANT_CHECK_EQUALS(i, 123);
      YAUL_VARIANT_CHECK_THROWS(yaul::strict_get<char>(std::move(x)), yaul::bad_get);
      YAUL_VARIANT_CHECK_THROWS(yaul::strict_get<S01>(std::move(x)), yaul::bad_get);
    }
    {
      X01&& x{'a'};
      char&& c = yaul::strict_get<char>(std::move(x));
      YAUL_VARIANT_CHECK_EQUALS(c, 'a');
      YAUL_VARIANT_CHECK_THROWS(yaul::strict_get<int>(std::move(x)), yaul::bad_get);
      YAUL_VARIANT_CHECK_THROWS(yaul::strict_get<S01>(std::move(x)), yaul::bad_get);
    }
    {
      X01&& x{S01{X01{234}, X01{'d'}}};
      S01&& s = yaul::strict_get<S01>(std::move(x));
      YAUL_VARIANT_CHECK(s.left == X01{234});
      YAUL_VARIANT_CHECK(s.right == X01{'d'});
      YAUL_VARIANT_CHECK_THROWS(yaul::strict_get<int>(std::move(x)), yaul::bad_get);
      YAUL_VARIANT_CHECK_THROWS(yaul::strict_get<char>(std::move(x)), yaul::bad_get);
    }
  }

  // X01 const&&
  {
    {
      X01 const&& x{123};
      int const&& i = yaul::strict_get<int>(std::move(x));
      YAUL_VARIANT_CHECK_EQUALS(i, 123);
      YAUL_VARIANT_CHECK_THROWS(yaul::strict_get<char>(std::move(x)), yaul::bad_get);
      YAUL_VARIANT_CHECK_THROWS(yaul::strict_get<S01>(std::move(x)), yaul::bad_get);
    }
    {
      X01 const&& x{'a'};
      char const&& c = yaul::strict_get<char>(std::move(x));
      YAUL_VARIANT_CHECK_EQUALS(c, 'a');
      YAUL_VARIANT_CHECK_THROWS(yaul::strict_get<int>(std::move(x)), yaul::bad_get);
      YAUL_VARIANT_CHECK_THROWS(yaul::strict_get<S01>(std::move(x)), yaul::bad_get);
    }
    {
      X01 const&& x{S01{X01{234}, X01{'d'}}};
      S01 const&& s = yaul::strict_get<S01>(std::move(x));
      YAUL_VARIANT_CHECK(s.left == X01{234});
      YAUL_VARIANT_CHECK(s.right == X01{'d'});
      YAUL_VARIANT_CHECK_THROWS(yaul::strict_get<int>(std::move(x)), yaul::bad_get);
      YAUL_VARIANT_CHECK_THROWS(yaul::strict_get<char>(std::move(x)), yaul::bad_get);
    }
  }
}

void test__strict_get__02()
{
  // X02&
  {
    {
      X02 x{123};
      int& i = yaul::strict_get<int>(x);
      YAUL_VARIANT_CHECK_EQUALS(i, 123);
      YAUL_VARIANT_CHECK_THROWS(yaul::strict_get<char>(x), yaul::bad_get);
      YAUL_VARIANT_CHECK_THROWS(yaul::strict_get<S02>(x), yaul::bad_get);
    }
    {
      X02 x{'a'};
      char& c = yaul::strict_get<char>(x);
      YAUL_VARIANT_CHECK_EQUALS(c, 'a');
      YAUL_VARIANT_CHECK_THROWS(yaul::strict_get<int>(x), yaul::bad_get);
      YAUL_VARIANT_CHECK_THROWS(yaul::strict_get<S02>(x), yaul::bad_get);
    }
    {
      X02 x{S02{X02{234}, X02{'d'}}};
      S02& s = yaul::strict_get<S02>(x);
      YAUL_VARIANT_CHECK(std::get<0>(s) == X02{234});
      std::get<0>(s) = X02{123};
      std::get<1>(s) = 'a';
      YAUL_VARIANT_CHECK(std::get<0>(yaul::strict_get<S02>(x)) == X02{123});
      YAUL_VARIANT_CHECK(std::get<1>(yaul::strict_get<S02>(x)) == X02{'a'});
      YAUL_VARIANT_CHECK_THROWS(yaul::strict_get<int>(x), yaul::bad_get);
      YAUL_VARIANT_CHECK_THROWS(yaul::strict_get<char>(x), yaul::bad_get);
    }
  }

  // X02 const&
  {
    {
      X02 const x{123};
      int const& i = yaul::strict_get<int>(x);
      YAUL_VARIANT_CHECK_EQUALS(i, 123);
      YAUL_VARIANT_CHECK_THROWS(yaul::strict_get<char>(x), yaul::bad_get);
      YAUL_VARIANT_CHECK_THROWS(yaul::strict_get<S02>(x), yaul::bad_get);
    }
    {
      X02 const x{'a'};
      char const& c = yaul::strict_get<char>(x);
      YAUL_VARIANT_CHECK_EQUALS(c, 'a');
      YAUL_VARIANT_CHECK_THROWS(yaul::strict_get<int>(x), yaul::bad_get);
      YAUL_VARIANT_CHECK_THROWS(yaul::strict_get<S02>(x), yaul::bad_get);
    }
    {
      X02 const x{S02{X02{234}, X02{'d'}}};
      S02 const& s = yaul::strict_get<S02>(x);
      YAUL_VARIANT_CHECK(std::get<0>(s) == X02{234});
      YAUL_VARIANT_CHECK(std::get<1>(s) == X02{'d'});
      YAUL_VARIANT_CHECK_THROWS(yaul::strict_get<int>(x), yaul::bad_get);
      YAUL_VARIANT_CHECK_THROWS(yaul::strict_get<char>(x), yaul::bad_get);
    }
  }

  // X02&&
  {
    {
      X02&& x{123};
      int&& i = yaul::strict_get<int>(std::move(x));
      YAUL_VARIANT_CHECK_EQUALS(i, 123);
      YAUL_VARIANT_CHECK_THROWS(yaul::strict_get<char>(std::move(x)), yaul::bad_get);
      YAUL_VARIANT_CHECK_THROWS(yaul::strict_get<S02>(std::move(x)), yaul::bad_get);
    }
    {
      X02&& x{'a'};
      char&& c = yaul::strict_get<char>(std::move(x));
      YAUL_VARIANT_CHECK_EQUALS(c, 'a');
      YAUL_VARIANT_CHECK_THROWS(yaul::strict_get<int>(std::move(x)), yaul::bad_get);
      YAUL_VARIANT_CHECK_THROWS(yaul::strict_get<S02>(std::move(x)), yaul::bad_get);
    }
    {
      X02&& x{S02{X02{234}, X02{'d'}}};
      S02&& s = yaul::strict_get<S02>(std::move(x));
      YAUL_VARIANT_CHECK(std::get<0>(std::move(s)) == X02{234});
      YAUL_VARIANT_CHECK(std::get<1>(std::move(s)) == X02{'d'});
      YAUL_VARIANT_CHECK_THROWS(yaul::strict_get<int>(std::move(x)), yaul::bad_get);
      YAUL_VARIANT_CHECK_THROWS(yaul::strict_get<char>(std::move(x)), yaul::bad_get);
    }
  }

  // X02 const&&
  {
    {
      X02 const&& x{123};
      int const&& i = yaul::strict_get<int>(std::move(x));
      YAUL_VARIANT_CHECK_EQUALS(i, 123);
      YAUL_VARIANT_CHECK_THROWS(yaul::strict_get<char>(std::move(x)), yaul::bad_get);
      YAUL_VARIANT_CHECK_THROWS(yaul::strict_get<S02>(std::move(x)), yaul::bad_get);
    }
    {
      X02 const&& x{'a'};
      char const&& c = yaul::strict_get<char>(std::move(x));
      YAUL_VARIANT_CHECK_EQUALS(c, 'a');
      YAUL_VARIANT_CHECK_THROWS(yaul::strict_get<int>(std::move(x)), yaul::bad_get);
      YAUL_VARIANT_CHECK_THROWS(yaul::strict_get<S02>(std::move(x)), yaul::bad_get);
    }
    {
      X02 const&& x{S02{X02{234}, X02{'d'}}};
      S02 const&& s = yaul::strict_get<S02>(std::move(x));
      YAUL_VARIANT_CHECK(std::get<0>(std::move(s)) == X02{234});
      YAUL_VARIANT_CHECK(std::get<1>(std::move(s)) == X02{'d'});
      YAUL_VARIANT_CHECK_THROWS(yaul::strict_get<int>(std::move(x)), yaul::bad_get);
      YAUL_VARIANT_CHECK_THROWS(yaul::strict_get<char>(std::move(x)), yaul::bad_get);
    }
  }
}

void test__get__01()
{
  // X01&
  {
    {
      X01 x{123};
      int& i = yaul::get<int>(x);
      YAUL_VARIANT_CHECK_EQUALS(i, 123);
      YAUL_VARIANT_CHECK_THROWS(yaul::get<char>(x), yaul::bad_get);
      YAUL_VARIANT_CHECK_THROWS(yaul::get<S01>(x), yaul::bad_get);
    }
    {
      X01 x{'a'};
      char& c = yaul::get<char>(x);
      YAUL_VARIANT_CHECK_EQUALS(c, 'a');
      YAUL_VARIANT_CHECK_THROWS(yaul::get<int>(x), yaul::bad_get);
      YAUL_VARIANT_CHECK_THROWS(yaul::get<S01>(x), yaul::bad_get);
    }
    {
      X01 x{S01{X01{234}, X01{'d'}}};
      S01& s = yaul::get<S01>(x);
      YAUL_VARIANT_CHECK(s.left == X01{234});
      s.left = X01{123};
      s.right = 'a';
      YAUL_VARIANT_CHECK(yaul::get<S01>(x).left == X01{123});
      YAUL_VARIANT_CHECK(yaul::get<S01>(x).right == X01{'a'});
      YAUL_VARIANT_CHECK_THROWS(yaul::get<int>(x), yaul::bad_get);
      YAUL_VARIANT_CHECK_THROWS(yaul::get<char>(x), yaul::bad_get);
    }
  }

  // X01 const&
  {
    {
      X01 const x{123};
      int const& i = yaul::get<int>(x);
      YAUL_VARIANT_CHECK_EQUALS(i, 123);
      YAUL_VARIANT_CHECK_THROWS(yaul::get<char>(x), yaul::bad_get);
      YAUL_VARIANT_CHECK_THROWS(yaul::get<S01>(x), yaul::bad_get);
    }
    {
      X01 const x{'a'};
      char const& c = yaul::get<char>(x);
      YAUL_VARIANT_CHECK_EQUALS(c, 'a');
      YAUL_VARIANT_CHECK_THROWS(yaul::get<int>(x), yaul::bad_get);
      YAUL_VARIANT_CHECK_THROWS(yaul::get<S01>(x), yaul::bad_get);
    }
    {
      X01 const x{S01{X01{234}, X01{'d'}}};
      S01 const& s = yaul::get<S01>(x);
      YAUL_VARIANT_CHECK(s.left == X01{234});
      YAUL_VARIANT_CHECK(s.right == X01{'d'});
      YAUL_VARIANT_CHECK_THROWS(yaul::get<int>(x), yaul::bad_get);
      YAUL_VARIANT_CHECK_THROWS(yaul::get<char>(x), yaul::bad_get);
    }
  }

  // X01&&
  {
    {
      X01&& x{123};
      int&& i = yaul::get<int>(std::move(x));
      YAUL_VARIANT_CHECK_EQUALS(i, 123);
      YAUL_VARIANT_CHECK_THROWS(yaul::get<char>(std::move(x)), yaul::bad_get);
      YAUL_VARIANT_CHECK_THROWS(yaul::get<S01>(std::move(x)), yaul::bad_get);
    }
    {
      X01&& x{'a'};
      char&& c = yaul::get<char>(std::move(x));
      YAUL_VARIANT_CHECK_EQUALS(c, 'a');
      YAUL_VARIANT_CHECK_THROWS(yaul::get<int>(std::move(x)), yaul::bad_get);
      YAUL_VARIANT_CHECK_THROWS(yaul::get<S01>(std::move(x)), yaul::bad_get);
    }
    {
      X01&& x{S01{X01{234}, X01{'d'}}};
      S01&& s = yaul::get<S01>(std::move(x));
      YAUL_VARIANT_CHECK(s.left == X01{234});
      YAUL_VARIANT_CHECK(s.right == X01{'d'});
      YAUL_VARIANT_CHECK_THROWS(yaul::get<int>(std::move(x)), yaul::bad_get);
      YAUL_VARIANT_CHECK_THROWS(yaul::get<char>(std::move(x)), yaul::bad_get);
    }
  }

  // X01 const&&
  {
    {
      X01 const&& x{123};
      int const&& i = yaul::get<int>(std::move(x));
      YAUL_VARIANT_CHECK_EQUALS(i, 123);
      YAUL_VARIANT_CHECK_THROWS(yaul::get<char>(std::move(x)), yaul::bad_get);
      YAUL_VARIANT_CHECK_THROWS(yaul::get<S01>(std::move(x)), yaul::bad_get);
    }
    {
      X01 const&& x{'a'};
      char const&& c = yaul::get<char>(std::move(x));
      YAUL_VARIANT_CHECK_EQUALS(c, 'a');
      YAUL_VARIANT_CHECK_THROWS(yaul::get<int>(std::move(x)), yaul::bad_get);
      YAUL_VARIANT_CHECK_THROWS(yaul::get<S01>(std::move(x)), yaul::bad_get);
    }
    {
      X01 const&& x{S01{X01{234}, X01{'d'}}};
      S01 const&& s = yaul::get<S01>(std::move(x));
      YAUL_VARIANT_CHECK(s.left == X01{234});
      YAUL_VARIANT_CHECK(s.right == X01{'d'});
      YAUL_VARIANT_CHECK_THROWS(yaul::get<int>(std::move(x)), yaul::bad_get);
      YAUL_VARIANT_CHECK_THROWS(yaul::get<char>(std::move(x)), yaul::bad_get);
    }
  }
}

void test__get__02()
{
  // X02&
  {
    {
      X02 x{123};
      int& i = yaul::get<int>(x);
      YAUL_VARIANT_CHECK_EQUALS(i, 123);
      YAUL_VARIANT_CHECK_THROWS(yaul::get<char>(x), yaul::bad_get);
      YAUL_VARIANT_CHECK_THROWS(yaul::get<S02>(x), yaul::bad_get);
    }
    {
      X02 x{'a'};
      char& c = yaul::get<char>(x);
      YAUL_VARIANT_CHECK_EQUALS(c, 'a');
      YAUL_VARIANT_CHECK_THROWS(yaul::get<int>(x), yaul::bad_get);
      YAUL_VARIANT_CHECK_THROWS(yaul::get<S02>(x), yaul::bad_get);
    }
    {
      X02 x{S02{X02{234}, X02{'d'}}};
      S02& s = yaul::get<S02>(x);
      YAUL_VARIANT_CHECK(std::get<0>(s) == X02{234});
      std::get<0>(s) = X02{123};
      std::get<1>(s) = 'a';
      YAUL_VARIANT_CHECK(std::get<0>(yaul::get<S02>(x)) == X02{123});
      YAUL_VARIANT_CHECK(std::get<1>(yaul::get<S02>(x)) == X02{'a'});
      YAUL_VARIANT_CHECK_THROWS(yaul::get<int>(x), yaul::bad_get);
      YAUL_VARIANT_CHECK_THROWS(yaul::get<char>(x), yaul::bad_get);
    }
  }

  // X02 const&
  {
    {
      X02 const x{123};
      int const& i = yaul::get<int>(x);
      YAUL_VARIANT_CHECK_EQUALS(i, 123);
      YAUL_VARIANT_CHECK_THROWS(yaul::get<char>(x), yaul::bad_get);
      YAUL_VARIANT_CHECK_THROWS(yaul::get<S02>(x), yaul::bad_get);
    }
    {
      X02 const x{'a'};
      char const& c = yaul::get<char>(x);
      YAUL_VARIANT_CHECK_EQUALS(c, 'a');
      YAUL_VARIANT_CHECK_THROWS(yaul::get<int>(x), yaul::bad_get);
      YAUL_VARIANT_CHECK_THROWS(yaul::get<S02>(x), yaul::bad_get);
    }
    {
      X02 const x{S02{X02{234}, X02{'d'}}};
      S02 const& s = yaul::get<S02>(x);
      YAUL_VARIANT_CHECK(std::get<0>(s) == X02{234});
      YAUL_VARIANT_CHECK(std::get<1>(s) == X02{'d'});
      YAUL_VARIANT_CHECK_THROWS(yaul::get<int>(x), yaul::bad_get);
      YAUL_VARIANT_CHECK_THROWS(yaul::get<char>(x), yaul::bad_get);
    }
  }

  // X02&&
  {
    {
      X02&& x{123};
      int&& i = yaul::get<int>(std::move(x));
      YAUL_VARIANT_CHECK_EQUALS(i, 123);
      YAUL_VARIANT_CHECK_THROWS(yaul::get<char>(std::move(x)), yaul::bad_get);
      YAUL_VARIANT_CHECK_THROWS(yaul::get<S02>(std::move(x)), yaul::bad_get);
    }
    {
      X02&& x{'a'};
      char&& c = yaul::get<char>(std::move(x));
      YAUL_VARIANT_CHECK_EQUALS(c, 'a');
      YAUL_VARIANT_CHECK_THROWS(yaul::get<int>(std::move(x)), yaul::bad_get);
      YAUL_VARIANT_CHECK_THROWS(yaul::get<S02>(std::move(x)), yaul::bad_get);
    }
    {
      X02&& x{S02{X02{234}, X02{'d'}}};
      S02&& s = yaul::get<S02>(std::move(x));
      YAUL_VARIANT_CHECK(std::get<0>(std::move(s)) == X02{234});
      YAUL_VARIANT_CHECK(std::get<1>(std::move(s)) == X02{'d'});
      YAUL_VARIANT_CHECK_THROWS(yaul::get<int>(std::move(x)), yaul::bad_get);
      YAUL_VARIANT_CHECK_THROWS(yaul::get<char>(std::move(x)), yaul::bad_get);
    }
  }

  // X02 const&&
  {
    {
      X02 const&& x{123};
      int const&& i = yaul::get<int>(std::move(x));
      YAUL_VARIANT_CHECK_EQUALS(i, 123);
      YAUL_VARIANT_CHECK_THROWS(yaul::get<char>(std::move(x)), yaul::bad_get);
      YAUL_VARIANT_CHECK_THROWS(yaul::get<S02>(std::move(x)), yaul::bad_get);
    }
    {
      X02 const&& x{'a'};
      char const&& c = yaul::get<char>(std::move(x));
      YAUL_VARIANT_CHECK_EQUALS(c, 'a');
      YAUL_VARIANT_CHECK_THROWS(yaul::get<int>(std::move(x)), yaul::bad_get);
      YAUL_VARIANT_CHECK_THROWS(yaul::get<S02>(std::move(x)), yaul::bad_get);
    }
    {
      X02 const&& x{S02{X02{234}, X02{'d'}}};
      S02 const&& s = yaul::get<S02>(std::move(x));
      YAUL_VARIANT_CHECK(std::get<0>(std::move(s)) == X02{234});
      YAUL_VARIANT_CHECK(std::get<1>(std::move(s)) == X02{'d'});
      YAUL_VARIANT_CHECK_THROWS(yaul::get<int>(std::move(x)), yaul::bad_get);
      YAUL_VARIANT_CHECK_THROWS(yaul::get<char>(std::move(x)), yaul::bad_get);
    }
  }
}


int main()
{
  test__relaxed_get__01();
  test__strict_get__01();
  test__get__01();
  return YAUL_VARIANT_TEST_EXIT_CODE;
}
