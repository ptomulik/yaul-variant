// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <yaul/variant/detail/apply_visitor_unary.hpp>
#include <yaul/variant/variant.hpp>
#include <yaul/variant/test_config.hpp>

void test__apply_visitor__01()
{
  using yaul::variant;
  struct visitor
  {
    typedef int result_type;

    mutable int   last_i;
    mutable char  last_c;
    visitor() noexcept : last_i{0}, last_c{'\0'}    { }
    int operator()(int& i) & noexcept               { last_i = i; return 0x011; }
    int operator()(int const& i) & noexcept         { last_i = i; return 0x012; }
    int operator()(int&& i) & noexcept              { last_i = i; return 0x013; }
    int operator()(int& i) const & noexcept         { last_i = i; return 0x021; }
    int operator()(int const& i) const & noexcept   { last_i = i; return 0x022; }
    int operator()(int&& i) const & noexcept        { last_i = i; return 0x023; }
    int operator()(int& i) && noexcept              { last_i = i; return 0x031; }
    int operator()(int const& i) && noexcept        { last_i = i; return 0x032; }
    int operator()(int&& i) && noexcept             { last_i = i; return 0x033; }

    int operator()(char& c) & noexcept              { last_c = c; return 0x111; }
    int operator()(char const& c) & noexcept        { last_c = c; return 0x112; }
    int operator()(char&& c) & noexcept             { last_c = c; return 0x113; }
    int operator()(char& c) const & noexcept        { last_c = c; return 0x121; }
    int operator()(char const& c) const & noexcept  { last_c = c; return 0x122; }
    int operator()(char&& c) const & noexcept       { last_c = c; return 0x123; }
    int operator()(char& c) && noexcept             { last_c = c; return 0x131; }
    int operator()(char const& c) && noexcept       { last_c = c; return 0x132; }
    int operator()(char&& c) && noexcept            { last_c = c; return 0x133; }
  };

  {
    visitor             vis;
    variant<int,char>   var{1};
    YAUL_VARIANT_CHECK_EQUALS(yaul::apply_visitor(vis,var), 0x011);
    YAUL_VARIANT_CHECK_EQUALS(vis.last_i, 1);
    static_assert(noexcept(yaul::apply_visitor(vis,var)), "");
  }
  {
    visitor const       vis;
    variant<int,char>   var{2};
    YAUL_VARIANT_CHECK_EQUALS(yaul::apply_visitor(vis,var), 0x021);
    YAUL_VARIANT_CHECK_EQUALS(vis.last_i, 2);
    static_assert(noexcept(yaul::apply_visitor(vis,var)), "");
  }
  {
    visitor             vis;
    variant<int,char>   var{3};
    YAUL_VARIANT_CHECK_EQUALS(yaul::apply_visitor(std::move(vis),var), 0x031);
    YAUL_VARIANT_CHECK_EQUALS(vis.last_i, 3);
    static_assert(noexcept(yaul::apply_visitor(std::move(vis),var)), "");
  }

  {
    visitor             vis;
    variant<int,char>  const var{4};
    YAUL_VARIANT_CHECK_EQUALS(yaul::apply_visitor(vis,var), 0x012);
    YAUL_VARIANT_CHECK_EQUALS(vis.last_i, 4);
    static_assert(noexcept(yaul::apply_visitor(vis,var)), "");
  }
  {
    visitor const       vis;
    variant<int,char> const  var{5};
    YAUL_VARIANT_CHECK_EQUALS(yaul::apply_visitor(vis,var), 0x022);
    YAUL_VARIANT_CHECK_EQUALS(vis.last_i, 5);
    static_assert(noexcept(yaul::apply_visitor(vis,var)), "");
  }
  {
    visitor             vis;
    variant<int,char> const  var{6};
    YAUL_VARIANT_CHECK_EQUALS(yaul::apply_visitor(std::move(vis),var), 0x032);
    YAUL_VARIANT_CHECK_EQUALS(vis.last_i, 6);
    static_assert(noexcept(yaul::apply_visitor(std::move(vis),var)), "");
  }

  {
    visitor             vis;
    variant<int,char>   var{7};
    YAUL_VARIANT_CHECK_EQUALS(yaul::apply_visitor(vis,std::move(var)), 0x013);
    YAUL_VARIANT_CHECK_EQUALS(vis.last_i, 7);
    static_assert(noexcept(yaul::apply_visitor(vis,std::move(var))), "");
  }
  {
    visitor const       vis;
    variant<int,char>   var{8};
    YAUL_VARIANT_CHECK_EQUALS(yaul::apply_visitor(vis,std::move(var)), 0x023);
    YAUL_VARIANT_CHECK_EQUALS(vis.last_i, 8);
    static_assert(noexcept(yaul::apply_visitor(vis,std::move(var))), "");
  }
  {
    visitor             vis;
    variant<int,char>   var{9};
    YAUL_VARIANT_CHECK_EQUALS(yaul::apply_visitor(std::move(vis),std::move(var)), 0x033);
    YAUL_VARIANT_CHECK_EQUALS(vis.last_i, 9);
    static_assert(noexcept(yaul::apply_visitor(std::move(vis),std::move(var))), "");
  }

  {
    visitor             vis;
    variant<int,char>   var{'a'};
    YAUL_VARIANT_CHECK_EQUALS(yaul::apply_visitor(vis,var), 0x111);
    YAUL_VARIANT_CHECK_EQUALS(vis.last_c, 'a');
    static_assert(noexcept(yaul::apply_visitor(vis,var)), "");
  }
  {
    visitor const       vis;
    variant<int,char>   var{'b'};
    YAUL_VARIANT_CHECK_EQUALS(yaul::apply_visitor(vis,var), 0x121);
    YAUL_VARIANT_CHECK_EQUALS(vis.last_c, 'b');
    static_assert(noexcept(yaul::apply_visitor(vis,var)), "");
  }
  {
    visitor             vis;
    variant<int,char>   var{'c'};
    YAUL_VARIANT_CHECK_EQUALS(yaul::apply_visitor(std::move(vis),var), 0x131);
    YAUL_VARIANT_CHECK_EQUALS(vis.last_c, 'c');
    static_assert(noexcept(yaul::apply_visitor(std::move(vis),var)), "");
  }

  {
    visitor             vis;
    variant<int,char>  const var{'d'};
    YAUL_VARIANT_CHECK_EQUALS(yaul::apply_visitor(vis,var), 0x112);
    YAUL_VARIANT_CHECK_EQUALS(vis.last_c, 'd');
    static_assert(noexcept(yaul::apply_visitor(vis,var)), "");
  }
  {
    visitor const       vis;
    variant<int,char> const  var{'e'};
    YAUL_VARIANT_CHECK_EQUALS(yaul::apply_visitor(vis,var), 0x122);
    YAUL_VARIANT_CHECK_EQUALS(vis.last_c, 'e');
    static_assert(noexcept(yaul::apply_visitor(vis,var)), "");
  }
  {
    visitor             vis;
    variant<int,char> const  var{'f'};
    YAUL_VARIANT_CHECK_EQUALS(yaul::apply_visitor(std::move(vis),var), 0x132);
    YAUL_VARIANT_CHECK_EQUALS(vis.last_c, 'f');
    static_assert(noexcept(yaul::apply_visitor(std::move(vis),var)), "");
  }

  {
    visitor             vis;
    variant<int,char>   var{'g'};
    YAUL_VARIANT_CHECK_EQUALS(yaul::apply_visitor(vis,std::move(var)), 0x113);
    YAUL_VARIANT_CHECK_EQUALS(vis.last_c, 'g');
    static_assert(noexcept(yaul::apply_visitor(vis,std::move(var))), "");
  }
  {
    visitor const       vis;
    variant<int,char>   var{'h'};
    YAUL_VARIANT_CHECK_EQUALS(yaul::apply_visitor(vis,std::move(var)), 0x123);
    YAUL_VARIANT_CHECK_EQUALS(vis.last_c, 'h');
    static_assert(noexcept(yaul::apply_visitor(vis,std::move(var))), "");
  }
  {
    visitor             vis;
    variant<int,char>   var{'i'};
    YAUL_VARIANT_CHECK_EQUALS(yaul::apply_visitor(std::move(vis),std::move(var)), 0x133);
    YAUL_VARIANT_CHECK_EQUALS(vis.last_c, 'i');
    static_assert(noexcept(yaul::apply_visitor(std::move(vis),std::move(var))), "");
  }
}

void test__apply_visitor__02()
{
  using yaul::variant;
  struct visitor
  {
    typedef int result_type;

    int operator()(int&) &                { return 0x011; }
    int operator()(int const&) &          { return 0x012; }
    int operator()(int&&) &               { return 0x013; }
    int operator()(int&) const &          { return 0x021; }
    int operator()(int const&) const &    { return 0x022; }
    int operator()(int&&) const &         { return 0x023; }
    int operator()(int&) &&               { return 0x031; }
    int operator()(int const&) &&         { return 0x032; }
    int operator()(int&&) &&              { return 0x033; }

    int operator()(char&) &               { return 0x111; }
    int operator()(char const&) &         { return 0x112; }
    int operator()(char&&) &              { return 0x113; }
    int operator()(char&) const &         { return 0x121; }
    int operator()(char const&) const &   { return 0x122; }
    int operator()(char&&) const &        { return 0x123; }
    int operator()(char&) &&              { return 0x131; }
    int operator()(char const&) &&        { return 0x132; }
    int operator()(char&&) &&             { return 0x133; }
  };

  {
    visitor             vis;
    variant<int,char>   var{2};
    YAUL_VARIANT_CHECK_EQUALS(yaul::apply_visitor(vis,var), 0x011);
    static_assert(!noexcept(yaul::apply_visitor(vis,var)), "");
  }
  {
    visitor const       vis{};
    variant<int,char>   var{2};
    YAUL_VARIANT_CHECK_EQUALS(yaul::apply_visitor(vis,var), 0x021);
    static_assert(!noexcept(yaul::apply_visitor(vis,var)), "");
  }
  {
    visitor             vis;
    variant<int,char>   var{2};
    YAUL_VARIANT_CHECK_EQUALS(yaul::apply_visitor(std::move(vis),var), 0x031);
    static_assert(!noexcept(yaul::apply_visitor(std::move(vis),var)), "");
  }

  {
    visitor             vis;
    variant<int,char>  const var{2};
    YAUL_VARIANT_CHECK_EQUALS(yaul::apply_visitor(vis,var), 0x012);
    static_assert(!noexcept(yaul::apply_visitor(vis,var)), "");
  }
  {
    visitor const       vis{};
    variant<int,char> const  var{2};
    YAUL_VARIANT_CHECK_EQUALS(yaul::apply_visitor(vis,var), 0x022);
    static_assert(!noexcept(yaul::apply_visitor(vis,var)), "");
  }
  {
    visitor             vis;
    variant<int,char> const  var{2};
    YAUL_VARIANT_CHECK_EQUALS(yaul::apply_visitor(std::move(vis),var), 0x032);
    static_assert(!noexcept(yaul::apply_visitor(std::move(vis),var)), "");
  }

  {
    visitor             vis;
    variant<int,char>   var{2};
    YAUL_VARIANT_CHECK_EQUALS(yaul::apply_visitor(vis,std::move(var)), 0x013);
    static_assert(!noexcept(yaul::apply_visitor(vis,std::move(var))), "");
  }
  {
    visitor const       vis{};
    variant<int,char>   var{2};
    YAUL_VARIANT_CHECK_EQUALS(yaul::apply_visitor(vis,std::move(var)), 0x023);
    static_assert(!noexcept(yaul::apply_visitor(vis,std::move(var))), "");
  }
  {
    visitor             vis;
    variant<int,char>   var{2};
    YAUL_VARIANT_CHECK_EQUALS(yaul::apply_visitor(std::move(vis),std::move(var)), 0x033);
    static_assert(!noexcept(yaul::apply_visitor(std::move(vis),std::move(var))), "");
  }

  {
    visitor             vis;
    variant<int,char>   var{'a'};
    YAUL_VARIANT_CHECK_EQUALS(yaul::apply_visitor(vis,var), 0x111);
    static_assert(!noexcept(yaul::apply_visitor(vis,var)), "");
  }
  {
    visitor const       vis{};
    variant<int,char>   var{'a'};
    YAUL_VARIANT_CHECK_EQUALS(yaul::apply_visitor(vis,var), 0x121);
    static_assert(!noexcept(yaul::apply_visitor(vis,var)), "");
  }
  {
    visitor             vis;
    variant<int,char>   var{'a'};
    YAUL_VARIANT_CHECK_EQUALS(yaul::apply_visitor(std::move(vis),var), 0x131);
    static_assert(!noexcept(yaul::apply_visitor(std::move(vis),var)), "");
  }

  {
    visitor             vis;
    variant<int,char>  const var{'a'};
    YAUL_VARIANT_CHECK_EQUALS(yaul::apply_visitor(vis,var), 0x112);
    static_assert(!noexcept(yaul::apply_visitor(vis,var)), "");
  }
  {
    visitor const       vis{};
    variant<int,char> const  var{'a'};
    YAUL_VARIANT_CHECK_EQUALS(yaul::apply_visitor(vis,var), 0x122);
    static_assert(!noexcept(yaul::apply_visitor(vis,var)), "");
  }
  {
    visitor             vis;
    variant<int,char> const  var{'a'};
    YAUL_VARIANT_CHECK_EQUALS(yaul::apply_visitor(std::move(vis),var), 0x132);
    static_assert(!noexcept(yaul::apply_visitor(std::move(vis),var)), "");
  }

  {
    visitor             vis;
    variant<int,char>   var{'a'};
    YAUL_VARIANT_CHECK_EQUALS(yaul::apply_visitor(vis,std::move(var)), 0x113);
    static_assert(!noexcept(yaul::apply_visitor(vis,std::move(var))), "");
  }
  {
    visitor const       vis{};
    variant<int,char>   var{'a'};
    YAUL_VARIANT_CHECK_EQUALS(yaul::apply_visitor(vis,std::move(var)), 0x123);
    static_assert(!noexcept(yaul::apply_visitor(vis,std::move(var))), "");
  }
  {
    visitor             vis;
    variant<int,char>   var{'a'};
    YAUL_VARIANT_CHECK_EQUALS(yaul::apply_visitor(std::move(vis),std::move(var)), 0x133);
    static_assert(!noexcept(yaul::apply_visitor(std::move(vis),std::move(var))), "");
  }
}

int main()
{
  test__apply_visitor__01();
  test__apply_visitor__02();
  return YAUL_VARIANT_TEST_EXIT_CODE;
}
