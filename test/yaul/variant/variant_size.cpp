// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <yaul/variant/variant_size.hpp>
#include <type_traits>

using yaul::variant_size;
using yaul::variant;
using yaul::detail::variant::not_a_variant;

static_assert(variant_size<variant<int> >::value == 1ul, "");
static_assert(variant_size<variant<int,char> >::value == 2ul, "");
static_assert(variant_size<variant<int,char,float> >::value == 3ul, "");

static_assert(variant_size<variant<int,char,float> const>::value == 3ul, "");
static_assert(variant_size<variant<int,char,float> volatile>::value == 3ul, "");
static_assert(variant_size<variant<int,char,float> const volatile>::value == 3ul, "");

template<typename...> struct V1;
template<typename...> struct V2;

namespace yaul { namespace detail { namespace variant {
template<>
  struct is_variant_template<V1>
    : std::integral_constant<bool, true>
  { };
} } } // end namespace yaul::detail::variant

static_assert(variant_size<V1<int,char> >::value == 2, "");
static_assert(std::is_base_of<not_a_variant< V2<int,char> >, variant_size<V2<int,char> > >::value, "");

int main()
{
  return 0;
}
