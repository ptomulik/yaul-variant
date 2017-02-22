// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

// yaul/variant/detail/contains.hpp

/** // doc: yaul/variant/detail/contains.hpp {{{
 * \file yaul/variant/detail/contains.hpp
 * \todo Write documentation
 */ // }}}
#ifndef YAUL_VARIANT_DETAIL_CONTAINS_HPP
#define YAUL_VARIANT_DETAIL_CONTAINS_HPP

#include <yaul/variant/detail/find.hpp>
#include <yaul/variant/variant_size.hpp>
#include <type_traits>

namespace yaul { namespace detail { namespace variant {
/** \ingroup MetafunctionsGroup
 * @{ */
/** // doc: contains {{{
 * \todo Write documentation
 */ // }}}
template <typename U, typename Variant>
  struct contains
    : std::integral_constant<bool, find<U,Variant>::value != variant_size<Variant>::value>
  { };
/** @} */
} } } // end namespace yaul::detail::variant

#endif /* YAUL_VARIANT_DETAIL_CONTAINS_HPP */
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
