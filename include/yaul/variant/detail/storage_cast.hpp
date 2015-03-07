// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

// yaul/variant/detail/storage_cast.hpp

/** // doc: yaul/variant/detail/storage_cast.hpp {{{
 * \file yaul/variant/detail/storage_cast.hpp
 * \todo Write documentation
 */ // }}}
#ifndef YAUL_VARIANT_DETAIL_STORAGE_CAST_HPP
#define YAUL_VARIANT_DETAIL_STORAGE_CAST_HPP

#include <yaul/variant/recursive_wrapper_fwd.hpp>
#include <type_traits>
#include <utility>

namespace yaul { namespace detail { namespace variant {

template< typename T, bool IsRecursiveWrapper = is_recursive_wrapper<
                        typename std::remove_reference<T>::type
                      >::value >
  struct storage_cast_impl
  {
    typedef T type;

    template< typename S >
    constexpr static type
    apply(S&& s) noexcept
    {
      return reinterpret_cast<T>(s);
    }
  };

template< typename T >
  struct storage_cast_impl<T, true>
  {
    typedef decltype(std::declval<T>().get()) type;

    template< typename S >
    constexpr static type
    apply(S&& s) noexcept
    {
      return reinterpret_cast<T>(s).get();
    }
  };


template< typename T, typename S>
constexpr typename storage_cast_impl<T>::type
storage_cast(S&& s) noexcept
{
  return storage_cast_impl<T>::apply(std::forward<S>(s));
}
} } } // end namespace yaul::detail::variant

#endif /* YAUL_VARIANT_DETAIL_STORAGE_CAST_HPP */
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
