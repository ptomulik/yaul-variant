// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

// yaul/variant/detail/is_nonrecursive_trivially_destructible.hpp

/** // doc: yaul/variant/detail/is_nonrecursive_trivially_destructible.hpp {{{
 * \file yaul/variant/detail/is_nonrecursive_trivially_destructible.hpp
 * \todo Write documentation
 */ // }}}
#ifndef YAUL_VARIANT_DETAIL_IS_NONRECURSIVE_TRIVIALLY_DESTRUCTIBLE_HPP
#define YAUL_VARIANT_DETAIL_IS_NONRECURSIVE_TRIVIALLY_DESTRUCTIBLE_HPP

#include <yaul/variant/recursive_wrapper_fwd.hpp>
#include <type_traits>

namespace yaul { namespace detail { namespace variant {

template< typename T, bool = yaul::is_recursive_wrapper<T>::value>
  struct is_nonrecursive_trivially_destructible_impl
    : std::is_trivially_destructible<T>
  { };
// We know in advance, that recursive wrapper is not trivially destructible
// (it maintains internal pointer). We won't it to get instantiated by
// std::is_trivially_destructible, as this leads to template recursion and
// yields compile errors on gcc. So, for recursive wrappers we simply return
// false.
template< typename T >
  struct is_nonrecursive_trivially_destructible_impl<T,true>
    : std::integral_constant<bool, false>
  { };

template< typename T >
  struct is_nonrecursive_trivially_destructible
    : is_nonrecursive_trivially_destructible_impl<T>
  { };

} } } // end namespace yaul::detail::variant

#endif /* YAUL_VARIANT_DETAIL_IS_NONRECURSIVE_TRIVIALLY_DESTRUCTIBLE_HPP */
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
