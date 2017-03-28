// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <yaul/variant/detail/variant_storage.hpp>
#include <yaul/variant/variant_fwd.hpp>
#include <yaul/variant/test_config.hpp>
#include <type_traits>

using yaul::detail::variant::make_variant_storage;
using yaul::detail::variant::make_variant_storage_t;
using yaul::detail::variant::make_variadic_storage_t;

template<typename...> struct V1;

namespace yaul { namespace detail { namespace variant {
template<>
struct is_variant_template<V1>
  : std::integral_constant<bool,true>
{ };
} } } // end namespace yaul::detail::variant

static_assert(std::is_same<make_variant_storage< V1<int,char> >::type, make_variadic_storage_t<int,char> >::value, "");
static_assert(std::is_same<make_variant_storage_t< V1<int,char> >, make_variant_storage<V1<int,char> >::type>::value, "");

int main()
{
  return YAUL_VARIANT_TEST_EXIT_CODE;
}
