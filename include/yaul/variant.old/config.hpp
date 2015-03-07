// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

// yaul/variant/config.hpp

/** // doc: yaul/variant/config.hpp {{{
 * \file yaul/variant/config.hpp
 * \todo Write documentation
 */ // }}}
#ifndef YAUL_VARIANT_CONFIG_HPP
#define YAUL_VARIANT_CONFIG_HPP

#ifdef YAUL_VARIANT_DISABLE_NOEXCEPT_PROPAGATION
# ifndef YAUL_VARIANT_DISABLE_NOEXCEPT_PROPAGATION_IN_CTORS
/** // doc: {{{
 * \todo Write documentation
 */ // }}}
#   define YAUL_VARIANT_DISABLE_NOEXCEPT_PROPAGATION_IN_CTORS
# endif
# ifndef YAUL_VARIANT_DISABLE_NOEXCEPT_PROPAGATION_IN_ASSIGNMENTS
/** // doc: {{{
 * \todo Write documentation
 */ // }}}
#   define YAUL_VARIANT_DISABLE_NOEXCEPT_PROPAGATION_IN_ASSIGNMENTS
# endif
# ifndef YAUL_VARIANT_DISABLE_NOEXCEPT_PROPAGATION_IN_APPLY_VISITOR
/** // doc: {{{
 * \todo Write documentation
 */ // }}}
#   define YAUL_VARIANT_DISABLE_NOEXCEPT_PROPAGATION_IN_APPLY_VISITOR
# endif
# ifndef YAUL_VARIANT_DISABLE_NOEXCEPT_PROPAGATION_IN_DESTRUCTOR_VISITOR
/** // doc: {{{
 * \todo Write documentation
 */ // }}}
#   define YAUL_VARIANT_DISABLE_NOEXCEPT_PROPAGATION_IN_DESTRUCTOR_VISITOR
# endif
#endif

#ifdef YAUL_VARIANT_DISABLE_NOEXCEPT_PROPAGATION_IN_CTORS
# ifndef YAUL_VARIANT_DISABLE_NOEXCEPT_PROPAGATION_IN_DFLT_CTOR
/** // doc: {{{
 * \todo Write documentation
 */ // }}}
#   define YAUL_VARIANT_DISABLE_NOEXCEPT_PROPAGATION_IN_DFLT_CTOR
# endif

# ifndef YAUL_VARIANT_DISABLE_NOEXCEPT_PROPAGATION_IN_COPY_CTOR
/** // doc: {{{
 * \todo Write documentation
 */ // }}}
#   define YAUL_VARIANT_DISABLE_NOEXCEPT_PROPAGATION_IN_COPY_CTOR
# endif

# ifndef YAUL_VARIANT_DISABLE_NOEXCEPT_PROPAGATION_IN_MOVE_CTOR
/** // doc: {{{
 * \todo Write documentation
 */ // }}}
#   define YAUL_VARIANT_DISABLE_NOEXCEPT_PROPAGATION_IN_MOVE_CTOR
# endif

# ifndef YAUL_VARIANT_DISABLE_NOEXCEPT_PROPAGATION_IN_LREF_CTOR
/** // doc: {{{
 * \todo Write documentation
 */ // }}}
#   define YAUL_VARIANT_DISABLE_NOEXCEPT_PROPAGATION_IN_LREF_CTOR
# endif

# ifndef YAUL_VARIANT_DISABLE_NOEXCEPT_PROPAGATION_IN_CREF_CTOR
/** // doc: {{{
 * \todo Write documentation
 */ // }}}
#   define YAUL_VARIANT_DISABLE_NOEXCEPT_PROPAGATION_IN_CREF_CTOR
# endif

# ifndef YAUL_VARIANT_DISABLE_NOEXCEPT_PROPAGATION_IN_RREF_CTOR
/** // doc: {{{
 * \todo Write documentation
 */ // }}}
#   define YAUL_VARIANT_DISABLE_NOEXCEPT_PROPAGATION_IN_RREF_CTOR
# endif
#endif

#ifdef YAUL_VARIANT_DISABLE_NOEXCEPT_PROPAGATION_IN_ASSIGNMENTS
# ifndef YAUL_VARIANT_DISABLE_NOEXCEPT_PROPAGATION_IN_COPY_ASSIGNMENT
/** // doc: {{{
 * \todo Write documentation
 */ // }}}
#   define YAUL_VARIANT_DISABLE_NOEXCEPT_PROPAGATION_IN_COPY_ASSIGNMENT
# endif

# ifndef YAUL_VARIANT_DISABLE_NOEXCEPT_PROPAGATION_IN_MOVE_ASSIGNMENT
/** // doc: {{{
 * \todo Write documentation
 */ // }}}
#   define YAUL_VARIANT_DISABLE_NOEXCEPT_PROPAGATION_IN_MOVE_ASSIGNMENT
# endif

# ifndef YAUL_VARIANT_DISABLE_NOEXCEPT_PROPAGATION_IN_LREF_ASSIGNMENT
/** // doc: {{{
 * \todo Write documentation
 */ // }}}
#   define YAUL_VARIANT_DISABLE_NOEXCEPT_PROPAGATION_IN_LREF_ASSIGNMENT
# endif

# ifndef YAUL_VARIANT_DISABLE_NOEXCEPT_PROPAGATION_IN_CREF_ASSIGNMENT
/** // doc: {{{
 * \todo Write documentation
 */ // }}}
#   define YAUL_VARIANT_DISABLE_NOEXCEPT_PROPAGATION_IN_CREF_ASSIGNMENT
# endif

# ifndef YAUL_VARIANT_DISABLE_NOEXCEPT_PROPAGATION_IN_RREF_ASSIGNMENT
/** // doc: {{{
 * \todo Write documentation
 */ // }}}
#   define YAUL_VARIANT_DISABLE_NOEXCEPT_PROPAGATION_IN_RREF_ASSIGNMENT
# endif

# ifndef YAUL_VARIANT_DISABLE_NOEXCEPT_PROPAGATION_IN_ASSIGNER_VISITOR
/** // doc: {{{
 * \todo Write documentation
 */ // }}}
#   define YAUL_VARIANT_DISABLE_NOEXCEPT_PROPAGATION_IN_ASSIGNER_VISITOR
# endif
#endif

#if (defined YAUL_VARIANT_DISABLE_NOEXCEPT_PROPAGATION_IN_COPY_CTOR) && \
    (defined YAUL_VARIANT_DISABLE_NOEXCEPT_PROPAGATION_IN_MOVE_CTOR) 
# ifndef YAUL_VARIANT_DISABLE_NOEXCEPT_PROPAGATION_IN_INITIALIZER_VISITOR
#   define YAUL_VARIANT_DISABLE_NOEXCEPT_PROPAGATION_IN_INITIALIZER_VISITOR
# endif
#endif

// FIXME: elaborate when we should disable NOEXCEPT_PROPAGATION_IN_INITIALIZE
// # ifndef YAUL_VARIANT_DISABLE_NOEXCEPT_PROPAGATION_IN_INITIALIZE
// #   define YAUL_VARIANT_DISABLE_NOEXCEPT_PROPAGATION_IN_INITIALIZE
// # endif

#endif /* YAUL_VARIANT_CONFIG_HPP */
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
