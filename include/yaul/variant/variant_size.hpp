// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

// yaul/variant/variant_size.hpp

/** // doc: yaul/variant/variant_size.hpp {{{
 * \file yaul/variant/variant_size.hpp
 * \brief Implements \ref yaul::variant_size metafunction
 */ // }}}
#ifndef YAUL_VARIANT_VARIANT_SIZE_HPP
#define YAUL_VARIANT_VARIANT_SIZE_HPP

#include <yaul/variant/variant_fwd.hpp>
#include <type_traits>
#include <cstddef>

namespace yaul {

/** // doc: variant_size {{{
 * \brief Provides access to the number of alternatives in a possibly
 *        cv-qualified variant as a compile-time constant expression.
 *
 * \tparam Variant The variant type to be examined.
 *
 * \par Synopsis
 * \code
 *  template <typename T>
 *  struct variant_size; // undefined
 * \endcode
 * \code
 *  template <typename T0, typename... Others>
 *  struct variant_size<variant<T0,Others...> >
 *    : std::integral_constant<std::size_t, 1ul + sizeof.,..(Others)> { };
 * \endcode
 * \code
 *  template <typename T> struct variant_size<T const>;
 *  template <typename T> struct variant_size<T volatile>;
 *  template <typename T> struct variant_size<T const volatile>;
 * \endcode
 */ // }}}
template <typename Variant>
  struct variant_size;
/** \cond DOXYGEN_SHOW_TEMPLATE_SPECIALIZATIONS */
template <typename T>
  struct variant_size<T const>
    : variant_size<T>
  { };
template <typename T>
  struct variant_size<T volatile>
    : variant_size<T>
  { };
template <typename T>
  struct variant_size<T const volatile>
    : variant_size<T>
  { };
#if 0
template <typename T0, typename... Others>
  struct variant_size<variant<T0, Others...> >
    : std::integral_constant<std::size_t, 1ul + sizeof...(Others)>
  { };
#endif
template <template <typename...> class V, typename T0, typename... Others>
  struct variant_size< V<T0, Others...> >
    : std::conditional<
          detail::variant::is_variant_template<V>::value
        , std::integral_constant<std::size_t, 1ul + sizeof...(Others)>
        , detail::variant::not_a_variant< V<T0,Others...> >
      >::type
  { };
/** \endcond */

} // end namespace yaul::detail::variant

#endif /* YAUL_VARIANT_VARIANT_SIZE_HPP */
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
