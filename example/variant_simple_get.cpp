// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

/** // doc: file variant_simple_get.cpp {{{
 * \file variant_simple_get.cpp
 * \brief Usage example for \ref yaul::get() function
 */ // }}}
/** // doc: example variant_simple_get.cpp {{{
 * \example variant_simple_get.cpp
 *
 * Usage example for \ref yaul::get() function
 */ // }}}

// [Code]
#include <yaul/variant/variant.hpp>
#include <yaul/variant/get.hpp>
#include <iostream>

using IntOrChar = yaul::variant<int,char>;
int main()
{
  IntOrChar v{10};
  try {
    using yaul::get;
    std::cout << "1. get<int>(): "   << get<int>(v)  << std::endl;
    v = 'c';
    std::cout << "2. get<char>(): "  << get<char>(v) << std::endl;
    std::cout << "3. get<int>(): "   << get<int>(v)  << std::endl;
  } catch(yaul::bad_get const& e) {
    std::cout << e.what() << std::endl;
  }
  return 0;
}
// [Code]

/* [Output] *
1. get<int>(): 10
2. get<char>(): c
yaul::bad_get: failed to get using yaul::get
 * [Output] */

// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
