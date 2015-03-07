// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

// yaul/variant/detail/index_selector.hpp

/** // doc: yaul/variant/detail/index_selector.hpp {{{
 * \file yaul/variant/detail/index_selector.hpp
 * \todo Write documentation
 */ // }}}
#ifndef YAUL_VARIANT_DETAIL_INDEX_SELECTOR_HPP
#define YAUL_VARIANT_DETAIL_INDEX_SELECTOR_HPP

#include <type_traits>
#include <cstddef>

namespace yaul { namespace detail { namespace variant {
/** \ingroup DetailMetafunctionsGroup
 * @{ */
template <std::size_t I, typename... Types>
struct index_selector_impl;

template <std::size_t I, typename Head, typename... Tail>
struct index_selector_impl<I, Head, Tail...>
  : index_selector_impl<I+1, Tail...>
{
  using index_selector_impl<I+1, Tail...>::apply;
  static constexpr std::size_t apply(Head&) noexcept { return I; }
  static constexpr std::size_t apply(Head const&) noexcept { return I; }
  static constexpr std::size_t apply(Head&&) noexcept { return I; }
};

template <std::size_t I, typename Last>
struct index_selector_impl<I, Last>
{
  static constexpr std::size_t apply(Last&) noexcept { return I; }
  static constexpr std::size_t apply(Last const&) noexcept { return I; }
  static constexpr std::size_t apply(Last&&) noexcept { return I; }
};

template <typename... Types>
struct index_selector
  : index_selector_impl<0ul, Types...>
{
  using index_selector_impl<0ul, Types...>::apply;
};
/** @} */
} } } // end namespace yaul::detail::variant

#endif /* YAUL_VARIANT_DETAIL_INDEX_SELECTOR_HPP */
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
