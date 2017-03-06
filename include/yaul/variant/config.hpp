// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

// yaul/variant/config.hpp

/** // doc: yaul/variant/config.hpp {{{
 * \file yaul/variant/config.hpp
 * \brief Configuration directives for Yaul.Variant library
 */ // }}}
#ifndef YAUL_VARIANT_CONFIG_HPP
#define YAUL_VARIANT_CONFIG_HPP

#if defined(__GNUC__) && !defined(__clang__)
# define YAUL_VARIANT_GCC_VERSION \
    (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)
# if YAUL_VARIANT_GCC_VERSION < 40901
    // GCC Bug[59296]: https://gcc.gnu.org/bugzilla/show_bug.cgi?id=59296
#   define YAUL_VARIANT_GCC_BUG_59296 1
# endif
# if YAUL_VARIANT_GCC_VERSION < 80001
    // FIXME: which version will fix it?
    // https://gcc.gnu.org/bugzilla/show_bug.cgi?id=66297
#   define YAUL_VARIANT_GCC_BUG_66297 1
    // http://www.open-std.org/jtc1/sc22/wg21/docs/cwg_defects.html#1684
#   define YAUL_VARIANT_CWG_DEFECT_1684 1
# endif
#endif

#if defined(__clang__)
# define YAUL_VARIANT_CLANG_VERSION \
    (__clang_major__ * 10000 + __clang_minor__ * 100 + __clang_patchlevel__)
# if YAUL_VARIANT_CLANG_VERSION < 30601
#   define YAUL_VARIANT_CWG_DEFECT_1684 1
# endif
#endif

//
// r-value reference qualified functions with const/volatile qualifiers
//
#ifdef YAUL_VARIANT_GCC_BUG_59296
# define YAUL_VARIANT_NO_RRCV_QUALIFIED_FUNCTIONS 1
#endif

//
// constexpr ctors with non-empty body
//
#if __cplusplus < 201402L
# define YAUL_VARIANT_NO_CONSTEXPR_ON_NONEMPTY_CTORS 1
#endif

//
// placement new in constexpr functions
//
#if (__cplusplus < 201402L) || (defined(__clang__))
# define YAUL_VARIANT_NO_CONSTEXPR_ON_FUNCTIONS_WITH_PLACEMENT_NEW 1
#endif

//
// constexpr functions enclosed in non-literal classes
//
#ifdef YAUL_VARIANT_CWG_DEFECT_1684
# define YAUL_VARIANT_NO_CONSTEXPR_ON_FUNCTIONS_IN_NONLITERAL_CLASS 1
#endif

//
// constexprness of non-const functions
//
#if __cplusplus >= 201402L
# define YAUL_VARIANT_NO_CONSTEXPR_IMPLIED_CONST_ON_FUNCTIONS 1
#endif

#if !defined(YAUL_VARIANT_NO_CONSTEXPR_IMPLIED_CONST_ON_FUNCTIONS) // || ...
# define YAUL_VARIANT_NO_CONSTEXPR_ON_NONCONST_FUNCTIONS 1
#endif



#endif /* YAUL_VARIANT_CONFIG_HPP */
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
