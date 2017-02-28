// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

/** // doc: file variant_simple_visitor.cpp {{{
 * \file variant_simple_visitor.cpp
 * \brief Usage example for \ref yaul::apply_visitor
 */ // }}}
/** // doc: example variant_simple_visitor.cpp {{{
 * \example variant_simple_visitor.cpp
 * \brief Usage example for \ref yaul::apply_visitor
 */ // }}}

// [Code]
#include <yaul/variant/variant.hpp>
#include <yaul/variant/apply_visitor.hpp>
#include <iostream>

using IntOrChar = yaul::variant<int,char>;

struct print_value
  : yaul::static_visitor<void>
{
  int n_;
  print_value(int n) : n_(n) { }
  void operator()(int i) const  { std::cout << this->n_ << ". " << i << std::endl; }
  void operator()(char c) const { std::cout << this->n_ << ". " << c << std::endl; }
};

int main()
{
  IntOrChar v{10};
  yaul::apply_visitor(print_value(1), v);
  v = 'c';
  yaul::apply_visitor(print_value(2), v);
  return 0;
}
// [Code]

/* [Output] *
1. 10
2. c
 * [Output] */

// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
