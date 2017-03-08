// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

// yaul/variant/detail/all_trivially_destructible.hpp

/** // doc: yaul/variant/detail/all_trivially_destructible.hpp {{{
 * \file yaul/variant/detail/all_trivially_destructible.hpp
 * \brief Provides \ref yaul::detail::variant::all_trivially_destructible metafunction
 */ // }}}
#ifndef YAUL_VARIANT_DETAIL__ALL_TRIVIALLY_DESTRUCTIBLE_HPP
#define YAUL_VARIANT_DETAIL__ALL_TRIVIALLY_DESTRUCTIBLE_HPP

#include <type_traits>

namespace yaul { namespace detail { namespace variant {
/** // doc: all_trivially_destructible {{{
 * \brief Yields `true` if all of the `Types...` are trivially destructible.
 *
 * \tparam Types The types to be examined. For empty types, `true` is returned.
 *
 * \par Synopsis
 * \code
 *  template<typename... Types>
 *  struct all_trivially_destructible
 *   : std::integral_constant<bool, unspecified>
 *  { };
 * \endcode
 */ // }}}
template <typename... Types>
struct all_trivially_destructible
  : std::integral_constant<bool, true>
{ };

template <typename First, typename... Rest>
struct all_trivially_destructible<First,Rest...>
  : std::integral_constant<
      bool
    , (std::is_trivially_destructible<First>::value &&
       all_trivially_destructible<Rest...>::value)
    >
{ };
} } } // end namespace yaul::detail::variant

#endif /* YAUL_VARIANT_DETAIL__ALL_TRIVIALLY_DESTRUCTIBLE_HPP */
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
