// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

// yaul/variant/variant_find.hpp

/** // doc: yaul/variant/variant_find.hpp {{{
 * \file yaul/variant/variant_find.hpp
 * \todo Write documentation
 */ // }}}
#ifndef YAUL_VARIANT_VARIANT_FIND_HPP
#define YAUL_VARIANT_VARIANT_FIND_HPP

#include <yaul/variant/variant_find_if.hpp>
#include <type_traits>

namespace yaul { namespace detail { namespace variant {
/** \ingroup FixMe FIXME
 * @{ */
template<typename U>
struct variant_find_same
{
  template<typename T>
    struct apply
      : std::is_same<U,T>
    {};
};
/** \endcond */
/** @} */
} } } // end namespace yaul::detail::variant

namespace yaul {
/** \ingroup MetafunctionsGroup
 * @{ */
/** // doc: variant_find {{{
 * \todo Write documentation
 */ // }}}
template< typename U, typename Variant >
  struct variant_find
    : variant_find_if<detail::variant::variant_find_same<U>, Variant>
  { };
/** @} */
} // end namespace yaul


#endif /* YAUL_VARIANT_VARIANT_FIND_HPP */
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
