// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

/** // doc: file variant_dispatched_get.cpp {{{
 * \file variant_dispatched_get.cpp
 * \brief Usage example for \ref yaul::get() function
 */ // }}}
/** // doc: example variant_dispatched_get.cpp {{{
 * \example variant_dispatched_get.cpp
 *
 * Usage example for \ref yaul::get() function
 */ // }}}

// [Code]
#include <yaul/variant/variant.hpp>
#include <yaul/variant/get.hpp>
#include <iostream>

using IntOrChar = yaul::variant<int,char>;

void print_value(int n, IntOrChar const& v)
{
  using yaul::get;
  std::cout << n << ". ";
  switch(v.which())
    {
      case 0:   std::cout << "get<int>(): "   << get<int>(v);   break;
      case 1:   std::cout << "get<char>(): "  << get<char>(v);  break;
      default:  std::cout << "internal error";                  break;
    }
  std::cout << std::endl;
}

int main()
{
  IntOrChar v{10};
  try {
    print_value(1, v);
    v = 'c';
    print_value(2, v);
  } catch(yaul::bad_get const& e) {
    std::cout << e.what() << std::endl;
  }
  return 0;
}
// [Code]

/* [Output] *
1. get<int>(): 10
2. get<char>(): c
 * [Output] */

// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
