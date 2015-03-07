// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <yaul/variant/recursive_variant.hpp>
#include <yaul/variant/test_config.hpp>
#include <yaul/variant/apply_visitor.hpp>
#include <string>
#include <vector>

void test__make_recursive_variant__01()
{
  using std::is_same;
  using yaul::make_recursive_variant;
  using yaul::variant;
  using yaul::recursive_variant_;
  using yaul::detail::variant::recursive_flag;

  static_assert(is_same<make_recursive_variant<int,recursive_variant_, char>::type, variant<recursive_flag<int>,recursive_variant_,char> >::value, "");
}

void test__recursive_variant__01()
{
  using std::is_same;
  using yaul::make_recursive_variant;
  using yaul::variant;
  using yaul::recursive_variant_;
  using yaul::detail::variant::recursive_flag;

  {
    typedef make_recursive_variant<int, char, recursive_variant_>::type V;
    V v{};
    YAUL_VARIANT_CHECK_EQUALS(v.which(), 0);
    v = 'a';
    YAUL_VARIANT_CHECK_EQUALS(v.which(), 1);
    v = V{3};
    YAUL_VARIANT_CHECK_EQUALS(v.which(), 0);
  }
}

typedef yaul::make_recursive_variant<
          int
       , char
       , std::string
       , std::vector<yaul::recursive_variant_>
>::type X02;

struct V02
{
  static int i;
  static char c;
  static std::string s;

  static void reset() { i = 0; c = '\0'; s.clear(); }

  typedef int result_type;

  result_type operator()(int& a) &                    { i = a; return 0x111; }
  result_type operator()(int const& a) &              { i = a; return 0x112; }
  result_type operator()(int&& a) &                   { i = std::move(a); return 0x113; }

  result_type operator()(char& a) &                   { c = a; return 0x121; }
  result_type operator()(char const& a) &             { c = a; return 0x122; }
  result_type operator()(char&& a) &                  { c = std::move(a); return 0x123; }

  result_type operator()(std::string& a) &            { s = a; return 0x131; }
  result_type operator()(std::string const& a) &      { s = a; return 0x132; }
  result_type operator()(std::string&& a) &           { s = std::move(a); return 0x133; }

  result_type operator()(std::vector<X02>& a) &       { return yaul::apply_visitor(*this, a.back()); }
  result_type operator()(std::vector<X02> const& a) & { return yaul::apply_visitor(*this, a.back()); }
  result_type operator()(std::vector<X02>&& a) &      { return yaul::apply_visitor(*this, std::move(a).back()); }

  result_type operator()(int& a) const&               { i = a; return 0x211; }
  result_type operator()(int const& a) const&         { i = a; return 0x212; }
  result_type operator()(int&& a) const&              { i = std::move(a); return 0x213; }

  result_type operator()(char& a) const&              { c = a; return 0x221; }
  result_type operator()(char const& a) const&        { c = a; return 0x222; }
  result_type operator()(char&& a) const&             { c = std::move(a); return 0x223; }

  result_type operator()(std::string& a) const&       { s = a; return 0x231; }
  result_type operator()(std::string const& a) const& { s = a; return 0x232; }
  result_type operator()(std::string&& a) const&      { s = std::move(a); return 0x233; }

  result_type operator()(std::vector<X02>& a) const&  { return yaul::apply_visitor(*this, a.back()); }
  result_type operator()(std::vector<X02> const& a) const& { return yaul::apply_visitor(*this, a.back()); }
  result_type operator()(std::vector<X02>&& a) const& { return yaul::apply_visitor(*this, std::move(a).back()); }

  result_type operator()(int& a) &&                   { i = a; return 0x311; }
  result_type operator()(int const& a) &&             { i = a; return 0x312; }
  result_type operator()(int&& a) &&                  { i = std::move(a); return 0x313; }

  result_type operator()(char& a) &&                  { c = a; return 0x321; }
  result_type operator()(char const& a) &&            { c = a; return 0x322; }
  result_type operator()(char&& a) &&                 { c = std::move(a); return 0x323; }

  result_type operator()(std::string& a) &&           { s = a; return 0x331; }
  result_type operator()(std::string const& a) &&     { s = a; return 0x332; }
  result_type operator()(std::string&& a) &&          { s = std::move(a); return 0x333; }

  result_type operator()(std::vector<X02>& a) &&      { return yaul::apply_visitor(std::move(*this), a.back()); }
  result_type operator()(std::vector<X02> const& a) && { return yaul::apply_visitor(std::move(*this), a.back()); }
  result_type operator()(std::vector<X02>&& a) &&     { return yaul::apply_visitor(std::move(*this), std::move(a).back()); }
};

int V02::i;
char V02::c;
std::string V02::s;

void test__recursive_variant__02()
{
  using yaul::apply_visitor;

  // V02&
  {
    V02 v;
    // X02&
    {
      {
        X02 x{123};
        V02::reset();
        YAUL_VARIANT_CHECK_EQUALS(apply_visitor(v,x), 0x111);
        YAUL_VARIANT_CHECK_EQUALS(V02::i, 123);
      }

      {
        X02 x{'a'};
        V02::reset();
        YAUL_VARIANT_CHECK_EQUALS(apply_visitor(v,x), 0x121);
        YAUL_VARIANT_CHECK_EQUALS(V02::c, 'a');
      }

      {
        X02 x{"abc"};
        V02::reset();
        YAUL_VARIANT_CHECK_EQUALS(apply_visitor(v,x), 0x131);
        YAUL_VARIANT_CHECK_EQUALS(V02::s, "abc");
      }

      {
        X02 x{std::vector<X02>{X02{124}, X02{'b'}, X02{"def"}}};
        V02::reset();
        YAUL_VARIANT_CHECK_EQUALS(apply_visitor(v,x), 0x131);
        YAUL_VARIANT_CHECK_EQUALS(V02::s, "def");
      }
    }

    // X02 const&
    {
      {
        X02 const x{123};
        V02::reset();
        YAUL_VARIANT_CHECK_EQUALS(apply_visitor(v,x), 0x112);
        YAUL_VARIANT_CHECK_EQUALS(V02::i, 123);
      }

      {
        X02 const x{'a'};
        V02::reset();
        YAUL_VARIANT_CHECK_EQUALS(apply_visitor(v,x), 0x122);
        YAUL_VARIANT_CHECK_EQUALS(V02::c, 'a');
      }

      {
        X02 const x{"abc"};
        V02::reset();
        YAUL_VARIANT_CHECK_EQUALS(apply_visitor(v,x), 0x132);
        YAUL_VARIANT_CHECK_EQUALS(V02::s, "abc");
      }

      {
        X02 const x{std::vector<X02>{X02{124}, X02{'b'}, X02{"def"}}};
        V02::reset();
        YAUL_VARIANT_CHECK_EQUALS(apply_visitor(v,x), 0x132);
        YAUL_VARIANT_CHECK_EQUALS(V02::s, "def");
      }
    }

    // X02&&
    {
      {
        V02::reset();
        YAUL_VARIANT_CHECK_EQUALS(apply_visitor(v,X02{123}), 0x113);
        YAUL_VARIANT_CHECK_EQUALS(V02::i, 123);
      }

      {
        V02::reset();
        YAUL_VARIANT_CHECK_EQUALS(apply_visitor(v,X02{'a'}), 0x123);
        YAUL_VARIANT_CHECK_EQUALS(V02::c, 'a');
      }

      {
        V02::reset();
        YAUL_VARIANT_CHECK_EQUALS(apply_visitor(v,X02{"abc"}), 0x133);
        YAUL_VARIANT_CHECK_EQUALS(V02::s, "abc");
      }

      {
        V02::reset();
        YAUL_VARIANT_CHECK_EQUALS(apply_visitor(v,X02{std::vector<X02>{X02{124}, X02{'b'}, X02{"def"}}}), 0x133);
        YAUL_VARIANT_CHECK_EQUALS(V02::s, "def");
      }
    }
  }

  //
  // V02 const&
  //
  {
    V02 const v{};
    // X02&
    {
      {
        X02 x{123};
        V02::reset();
        YAUL_VARIANT_CHECK_EQUALS(apply_visitor(v,x), 0x211);
        YAUL_VARIANT_CHECK_EQUALS(V02::i, 123);
      }

      {
        X02 x{'a'};
        V02::reset();
        YAUL_VARIANT_CHECK_EQUALS(apply_visitor(v,x), 0x221);
        YAUL_VARIANT_CHECK_EQUALS(V02::c, 'a');
      }

      {
        X02 x{"abc"};
        V02::reset();
        YAUL_VARIANT_CHECK_EQUALS(apply_visitor(v,x), 0x231);
        YAUL_VARIANT_CHECK_EQUALS(V02::s, "abc");
      }

      {
        X02 x{std::vector<X02>{X02{124}, X02{'b'}, X02{"def"}}};
        V02::reset();
        YAUL_VARIANT_CHECK_EQUALS(apply_visitor(v,x), 0x231);
        YAUL_VARIANT_CHECK_EQUALS(V02::s, "def");
      }
    }

    // X02 const&
    {
      {
        X02 const x{123};
        V02::reset();
        YAUL_VARIANT_CHECK_EQUALS(apply_visitor(v,x), 0x212);
        YAUL_VARIANT_CHECK_EQUALS(V02::i, 123);
      }

      {
        X02 const x{'a'};
        V02::reset();
        YAUL_VARIANT_CHECK_EQUALS(apply_visitor(v,x), 0x222);
        YAUL_VARIANT_CHECK_EQUALS(V02::c, 'a');
      }

      {
        X02 const x{"abc"};
        V02::reset();
        YAUL_VARIANT_CHECK_EQUALS(apply_visitor(v,x), 0x232);
        YAUL_VARIANT_CHECK_EQUALS(V02::s, "abc");
      }

      {
        X02 const x{std::vector<X02>{X02{124}, X02{'b'}, X02{"def"}}};
        V02::reset();
        YAUL_VARIANT_CHECK_EQUALS(apply_visitor(v,x), 0x232);
        YAUL_VARIANT_CHECK_EQUALS(V02::s, "def");
      }
    }

    // X02&&
    {
      {
        V02::reset();
        YAUL_VARIANT_CHECK_EQUALS(apply_visitor(v,X02{123}), 0x213);
        YAUL_VARIANT_CHECK_EQUALS(V02::i, 123);
      }

      {
        V02::reset();
        YAUL_VARIANT_CHECK_EQUALS(apply_visitor(v,X02{'a'}), 0x223);
        YAUL_VARIANT_CHECK_EQUALS(V02::c, 'a');
      }

      {
        V02::reset();
        YAUL_VARIANT_CHECK_EQUALS(apply_visitor(v,X02{"abc"}), 0x233);
        YAUL_VARIANT_CHECK_EQUALS(V02::s, "abc");
      }

      {
        V02::reset();
        YAUL_VARIANT_CHECK_EQUALS(apply_visitor(v,X02{std::vector<X02>{X02{124}, X02{'b'}, X02{"def"}}}), 0x233);
        YAUL_VARIANT_CHECK_EQUALS(V02::s, "def");
      }
    }
  }

  //
  // V02&&
  //
  {
    // X02&
    {
      {
        X02 x{123};
        V02::reset();
        YAUL_VARIANT_CHECK_EQUALS(apply_visitor(V02{},x), 0x311);
        YAUL_VARIANT_CHECK_EQUALS(V02::i, 123);
      }

      {
        X02 x{'a'};
        V02::reset();
        YAUL_VARIANT_CHECK_EQUALS(apply_visitor(V02{},x), 0x321);
        YAUL_VARIANT_CHECK_EQUALS(V02::c, 'a');
      }

      {
        X02 x{"abc"};
        V02::reset();
        YAUL_VARIANT_CHECK_EQUALS(apply_visitor(V02{},x), 0x331);
        YAUL_VARIANT_CHECK_EQUALS(V02::s, "abc");
      }

      {
        X02 x{std::vector<X02>{X02{124}, X02{'b'}, X02{"def"}}};
        V02::reset();
        YAUL_VARIANT_CHECK_EQUALS(apply_visitor(V02{},x), 0x331);
        YAUL_VARIANT_CHECK_EQUALS(V02::s, "def");
      }
    }

    // X02 const&
    {
      {
        X02 const x{123};
        V02::reset();
        YAUL_VARIANT_CHECK_EQUALS(apply_visitor(V02{},x), 0x312);
        YAUL_VARIANT_CHECK_EQUALS(V02::i, 123);
      }

      {
        X02 const x{'a'};
        V02::reset();
        YAUL_VARIANT_CHECK_EQUALS(apply_visitor(V02{},x), 0x322);
        YAUL_VARIANT_CHECK_EQUALS(V02::c, 'a');
      }

      {
        X02 const x{"abc"};
        V02::reset();
        YAUL_VARIANT_CHECK_EQUALS(apply_visitor(V02{},x), 0x332);
        YAUL_VARIANT_CHECK_EQUALS(V02::s, "abc");
      }

      {
        X02 const x{std::vector<X02>{X02{124}, X02{'b'}, X02{"def"}}};
        V02::reset();
        YAUL_VARIANT_CHECK_EQUALS(apply_visitor(V02{},x), 0x332);
        YAUL_VARIANT_CHECK_EQUALS(V02::s, "def");
      }
    }

    // X02&&
    {
      {
        V02::reset();
        YAUL_VARIANT_CHECK_EQUALS(apply_visitor(V02{},X02{123}), 0x313);
        YAUL_VARIANT_CHECK_EQUALS(V02::i, 123);
      }

      {
        V02::reset();
        YAUL_VARIANT_CHECK_EQUALS(apply_visitor(V02{},X02{'a'}), 0x323);
        YAUL_VARIANT_CHECK_EQUALS(V02::c, 'a');
      }

      {
        V02::reset();
        YAUL_VARIANT_CHECK_EQUALS(apply_visitor(V02{},X02{"abc"}), 0x333);
        YAUL_VARIANT_CHECK_EQUALS(V02::s, "abc");
      }

      {
        V02::reset();
        YAUL_VARIANT_CHECK_EQUALS(apply_visitor(V02{},X02{std::vector<X02>{X02{124}, X02{'b'}, X02{"def"}}}), 0x333);
        YAUL_VARIANT_CHECK_EQUALS(V02::s, "def");
      }
    }
  }
}

int main()
{
  test__make_recursive_variant__01();
  test__recursive_variant__01();
  return YAUL_VARIANT_TEST_EXIT_CODE;
}
