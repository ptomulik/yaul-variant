// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

// yaul/variant/yaul::detail::variant::recursive_variant.hpp

/** // doc: yaul/variant/yaul::detail::variant::recursive_variant.hpp {{{
 * \file yaul/variant/yaul::detail::variant::recursive_variant.hpp
 * \todo Write documentation
 */ // }}}
#ifndef YAUL_VARIANT_RECURSIVE_VARIANT_HPP
#define YAUL_VARIANT_RECURSIVE_VARIANT_HPP

#include <yaul/variant/variant.hpp>
#include <yaul/variant/recursive_variant_fwd.hpp>
#include <yaul/variant/detail/recursive_flag.hpp>
#include <yaul/variant/detail/recursive_variant.hpp>

namespace yaul {
template< typename T0, typename... Others >
  struct make_recursive_variant
  {
    typedef yaul::variant<
        detail::variant::recursive_flag< T0 >
      , Others...
      > type;
  };
} // end namespace yaul

#endif /* YAUL_VARIANT_RECURSIVE_VARIANT_HPP */
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
