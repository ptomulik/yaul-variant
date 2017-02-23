// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

// yaul/variant/variant_size.hpp

/** // doc: yaul/variant/variant_size.hpp {{{
 * \file yaul/variant/variant_size.hpp
 * \todo Write documentation
 */ // }}}
#ifndef YAUL_VARIANT_VARIANT_SIZE_HPP
#define YAUL_VARIANT_VARIANT_SIZE_HPP

#include <yaul/variant/variant_fwd.hpp>
#include <type_traits>
#include <cstddef>

namespace yaul {
/** \ingroup group-metafunctions
 * @{ */
/** // doc: variant_size {{{
 * \todo Write documentation
 */ // }}}
template <typename Variant>
  struct variant_size;
/** \cond DOXYGEN_SHOW_TEMPLATE_SPECIALIZATIONS */
template <typename T0, typename... Others>
  struct variant_size<yaul::variant<T0, Others...> >
    : std::integral_constant<std::size_t, 1ul + sizeof...(Others)>
  { };
/** \endcond */
/** @} */
} // end namespace yaul::detail::variant

#endif /* YAUL_VARIANT_VARIANT_SIZE_HPP */
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
