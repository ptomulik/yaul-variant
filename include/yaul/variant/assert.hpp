// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

// yaul/variant/assert.hpp

/** // doc: yaul/variant/assert.hpp {{{
 * \file yaul/variant/assert.hpp
 * \brief Provides macros for runtime assertions
 */ // }}}
#ifndef YAUL_VARIANT_ASSERT_HPP
#define YAUL_VARIANT_ASSERT_HPP

#include <cassert>

/** \ingroup group-macros
 * @{ */

#ifdef YAUL_VARIANT_DOXYGEN_INVOKED

/** // doc: YAUL_VARIANT_ASSERT {{{
 * \def YAUL_VARIANT_ASSERT(expr)
 * \brief Runtime assertion
 *
 * By default \c YAUL_VARIANT_ASSERT(expr) expands to \c assert(expr).
 *
 * If a preprocessor symbol \ref YAUL_VARIANT_DISABLE_ASSERTS is defined and
 * evaluates to true, then \c YAUL_VARIANT_ASSERT(expr) expands to \c
 * ((void)0).
 *
 * This macro is currently used internally in the implementation of
 * \ref yaul::detail::variant::variant_base "variant_base".
 *
 */ // }}}
#define YAUL_VARIANT_ASSERT(expr)

/** // doc: YAUL_VARIANT_DISABLE_ASSERTS {{{
 * \def YAUL_VARIANT_DISABLE_ASSERTS
 * \brief Disables \ref YAUL_VARIANT_ASSERT macro.
 *
 * Define \ref YAUL_VARIANT_DISABLE_ASSERTS to 1 prior to including
 * \ref yaul/variant/assert.hpp to disable the YAUL_VARIANT_ASSERT macro
 * unconditionally.
 *
 * Define \ref YAUL_VARIANT_DISABLE_ASSERTS to 0 prior to including
 * \ref yaul/variant/assert.hpp to enable the YAUL_VARIANT_ASSERT macro
 * unconditionally.
 *
 * If \ref YAUL_VARIANT_DISABLE_ASSERTS is not defined and
 * \c YAUL_DISABLE_ASSERTS is defined prior to including
 * \ref yaul/variant/assert.hpp, then \ref YAUL_VARIANT_DISABLE_ASSERTS
 * gets defined to 1 in \ref yaul/variant/assert.hpp.
 *
 * <b>Example (disabling YAUL_VARIANT_ASSERT)</b>
 *
 * \code
 * #define YAUL_VARIANT_DISABLE_ASSERTS 1
 * #include <yaul/variant/assert.hpp>
 *
 * int main()
 * {
 *   YAUL_VARIANT_ASSERT(false); // expands to ((void)0);
 *   return 0;
 * }
 * \endcode
 *
 * <b>Example (enabling YAUL_VARIANT_ASSERT despite of YAUL_DISABLE_ASSERTS)</b>
 *
 * \code
 * #define YAUL_DISABLE_ASSERTS 1
 * #define YAUL_VARIANT_DISABLE_ASSERTS 0
 * #include <yaul/variant/assert.hpp>
 *
 * int main()
 * {
 *   YAUL_VARIANT_ASSERT(false); // expands to assert(false);
 *   return 0;
 * }
 * \endcode
 */ // }}}
#define YAUL_VARIANT_DISABLE_ASSERTS

#else

#ifdef YAUL_DISABLE_ASSERTS
# ifndef YAUL_VARIANT_DISABLE_ASSERTS
#   define YAUL_VARIANT_DISABLE_ASSERTS 1
# endif
#endif

#ifndef YAUL_VARIANT_ASSERT
# if YAUL_VARIANT_DISABLE_ASSERTS
#   define YAUL_VARIANT_ASSERT(expr) ((void)0)
# else
#   define YAUL_VARIANT_ASSERT(expr) assert(expr)
# endif
#endif

#endif // YAUL_VARIANT_DOXYGEN_INVOKED

/** @} */

#endif /* YAUL_VARIANT_ASSERT_HPP */
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
