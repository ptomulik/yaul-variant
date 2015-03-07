// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

// yaul/variant/detail/reflect.hpp

/** // doc: yaul/variant/detail/reflect.hpp {{{
 * \file yaul/variant/detail/reflect.hpp
 * \todo Write documentation
 */ // }}}
#ifndef YAUL_VARIANT_DETAIL_REFLECT_HPP
#define YAUL_VARIANT_DETAIL_REFLECT_HPP

#include <yaul/variant/static_visitor.hpp>
#include <typeinfo>

namespace yaul { namespace detail { namespace variant {
struct reflect
  : static_visitor<const std::type_info&>
{
  template< typename T>
  const std::type_info& operator()(T const&) && noexcept
  {
    return typeid(T);
  }
};
} } } // end namespace yaul::detail::variant

#endif /* YAUL_VARIANT_DETAIL_REFLECT_HPP */
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
