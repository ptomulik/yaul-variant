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
} // end namespace yaul

namespace yaul { namespace detail {

template< typename T >
  struct is_recursive_wrapper_impl
    : std::integral_constant<bool, false>
  { };

template< typename T >
  struct is_recursive_wrapper_impl< ::yaul::recursive_wrapper<T> >
    : std::integral_constant<bool, true>
  { };
} } // end namespace yaul::detail

namespace yaul {
template< typename T >
  struct is_recursive_wrapper
    : detail::is_recursive_wrapper_impl<typename std::remove_cv<T>::type>
  { };

template< typename T >
  struct wrap_recursive
  { typedef recursive_wrapper<T> type; };

template< typename T >
  struct unwrap_recursive
  { typedef T type; };

/** \cond DOXYGEN_SHOW_TEMPLATE_SPECIALIZATIONS */
template< typename T >
  struct wrap_recursive<T const>
  { typedef const typename wrap_recursive<T>::type type; };
template< typename T >
  struct wrap_recursive<T volatile>
  { typedef volatile typename wrap_recursive<T>::type type; };
template< typename T >
  struct wrap_recursive<T const volatile>
  { typedef const volatile typename wrap_recursive<T>::type type; };

template< typename T >
  struct unwrap_recursive< recursive_wrapper<T> >
  { typedef T type; };
template< typename T >
  struct unwrap_recursive< const recursive_wrapper<T> >
    : std::add_const<T>
  { };
template< typename T >
  struct unwrap_recursive< volatile recursive_wrapper<T> >
    : std::add_volatile<T>
  { };
template< typename T >
  struct unwrap_recursive< const volatile recursive_wrapper<T> >
    : std::add_cv<T>
  { };
/** \endcond */
} // end namespace yaul



#endif /* YAUL_VARIANT_RECURSIVE_WRAPPER_FWD_HPP */
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
