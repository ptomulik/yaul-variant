// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

// yaul/variant/detail/recursive_flag.hpp

/** // doc: yaul/variant/detail/recursive_flag.hpp {{{
 * \file yaul/variant/detail/recursive_flag.hpp
 * \todo Write documentation
 */ // }}}
#ifndef YAUL_VARIANT_DETAIL_RECURSIVE_FLAG_HPP
#define YAUL_VARIANT_DETAIL_RECURSIVE_FLAG_HPP

#include <type_traits>

namespace yaul { namespace detail { namespace variant {
/** \ingroup group-fixme FIXME:
 * @{ */
/** // doc: recursive_flag {{{
 * \todo Write documentation
 */ // }}}
template< typename T >
  struct recursive_flag
  {
    typedef T type;
  };

template< typename T >
  struct is_recursive_flag_impl
    : std::integral_constant<bool, false>
  {
  };

template< typename T >
  struct remove_recursive_flag
  {
    typedef T type;
  };


/** \cond DOXYGEN_SHOW_TEMPLATE_SPECIALIZATIONS */
template< typename T >
  struct is_recursive_flag_impl< recursive_flag<T> >
    : std::integral_constant<bool, true>
  { };

template< typename T >
  struct remove_recursive_flag< recursive_flag<T> >
  {
    typedef T type;
  };
/** \endcond */

/** // doc: is_recursive_flag {{{
 * \todo Write documentation
 */ // }}}
template< typename T >
  struct is_recursive_flag
    : is_recursive_flag_impl< typename std::remove_cv<T>::type >
  {

  };

/** @} */
} } } // end namespace yaul::detail::variant

#endif /* YAUL_VARIANT_DETAIL_RECURSIVE_FLAG_HPP */
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
