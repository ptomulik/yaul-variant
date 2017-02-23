// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

// yaul/variant/detail/find.hpp

/** // doc: yaul/variant/detail/find.hpp {{{
 * \file yaul/variant/detail/find.hpp
 * \todo Write documentation
 */ // }}}
#ifndef YAUL_VARIANT_DETAIL_FIND_HPP
#define YAUL_VARIANT_DETAIL_FIND_HPP

#include <yaul/variant/detail/find_if.hpp>
#include <yaul/variant/detail/predicates.hpp>

namespace yaul { namespace detail { namespace variant {
/** \ingroup group-detail-algorithms
 * @{ */
/** // doc: find {{{
 * \todo Write documentation
 */ // }}}
template< typename U, typename Variant >
  struct find
    : find_if<is_same_as<U>, Variant>
  { };
/** @} */
} } } // end namespace yaul::detail::variant


#endif /* YAUL_VARIANT_DETAIL_FIND_HPP */
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
