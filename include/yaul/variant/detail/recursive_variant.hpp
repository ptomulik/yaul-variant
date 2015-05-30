// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

// yaul/variant/detail/recursive_variant.hpp

/** // doc: yaul/variant/detail/recursive_variant.hpp {{{
 * \file yaul/variant/detail/recursive_variant.hpp
 * \todo Write documentation
 */ // }}}
#ifndef YAUL_VARIANT_DETAIL_RECURSIVE_VARIANT_HPP
#define YAUL_VARIANT_DETAIL_RECURSIVE_VARIANT_HPP

#include <yaul/variant/recursive_variant_fwd.hpp>
#include <yaul/variant/recursive_wrapper.hpp>
#include <type_traits>

namespace yaul { namespace detail { namespace variant {
/** \ingroup FixMe FIXME:
 * @{ */

/** // doc: recursive_variant {{{
 * \todo Write documentation
 */ // }}}
template< typename T >
class recursive_variant
  : public yaul::recursive_wrapper<T>
{
  using Base = yaul::recursive_wrapper<T>;
public:
  using Base::Base;
  using Base::operator=;
};

/** \endcond */
/** @} */
} } } // end namespace yaul::detail::variant

#endif /* YAUL_VARIANT_DETAIL_RECURSIVE_VARIANT_HPP */
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
