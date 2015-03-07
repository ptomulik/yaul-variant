// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

// yaul/variant/detail/destructor_visitor.hpp

/** // doc: yaul/variant/detail/destructor_visitor.hpp {{{
 * \file yaul/variant/detail/destructor_visitor.hpp
 * \todo Write documentation
 */ // }}}
#ifndef YAUL_VARIANT_DETAIL_DESTRUCTOR_VISITOR_HPP
#define YAUL_VARIANT_DETAIL_DESTRUCTOR_VISITOR_HPP

#include <yaul/variant/config.hpp>
#include <yaul/variant/static_visitor.hpp>
#include <type_traits>

namespace yaul { namespace detail { namespace variant {
/** \ingroup FixMe FIXME:
 * @{ */
/** // doc: destructor_visitor {{{
 */ // }}}
template<typename Variant>
  struct destructor_visitor
    : ::yaul::static_visitor<>
  {
    template<typename T>
    using raw_t = typename std::remove_cv<typename std::remove_reference<T>::type>::type;

    template<typename T>
    result_type operator()(T&& t)
#ifndef YAUL_VARIANT_DISABLE_NOEXCEPT_PROPAGATION_IN_DESTRUCTOR_VISITOR
      noexcept(noexcept(t.~raw_t<T>()))
#endif
    {
      t.~raw_t<T>();
    }
  };
/** @} */
} } } // end namespace yaul::detail::variant

#endif /* YAUL_VARIANT_DETAIL_DESTRUCTOR_VISITOR_HPP */
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
