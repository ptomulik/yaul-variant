// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

// yaul/variant/detail/variant_assigner.hpp

/** // doc: yaul/variant/detail/variant_assigner.hpp {{{
 * \file yaul/variant/detail/variant_assigner.hpp
 * \todo Write documentation
 */ // }}}
#ifndef YAUL_VARIANT_DETAIL_VARIANT_ASSIGNER_HPP
#define YAUL_VARIANT_DETAIL_VARIANT_ASSIGNER_HPP

#include <yaul/variant/static_visitor.hpp>
#include <utility>

namespace yaul { namespace detail { namespace variant {
/** \ingroup group-fixme FIXME:
 * @{ */
/** // doc: variant_assigner {{{
 * \todo Write documentation
 */ // }}}
template<typename Variant>
  struct variant_assigner
    : static_visitor<void>
  {
    variant_assigner() = delete;
    variant_assigner(Variant& target) noexcept
      : target_(target)
    { }

    template<typename T>
    void operator()(T&& t) &&
      noexcept(noexcept(std::declval<variant_assigner&&>().target_ = std::forward<T>(t)))
    {
      std::move(*this).target_ = std::forward<T>(t);
    }
  private:
    Variant& target_;
  };
/** @} */
} } } // end namesapce yaul::detail::variant

#endif /* YAUL_VARIANT_DETAIL_VARIANT_ASSIGNER_HPP */
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
