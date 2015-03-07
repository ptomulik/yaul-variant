// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <yaul/variant/variant_element.hpp>
#include <type_traits>

using yaul::variant_element;
using yaul::variant_element_t;
using yaul::variant;
using std::is_same;

// variant_element
static_assert(is_same<typename variant_element<0ul,variant<int> >::type, int>::value, "");
static_assert(is_same<typename variant_element<0ul,variant<int,char> >::type, int>::value, "");
static_assert(is_same<typename variant_element<1ul,variant<int,char> >::type, char>::value, "");

// variant_element_t
static_assert(is_same<variant_element_t<0ul,variant<int> >, int>::value, "");
static_assert(is_same<variant_element_t<0ul,variant<int,char> >, int>::value, "");
static_assert(is_same<variant_element_t<1ul,variant<int,char> >, char>::value, "");

// tests for cv-qualified variant
static_assert(is_same<variant_element_t<0ul,const variant<int,char> >, const int>::value, "");
static_assert(is_same<variant_element_t<1ul,const variant<int,char> >, const char>::value, "");
static_assert(is_same<variant_element_t<0ul,volatile variant<int,char> >, volatile int>::value, "");
static_assert(is_same<variant_element_t<1ul,volatile variant<int,char> >, volatile char>::value, "");
static_assert(is_same<variant_element_t<0ul,const volatile variant<int,char> >, const volatile int>::value, "");
static_assert(is_same<variant_element_t<1ul,const volatile variant<int,char> >, const volatile char>::value, "");

int main()
{
  return 0;
}
