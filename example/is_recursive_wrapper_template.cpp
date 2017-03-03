// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

/** // doc: file is_recursive_wrapper_template.cpp {{{
 * \file is_recursive_wrapper_template.cpp
 * \brief Usage example for \ref yaul::detail::variant::is_recursive_wrapper_template
 */ // }}}
/** // doc: example is_recursive_wrapper_template.cpp {{{
 * \example is_recursive_wrapper_template.cpp
 * \brief Usage example for \ref yaul::detail::variant::is_recursive_wrapper_template
 */ // }}}

// [Code]
#include <yaul/variant/recursive_wrapper_fwd.hpp>
#include <type_traits>

template <typename...> struct F1;
template <typename...> struct F2;

// specialize is_recursive_wrapper_template for our template F2
namespace yaul { namespace detail { namespace variant {
template<>
  struct is_recursive_wrapper_template<F2>
    : std::integral_constant<bool, true>
  { };
} } } // end namespace yaul::detail::variant

using yaul::detail::variant::is_recursive_wrapper_template;
using yaul::is_recursive_wrapper;
using yaul::wrap_recursive_wrapper;
using yaul::unwrap_recursive_wrapper;

static_assert(!is_recursive_wrapper_template<F1>::value, "");
static_assert( is_recursive_wrapper_template<F2>::value, "");
static_assert(!is_recursive_wrapper<F1<int> >::value, "");
static_assert( is_recursive_wrapper<F2<int> >::value, "");
static_assert(std::is_same<wrap_recursive_wrapper<int, F1>::type, int>::value, "");
static_assert(std::is_same<wrap_recursive_wrapper<int, F2>::type, F2<int> >::value, "");
static_assert(std::is_same<unwrap_recursive_wrapper<F1<int> >::type, F1<int> >::value, "");
static_assert(std::is_same<unwrap_recursive_wrapper<F2<int> >::type, int>::value, "");

int main() { return 0; }
// [Code]

/* [Output] *
 * [Output] */

// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
