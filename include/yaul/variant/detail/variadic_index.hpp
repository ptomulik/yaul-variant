// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

// yaul/variant/detail/variadic_index.hpp

/** // doc: yaul/variant/detail/variadic_index.hpp {{{
 * \file yaul/variant/detail/variadic_index.hpp
 * \brief Provides \ref yaul::detail::variant::variadic_index metafunction
 */ // }}}
#ifndef YAUL_VARIANT_DETAIL_VARIADIC_INDEX_HPP
#define YAUL_VARIANT_DETAIL_VARIADIC_INDEX_HPP

#include <climits>

namespace yaul { namespace detail { namespace variant {

template<bool>  struct variadic_index_schar_if        { typedef signed char type; };
template<>      struct variadic_index_schar_if<false> { typedef int type; };

/** // variadic_index {{{
 * \brief Determine what integral type should be used to index alterternative
 *        types in a variadic types list.
 *
 * The result depends on the sizeof...(Types). The metafunction yields either
 * `signed char` (`sizeof...(Types) < SCHAR_MAX`) or `int`.
 */ // }}}
template<typename... Types>
struct variadic_index
  : variadic_index_schar_if<(sizeof...(Types) < SCHAR_MAX)>
{ };

/** // variadic_index_t {{{
 * \brief Alias for `typename variadic_index<Types...>::type`
 */ // }}}
template<typename... Types>
using variadic_index_t = typename variadic_index<Types...>::type;

} } } // end namespace yaul::detail::variant

#endif /* YAUL_VARIANT_DETAIL_VARIADIC_INDEX_HPP */
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
