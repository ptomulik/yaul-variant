// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

/** // doc: file enable_recursive.cpp {{{
 * \file enable_recursive.cpp
 * \brief Usage example for \ref yaul::detail::variant::enable_recursive
 */ // }}}
/** // doc: example enable_recursive.cpp {{{
 * \example enable_recursive.cpp
 * \brief Usage example for \ref yaul::detail::variant::enable_recursive
 */ // }}}

// [Code]
#include <yaul/variant/detail/enable_recursive.hpp>
#include <yaul/variant/recursive_variant_tag.hpp>

using yaul::detail::variant::enable_recursive;
using yaul::recursive_variant_tag;
using yaul::recursive_wrapper;

template <typename...> struct X;
template <typename...> struct F;
using V = X<int, char, recursive_variant_tag>;

static_assert(std::is_same<enable_recursive<recursive_variant_tag, V>::type, recursive_wrapper<V> >::value, "");
static_assert(std::is_same<enable_recursive<recursive_variant_tag&, V>::type, V&>::value, "");
static_assert(std::is_same<enable_recursive<recursive_variant_tag const&, V>::type, V const&>::value, "");
static_assert(std::is_same<enable_recursive<recursive_variant_tag const*, V>::type, V const*>::value, "");
static_assert(std::is_same<enable_recursive<V, V>::type, recursive_wrapper< X<int, char, V> > >::value, "");
static_assert(std::is_same<enable_recursive<F<recursive_variant_tag>, V>::type, recursive_wrapper< F<V> > >::value, "");

int main() { return 0; }
// [Code]

/* [Output] *
 * [Output] */

// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
