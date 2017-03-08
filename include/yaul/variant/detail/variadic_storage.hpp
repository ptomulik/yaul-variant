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
#include <yaul/variant/detail/all_trivially_destructible.hpp>
#include <yaul/variant/detail/index_sequence.hpp>
#include <yaul/variant/detail/in_place_tags.hpp>
#include <cstddef>

namespace yaul { namespace detail { namespace variant {

template<typename Union, std::size_t I>
#if !defined(YAUL_VARIANT_NO_CONSTEXPR_VOID)
constexpr
#endif
void variadic_union_dtor(Union&& u)
{ std::forward<Union>(u).destruct(in_place_index_t<I>{}); }

template<bool TrivialDtor, typename... Types>
struct variadic_storage_impl
{
private:
  using Union = variadic_union<Types...>;
  using Index = variadic_index_t<Types...>;

  template<std::size_t... Indices>
    struct dtors
    {
      static constexpr void (*vtab[])(Union const&) =
        { &variadic_union_dtor<Union const&, Indices>... };
    };


  template<size_t... Indices>
  constexpr
  void reset_impl(index_sequence<Indices...>)
  {
    // some guard here... for index_ being out of range
    dtors<Indices...>::vtab[index_](union_);
  }

public:
#if 0
  typedef Index index_type;

  template<std::size_t I, typename... Args>
  constexpr
  variadic_storage(in_place_index<I>, Args&&... args)
    noexcept(noexcept(union_(in_place_index<I>{}, std::forward<Args>(args)...)))
    : index_(I), union_(in_place_index<I>{}, std::forward<Args>(args)...)
  { }
#endif


  void reset() // noexcept?
  {
    reset_impl(make_index_sequence<sizeof...(Types)>{});
    // index_ = ... set out of range
  }

private:
  Index index_;
  Union union_;
};

#if 0
template<typename... Types>
struct variadic_storage_impl<false, Types...>
  : variadic_storage_impl<true,Types...>
{
  //~variadic_storage_impl()
  //{
  //}
};
#endif

/** // doc: variadic_storage {{{
 * \todo Write documentation
 */ // }}}
template<typename... Types>
struct variadic_storage
  : variadic_storage_impl<all_trivially_destructible<Types...>::value, Types...>
{
};

} } } // end namespace yaul::detail::variant

#endif /* YAUL_VARIANT_DETAIL_VARIADIC_STORAGE_HPP */
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
