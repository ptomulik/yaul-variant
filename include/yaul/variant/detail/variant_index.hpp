// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

// yaul/variant/detail/variant_index.hpp

/** // doc: yaul/variant/detail/variant_index.hpp {{{
 * \file yaul/variant/detail/variant_index.hpp
 * \brief Provides \ref yaul::detail::variant::variant_index metafunction
 */ // }}}
#ifndef YAUL_VARIANT_DETAIL_VARIANT_INDEX_HPP
#define YAUL_VARIANT_DETAIL_VARIANT_INDEX_HPP

#include <yaul/variant/variant_size.hpp>
#include <type_traits>
#include <climits>

namespace yaul { namespace detail { namespace variant {

template< typename Variant, typename = void >
  struct variant_index_impl
  {
    typedef int type;
  };
/** \cond DOXYGEN_SHOW_TEMPLATE_SPECIALIZATIONS */
template< typename Variant >
  struct variant_index_impl<
      Variant
    , typename std::enable_if<(variant_size<Variant>::value < SCHAR_MAX)>::type
    >
  {
    typedef signed char type;
  };
/** \endcond */

/** // doc: variant_index {{{
 * \brief Determines the integer type that should be used to represent
 *        alternative type index for `Variant`.
 *
 * \tparam Variant The variant with alternatives
 *
 * \par Synopsis
 * \code
 *  template <typename Variant>
 *  struct variant_index
 *    {
 *      typename unspecified type;
 *    };
 * \endcode
 *
 * \par Description
 * If the number of alternatives in `Variant` is less than `SCHAR_MAX`,
 * the `variant_index<Variant>::type` yields `signed char`. Otherwise,
 * it yields `int`.
 *
 */ // }}}
template< typename Variant >
  struct variant_index
    : variant_index_impl<Variant>
  { };
/** // doc: variant_index_t {{{
 * \todo Write documentation
 */ // }}}
template< typename Variant >
  using variant_index_t = typename variant_index<Variant>::type;
} } } // end namespace yaul::detail::variant

#endif /* YAUL_VARIANT_DETAIL_VARIANT_INDEX_HPP */
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
