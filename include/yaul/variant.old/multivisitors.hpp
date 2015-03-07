// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

// yaul/variant/multivisitors.hpp

/** // doc: yaul/variant/multivisitors.hpp {{{
 * \file yaul/variant/multivisitors.hpp
 * \todo Write documentation
 */ // }}}
#ifndef YAUL_VARIANT_MULTIVISITORS_HPP
#define YAUL_VARIANT_MULTIVISITORS_HPP

namespace yaul {
/** // doc: apply_visitor() {{{
 * \todo Write documentation
 */ // }}}
template<typename MultiVisitor, typename Variant1, typename Variant2,
         typename Variant3, typename Tail...>
typename MultiVisitor::result_type /* OR decltype(auto) */
apply_visitor(MultiVisitor&, Variant1&, Variant2&, Variant3&, Tail&...)
{
  // TODO: implement
}
/** // doc: apply_visitor() {{{
 * \todo Write documentation
 */ // }}}
template<typename MultiVisitor, typename Variant1, typename Variant2,
         typename Variant3, typename Tail...>
typename MultiVisitor::result_type /* OR decltype(auto) */
apply_visitor(const MultiVisitor&, Variant1&, Variant2&, Variant3&, Tail&...)
{
  // TODO: implement
}
} // end namespace yaul

#endif /* YAUL_VARIANT_MULTIVISITORS_HPP */
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
