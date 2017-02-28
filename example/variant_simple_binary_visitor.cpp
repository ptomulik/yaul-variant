// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

/** // doc: file variant_simple_binary_visitor.cpp {{{
 * \file variant_simple_binary_visitor.cpp
 * \brief Simple example with binary visitor
 */ // }}}
/** // doc: example variant_simple_binary_visitor.cpp {{{
 * \example variant_simple_binary_visitor.cpp
 * \brief Simple example with binary visitor
 */ // }}}

// [Code]
#include <yaul/variant/variant.hpp>
#include <yaul/variant/apply_visitor.hpp>
#include <string>
#include <iostream>

struct join
  : yaul::static_visitor<std::string>
{
  join(std::string const& sep) : sep_(sep) { }
  template<typename T1, typename T2>
  std::string operator()(T1 const& left, T2 const& right) const
  { return join::tostr(left) + this->sep_ + join::tostr(right); }
private:
  template<typename T>
  static std::string tostr(T&& x) { return std::to_string(std::forward<T>(x)); }
  static std::string const& tostr(std::string const& s) { return s; }

  std::string sep_;
};

int main()
{
  yaul::variant<int,std::string> v1{10};
  yaul::variant<float,std::string> v2{1.2f};

  std::cout << "1: " << yaul::apply_visitor(join(", "), v1, v2) << std::endl;
  v1 = "eleven";
  std::cout << "2: " << yaul::apply_visitor(join(", "), v1, v2) << std::endl;
  v2 = "twelve";
  std::cout << "3: " << yaul::apply_visitor(join(", "), v1, v2) << std::endl;
  std::cout << "4: " << yaul::apply_visitor(join(", "), v2, v1) << std::endl;

  return 0;
}
// [Code]

/* [Output] *
1: 10, 1.200000
2: eleven, 1.200000
3: eleven, twelve
4: twelve, eleven
 * [Output] */

// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
