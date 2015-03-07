// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

// yaul/variant/detail/apply_visitor_unary.hpp

/** // doc: yaul/variant/detail/apply_visitor_unary.hpp {{{
 * \file yaul/variant/detail/apply_visitor_unary.hpp
 * \todo Write documentation
 */ // }}}
#ifndef YAUL_VARIANT_DETAIL_APPLY_VISITOR_UNARY_HPP
#define YAUL_VARIANT_DETAIL_APPLY_VISITOR_UNARY_HPP

#include <type_traits>
#include <utility>

namespace yaul {
/** // doc: apply_visitor() {{{
 * \todo Write documentation
 */ // }}}
template<typename Visitor, typename Visitable>
typename std::remove_reference<Visitor>::type::result_type // FIXME: elaborate
apply_visitor(Visitor&& vis, Visitable&& t)
    noexcept(noexcept(
          std::forward<Visitable>(t).apply_visitor(std::forward<Visitor>(vis))
    ))
{
  return  std::forward<Visitable>(t).apply_visitor(std::forward<Visitor>(vis));
}
} // end namespace yaul

#endif /* YAUL_VARIANT_DETAIL_APPLY_VISITOR_UNARY_HPP */
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
