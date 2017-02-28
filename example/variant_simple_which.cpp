// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/** // doc: variant_simple_which.cpp (file) {{{
 * \file variant_simple_which.cpp
 * \brief Usage example for variant's which() method.
 */ // }}}
/** // doc: variant_simple_which.cpp (example) {{{
 * \example variant_simple_which.cpp
 * \brief Usage example of yaul::variant and which() method.
 */ // }}}
// [Code]
#include <yaul/variant/variant.hpp>
#include <iostream>

using IntOrChar = yaul::variant<int,char>;

int main()
{
  IntOrChar v;
  std::cout << "v.which(): " << v.which() << std::endl;
  v = 'a';
  std::cout << "v.which(): " << v.which() << std::endl;
  v = 23;
  std::cout << "v.which(): " << v.which() << std::endl;
  return 0;
}
// [Code]

/* [Output]
v.which(): 0
v.which(): 1
v.which(): 0
   [Output] */

// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
