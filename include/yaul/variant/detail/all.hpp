// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

// yaul/variant/detail/all.hpp

/** // doc: yaul/variant/detail/all.hpp {{{
 * \file yaul/variant/detail/all.hpp
 * \todo Write documentation
 */ // }}}
#ifndef YAUL_VARIANT_DETAIL_ALL_HPP
#define YAUL_VARIANT_DETAIL_ALL_HPP

#include <yaul/variant/detail/any.hpp>
#include <yaul/variant/detail/predicates.hpp>
#include <type_traits>

namespace yaul { namespace detail { namespace variant {
/** \ingroup MetafunctionsGroup
 * @{ */
/** // doc: variant_all {{{
 * \todo Write documentation
 */ // }}}
template <typename Pred, typename Variant>
  struct all
      : std::integral_constant<bool, !(any<not_<Pred>, Variant>::value)>
  { };
/** @} */
} } } // end namespace yaul::detail::variant

#endif /* YAUL_VARIANT_DETAIL_ALL_HPP */
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
