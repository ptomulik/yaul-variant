// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

// yaul/variant/apply_visitor.hpp

/** // doc: yaul/variant/apply_visitor.hpp {{{
 * \file yaul/variant/apply_visitor.hpp
 * \todo Write documentation
 */ // }}}
#ifndef YAUL_VARIANT_APPLY_VISITOR_HPP
#define YAUL_VARIANT_APPLY_VISITOR_HPP

namespace yaul {
/** // doc: apply_visitor_delayed_t {{{
 * \todo Write documentation
 */ // }}}
template<typename Visitor>
class apply_visitor_delayed_t
{
  // TODO: implement
};
/** // doc: apply_visitor_delayed_cpp14_t {{{
 * \todo Write documentation
 */ // }}}
template<typename Visitor>
class apply_visitor_delayed_cpp14_t
{
  // TODO: implement
};
/** // doc: apply_visitor() {{{
 * \todo Write documentation
 */ // }}}
template<typename Visitor, typename Variant>
typename Visitor::result_type
apply_visitor(Visitor&, Variant&)
{
  // TODO: implement
}
/** // doc: apply_visitor() {{{
 * \todo Write documentation
 */ // }}}
template<typename Visitor, typename Variant>
typename Visitor::result_type
apply_visitor(const Visitor&, Variant&)
{
  // TODO: implement
}
/** // doc: apply_visitor() {{{
 * \todo Write documentation
 */ // }}}
template<typename BinaryVisitor, typename Variant1, typename Variant2>
typename BinaryVisitor::result_type /* OR decltype(auto) */
apply_visitor(BinaryVisitor&, Variant1&, Variant2&)
{
  // TODO: implement
}
/** // doc: apply_visitor() {{{
 * \todo Write documentation
 */ // }}}
template<typename BinaryVisitor, typename Variant1, typename Variant2>
typename BinaryVisitor::result_type /* OR decltype(auto) */
apply_visitor(const BinaryVisitor&, Variant1&, Variant2&)
{
  // TODO: implement
}
/** // doc: apply_visitor() {{{
 * \todo Write documentation
 */ // }}}
template<typename MultiVisitor, typename Variant1, typename Variant2,
         typename Variant3, typename... Tail>
typename MultiVisitor::result_type /* OR decltype(auto) */
apply_visitor(MultiVisitor&, Variant1&, Variant2&, Variant3&, Tail&...)
{
  // TODO: implement
}
/** // doc: apply_visitor() {{{
 * \todo Write documentation
 */ // }}}
template<typename MultiVisitor, typename Variant1, typename Variant2,
         typename Variant3, typename... Tail>
typename MultiVisitor::result_type /* OR decltype(auto) */
apply_visitor(const MultiVisitor&, Variant1&, Variant2&, Variant3&, Tail&...)
{
  // TODO: implement
}
/** // doc: apply_visitor() {{{
 * \todo Write documentation
 */ // }}}
template<typename Visitor>
apply_visitor_delayed_t<Visitor>
apply_visitor(Visitor&)
{
  // TODO: implement
}
/** // doc: apply_visitor() {{{
 * \todo Write documentation
 */ // }}}
template<typename Visitor>
apply_visitor_delayed_cpp14_t<Visitor>
apply_visitor(Visitor&)
{
  // TODO: implement
}
} // end namespace yaul

#endif /* YAUL_VARIANT_APPLY_VISITOR_HPP */
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
