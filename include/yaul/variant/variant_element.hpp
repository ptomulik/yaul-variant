// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

// yaul/variant/variant_element.hpp

/** // doc: yaul/variant/variant_element.hpp {{{
 * \file yaul/variant/variant_element.hpp
 * \todo Write documentation
 */ // }}}
#ifndef YAUL_VARIANT_VARIANT_ELEMENT_HPP
#define YAUL_VARIANT_VARIANT_ELEMENT_HPP

#include <cstddef>
#include <type_traits>

namespace yaul {
/** \ingroup group-metafunctions
 * @{ */
/** // doc: variant_element {{{
 * \todo Write documentation
 */ // }}}
template< std::size_t I, typename Variant >
  struct variant_element;
/** // doc: variant_element_t {{{
 * \todo Write documentation
 */ // }}}
template< std::size_t I, typename Variant >
  using variant_element_t = typename variant_element<I,Variant>::type;
/** \cond DOXYGEN_SHOW_TEMPLATE_SPECIALIZATIONS */
template< std::size_t I, typename T >
  struct variant_element<I, const T>
    : std::add_const<typename variant_element<I, T>::type>
  { };
template< std::size_t I, typename T >
  struct variant_element<I, volatile T>
    : std::add_volatile<typename variant_element<I, T>::type>
  { };
template< std::size_t I, typename T >
  struct variant_element<I, const volatile T>
    : std::add_cv<typename variant_element<I, T>::type>
  { };
/** \endcond */
/** @} */
} // end namespace yaul

#include <yaul/variant/variant_fwd.hpp>

namespace yaul {
/** \ingroup group-metafunctions
 * @{ */
/** \cond DOXYGEN_SHOW_TEMPLATE_SPECIALIZATIONS */
template< std::size_t I, typename T0, typename... Others >
  struct variant_element<I, yaul::variant<T0,Others...> >
    : variant_element<I-1, yaul::variant<Others...> >
  { };
template< typename T0, typename... Others >
  struct variant_element<0ul, yaul::variant<T0,Others...> >
  {
    typedef T0 type;
  };
/** \endcond */
/** @} */
} // end namespace variant

#endif /* YAUL_VARIANT_VARIANT_ELEMENT_HPP */
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
