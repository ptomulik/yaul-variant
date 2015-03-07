// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

// yaul/variant/${unit}.hpp

/** // doc: yaul/variant/${unit}.hpp {{{
 * \file yaul/variant/${unit}.hpp
 * \todo Write documentation
 */ // }}}
#ifndef YAUL_VARIANT_DETAIL_VARIANT_WHICH_HPP
#define YAUL_VARIANT_DETAIL_VARIANT_WHICH_HPP

#include <yaul/variant/variant_size.hpp>
#include <type_traits>
#include <climits>

namespace yaul { namespace detail { namespace variant {
/** \ingroup DetailMetafunctions
 * @{ */
template< typename Variant, typename = void >
  struct variant_which_impl
  {
    typedef int type;
  };
/** // doc: variant_which {{{
 * \todo Write documentation
 */ // }}}
template< typename Variant >
  struct variant_which
    : variant_which_impl<Variant>
  { };
/** // doc: variant_which_t {{{
 * \todo Write documentation
 */ // }}}
template< typename Variant >
  using variant_which_t = typename variant_which<Variant>::type;
/** \cond DOXYGEN_SHOW_TEMPLATE_SPECIALIZATIONS */
template< typename Variant >
  struct variant_which_impl<
      Variant
    , typename std::enable_if<(variant_size<Variant>::value < SCHAR_MAX)>::type
    >
  {
    typedef signed char type;
  };
/** \endcond */
/** @} */
} } } // end namespace yaul::detail::variant

#endif /* YAUL_VARIANT_DETAIL_VARIANT_WHICH_HPP */
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
