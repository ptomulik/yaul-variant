// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <yaul/variant/detail/variant_storage.hpp>
#include <type_traits>

using yaul::detail::variant::variant_storage;
using yaul::detail::variant::variant_storage_t;
using yaul::variant;
using std::is_same;

//////////////////////////////////////////////////////////////////////////////
static_assert(is_same< typename variant_storage< variant<int> >::type,
                          typename std::aligned_storage< sizeof(int), alignof(int) >::type
                     >::value, "");
static_assert(is_same< variant_storage_t< variant<int> >,
                          typename std::aligned_storage< sizeof(int), alignof(int) >::type
                     >::value, "");

//////////////////////////////////////////////////////////////////////////////
static_assert(is_same< typename variant_storage< variant<char,double> >::type,
                          typename std::aligned_storage< sizeof(double), alignof(double) >::type
                     >::value, "");
static_assert(is_same< variant_storage_t< variant<char,double> >,
                          typename std::aligned_storage< sizeof(double), alignof(double) >::type
                     >::value, "");

//////////////////////////////////////////////////////////////////////////////
struct S
{
  char c;
  int  i;
  double d;
};
static_assert(is_same< typename variant_storage< variant<char,double, S> >::type,
                          typename std::aligned_storage< sizeof(S), alignof(S) >::type
                     >::value, "");
static_assert(is_same< variant_storage_t< variant<char,double, S> >,
                          typename std::aligned_storage< sizeof(S), alignof(S) >::type
                     >::value, "");
int main()
{
  return 0;
}
