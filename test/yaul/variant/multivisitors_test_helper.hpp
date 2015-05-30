// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

// yaul/variant/detail/multivisitors_test_helper.hpp

/** // doc: yaul/variant/multivisitors_test_helper.hpp {{{
 * \file yaul/variant/multivisitors_test_helper.hpp
 * \todo Write documentation
 */ // }}}
#ifndef YAUL_VARIANT_MULTIVISITORS_TEST_HELPER_HPP
#define YAUL_VARIANT_MULTIVISITORS_TEST_HELPER_HPP

struct V01
{
  static int i1;
  static int i2;
  static int i3;
  typedef int result_type;

  template<typename T1, typename T2, typename T3>
    int operator()(T1&&, T2&&, T3&&) & noexcept         { return -1; }
  //
  // & (*this)
  //
  int operator()(int& a1, int& a2, int& a3) & noexcept                      { i1 = a1; i2 = a2; i3 = a3; return 0x1111111; }
  int operator()(int& a1, int& a2, int const& a3) & noexcept                { i1 = a1; i2 = a2; i3 = a3; return 0x1111112; }
  int operator()(int& a1, int& a2, int&& a3) & noexcept                     { i1 = a1; i2 = a2; i3 = a3; return 0x1111113; }

  int operator()(int& a1, int const& a2, int& a3) & noexcept                { i1 = a1; i2 = a2; i3 = a3; return 0x1111211; }
  int operator()(int& a1, int const& a2, int const& a3) & noexcept          { i1 = a1; i2 = a2; i3 = a3; return 0x1111212; }
  int operator()(int& a1, int const& a2, int&& a3) & noexcept               { i1 = a1; i2 = a2; i3 = a3; return 0x1111213; }

  int operator()(int& a1, int&& a2, int& a3) & noexcept                     { i1 = a1; i2 = a2; i3 = a3; return 0x1111311; }
  int operator()(int& a1, int&& a2, int const& a3) & noexcept               { i1 = a1; i2 = a2; i3 = a3; return 0x1111312; }
  int operator()(int& a1, int&& a2, int&& a3) & noexcept                    { i1 = a1; i2 = a2; i3 = a3; return 0x1111313; }

  int operator()(int const& a1, int& a2, int& a3) & noexcept                { i1 = a1; i2 = a2; i3 = a3; return 0x1121111; }
  int operator()(int const& a1, int& a2, int const& a3) & noexcept          { i1 = a1; i2 = a2; i3 = a3; return 0x1121112; }
  int operator()(int const& a1, int& a2, int&& a3) & noexcept               { i1 = a1; i2 = a2; i3 = a3; return 0x1121113; }

  int operator()(int const& a1, int const& a2, int& a3) & noexcept          { i1 = a1; i2 = a2; i3 = a3; return 0x1121211; }
  int operator()(int const& a1, int const& a2, int const& a3) & noexcept    { i1 = a1; i2 = a2; i3 = a3; return 0x1121212; }
  int operator()(int const& a1, int const& a2, int&& a3) & noexcept         { i1 = a1; i2 = a2; i3 = a3; return 0x1121213; }

  int operator()(int const& a1, int&& a2, int& a3) & noexcept               { i1 = a1; i2 = a2; i3 = a3; return 0x1121311; }
  int operator()(int const& a1, int&& a2, int const& a3) & noexcept         { i1 = a1; i2 = a2; i3 = a3; return 0x1121312; }
  int operator()(int const& a1, int&& a2, int&& a3) & noexcept              { i1 = a1; i2 = a2; i3 = a3; return 0x1121313; }

  int operator()(int&& a1, int& a2, int& a3) & noexcept                     { i1 = a1; i2 = a2; i3 = a3; return 0x1131111; }
  int operator()(int&& a1, int& a2, int const& a3) & noexcept               { i1 = a1; i2 = a2; i3 = a3; return 0x1131112; }
  int operator()(int&& a1, int& a2, int&& a3) & noexcept                    { i1 = a1; i2 = a2; i3 = a3; return 0x1131113; }

  int operator()(int&& a1, int const& a2, int& a3) & noexcept               { i1 = a1; i2 = a2; i3 = a3; return 0x1131211; }
  int operator()(int&& a1, int const& a2, int const& a3) & noexcept         { i1 = a1; i2 = a2; i3 = a3; return 0x1131212; }
  int operator()(int&& a1, int const& a2, int&& a3) & noexcept              { i1 = a1; i2 = a2; i3 = a3; return 0x1131213; }

  int operator()(int&& a1, int&& a2, int& a3) & noexcept                    { i1 = a1; i2 = a2; i3 = a3; return 0x1131311; }
  int operator()(int&& a1, int&& a2, int const& a3) & noexcept              { i1 = a1; i2 = a2; i3 = a3; return 0x1131312; }
  int operator()(int&& a1, int&& a2, int&& a3) & noexcept                   { i1 = a1; i2 = a2; i3 = a3; return 0x1131313; }

  //
  // const& (*this)
  //
  int operator()(int& a1, int& a2, int& a3) const& noexcept                   { i1 = a1; i2 = a2; i3 = a3; return 0x2111111; }
  int operator()(int& a1, int& a2, int const& a3) const& noexcept             { i1 = a1; i2 = a2; i3 = a3; return 0x2111112; }
  int operator()(int& a1, int& a2, int&& a3) const& noexcept                  { i1 = a1; i2 = a2; i3 = a3; return 0x2111113; }

  int operator()(int& a1, int const& a2, int& a3) const& noexcept             { i1 = a1; i2 = a2; i3 = a3; return 0x2111211; }
  int operator()(int& a1, int const& a2, int const& a3) const& noexcept       { i1 = a1; i2 = a2; i3 = a3; return 0x2111212; }
  int operator()(int& a1, int const& a2, int&& a3) const& noexcept            { i1 = a1; i2 = a2; i3 = a3; return 0x2111213; }

  int operator()(int& a1, int&& a2, int& a3) const& noexcept                  { i1 = a1; i2 = a2; i3 = a3; return 0x2111311; }
  int operator()(int& a1, int&& a2, int const& a3) const& noexcept            { i1 = a1; i2 = a2; i3 = a3; return 0x2111312; }
  int operator()(int& a1, int&& a2, int&& a3) const& noexcept                 { i1 = a1; i2 = a2; i3 = a3; return 0x2111313; }

  int operator()(int const& a1, int& a2, int& a3) const& noexcept             { i1 = a1; i2 = a2; i3 = a3; return 0x2121111; }
  int operator()(int const& a1, int& a2, int const& a3) const& noexcept       { i1 = a1; i2 = a2; i3 = a3; return 0x2121112; }
  int operator()(int const& a1, int& a2, int&& a3) const& noexcept            { i1 = a1; i2 = a2; i3 = a3; return 0x2121113; }

  int operator()(int const& a1, int const& a2, int& a3) const& noexcept       { i1 = a1; i2 = a2; i3 = a3; return 0x2121211; }
  int operator()(int const& a1, int const& a2, int const& a3) const& noexcept { i1 = a1; i2 = a2; i3 = a3; return 0x2121212; }
  int operator()(int const& a1, int const& a2, int&& a3) const& noexcept      { i1 = a1; i2 = a2; i3 = a3; return 0x2121213; }

  int operator()(int const& a1, int&& a2, int& a3) const& noexcept            { i1 = a1; i2 = a2; i3 = a3; return 0x2121311; }
  int operator()(int const& a1, int&& a2, int const& a3) const& noexcept      { i1 = a1; i2 = a2; i3 = a3; return 0x2121312; }
  int operator()(int const& a1, int&& a2, int&& a3) const& noexcept           { i1 = a1; i2 = a2; i3 = a3; return 0x2121313; }

  int operator()(int&& a1, int& a2, int& a3) const& noexcept                  { i1 = a1; i2 = a2; i3 = a3; return 0x2131111; }
  int operator()(int&& a1, int& a2, int const& a3) const& noexcept            { i1 = a1; i2 = a2; i3 = a3; return 0x2131112; }
  int operator()(int&& a1, int& a2, int&& a3) const& noexcept                 { i1 = a1; i2 = a2; i3 = a3; return 0x2131113; }

  int operator()(int&& a1, int const& a2, int& a3) const& noexcept            { i1 = a1; i2 = a2; i3 = a3; return 0x2131211; }
  int operator()(int&& a1, int const& a2, int const& a3) const& noexcept      { i1 = a1; i2 = a2; i3 = a3; return 0x2131212; }
  int operator()(int&& a1, int const& a2, int&& a3) const& noexcept           { i1 = a1; i2 = a2; i3 = a3; return 0x2131213; }

  int operator()(int&& a1, int&& a2, int& a3) const& noexcept                 { i1 = a1; i2 = a2; i3 = a3; return 0x2131311; }
  int operator()(int&& a1, int&& a2, int const& a3) const& noexcept           { i1 = a1; i2 = a2; i3 = a3; return 0x2131312; }
  int operator()(int&& a1, int&& a2, int&& a3) const& noexcept                { i1 = a1; i2 = a2; i3 = a3; return 0x2131313; }

  //
  //
  //
  int operator()(int& a1, int& a2, int& a3) && noexcept                       { i1 = a1; i2 = a2; i3 = a3; return 0x3111111; }
  int operator()(int& a1, int& a2, int const& a3) && noexcept                 { i1 = a1; i2 = a2; i3 = a3; return 0x3111112; }
  int operator()(int& a1, int& a2, int&& a3) && noexcept                      { i1 = a1; i2 = a2; i3 = a3; return 0x3111113; }

  int operator()(int& a1, int const& a2, int& a3) && noexcept                 { i1 = a1; i2 = a2; i3 = a3; return 0x3111211; }
  int operator()(int& a1, int const& a2, int const& a3) && noexcept           { i1 = a1; i2 = a2; i3 = a3; return 0x3111212; }
  int operator()(int& a1, int const& a2, int&& a3) && noexcept                { i1 = a1; i2 = a2; i3 = a3; return 0x3111213; }

  int operator()(int& a1, int&& a2, int& a3) && noexcept                      { i1 = a1; i2 = a2; i3 = a3; return 0x3111311; }
  int operator()(int& a1, int&& a2, int const& a3) && noexcept                { i1 = a1; i2 = a2; i3 = a3; return 0x3111312; }
  int operator()(int& a1, int&& a2, int&& a3) && noexcept                     { i1 = a1; i2 = a2; i3 = a3; return 0x3111313; }

  int operator()(int const& a1, int& a2, int& a3) && noexcept                 { i1 = a1; i2 = a2; i3 = a3; return 0x3121111; }
  int operator()(int const& a1, int& a2, int const& a3) && noexcept           { i1 = a1; i2 = a2; i3 = a3; return 0x3121112; }
  int operator()(int const& a1, int& a2, int&& a3) && noexcept                { i1 = a1; i2 = a2; i3 = a3; return 0x3121113; }

  int operator()(int const& a1, int const& a2, int& a3) && noexcept           { i1 = a1; i2 = a2; i3 = a3; return 0x3121211; }
  int operator()(int const& a1, int const& a2, int const& a3) && noexcept     { i1 = a1; i2 = a2; i3 = a3; return 0x3121212; }
  int operator()(int const& a1, int const& a2, int&& a3) && noexcept          { i1 = a1; i2 = a2; i3 = a3; return 0x3121213; }

  int operator()(int const& a1, int&& a2, int& a3) && noexcept                { i1 = a1; i2 = a2; i3 = a3; return 0x3121311; }
  int operator()(int const& a1, int&& a2, int const& a3) && noexcept          { i1 = a1; i2 = a2; i3 = a3; return 0x3121312; }
  int operator()(int const& a1, int&& a2, int&& a3) && noexcept               { i1 = a1; i2 = a2; i3 = a3; return 0x3121313; }

  int operator()(int&& a1, int& a2, int& a3) && noexcept                      { i1 = a1; i2 = a2; i3 = a3; return 0x3131111; }
  int operator()(int&& a1, int& a2, int const& a3) && noexcept                { i1 = a1; i2 = a2; i3 = a3; return 0x3131112; }
  int operator()(int&& a1, int& a2, int&& a3) && noexcept                     { i1 = a1; i2 = a2; i3 = a3; return 0x3131113; }

  int operator()(int&& a1, int const& a2, int& a3) && noexcept                { i1 = a1; i2 = a2; i3 = a3; return 0x3131211; }
  int operator()(int&& a1, int const& a2, int const& a3) && noexcept          { i1 = a1; i2 = a2; i3 = a3; return 0x3131212; }
  int operator()(int&& a1, int const& a2, int&& a3) && noexcept               { i1 = a1; i2 = a2; i3 = a3; return 0x3131213; }

  int operator()(int&& a1, int&& a2, int& a3) && noexcept                     { i1 = a1; i2 = a2; i3 = a3; return 0x3131311; }
  int operator()(int&& a1, int&& a2, int const& a3) && noexcept               { i1 = a1; i2 = a2; i3 = a3; return 0x3131312; }
  int operator()(int&& a1, int&& a2, int&& a3) && noexcept                    { i1 = a1; i2 = a2; i3 = a3; return 0x3131313; }
};

int V01::i1;
int V01::i2;
int V01::i3;

#endif /* YAUL_VARIANT_MULTIVISITORS_TEST_HELPER_HPP */
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
