// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

// yaul/variant/variant_contains.hpp

/** // doc: yaul/variant/variant_contains.hpp {{{
 * \file yaul/variant/variant_contains.hpp
 * \todo Write documentation
 */ // }}}
#ifndef YAUL_VARIANT_VARIANT_CONTAINS_HPP
#define YAUL_VARIANT_VARIANT_CONTAINS_HPP

#include <yaul/variant/variant_find.hpp>
#include <yaul/variant/variant_size.hpp>
#include <type_traits>

namespace yaul {
/** \ingroup MetafunctionsGroup 
 * @{ */
/** // doc: variant_contains {{{
 * \todo Write documentation
 */ // }}}
template <typename U, typename Variant>
  struct variant_contains
    : std::integral_constant<
          bool
        , variant_find<U,Variant>::value != variant_size<Variant>::value
      >
  { };
/** @} */
} // end namespace yaul::detail::variant

#endif /* YAUL_VARIANT_VARIANT_CONTAINS_HPP */
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
