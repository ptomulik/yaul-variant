// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

// yaul/variant/detail/variant_getter.hpp

/** // doc: yaul/variant/detail/variant_getter.hpp {{{
 * \file yaul/variant/detail/variant_getter.hpp
 * \todo Write documentation
 */ // }}}
#ifndef YAUL_VARIANT_DETAIL_VARIANT_GETTER_HPP
#define YAUL_VARIANT_DETAIL_VARIANT_GETTER_HPP

#include <yaul/variant/static_visitor.hpp>
#include <yaul/variant/bad_get.hpp>
#include <type_traits>
#include <utility>

namespace yaul { namespace detail { namespace variant {
/** \ingroup group-fixme
 * @{ */
/** // doc: variant_getter {{{
 * \todo Write documentation
 */ // }}}
template< typename T >
struct variant_getter;

/** \cond DOXYGEN_SHOW_TEMPLATE_SPECIALIZATIONS */
template< typename T >
struct variant_getter<T&>
  : static_visitor<T&>
{
  constexpr T&
  operator()(T& t) const&& noexcept
  { return t; }

  template< typename TT >
  T& operator()(TT&&) const&&
  { throw yaul::bad_get(); }
};

template< typename T >
struct variant_getter<T&&>
  : static_visitor<T&&>
{
  constexpr T&&
  operator()(T&& t) const&& noexcept
  { return std::move(t); }

  template< typename TT >
  T&& operator()(TT&&) const&&
  { throw yaul::bad_get(); }
};

template< typename T >
struct variant_getter<T*>
  : static_visitor<T*>
{
  constexpr T*
  operator()(T& t) const&& noexcept
  { return &t; }

  template< typename TT >
  constexpr T*
  operator()(TT&&) const&& noexcept
  { return nullptr; }
};
/** \endcond */

/** @} */
} } } // end namespace yaul::detail::variant

#endif /* YAUL_VARIANT_DETAIL_VARIANT_GETTER_HPP */
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
