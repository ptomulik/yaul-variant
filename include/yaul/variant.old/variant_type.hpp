// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

// yaul/variant/variant_type.hpp

/** // doc: yaul/variant/variant_type.hpp {{{
 * \file yaul/variant/variant_type.hpp
 * \todo Write documentation
 */ // }}}
#ifndef YAUL_VARIANT_DETAIL_VARIANT_TYPE_HPP
#define YAUL_VARIANT_DETAIL_VARIANT_TYPE_HPP

#include <yaul/variant/variant_fwd.hpp>
#include <cstddef>

namespace yaul {
/** \ingroup MetafunctionsGroup
 * @{ */
/** // doc: variant_type {{{
 * \todo Write documentation
 */ // }}}
template <std::size_t I, typename Variant>
  struct variant_type;
/** \cond DOXYGEN_SHOW_TEMPLATE_SPECIALIZATIONS */
template <std::size_t I, typename T0, typename... Others>
  struct variant_type<I, yaul::variant<T0,Others...> >
    : variant_type<I-1, yaul::variant<Others...> >
  { };
template <typename T0, typename... Others>
  struct variant_type<0ul, yaul::variant<T0,Others...> >
  {
    typedef T0 type;
  };
/** \endcond */
/** @} */
} // end namespace variant

#endif /* YAUL_VARIANT_DETAIL_VARIANT_TYPE_HPP */
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
