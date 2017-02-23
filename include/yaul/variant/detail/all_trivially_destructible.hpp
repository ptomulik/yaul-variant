// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

// yaul/variant/detail/all_trivially_destructible.hpp

/** // doc: yaul/variant/detail/all_trivially_destructible.hpp {{{
 * \file yaul/variant/detail/all_trivially_destructible.hpp
 * \todo Write documentation
 */ // }}}
#ifndef YAUL_VARIANT_DETAIL_ALL_TRIVIALLY_DESTRUCTIBLE_HPP
#define YAUL_VARIANT_DETAIL_ALL_TRIVIALLY_DESTRUCTIBLE_HPP

#include <yaul/variant/variant_fwd.hpp>
#include <yaul/variant/detail/recursive_flag.hpp>
#include <yaul/variant/detail/enable_recursive.hpp>
#include <yaul/variant/detail/is_nonrecursive_trivially_destructible.hpp>

namespace yaul { namespace detail { namespace variant {

template< typename... Types >
  struct all_trivially_destructible_impl;

template< typename T0, typename... Other >
  struct all_trivially_destructible_impl<T0,Other...>
    : std::integral_constant<
        bool
      , (all_trivially_destructible_impl<T0>::value &&
         all_trivially_destructible_impl<Other...>::value)
      >
  { };

template< typename T0 >
  struct all_trivially_destructible_impl<T0>
    : is_nonrecursive_trivially_destructible<
        typename remove_recursive_flag<T0>::type
      >
  { };

template< typename Variant >
  struct all_trivially_destructible;

template< typename T0, typename... Others >
  struct all_trivially_destructible< yaul::variant<T0,Others...> >
    : all_trivially_destructible_impl<T0,Others...>
  { };

template< typename T0, typename... Others >
  struct all_trivially_destructible< yaul::variant<recursive_flag<T0>,Others...> >
    : all_trivially_destructible_impl<
        typename enable_recursive<T0, yaul::variant<recursive_flag<T0>,Others...> >::type,
        typename enable_recursive<Others, yaul::variant<recursive_flag<T0>,Others...> >::type...
    >
  { };
} } } // end namespace yaul::detail::variant

#endif /* YAUL_VARIANT_DETAIL_ALL_TRIVIALLY_DESTRUCTIBLE_HPP */
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
