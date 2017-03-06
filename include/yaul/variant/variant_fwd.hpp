// Copyright (C) 2015-2017, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

// yaul/variant/variant_fwd.hpp

/** // doc: yaul/variant/variant_fwd.hpp {{{
 * \file yaul/variant/variant_fwd.hpp
 * \todo Write documentation
 */ // }}}
#ifndef YAUL_VARIANT_VARIANT_FWD_HPP
#define YAUL_VARIANT_VARIANT_FWD_HPP

#include <type_traits>

namespace yaul {
template< typename T0, typename... Others > class variant;
template< typename T0, typename... Others > struct make_recursive_variant;
} // end namespace yaul

namespace yaul { namespace detail { namespace  variant {

/** // doc: not_a_variant {{{
 * \brief Used to denote, that argument provided to metafunction is not a variant
 */ // }}}
template<typename T>
struct not_a_variant {};

/** // doc: is_variant_template {{{
 * \brief Checks, whether a given template class attempts to be a variant
 *
 * \tparam T Class template to be examined
 *
 * \par Synopsis
 * \code
 *  template< template <typename...> class >
 *  struct is_variant_template
 *    : std::integral_constant<bool, unspecified>
 *    { };
 * \endcode
 *
 * \par Description
 * If it holds
 * \code
 *  is_variant_template<W>::value == true
 * \endcode
 * for some class template `W`, then for any suitable types `Types...`,
 * `W<Types...>` is treated as a variant class by several metafunctions across
 * the library.
 */ // }}}
template< template<typename...> class T >
struct is_variant_template
  : std::integral_constant<bool, false>
{ };

/** \cond DOXYGEN_SHOW_TEMPLATE_SPECIALIZATIONS */
template<>
  struct is_variant_template< ::yaul::variant >
    : std::integral_constant<bool, true>
  { };
/** \endcond */

} } } // end namespace yaul::detail::variant

#endif /* YAUL_VARIANT_VARIANT_FWD_HPP */
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
