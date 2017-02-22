// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

// yaul/variant/variant_find_if.hpp

/** // doc: yaul/variant/variant_find_if.hpp {{{
 * \file yaul/variant/variant_find_if.hpp
 * \todo Write documentation
 */ // }}}
#ifndef YAUL_VARIANT_VARIANT_FIND_IF_HPP
#define YAUL_VARIANT_VARIANT_FIND_IF_HPP

#include <yaul/variant/recursive_wrapper_fwd.hpp>
#include <yaul/variant/detail/recursive_flag.hpp>
#include <yaul/variant/detail/enable_recursive.hpp>
#include <yaul/variant/variant_fwd.hpp>
#include <cstddef>
#include <type_traits>

namespace yaul { namespace detail { namespace variant {
/** \ingroup FixMe FIXME
 * @{ */
template< std::size_t I, typename Pred, typename... Types >
  struct variant_find_if_impl;

/** \cond DOXYGEN_SHOW_TEMPLATE_SPECIALIZATIONS */
template< std::size_t I, typename Pred, typename T0, typename... Others >
  struct variant_find_if_impl<I, Pred, T0, Others...>
    : std::conditional<
        Pred::template apply<typename unwrap_recursive_wrapper<T0>::type>::value
      , std::integral_constant<std::size_t, I>
      , variant_find_if_impl<I+1, Pred, Others...>
      >::type
  { };


// nothing found, end of search
template< std::size_t I, typename Pred >
  struct variant_find_if_impl<I, Pred >
    : std::integral_constant<std::size_t, I>
  { };
/** \endcond */
/** @} */
} } } // end namespace yaul::detail::variant

namespace yaul {
/** \ingroup MetafunctionsGroup
 * @{ */
/** // doc: variant_find_if {{{
 * \todo Write documentation
 */ // }}}
template< typename U, typename Variant >
  struct variant_find_if;

/** \cond DOXYGEN_SHOW_TEMPLATE_SPECIALIZATIONS */
template< typename Pred, typename T0, typename... Others>
  struct variant_find_if<Pred, variant<T0, Others...> >
    : detail::variant::variant_find_if_impl<0ul, Pred, T0, Others...>
  {
  };
template< typename Pred, typename T0, typename... Others>
  struct variant_find_if<Pred, variant<detail::variant::recursive_flag<T0>, Others...> >
    : detail::variant::variant_find_if_impl<
        0ul, Pred,
        typename detail::variant::enable_recursive<T0, variant<detail::variant::recursive_flag<T0>,Others...> >::type,
        typename detail::variant::enable_recursive<Others, variant<detail::variant::recursive_flag<T0>,Others...> >::type...
      >
  {
  };
/** \endcond */
/** @} */
} // end namespace yaul


#endif /* YAUL_VARIANT_VARIANT_FIND_IF_HPP */
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
