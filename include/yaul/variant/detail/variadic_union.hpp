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

/** // doc: variadic_union_member {{{
 * \brief Wrapper for \ref yaul::detail::variant::variadic_union "variadic_union"
 *        members.
 *
 * \tparam T The type to be wrapped
 *
 * \par Description
 * Any valid instantiation of this class is trivially destructible, which is
 * its main purpose.
 */ // }}}
template<typename T, bool = std::is_trivially_destructible<T>::value>
struct variadic_union_member;

template<typename T>
struct variadic_union_member<T, true>
{
  template<typename... Args>
  constexpr variadic_union_member(in_place_index_t<0ul>, Args&&... args)
      noexcept(noexcept(T(std::forward<Args>(args)...)))
    : storage(std::forward<Args>(args)...)
  { }

#if !defined(YAUL_VARIANT_NO_CONSTEXPR_ON_NONCONST_FUNCTIONS)
  constexpr
#endif
  T& get()& noexcept
  { return storage; }

  constexpr
  const T& get() const& noexcept
  { return storage; }

#if !defined(YAUL_VARIANT_NO_CONSTEXPR_ON_NONCONST_FUNCTIONS)
  constexpr
#endif
  volatile T& get() volatile& noexcept
  { return storage; }

  constexpr
  const volatile T& get() const volatile& noexcept
  { return storage; }

#if !defined(YAUL_VARIANT_NO_CONSTEXPR_ON_NONCONST_FUNCTIONS)
  constexpr
#endif
  T&& get()&& noexcept
  { return std::move(storage); }

#ifndef YAUL_VARIANT_NO_RRCV_QUALIFIED_FUNCTIONS
  constexpr const T&& get() const&& noexcept
  { return std::move(storage); }

#if !defined(YAUL_VARIANT_NO_CONSTEXPR_ON_NONCONST_FUNCTIONS)
  constexpr
#endif
  volatile T&& get() volatile&& noexcept
  { return std::move(storage); }

  constexpr const volatile T&& get() const volatile&& noexcept
  { return std::move(storage); }
#endif

  T storage;
};

template<typename T>
struct variadic_union_member<T, false>
{
  template<typename... Args>
#if !defined(YAUL_VARIANT_NO_CONSTEXPR_ON_NONEMPTY_CTORS) && \
    !defined(YAUL_VARIANT_NO_CONSTEXPR_ON_FUNCTIONS_WITH_PLACEMENT_NEW)
  constexpr
#endif
  variadic_union_member(in_place_index_t<0ul>, Args&&... args)
  { ::new (&storage) T(std::forward<Args>(args)...); }

#if !defined(YAUL_VARIANT_NO_CONSTEXPR_ON_NONCONST_FUNCTIONS)
  constexpr
#endif
  T& get()& noexcept
  { return *get_ptr(); }

  constexpr
  const T& get() const& noexcept
  { return *get_ptr(); }

#if !defined(YAUL_VARIANT_NO_CONSTEXPR_ON_NONCONST_FUNCTIONS)
  constexpr
#endif
  volatile T& get() volatile& noexcept
  { return *get_ptr(); }

  constexpr
  const volatile T& get() const volatile& noexcept
  { return *get_ptr(); }

#if !defined(YAUL_VARIANT_NO_CONSTEXPR_ON_NONCONST_FUNCTIONS)
  constexpr
#endif
  T&& get()&& noexcept
  { return std::move(*get_ptr()); }

#ifndef YAUL_VARIANT_NO_RRCV_QUALIFIED_FUNCTIONS
  constexpr
  const T&& get() const&& noexcept
  { return std::move(*get_ptr()); }

#if !defined(YAUL_VARIANT_NO_CONSTEXPR_ON_NONCONST_FUNCTIONS)
  constexpr
#endif
  volatile T&& get() volatile&& noexcept
  { return std::move(*get_ptr()); }

  constexpr
  const volatile T&& get() const volatile&& noexcept
  { return std::move(*get_ptr()); }
#endif // YAUL_VARIANT_NO_RRCV_QUALIFIED_FUNCTIONS

#if !defined(YAUL_VARIANT_NO_CONSTEXPR_ON_NONCONST_FUNCTIONS)
  constexpr
#endif
  void* get_addr() noexcept
  { return static_cast<void*>(&storage); }

  constexpr
  void const* get_addr() const noexcept
  { return static_cast<const void*>(&storage); }

#if !defined(YAUL_VARIANT_NO_CONSTEXPR_ON_NONCONST_FUNCTIONS)
  constexpr
#endif
  void volatile* get_addr() volatile noexcept
  { return static_cast<volatile void*>(&storage); }

  constexpr
  void const volatile* get_addr() const volatile noexcept
  { return static_cast<const volatile void*>(&storage); }

#if !defined(YAUL_VARIANT_NO_CONSTEXPR_ON_NONCONST_FUNCTIONS)
  constexpr
#endif
  T* get_ptr() noexcept
  { return static_cast<T*>(get_addr()); }

  constexpr
  T const* get_ptr() const noexcept
  { return static_cast<T const*>(get_addr()); }

#if !defined(YAUL_VARIANT_NO_CONSTEXPR_ON_NONCONST_FUNCTIONS)
  constexpr
#endif
  T volatile* get_ptr() volatile noexcept
  { return static_cast<T volatile*>(get_addr()); }

  constexpr
  T const volatile* get_ptr() const volatile noexcept
  { return static_cast<T const volatile*>(get_addr()); }

  std::aligned_storage<sizeof(T), alignof(T)> storage;
};

template<std::size_t I, std::size_t J, typename... Types>
struct variadic_element_impl
{ /* intentionaly empty - necessary to work in SFINAE context */ };

template<std::size_t I, std::size_t J, typename First, typename... Types>
struct variadic_element_impl<I, J, First, Types...>
  : variadic_element_impl<I, J+1ul, Types...>
{ };

template<std::size_t I, typename First, typename... Rest>
struct variadic_element_impl<I, I, First, Rest...>
{
  typedef First type;
};


template<std::size_t I, typename... Types>
struct variadic_element
  : variadic_element_impl<I, 0ul, Types...>
{ /* do not put any static_asserts here - this metafun is used for SFINAE */ };


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
