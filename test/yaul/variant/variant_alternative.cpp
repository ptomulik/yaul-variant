// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <yaul/variant/variant_alternative.hpp>
#include <type_traits>

using yaul::variant_alternative;
using yaul::variant_alternative_t;
using yaul::variant;
using yaul::detail::variant::not_a_variant;
using std::is_same;

// variant_alternative
static_assert(is_same<typename variant_alternative<0ul,variant<int> >::type, int>::value, "");
static_assert(is_same<typename variant_alternative<0ul,variant<int,char> >::type, int>::value, "");
static_assert(is_same<typename variant_alternative<1ul,variant<int,char> >::type, char>::value, "");

// variant_alternative_t
static_assert(is_same<variant_alternative_t<0ul,variant<int> >, int>::value, "");
static_assert(is_same<variant_alternative_t<0ul,variant<int,char> >, int>::value, "");
static_assert(is_same<variant_alternative_t<1ul,variant<int,char> >, char>::value, "");

// tests for cv-qualified variant
static_assert(is_same<variant_alternative_t<0ul,const variant<int,char> >, const int>::value, "");
static_assert(is_same<variant_alternative_t<1ul,const variant<int,char> >, const char>::value, "");
static_assert(is_same<variant_alternative_t<0ul,volatile variant<int,char> >, volatile int>::value, "");
static_assert(is_same<variant_alternative_t<1ul,volatile variant<int,char> >, volatile char>::value, "");
static_assert(is_same<variant_alternative_t<0ul,const volatile variant<int,char> >, const volatile int>::value, "");
static_assert(is_same<variant_alternative_t<1ul,const volatile variant<int,char> >, const volatile char>::value, "");

template<typename...> struct V1;
template<typename...> struct V2;

namespace yaul { namespace detail { namespace variant {
template<>
  struct is_variant_template<V1>
    : std::integral_constant<bool, true>
  { };
} } } // end namespace yaul::detail::variant

static_assert(is_same<variant_alternative_t<0ul, V1<int,char> >, int>::value, "");
static_assert(is_same<variant_alternative_t<1ul, V1<int,char> >, char>::value, "");

static_assert(std::is_base_of<not_a_variant< V2<int,char> >, variant_alternative<0ul, V2<int,char> > >::value, "");

int main()
{
  return 0;
}
