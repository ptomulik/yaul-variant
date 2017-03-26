// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

// yaul/variant/detail/all.hpp

/** // doc: yaul/variant/detail/all.hpp {{{
 * \file yaul/variant/detail/all.hpp
 * \brief Provides \ref yaul::detail::variant::all metafunction
 */ // }}}
#ifndef YAUL_VARIANT_DETAIL_ALL_HPP
#define YAUL_VARIANT_DETAIL_ALL_HPP

#include <type_traits>

namespace yaul { namespace detail { namespace variant {

/** // doc: all {{{
 * \brief Yields `true` if all of the `Values` are `true`
 *
 * \tparam Values boolean values to be examined
 *
 * \par Synopsis
 *
 * \code
 *  template<bool... Values>
 *  struct all
 *    : std::integral_constant<bool, unspecified>
 *  { };
 * \endcode
 *
 * The metafunction returns `true` for empty list of `Values`.
 */ // }}}
template<bool... Values>
struct all;

/** \cond DOXYGEN_SHOW_TEMPLATE_SPECIALIZATIONS */
template<bool First, bool... Rest>
struct all<First,Rest...>
  : std::integral_constant<bool, First && all<Rest...>::value>
{ };

template<>
struct all<>
  : std::integral_constant<bool, true>
{ };
/** \endcond */

} } } // end namespace yaul::detail::variant

#endif /* YAUL_VARIANT_DETAIL_ALL_HPP */
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
