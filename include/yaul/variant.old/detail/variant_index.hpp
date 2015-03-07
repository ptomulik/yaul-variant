// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

// yaul/variant/detail/variant_index.hpp

/** // doc: yaul/variant/detail/variant_index.hpp {{{
 * \file yaul/variant/detail/variant_index.hpp
 * \todo Write documentation
 */ // }}}
#ifndef YAUL_VARIANT_DETAIL_VARIANT_INDEX_HPP
#define YAUL_VARIANT_DETAIL_VARIANT_INDEX_HPP

#include <type_traits>
#include <cstddef>

namespace yaul { namespace detail { namespace variant {
/** \ingroup FixMeGroup FIXME:
 * @{ */
/** // doc: ctor_index {{{
 * \todo Write documentation
 */ // }}}
template<std::size_t I>
struct variant_index
  : std::integral_constant<std::size_t, I>
{
};
/** @} */
} } } // yaul::detail::variant

#endif /* YAUL_VARIANT_DETAIL_VARIANT_INDEX_HPP */
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
