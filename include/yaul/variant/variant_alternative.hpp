// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

// yaul/variant/variant_alternative.hpp

/** // doc: yaul/variant/variant_alternative.hpp {{{
 * \file yaul/variant/variant_alternative.hpp
 * \brief Provides the \ref yaul::variant_alternative metafunction
 */ // }}}
#ifndef YAUL_VARIANT_VARIANT_ALTERNATIVE_HPP
#define YAUL_VARIANT_VARIANT_ALTERNATIVE_HPP

#include <cstddef>
#include <type_traits>

namespace yaul {

/** // doc: variant_alternative {{{
 * \brief Provides compile-time indexed access to the types of the alternatives
 *        of the possibly cv-qualified variant, combining cv-qualifications of
 *        the variant (if any) with the cv-qualifications of the alternative.
 *
 *  \tparam I Index of the alternative to be returned.
 *  \tparam Variant The variant with alternatives.
 *
 *  \par Synopsis
 *  \code
 *    template< std::size_t I, typename Variant >
 *    struct variant_alternative; // undefined
 *  \endcode
 *  \code
 *    template< std::size_t I, typename T0, typename... Types >
 *    struct variant_alternative<I, variant<T0,Types...> >;
 *  \endcode
 *  \code
 *    template< std::size_t I, typename T >
 *    struct variant_alternative<I, T const>
 *      : std::add_const<typename variant_alternative<I,T>::type> {};
 *    template< std::size_t I, typename T >
 *    struct variant_alternative<I, T volatile>
 *      : std::add_volatile<typename variant_alternative<I,T>::type> {};
 *    template< std::size_t I, typename T >
 *    struct variant_alternative<I, T const volatile>
 *      : std::add_cv<typename variant_alternative<I,T>::type> {};
 *  \endcode
 */ // }}}
template< std::size_t I, typename Variant >
  struct variant_alternative;
/** // doc: variant_alternative_t {{{
 * \brief An alias for `typename variant_alternative<I,Variant>::type`
 */ // }}}
template< std::size_t I, typename Variant >
  using variant_alternative_t = typename variant_alternative<I,Variant>::type;

/** \cond DOXYGEN_SHOW_TEMPLATE_SPECIALIZATIONS */
template< std::size_t I, typename T >
  struct variant_alternative<I, const T>
    : std::add_const<typename variant_alternative<I, T>::type>
  { };
template< std::size_t I, typename T >
  struct variant_alternative<I, volatile T>
    : std::add_volatile<typename variant_alternative<I, T>::type>
  { };
template< std::size_t I, typename T >
  struct variant_alternative<I, const volatile T>
    : std::add_cv<typename variant_alternative<I, T>::type>
  { };
/** \endcond */

} // end namespace yaul

#include <yaul/variant/variant_fwd.hpp>
#include <yaul/variant/detail/variadic_element.hpp>

namespace yaul {

/** \cond DOXYGEN_SHOW_TEMPLATE_SPECIALIZATIONS */
template<std::size_t I, template<typename...> class V, typename T0, typename... Others>
  struct variant_alternative<I, V<T0,Others...> >
    : std::conditional <
          detail::variant::is_variant_template<V>::value
        , detail::variant::variadic_element<I, T0, Others...>
        , detail::variant::not_a_variant< V<T0,Others...> > // has no nested `type`
      >::type
  { };
/** \endcond */

} // end namespace variant

#endif /* YAUL_VARIANT_VARIANT_ALTERNATIVE_HPP */
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
