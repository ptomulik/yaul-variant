// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

// yaul/variant/variant_find.hpp

/** // doc: yaul/variant/variant_find.hpp {{{
 * \file yaul/variant/variant_find.hpp
 * \todo Write documentation
 */ // }}}
#ifndef YAUL_VARIANT_VARIANT_FIND_HPP
#define YAUL_VARIANT_VARIANT_FIND_HPP

#include <yaul/variant/recursive_wrapper_fwd.hpp>
#include <yaul/variant/detail/recursive_flag.hpp>
#include <yaul/variant/detail/enable_recursive.hpp>
#include <yaul/variant/variant_fwd.hpp>
#include <cstddef>
#include <type_traits>

namespace yaul { namespace detail { namespace variant {
/** \ingroup FixMe FIXME
 * @{ */
template< std::size_t I, typename U, typename... Types >
  struct variant_find_impl;

/** \cond DOXYGEN_SHOW_TEMPLATE_SPECIALIZATIONS */
template< std::size_t I, typename U, typename T0, typename... Others >
  struct variant_find_impl<I, U, T0, Others...>
    : variant_find_impl< I+1, U, Others... >
  { };

// type matched...
template< std::size_t I, typename U, typename... Others >
  struct variant_find_impl<I, typename unwrap_recursive_wrapper<U>::type, U, Others... >
    : std::integral_constant<std::size_t, I>
  { };

// nothing found, end of search
template< std::size_t I, typename U >
  struct variant_find_impl< I, U >
    : std::integral_constant<std::size_t, I>
  { };
/** \endcond */
/** @} */
} } } // end namespace yaul::detail::variant

namespace yaul {
/** \ingroup MetafunctionsGroup
 * @{ */
/** // doc: variant_find {{{
 * \todo Write documentation
 */ // }}}
template< typename U, typename Variant >
  struct variant_find;

/** \cond DOXYGEN_SHOW_TEMPLATE_SPECIALIZATIONS */
template< typename U, typename T0, typename... Others>
  struct variant_find<U, variant<T0, Others...> >
    : detail::variant::variant_find_impl<0ul, U, T0, Others...>
  {
  };
template< typename U, typename T0, typename... Others>
  struct variant_find<U, variant<detail::variant::recursive_flag<T0>, Others...> >
    : detail::variant::variant_find_impl<0ul, U, T0, Others...>
  {
  };
/** \endcond */
/** @} */
} // end namespace yaul


#endif /* YAUL_VARIANT_VARIANT_FIND_HPP */
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
