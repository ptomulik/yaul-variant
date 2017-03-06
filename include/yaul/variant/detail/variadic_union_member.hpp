// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

// yaul/variant/detail/variadic_union_member.hpp

/** // doc: yaul/variant/detail/variadic_union_member.hpp {{{
 * \file yaul/variant/detail/variadic_union_member.hpp
 * \brief Provides \ref yaul::detail::variant::variadic_union_member
 */ // }}}
#ifndef YAUL_VARIANT_DETAIL_VARIADIC_UNION_MEMBER_HPP
#define YAUL_VARIANT_DETAIL_VARIADIC_UNION_MEMBER_HPP

#include <yaul/variant/detail/in_place_tags.hpp>
#include <yaul/variant/config.hpp>
#include <type_traits>
#include <utility>

namespace yaul { namespace detail { namespace variant {

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

} } } // end namespace yaul::detail::variant

#endif /* YAUL_VARIANT_DETAIL_VARIADIC_UNION_MEMBER_HPP */
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
