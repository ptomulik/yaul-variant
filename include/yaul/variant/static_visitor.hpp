// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

// yaul/variant/static_visitor.hpp

/** // doc: yaul/variant/static_visitor.hpp {{{
 * \file yaul/variant/static_visitor.hpp
 * \todo Write documentation
 */ // }}}
#ifndef YAUL_VARIANT_STATIC_VISITOR_HPP
#define YAUL_VARIANT_STATIC_VISITOR_HPP

namespace yaul { namespace detail {
struct is_static_visitor_tag { };
typedef void static_visitor_default_return;
} } // end namespace yaul::detail

namespace yaul {
/** // doc: static_visitor {{{
 * \todo Write documentation
 */ // }}}
template< typename ResultType = ::yaul::detail::static_visitor_default_return >
  struct static_visitor
    : public detail::is_static_visitor_tag
  {
    typedef ResultType result_type;
  protected: // for use as base class only
    static_visitor() = default;
    ~static_visitor() = default;
  };
} // end namespace yaul

#include <type_traits>
namespace yaul { namespace detail {
template< typename T >
  struct is_static_visitor_impl
    : std::is_base_of< is_static_visitor_tag, T >
  {
  };
} } // end namespace yaul::detail

namespace yaul {
/** \ingroup group-metafunctions
 * @{ */
/** // doc: is_static_visitor {{{
 * \todo Write documentation
 */ // }}}
template< typename T >
  struct is_static_visitor
    : detail::is_static_visitor_impl<T>
  {
  };
/** @} */
} // end namespace yaul

#endif /* YAUL_VARIANT_STATIC_VISITOR_HPP */
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
