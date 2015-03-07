// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

// yaul/variant/variant_find.hpp

/** // doc: yaul/variant/variant_find.hpp {{{
 * \file yaul/variant/variant_find.hpp
 * \todo Write documentation
 */ // }}}
#ifndef YAUL_VARIANT_VARIANT_FIND_HPP
#define YAUL_VARIANT_VARIANT_FIND_HPP

#include <cstddef>

namespace yaul { namespace detail { namespace variant {
/** \ingroup DetailMetafunctionsGroup 
 * @{ */
/** // doc: variant_find_impl {{{
 * \todo Write documentation
 */ // }}}
template <typename U, typename Variant, std::size_t I = 0ul>
struct variant_find_impl;
/** @} */
} } } // end namespace yaul::detail::variant

namespace yaul {
/** \ingroup MetafunctionsGroup 
 * @{ */
/** // doc: variant_find {{{
 * \todo Write documentation
 */ // }}}
template <typename U, typename Variant>
  struct variant_find
    : detail::variant::variant_find_impl<U, Variant>
  { };
/** @} */
} // end namespace yaul

#include <yaul/variant/variant_fwd.hpp>
#include <type_traits>

namespace yaul { namespace detail { namespace variant {
/** \ingroup DetailMetafunctionsGroup 
 * @{ */
/** \cond DOXYGEN_SHOW_TEMPLATE_SPECIALIZATIONS */
template <typename U, std::size_t I, typename T0, typename... Others>
  struct variant_find_impl<U, yaul::variant<T0,Others...>, I>
    : variant_find_impl<U, yaul::variant<Others...>, I+1>
  { };
template <typename U, std::size_t I, typename... Others>
  struct variant_find_impl<U, yaul::variant<U,Others...>, I>
    : std::integral_constant<std::size_t, I>
  { };
template <typename U, std::size_t I>
  struct variant_find_impl<U, yaul::variant<U>, I>
    : std::integral_constant<std::size_t, I>
  { };
template <typename U, typename T0, std::size_t I>
  struct variant_find_impl<U, yaul::variant<T0>, I>
    : std::integral_constant<std::size_t, I+1>
  { };
/** \endcond */
/** @} */
} } } // end namespace yaul::detail::variant


#endif /* YAUL_VARIANT_VARIANT_FIND_HPP */
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
