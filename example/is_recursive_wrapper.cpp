// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

/** // doc: file is_recursive_wrapper.cpp {{{
 * \file is_recursive_wrapper.cpp
 * \brief Usage example for \ref yaul::is_recursive_wrapper
 */ // }}}
/** // doc: example is_recursive_wrapper.cpp {{{
 * \example is_recursive_wrapper.cpp
 * \brief Usage example for \ref yaul::is_recursive_wrapper
 */ // }}}

// [Code]
#include <yaul/variant/recursive_wrapper_fwd.hpp>

using yaul::is_recursive_wrapper;
using yaul::recursive_wrapper;

struct T;
static_assert( is_recursive_wrapper< recursive_wrapper<T> >::value, "");
static_assert( is_recursive_wrapper< recursive_wrapper<T> const >::value, "");
static_assert( is_recursive_wrapper< recursive_wrapper<T> volatile >::value, "");
static_assert( is_recursive_wrapper< recursive_wrapper<T> const volatile >::value, "");
static_assert(!is_recursive_wrapper< recursive_wrapper<T const> >::value, "");
static_assert(!is_recursive_wrapper< recursive_wrapper<T volatile> >::value, "");
static_assert(!is_recursive_wrapper< recursive_wrapper<T const volatile> >::value, "");
static_assert(!is_recursive_wrapper< recursive_wrapper<T&> >::value, "");
static_assert(!is_recursive_wrapper< recursive_wrapper<T&&> >::value, "");
static_assert(!is_recursive_wrapper< recursive_wrapper<T[]> >::value, "");
static_assert(!is_recursive_wrapper< recursive_wrapper<T[2]> >::value, "");

int main() { return 0; }
// [Code]

/* [Output] *
 * [Output] */

// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
