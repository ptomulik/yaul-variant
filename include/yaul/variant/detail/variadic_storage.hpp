// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

// yaul/variant/detail/variadic_storage.hpp

/** // doc: yaul/variant/detail/variadic_storage.hpp {{{
 * \file yaul/variant/detail/variadic_storage.hpp
 * \brief Provides \ref yaul::detail::variant::variadic_storage class
 */ // }}}
#ifndef YAUL_VARIANT_DETAIL_VARIADIC_STORAGE_HPP
#define YAUL_VARIANT_DETAIL_VARIADIC_STORAGE_HPP

#include <yaul/variant/detail/variadic_union.hpp>
#include <yaul/variant/detail/variadic_index.hpp>
#include <yaul/variant/detail/index_sequence.hpp>
#include <yaul/variant/detail/in_place_tags.hpp>
#include <yaul/variant/detail/all.hpp>
#include <type_traits>
#include <cstddef>
#include <array>

namespace yaul {
/** // doc: variant_npos {{{
  * \brief Returned by \ref yaul::variant::index() when
  *        valueless_by_exception() is `true`.
  */ // }}}
constexpr std::size_t variant_npos = -1;
}

namespace yaul { namespace detail { namespace variant {

template<std::size_t I, typename Union>
#if !defined(YAUL_VARIANT_NO_CONSTEXPR_VOID)
constexpr
#endif
void variadic_union_destruct(Union&& u)
  noexcept(noexcept(std::forward<Union>(u).destruct(in_place_index_t<I>{})))
{ std::forward<Union>(u).destruct(in_place_index_t<I>{}); }

template<typename Union, std::size_t... Indices>
struct variadic_storage_vtable
{
  static constexpr void (*dtors[])(Union const&) =
    { &variadic_union_destruct<Indices, Union const&>... };
};

template<typename Union, std::size_t... Indices>
constexpr void (*variadic_storage_vtable<Union,Indices...>::dtors[])(Union const&);

template<bool TriviallyDestructible, typename... Types>
struct variadic_storage_impl
{
private:
  using Union = variadic_union<Types...>;
  using Index = variadic_index_t<Types...>;

public:

  typedef Index index_type;
  typedef Union union_type;

  template<std::size_t I, typename... Args>
  constexpr
  variadic_storage_impl(in_place_index_t<I>, Args&&... args)
    noexcept(noexcept(Union(in_place_index_t<I>{}, std::forward<Args>(args)...)))
    : union_(in_place_index_t<I>{}, std::forward<Args>(args)...), index_(I)
  { }

  constexpr index_type
  index() const noexcept
  { return index_; }

protected:
  Union union_;
  Index index_;
};
/** \cond DOXYGEN_SHOW_TEMPLATE_SPECIALIZATIONS */
template<typename... Types>
struct variadic_storage_impl<false, Types...>
  : variadic_storage_impl<true, Types...>
{
private:
  using Base = variadic_storage_impl<true, Types...>;
  using Union = typename Base::union_type;
  using Index = typename Base::index_type;

  template<size_t... Indices>
#if !defined(YAUL_VARIANT_NO_CONSTEXPR_VOID)
  constexpr
#endif
  void reset_impl(index_sequence<Indices...>) const
    noexcept(all<noexcept(variadic_union_destruct<Indices>(std::declval<Union const&>()))...>::value)
  {
    if(this->index_ != Index(::yaul::variant_npos))
      variadic_storage_vtable<Union, Indices...>::dtors[this->index_](this->union_);
  }

public:
  using Base::Base;

  void reset()
    noexcept(noexcept(
          std::declval<variadic_storage_impl&>().
          reset_impl(typename make_index_sequence<sizeof...(Types)>::type{})
          ))
  {
    reset_impl(typename make_index_sequence<sizeof...(Types)>::type{});
    this->index_ = Index(::yaul::variant_npos);
  }

  ~variadic_storage_impl()
    noexcept(noexcept(std::declval<variadic_storage_impl&>().reset()))
  { reset(); }
};
/** \endcond */

/** // doc: variadic_storage {{{
 * \todo Write documentation
 */ // }}}
template<typename... Types>
struct variadic_storage
  : variadic_storage_impl<all<std::is_trivially_destructible<Types>::value...>::value, Types...>
{
private:
  using Base = variadic_storage_impl<all<std::is_trivially_destructible<Types>::value...>::value, Types...>;
public:
  using Base::Base;
};

} } } // end namespace yaul::detail::variant

#endif /* YAUL_VARIANT_DETAIL_VARIADIC_STORAGE_HPP */
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
