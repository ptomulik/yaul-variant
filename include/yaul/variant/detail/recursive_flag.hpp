// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

// yaul/variant/detail/recursive_flag.hpp

/** // doc: yaul/variant/detail/recursive_flag.hpp {{{
 * \file yaul/variant/detail/recursive_flag.hpp
 * \brief Provides \ref yaul::detail::variant::recursive_flag
 */ // }}}
#ifndef YAUL_VARIANT_DETAIL_RECURSIVE_FLAG_HPP
#define YAUL_VARIANT_DETAIL_RECURSIVE_FLAG_HPP

namespace yaul { namespace detail { namespace variant {

/** // doc: recursive_flag {{{
 * \brief A type wrapper used to distinguish recursive variants from others
 *
 * A recursive variant shall use `recursive_flag<T0>` (instead of `T0`)
 * as the first alternative on the type list.
 */ // }}}
template< typename T >
  struct recursive_flag
  {
    typedef T type;
  };

/** // doc: remove_recursive_flag {{{
 * \brief Unwraps the \ref recursive_flag wrapper.
 *
 * \tparam T An input type
 *
 * \par Synopsis
 * \code
 * template<typename T>
 * struct remove_recursive_flag
 * {
 *    typedef unspecified type;
 * };
 * \endcode
 *
 * \par Description
 * for any type `X`
 * \code
 * using R = remove_recursive_flag< recursive_flag<X> >::type;
 * \endcode
 * yields `X`, and
 * \code
 * using R = remove_recursive_flag<X>::type;
 * \endcode
 * yields the input type `X`.
 */ // }}}
template< typename T >
  struct remove_recursive_flag
  {
    typedef T type;
  };

/** \cond DOXYGEN_SHOW_TEMPLATE_SPECIALIZATIONS */
template< typename T >
  struct remove_recursive_flag< recursive_flag<T> >
  {
    typedef T type;
  };
/** \endcond */

} } } // end namespace yaul::detail::variant

#endif /* YAUL_VARIANT_DETAIL_RECURSIVE_FLAG_HPP */
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
