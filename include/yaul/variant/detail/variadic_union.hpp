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

/** // doc: variadic_union {{{
 * \brief An template union with variadic list of types
 *
 * \tparam Types Alternative types to be supported by union
 *
 * \par Synopsis
 * \code
 *  template<typename... Types>
 *  union variadic_union
 *  {
 *  private:
 *    template<std::size_t I>
 *    using T = typename variadic_element<I, Types...>::type;         // (1)
 *
 *  public:
 *    template<std::size_t I, typename... Args>
 *    constexpr variadic_union(in_place_index_t<I>, Args&&... args);  // (2)
 *
 *    template<std::size_t I>
 *    constexpr T<I>&
 *    get(in_place_index_t<I>)& noexcept;
 *
 *    template<std::size_t I>
 *    constexpr T<I> const&
 *    get(in_place_index_t<I>) const& noexcept;
 *
 *    template<std::size_t I>
 *    constexpr T<I> volatile&
 *    get(in_place_index_t<I>) volatile& noexcept;
 *
 *    template<std::size_t I>
 *    constexpr T<I> const volatile&
 *    get(in_place_index_t<I>) const volatile& noexcept;
 *
 *    template<std::size_t I>
 *    constexpr T<I>&&
 *    get(in_place_index_t<I>)&& noexcept;
 *
 *    template<std::size_t I>
 *    constexpr T<I> const&&
 *    get(in_place_index_t<I>) const&& noexcept;
 *
 *    template<std::size_t I>
 *    constexpr T<I> volatile&&
 *    get(in_place_index_t<I>) volatile&& noexcept;
 *
 *    template<std::size_t I>
 *    constexpr T<I> const volatile&&
 *    get(in_place_index_t<I>) const volatile&& noexcept;
 *
 *    template<std::size_t I>
 *    constexpr void
 *    destruct(in_place_index_t<I>);    // (3)
 *  };
 * \endcode
 *
 * (1) Actual declaration of `T` is quite different and in particular doesn't
 *     work for `I == 0`.
 *
 * (2) If the underlying constructor call `T<I>(std::forward<Args>(args)...)`
 *     is `noexcept` then `variadic_union(in_place_index_t<I>{}, args...)` is
 *     also `noexcept`.
 *
 * (3) If `T<I>` is not trivially destructible, then `destruct(in_place_index<I>)`
 *     invokes `T<I>::~T<I>()`. Otherwise, the function is empty.
 *
 * \par Description
 * \ref yaul::detail::variant::variadic_union "Variadic_union" supports value
 * initialization and retrieval of one of alternative `Types...`.
 */ // }}}
template<typename... Types>
union variadic_union{ };

/** \cond DOXYGEN_SHOW_TEMPLATE_SPECIALIZATIONS */
template<typename First, typename... Rest>
union variadic_union<First, Rest...>
{
private:
  using FirstT  = variadic_union_member<First>;
  using RestT = variadic_union<Rest...>;
  FirstT first;
  RestT rest;

// FIXME: Is it necessary? I found it in gcc libstdc++ implementation.
//  constexpr variadic_union()
//    noexcept(noexcept(variadic_union<Rest...>()))
//    : rest()
//  { }

  template<std::size_t I>
  using T = typename variadic_element<I-1,Rest...>::type;

public:
  template<typename... Args>
  constexpr variadic_union(in_place_index_t<0ul>, Args&&... args)
    noexcept(noexcept(FirstT(in_place_index_t<0ul>{}, std::forward<Args>(args)...)))
    : first(in_place_index_t<0ul>{}, std::forward<Args>(args)...)
  { }

  template<std::size_t I, typename... Args>
  constexpr variadic_union(in_place_index_t<I>, Args&&... args)
    noexcept(noexcept(RestT(in_place_index_t<I-1>{}, std::forward<Args>(args)...)))
    : rest(in_place_index_t<I-1>{}, std::forward<Args>(args)...)
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

  template<std::size_t I>
#if !defined(YAUL_VARIANT_NO_CONSTEXPR_ON_NONCONST_FUNCTIONS)
  constexpr
#endif
  T<I>& // SFINAEd out if I >= sizeof...(Types)
  get(in_place_index_t<I>)& noexcept
  { return rest.get(in_place_index_t<I-1>{}); }

  template<std::size_t I>
  constexpr
  T<I> const& // SFINAEd out if I >= sizeof...(Types)
  get(in_place_index_t<I>) const& noexcept
  { return rest.get(in_place_index_t<I-1>{}); }

  template<std::size_t I>
#if !defined(YAUL_VARIANT_NO_CONSTEXPR_ON_NONCONST_FUNCTIONS)
  constexpr
#endif
  T<I> volatile& // SFINAEd out if I >= sizeof...(Types)
  get(in_place_index_t<I>) volatile& noexcept
  { return rest.get(in_place_index_t<I-1>{}); }

  template<std::size_t I>
  constexpr
  T<I> const volatile& // SFINAEd out if I >= sizeof...(Types)
  get(in_place_index_t<I>) const volatile& noexcept
  { return rest.get(in_place_index_t<I-1>{}); }

  template<std::size_t I>
#if !defined(YAUL_VARIANT_NO_CONSTEXPR_ON_NONCONST_FUNCTIONS)
  constexpr
#endif
  T<I>&& // SFINAEd out if I >= sizeof...(Types)
  get(in_place_index_t<I>)&& noexcept
  { return std::move(rest).get(in_place_index_t<I-1>{}); }

#ifndef YAUL_VARIANT_NO_RRCV_QUALIFIED_FUNCTIONS
  template<std::size_t I>
  constexpr
  T<I> const&& // SFINAEd out if I >= sizeof...(Types)
  get(in_place_index_t<I>) const&& noexcept
  { return std::move(rest).get(in_place_index_t<I-1>{}); }

  template<std::size_t I>
#if !defined(YAUL_VARIANT_NO_CONSTEXPR_ON_NONCONST_FUNCTIONS)
  constexpr
#endif
  T<I> volatile&& // SFINAEd out if I >= sizeof...(Types)
  get(in_place_index_t<I>) volatile&& noexcept
  { return std::move(rest).get(in_place_index_t<I-1>{}); }

  template<std::size_t I>
  constexpr
  T<I> const volatile&& // SFINAEd out if I >= sizeof...(Types)
  get(in_place_index_t<I>) const volatile&& noexcept
  { return std::move(rest).get(in_place_index_t<I-1>{}); }
#endif // YAUL_VARIANT_NO_RRCV_QUALIFIED_FUNCTIONS

  template<typename U = First>
#if !defined(YAUL_VARIANT_NO_CONSTEXPR_ON_NONCONST_FUNCTIONS)
  constexpr
#endif
  typename std::enable_if<!std::is_trivially_destructible<U>::value>::type
  destruct(in_place_index_t<0ul>) const
    noexcept(noexcept(std::declval<variadic_union_member<U>&>().destruct()))
  { first.destruct(); }

  template<typename U = First>
#if !defined(YAUL_VARIANT_NO_CONSTEXPR_ON_NONCONST_FUNCTIONS) && \
    !defined(YAUL_VARIANT_NO_CONSTEXPR_VOID)
  constexpr
#endif
  typename std::enable_if<std::is_trivially_destructible<U>::value>::type
  destruct(in_place_index_t<0ul>) const
    noexcept
  { }

  template<std::size_t I>
#if !defined(YAUL_VARIANT_NO_CONSTEXPR_ON_NONCONST_FUNCTIONS) && \
    !defined(YAUL_VARIANT_NO_CONSTEXPR_VOID)
  constexpr
#endif
  void destruct(in_place_index_t<I>) const
    noexcept(noexcept(std::declval<RestT&>().destruct(in_place_index_t<I-1>{})))
  { rest.destruct(in_place_index_t<I-1>{}); }
};
/** \endcond */

} } } // end namespace yaul::detail::variant

#endif /* YAUL_VARIANT_DETAIL_VARIADIC_UNION_HPP */
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
