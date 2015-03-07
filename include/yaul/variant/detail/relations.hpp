// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

// yaul/variant/detail/relations.hpp

/** // doc: yaul/variant/detail/relations.hpp {{{
 * \file yaul/variant/detail/relations.hpp
 * \todo Write documentation
 */ // }}}
#ifndef YAUL_VARIANT_DETAIL_RELATIONS_HPP
#define YAUL_VARIANT_DETAIL_RELATIONS_HPP

#include <yaul/variant/static_visitor.hpp>
#include <yaul/variant/detail/apply_visitor_binary.hpp>
#include <type_traits>

namespace yaul { namespace detail { namespace variant {

struct comp_base
  : yaul::static_visitor<bool>
{
  template< typename T1, typename T2>
  constexpr bool operator()(const T1&, const T2&) const&& noexcept
  {
    return false;
  }
};

struct eq_comp
  : comp_base
{
  using comp_base::operator();
  template< typename T >
  constexpr bool operator()(const T& lhs, const T& rhs) const&&
    noexcept(noexcept(lhs == rhs))
  {
    return lhs == rhs;
  }
};

struct neq_comp
  : comp_base
{
  using comp_base::operator();
  template< typename T >
  constexpr bool operator()(const T& lhs, const T& rhs) const&&
    noexcept(noexcept(lhs != rhs))
  {
    return lhs != rhs;
  }
};

struct lt_comp
  : comp_base
{
  using comp_base::operator();
  template< typename T >
  constexpr bool operator()(const T& lhs, const T& rhs) const&&
    noexcept(noexcept(lhs < rhs))
  {
    return lhs < rhs;
  }
};

struct gt_comp
  : comp_base
{
  using comp_base::operator();
  template< typename T >
  constexpr bool operator()(const T& lhs, const T& rhs) const&&
    noexcept(noexcept(lhs > rhs))
  {
    return lhs > rhs;
  }
};

struct le_comp
  : comp_base
{
  using comp_base::operator();
  template< typename T >
  constexpr bool operator()(const T& lhs, const T& rhs) const&&
    noexcept(noexcept(lhs <= rhs))
  {
    return lhs <= rhs;
  }
};

struct ge_comp
  : comp_base
{
  using comp_base::operator();
  template< typename T >
  constexpr bool operator()(const T& lhs, const T& rhs) const&&
    noexcept(noexcept(lhs >= rhs))
  {
    return lhs >= rhs;
  }
};

} } } // end namespace yaul::detail::variant

#endif /* YAUL_VARIANT_DETAIL_RELATIONS_HPP */
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
