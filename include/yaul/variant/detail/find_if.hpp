// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

// yaul/variant/detail/find_if.hpp

/** // doc: yaul/variant/detail/find_if.hpp {{{
 * \file yaul/variant/detail/find_if.hpp
 * \todo Write documentation
 */ // }}}
#ifndef YAUL_VARIANT_DETAIL_FIND_IF_HPP
#define YAUL_VARIANT_DETAIL_FIND_IF_HPP

#include <yaul/variant/recursive_wrapper_fwd.hpp>
#include <yaul/variant/detail/recursive_flag.hpp>
#include <yaul/variant/detail/enable_recursive.hpp>
#include <yaul/variant/variant_fwd.hpp>
#include <cstddef>
#include <type_traits>

namespace yaul { namespace detail { namespace variant {
/** \ingroup group-detail-algorithms
 * @{ */
/** // doc: find_if {{{
 * \todo Write documentation
 */ // }}}
#ifdef YAUL_VARIANT_DOXYGEN_INVOKED
template< typename Pred, typename Variant >
  struct find_if : std::integral_constant<std::size_t, index-value>
  { };
#else
template< typename Pred, typename Variant >
  struct find_if;

template< std::size_t I, typename Pred, typename... Types >
  struct find_if_impl;

/** \cond DOXYGEN_SHOW_TEMPLATE_SPECIALIZATIONS */
template< std::size_t I, typename Pred, typename T0, typename... Others >
  struct find_if_impl<I, Pred, T0, Others...>
    : std::conditional<
        Pred::template apply<typename unwrap_recursive_wrapper<T0>::type>::value
      , std::integral_constant<std::size_t, I>
      , find_if_impl<I+1, Pred, Others...>
      >::type
  { };


// nothing found, end of search
template< std::size_t I, typename Pred >
  struct find_if_impl<I, Pred >
    : std::integral_constant<std::size_t, I>
  { };

/** \cond DOXYGEN_SHOW_TEMPLATE_SPECIALIZATIONS */
template< typename Pred, typename T0, typename... Others>
  struct find_if<Pred, yaul::variant<T0, Others...> >
    : find_if_impl<0ul, Pred, T0, Others...>
  {
  };
template< typename Pred, typename T0, typename... Others>
  struct find_if<Pred, yaul::variant<recursive_flag<T0>, Others...> >
    : find_if_impl<
        0ul, Pred,
        typename enable_recursive<T0, yaul::variant<recursive_flag<T0>,Others...> >::type,
        typename enable_recursive<Others, yaul::variant<recursive_flag<T0>,Others...> >::type...
      >
  {
  };
/** \endcond */
#endif
/** @} */
} } } // end namespace yaul::detail::variant


#endif /* YAUL_VARIANT_DETAIL_FIND_IF_HPP */
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
