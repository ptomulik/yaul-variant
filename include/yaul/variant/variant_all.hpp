// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

// yaul/variant/variant_all.hpp

/** // doc: yaul/variant/variant_all.hpp {{{
 * \file yaul/variant/variant_all.hpp
 * \todo Write documentation
 */ // }}}
#ifndef YAUL_VARIANT_VARIANT_ALL_HPP
#define YAUL_VARIANT_VARIANT_ALL_HPP

#include <yaul/variant/variant_any.hpp>
#include <yaul/variant/detail/predicates.hpp>
#include <type_traits>

namespace yaul {
/** \ingroup MetafunctionsGroup
 * @{ */
/** // doc: variant_all {{{
 * \todo Write documentation
 */ // }}}
template <typename Pred, typename Variant>
  struct variant_all
      : std::integral_constant<
          bool
        , !(variant_any<detail::variant::not_<Pred>, Variant>::value)
        >
  { };
/** @} */
} // end namespace yaul::detail::variant

#endif /* YAUL_VARIANT_VARIANT_ALL_HPP */
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
