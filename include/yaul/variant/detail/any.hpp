// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

// yaul/variant/detail/any.hpp

/** // doc: yaul/variant/detail/any.hpp {{{
 * \file yaul/variant/detail/any.hpp
 * \todo Write documentation
 */ // }}}
#ifndef YAUL_VARIANT_DETAIL_ANY_HPP
#define YAUL_VARIANT_DETAIL_ANY_HPP

#include <yaul/variant/detail/find_if.hpp>
#include <yaul/variant/variant_size.hpp>
#include <type_traits>

namespace yaul { namespace detail { namespace variant {
/** \ingroup MetafunctionsGroup
 * @{ */
/** // doc: any {{{
 * \todo Write documentation
 */ // }}}
template <typename Pred, typename Variant>
  struct any
    : std::integral_constant<bool, find_if<Pred,Variant>::value != variant_size<Variant>::value>
  { };
/** @} */
} } } // end namespace yaul::detail::variant

#endif /* YAUL_VARIANT_DETAIL_ANY_HPP */
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
