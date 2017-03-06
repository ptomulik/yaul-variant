// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

// yaul/variant/detail/variadic_element.hpp

/** // doc: yaul/variant/detail/variadic_element.hpp {{{
 * \file yaul/variant/detail/variadic_element.hpp
 * \brief Provides \ref yaul::detail::variant::variadic_element metafunction
 */ // }}}
#ifndef YAUL_VARIANT_DETAIL_VARIADIC_ELEMENT_HPP
#define YAUL_VARIANT_DETAIL_VARIADIC_ELEMENT_HPP

#include <cstddef>

namespace yaul { namespace detail { namespace variant {

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

/** // doc: variadic_element {{{
 * \brief Return I'th type from variadic list of `Types`
 *
 * \tparam I Zero-based index of the type from `Types` to be returned
 * \tparam Types Types to pick the I'th type from
 *
 * \par Synopsis
 * \code
 *  template<std::size_t I, typename... Types>
 *  struct variadic_element
 *  {
 *    typedef unspecified type; // undefined if (I >= sizeof...(Types))
 *  };
 * \endcode
 *
 * \par Description
 * If `I < sizeof...(Types)`, then
 * \code
 *  variadic_element<I, Types...>::type
 * \endcode
 * is identical with the `I`-th of `Types...`. Otherwise the nested type `type`
 * is undefined.
 */ // }}}
template<std::size_t I, typename... Types>
struct variadic_element
  : variadic_element_impl<I, 0ul, Types...>
{ /* do not put any static_asserts here - this metafun is used for SFINAE */ };

} } } // end namespace yaul::detail::variant

#endif /* YAUL_VARIANT_DETAIL_VARIADIC_ELEMENT_HPP */
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
