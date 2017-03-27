// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

// yaul/variant/detail/variant_impl.hpp

/** // doc: yaul/variant/detail/variant_impl.hpp {{{
 * \file yaul/variant/detail/variant_impl.hpp
 * \todo Write documentation
 */ // }}}
#ifndef YAUL_VARIANT_DETAIL_VARIANT_IMPL_HPP
#define YAUL_VARIANT_DETAIL_VARIANT_IMPL_HPP

#include <cstddef>
#include <yaul/variant/variant_size.hpp>
#include <yaul/variant/variant_alternative.hpp>
#include <yaul/variant/detail/variant_base.hpp>

namespace yaul { namespace detail { namespace variant {

/** // doc: variant_impl {{{
 * \todo Write documentation
 */ // }}}
template<typename Variant, std::size_t Np>
class variant_impl;

/** \cond DOXYGEN_SHOW_TEMPLATE_SPECIALIZATIONS */
template<typename Variant, std::size_t Np>
class variant_impl
  : public variant_impl<Variant, Np+1>
{
  using Base = variant_impl<Variant, Np+1>;
  //using Base::Buffer;
  using T = variant_alternative_t<Np,Variant>; // current type

  public:
    using Base::Base;
};

template<typename Variant, std::size_t Np>
class variant_impl<Variant, (variant_size<Variant>::value-1ul)>
  : public variant_base<Variant>
{
  using Base = variant_base<Variant>;
  //using Buffer = Base::Buffer;
  using T = variant_alternative_t<Np,Variant>; // current type

public:
  using Base::Base;
};
/** \endcond */

} } } // end namespace yaul::detail::variant

#endif /* YAUL_VARIANT_DETAIL_VARIANT_IMPL_HPP */
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
