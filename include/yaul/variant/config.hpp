// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

// yaul/variant/config.hpp

/** // doc: yaul/variant/config.hpp {{{
 * \file yaul/variant/config.hpp
 * \brief Contains certain configuration directives for Yaul.Variant library
 */ // }}}
#ifndef YAUL_VARIANT_CONFIG_HPP
#define YAUL_VARIANT_CONFIG_HPP

#if defined(__GNUC__)
# define YAUL_VARIANT_GCC_VERSION (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL)
# if YAUL_VARIANT_GCC_VERSION < 40901
// GCC Bug[59296]: https://gcc.gnu.org/bugzilla/show_bug.cgi?id=59296
#   define YAUL_VARIANT_BUGGY_RREF_QUALIFIED_MEMBERS 1
# endif
#endif

#ifdef YAUL_VARIANT_BUGGY_RREF_QUALIFIED_MEMBERS
# define YAUL_VARIANT_NO_RREF_CV_QUALIFIED_MEMBERS 1
#endif


#endif /* YAUL_VARIANT_CONFIG_HPP */
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
