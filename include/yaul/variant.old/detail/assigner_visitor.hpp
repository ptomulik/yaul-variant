// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

// yaul/variant/detail/assigner_visitor.hpp

/** // doc: yaul/variant/detail/assigner_visitor.hpp {{{
 * \file yaul/variant/detail/assigner_visitor.hpp
 * \todo Write documentation
 */ // }}}
#ifndef YAUL_VARIANT_DETAIL_ASSIGNER_VISITOR_HPP
#define YAUL_VARIANT_DETAIL_ASSIGNER_VISITOR_HPP

#include <yaul/variant/config.hpp>
#include <yaul/variant/static_visitor.hpp>
#include <utility>

namespace yaul { namespace detail { namespace variant {
/** \ingroup FixMe FIXME:
 * @{ */
/** // doc: assigner_visitor {{{
 */ // }}}
template<typename Variant>
  struct assigner_visitor
    : static_visitor<Variant&>
  {
    assigner_visitor() = delete;
    assigner_visitor(Variant& target)
      : target_(target)
    {
    }
    template<typename T>
    result_type operator()(T&& t) const
#ifndef YAUL_VARIANT_DISABLE_NOEXCEPT_PROPAGATION_IN_ASSIGNER_VISITOR
      noexcept(noexcept(target_.assign_value_(std::forward<T>(t))))
#endif
    {
      return (target_ = std::forward<T>(t));
    }
  private:
    Variant& target_;
  };
/** @} */
} } } // end namespace yaul::detail::variant

#endif /* YAUL_VARIANT_DETAIL_ASSIGNER_VISITOR_HPP */
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
