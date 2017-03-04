// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <yaul/variant/detail/variant_buffer.hpp>
#include <yaul/variant/detail/recursive_flag.hpp>
#include <yaul/variant/recursive_variant_tag.hpp>
#include <yaul/variant/recursive_wrapper.hpp>
#include <type_traits>

using yaul::detail::variant::variant_buffer;
using yaul::detail::variant::variant_buffer_t;
using yaul::detail::variant::recursive_flag;
using yaul::recursive_variant_tag;
using yaul::recursive_wrapper;
using std::is_same;

// Imitates a variant template class
template<typename... Types>
struct V
{
  typedef typename variant_buffer<V<Types...> >::type Buffer;
  Buffer buffer;
};

//////////////////////////////////////////////////////////////////////////////
static_assert(is_same< variant_buffer< V<int> >::type,
                       std::aligned_storage< sizeof(int), alignof(int) >::type
                     >::value, "");
static_assert(is_same< variant_buffer_t< V<int> >,
                       std::aligned_storage< sizeof(int), alignof(int) >::type
                     >::value, "");

//////////////////////////////////////////////////////////////////////////////
static_assert(is_same< variant_buffer< V<char,double> >::type,
                       std::aligned_storage< sizeof(double), alignof(double) >::type
                     >::value, "");
static_assert(is_same< variant_buffer_t< V<char,double> >,
                       std::aligned_storage< sizeof(double), alignof(double) >::type
                     >::value, "");

//////////////////////////////////////////////////////////////////////////////
struct S
{
  char c;
  int  i;
  double d;
};
static_assert(is_same< variant_buffer< V<char,double, S> >::type,
                       std::aligned_storage< sizeof(S), alignof(S) >::type
                     >::value, "");
static_assert(is_same< variant_buffer_t< V<char,double, S> >,
                       std::aligned_storage< sizeof(S), alignof(S) >::type
                     >::value, "");

//////////////////////////////////////////////////////////////////////////////
template<typename T>
struct H
{
  T x[2];
};

using RecVar = V<recursive_flag<char>, H<recursive_variant_tag> >;
static_assert(is_same< variant_buffer<RecVar>::type,
                       std::aligned_storage<
                          sizeof(recursive_wrapper< H<RecVar> >),
                          alignof(recursive_wrapper< H<RecVar> >)
                       >::type
                     >::value, "");

int main()
{
  return 0;
}
