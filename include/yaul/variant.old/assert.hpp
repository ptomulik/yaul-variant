// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

// yaul/variant/assert.hpp

/** // doc: yaul/variant/assert.hpp {{{
 * \file yaul/variant/assert.hpp
 * \todo Write documentation
 */ // }}}
#ifndef YAUL_VARIANT_ASSERT_HPP
#define YAUL_VARIANT_ASSERT_HPP

#include <cassert>

#ifdef YAUL_DISABLE_ASSERTS
# ifndef YAUL_VARIANT_DISABLE_ASSERTS
#   define YAUL_VARIANT_DISABLE_ASSERTS
# endif
#endif

#ifndef YAUL_VARIANT_ASSERT
# ifndef YAUL_VARIANT_DISABLE_ASSERTS
#   define YAUL_VARIANT_ASSERT(expr) assert(expr)
# else
#   define YAUL_VARIANT_ASSERT ((void)0)
# endif
#endif

#endif /* YAUL_VARIANT_ASSERT_HPP */
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
