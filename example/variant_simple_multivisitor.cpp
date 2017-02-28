// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

/** // doc: file variant_simple_multivisitor.cpp {{{
 * \file variant_simple_multivisitor.cpp
 * \brief Simple example with multivisitor
 */ // }}}
/** // doc: example variant_simple_multivisitor.cpp {{{
 * \example variant_simple_multivisitor.cpp
 * \brief Simple example with multivisitor
 */ // }}}

// [Code]
#include <yaul/variant/variant.hpp>
#include <yaul/variant/apply_visitor.hpp>
#include <yaul/variant/multivisitors.hpp>
#include <string>
#include <iostream>

struct join
  : yaul::static_visitor<std::string>
{
  join(std::string const& sep) : sep_(sep) { }
  template<typename T1, typename T2, typename T3>
  std::string operator()(T1 const& x1, T2 const& x2, T3 const& x3) const
  { return join::tostr(x1) + this->sep_ + join::tostr(x2) + this->sep_ + join::tostr(x3); }
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
  yaul::variant<std::string,double> v3{"three dot four"};

  std::cout << "1: " << yaul::apply_visitor(join(", "), v1, v2, v3) << std::endl;

  return 0;
}
// [Code]


/* [Output] *
1: 10, 1.200000, three dot four
 * [Output] */

// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
