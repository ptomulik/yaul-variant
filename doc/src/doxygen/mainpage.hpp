// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

// mainpage.hpp

/**
 * \mainpage Yaul.Variant
 *
 * Yaul.Variant is a header-only library inspired by [Boost.Variant][] and
 * [std::variant][] (first appearing in C++17). The library provides
 * \ref yaul::variant class, a single-valued container which may be
 * assigned a value of one of alternative types. It's implemented in C++11
 * using its idioms and related programming techniques.
 *
 * \section sec-mainpage-intro Introduction
 *
 * The \ref yaul::variant template class implements a type-safe
 * union-like container. An instance of \ref yaul::variant at any
 * given time holds a value of one of its alternative types. Types are
 * indexed with a zero-based integer index. The variant may be queried
 * at any time for the index of currently assigned value type.
 *
 * \section sec-mainpage-features Features
 *
 * Notable features of \ref yaul::variant include:
 *
 *  - compile-time type-safe value visitation via \ref yaul::apply_visitor,
 *  - run-time checked explicit value retrieval via \ref yaul::get,
 *  - support for recursive variant types via \ref yaul::make_recursive_variant
 *    and \ref yaul::recursive_wrapper,
 *  - efficient implementation - stack based when possible.
 *
 *
 * <!-- Links -->
 * [Boost.Variant]: http://www.boost.org/doc/libs/release/libs/variant/
 * [std::variant]: http://en.cppreference.com/w/cpp/utility/variant
 */

// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
