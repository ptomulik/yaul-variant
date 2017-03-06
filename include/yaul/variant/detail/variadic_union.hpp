// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

// yaul/variant/detail/variadic_union.hpp

/** // doc: yaul/variant/detail/variadic_union.hpp {{{
 * \file yaul/variant/detail/variadic_union.hpp
 * \brief Provides \ref yaul::detail::variant::variadic_union
 */ // }}}
#ifndef YAUL_VARIANT_DETAIL_VARIADIC_UNION_HPP
#define YAUL_VARIANT_DETAIL_VARIADIC_UNION_HPP

#include <yaul/variant/detail/variadic_union_member.hpp>
#include <yaul/variant/detail/variadic_element.hpp>
#include <yaul/variant/detail/in_place_tags.hpp>
#include <yaul/variant/config.hpp>
#include <type_traits>
#include <utility>

namespace yaul { namespace detail { namespace variant {

//
// Current C++ standard does not allow placement new in constexpr functions
// (and ctors), so we can't just use std::aligned_storage in constexpr context.
// For that reason, a facility such as variadic union has to be used.
//
template<typename... Types>
union variadic_union{ };

/** \cond DOXYGEN_SHOW_TEMPLATE_SPECIALIZATIONS */
template<typename First, typename... Rest>
union variadic_union<First, Rest...>
{
  variadic_union_member<First> first;
  variadic_union<Rest...> rest;

// FIXME: Is it necessary? I found it in gcc libstdc++ implementation.
//  constexpr variadic_union()
//    noexcept(noexcept(variadic_union<Rest...>()))
//    : rest()
//  { }

  template<typename... Args>
  constexpr variadic_union(in_place_index_t<0ul>, Args&&... args)
    noexcept(noexcept(variadic_union_member<First>(in_place_index_t<0ul>{}, std::forward<Args>(args)...)))
    : first(in_place_index_t<0ul>{}, std::forward<Args>(args)...)
  { }

  template<std::size_t Np, typename... Args>
  constexpr variadic_union(in_place_index_t<Np>, Args&&... args)
    noexcept(noexcept(variadic_union<Rest...>(in_place_index_t<Np-1>{}, std::forward<Args>(args)...)))
    : rest(in_place_index_t<Np-1>{}, std::forward<Args>(args)...)
  { }

#if !defined(YAUL_VARIANT_NO_CONSTEXPR_ON_NONCONST_FUNCTIONS)
  constexpr
#endif
  First& get(in_place_index_t<0ul>)& noexcept
  { return first.get(); }

  constexpr
  First const& get(in_place_index_t<0ul>) const& noexcept
  { return first.get(); }

#if !defined(YAUL_VARIANT_NO_CONSTEXPR_ON_NONCONST_FUNCTIONS)
  constexpr
#endif
  First volatile& get(in_place_index_t<0ul>) volatile& noexcept
  { return first.get(); }

  constexpr
  First const volatile& get(in_place_index_t<0ul>) const volatile& noexcept
  { return first.get(); }

#if !defined(YAUL_VARIANT_NO_CONSTEXPR_ON_NONCONST_FUNCTIONS)
  constexpr
#endif
  First&& get(in_place_index_t<0ul>)&& noexcept
  { return std::move(first).get(); }

#ifndef YAUL_VARIANT_NO_RRCV_QUALIFIED_FUNCTIONS
  constexpr
  First const&& get(in_place_index_t<0ul>) const&& noexcept
  { return std::move(first).get(); }

#if !defined(YAUL_VARIANT_NO_CONSTEXPR_ON_NONCONST_FUNCTIONS)
  constexpr
#endif
  First volatile&& get(in_place_index_t<0ul>) volatile&& noexcept
  { return std::move(first).get(); }

  constexpr
  First const volatile&& get(in_place_index_t<0ul>) const volatile&& noexcept
  { return std::move(first).get(); }
#endif // YAUL_VARIANT_NO_RRCV_QUALIFIED_FUNCTIONS

  template<std::size_t Np>
#if !defined(YAUL_VARIANT_NO_CONSTEXPR_ON_NONCONST_FUNCTIONS)
  constexpr
#endif
  typename variadic_element<(Np-1), Rest...>::type& // causes SFINAE
  get(in_place_index_t<Np>)& noexcept
  { return rest.get(in_place_index_t<Np-1>{}); }

  template<std::size_t Np>
  constexpr
  typename variadic_element<(Np-1), Rest...>::type const& // causes SFINAE
  get(in_place_index_t<Np>) const& noexcept
  { return rest.get(in_place_index_t<Np-1>{}); }

  template<std::size_t Np>
#if !defined(YAUL_VARIANT_NO_CONSTEXPR_ON_NONCONST_FUNCTIONS)
  constexpr
#endif
  typename variadic_element<(Np-1), Rest...>::type volatile& // causes SFINAE
  get(in_place_index_t<Np>) volatile& noexcept
  { return rest.get(in_place_index_t<Np-1>{}); }

  template<std::size_t Np>
  constexpr
  typename variadic_element<(Np-1), Rest...>::type const volatile& // causes SFINAE
  get(in_place_index_t<Np>) const volatile& noexcept
  { return rest.get(in_place_index_t<Np-1>{}); }

  template<std::size_t Np>
#if !defined(YAUL_VARIANT_NO_CONSTEXPR_ON_NONCONST_FUNCTIONS)
  constexpr
#endif
  typename variadic_element<(Np-1), Rest...>::type&& // causes SFINAE
  get(in_place_index_t<Np>)&& noexcept
  { return std::move(rest).get(in_place_index_t<Np-1>{}); }

#ifndef YAUL_VARIANT_NO_RRCV_QUALIFIED_FUNCTIONS
  template<std::size_t Np>
  constexpr
  typename variadic_element<(Np-1), Rest...>::type const&& // causes SFINAE
  get(in_place_index_t<Np>) const&& noexcept
  { return std::move(rest).get(in_place_index_t<Np-1>{}); }

  template<std::size_t Np>
#if !defined(YAUL_VARIANT_NO_CONSTEXPR_ON_NONCONST_FUNCTIONS)
  constexpr
#endif
  typename variadic_element<(Np-1), Rest...>::type volatile&& // causes SFINAE
  get(in_place_index_t<Np>) volatile&& noexcept
  { return std::move(rest).get(in_place_index_t<Np-1>{}); }

  template<std::size_t Np>
  constexpr
  typename variadic_element<(Np-1), Rest...>::type const volatile&& // causes SFINAE
  get(in_place_index_t<Np>) const volatile&& noexcept
  { return std::move(rest).get(in_place_index_t<Np-1>{}); }
#endif // YAUL_VARIANT_NO_RRCV_QUALIFIED_FUNCTIONS
};
/** \endcond */

} } } // end namespace yaul::detail::variant

#endif /* YAUL_VARIANT_DETAIL_VARIADIC_UNION_HPP */
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
