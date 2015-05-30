// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

// yaul/variant/recursive_wrapper_fwd.hpp

/** // doc: yaul/variant/recursive_wrapper_fwd.hpp {{{
 * \file yaul/variant/recursive_wrapper_fwd.hpp
 * \todo Write documentation
 */ // }}}
#ifndef YAUL_VARIANT_RECURSIVE_WRAPPER_FWD_HPP
#define YAUL_VARIANT_RECURSIVE_WRAPPER_FWD_HPP

#include <type_traits>

namespace yaul {

template< typename T > class recursive_wrapper;
template< typename T > struct is_recursive_wrapper;

} // end namespace yaul

namespace yaul { namespace detail {

template< typename T >
  struct is_recursive_wrapper_impl
    : std::integral_constant<bool, false>
  { };

/** \cond DOXYGEN_SHOW_TEMPLATE_SPECIALIZATIONS */
template< typename T >
  struct is_recursive_wrapper_impl< ::yaul::recursive_wrapper<T> >
    : std::integral_constant<bool, true>
  { };
/** \endcond */

template< typename T, bool IsWrapper = yaul::is_recursive_wrapper<T>::value >
  struct unwrap_recursive_wrapper_impl
  {
    typedef T type;
  };

/** \cond DOXYGEN_SHOW_TEMPLATE_SPECIALIZATIONS */
template< template <typename...> class F, typename T >
  struct unwrap_recursive_wrapper_impl<F<T>, true>
  {
    typedef T type;
  };
/** \endcond */

} } // end namespace yaul::detail

namespace yaul {
template< typename T >
  struct is_recursive_wrapper
    : detail::is_recursive_wrapper_impl<typename std::remove_cv<T>::type>
  { };

/** // doc: unwrap_recursive_wrapper {{{
 * \todo Write documentation
 */ // }}}
template< typename T >
  struct unwrap_recursive_wrapper
    : detail::unwrap_recursive_wrapper_impl<T>
  { };
/** \cond DOXYGEN_SHOW_TEMPLATE_SPECIALIZATIONS */
template< typename T >
  struct unwrap_recursive_wrapper<T const>
  {
    typedef typename unwrap_recursive_wrapper<T>::type const type;
  };
template< typename T >
  struct unwrap_recursive_wrapper<T volatile>
  {
    typedef typename unwrap_recursive_wrapper<T>::type volatile type;
  };
template< typename T >
  struct unwrap_recursive_wrapper<T const volatile>
  {
    typedef typename unwrap_recursive_wrapper<T>::type const volatile type;
  };
/** \endcond */
} // end namespace yaul



#endif /* YAUL_VARIANT_RECURSIVE_WRAPPER_FWD_HPP */
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
