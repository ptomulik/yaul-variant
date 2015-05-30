// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

// yaul/variant/detail/recursive_variant_fwd.hpp

/** // doc: yaul/variant/detail/recursive_variant_fwd.hpp {{{
 * \file yaul/variant/detail/recursive_variant_fwd.hpp
 * \todo Write documentation
 */ // }}}
#ifndef YAUL_VARIANT_DETAIL_RECURSIVE_VARIANT_FWD_HPP
#define YAUL_VARIANT_DETAIL_RECURSIVE_VARIANT_FWD_HPP

#include <yaul/variant/recursive_wrapper_fwd.hpp>
#include <type_traits>

namespace yaul { namespace detail { namespace variant {

template< typename T >
  class recursive_variant;


template< typename T >
  struct is_recusive_variant_impl
    : std::integral_constant<bool, false>
  { };

/** \cond DOXYGEN_SHOW_TEMPLATE_SPECIALIZATIONS */
template< typename T >
  struct is_recusive_variant_impl< recursive_variant<T> >
    : std::integral_constant<bool, true>
  { };
/** \endcond */

template< typename T >
  struct is_recursive_variant
    : is_recusive_variant_impl<typename std::remove_cv<T>::type>
  {
  };

/** // doc: wrap_recursive_variant {{{
 * \todo Write documentation
 */ // }}}
template< typename T >
  struct wrap_recursive_variant
  {
    typedef recursive_variant<T> type;
  };

/** \cond DOXYGEN_SHOW_TEMPLATE_SPECIALIZATIONS */
template< typename T >
  struct wrap_recursive_variant<T const>
  {
    typedef typename wrap_recursive_variant<T>::type const type;
  };
template< typename T >
  struct wrap_recursive_variant<T volatile>
  {
    typedef typename wrap_recursive_variant<T>::type volatile type;
  };
template< typename T >
  struct wrap_recursive_variant<T const volatile>
  {
    typedef typename wrap_recursive_variant<T>::type const volatile type;
  };
/** \endcond */
/** @} */

} } } // end namespace yaul::detail::variant


namespace yaul { namespace detail {

/** \cond DOXYGEN_SHOW_TEMPLATE_SPECIALIZATIONS */
template<typename T>
struct is_recursive_wrapper_impl< ::yaul::detail::variant::recursive_variant<T> >
  : std::integral_constant<bool, true>
{ };
/** \endcond */

} } // end namespace yaul::detail

#endif /* YAUL_VARIANT_DETAIL_RECURSIVE_VARIANT_FWD_HPP */
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
