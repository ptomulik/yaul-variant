// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

// yaul/variant/detail/initializer_visitor.hpp

/** // doc: yaul/variant/detail/initializer_visitor.hpp {{{
 * \file yaul/variant/detail/initializer_visitor.hpp
 * \todo Write documentation
 */ // }}}
#ifndef YAUL_VARIANT_DETAIL_INITIALIZER_VISITOR_HPP
#define YAUL_VARIANT_DETAIL_INITIALIZER_VISITOR_HPP

#include <yaul/variant/config.hpp>
#include <yaul/variant/static_visitor.hpp>
#include <utility>

namespace yaul { namespace detail { namespace variant {
/** \ingroup FixMe FIXME:
 * @{ */
/** // doc: initializer_visitor {{{
 */ // }}}
template<typename Variant>
  struct initializer_visitor
    : ::yaul::static_visitor<>
  {
    initializer_visitor() = delete;

    initializer_visitor(Variant& variant) noexcept
      : variant_(variant)
    { }

    template<typename T>
    result_type operator()(T&& t) const
#ifndef YAUL_VARIANT_DISABLE_NOEXCEPT_PROPAGATION_IN_INITIALIZER_VISITOR
      noexcept(noexcept(reinterpret_cast<Variant*>(0)->initialize_(std::forward<T>(t))))
#endif
    {
      variant_.initialize_(std::forward<T>(t));
    }
  private:
    Variant& variant_;
  };
/** @} */
} } } // end namespace yaul::detail::variant

#endif /* YAUL_VARIANT_DETAIL_INITIALIZER_VISITOR_HPP */
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
