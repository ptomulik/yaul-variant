// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

// yaul/variant/detail/variant_storage.hpp

/** // doc: yaul/variant/detail/variant_storage.hpp {{{
 * \file yaul/variant/detail/variant_storage.hpp
 * \brief Provides metafunction \ref yaul::detail::variant::make_variant_storage
 *        and alias \ref yaul::detail::variant::make_variant_storage_t
 */ // }}}
#ifndef YAUL_VARIANT_DETAIL_VARIANT_STORAGE_HPP
#define YAUL_VARIANT_DETAIL_VARIANT_STORAGE_HPP

#include <yaul/variant/variant_fwd.hpp>
#include <yaul/variant/detail/variadic_storage.hpp>
#include <type_traits>

namespace yaul { namespace detail { namespace variant {
/** // doc: make_variant_storage {{{
 * \todo Write documentation
 */ // }}}
template<typename Variant>
struct make_variant_storage;

/** \cond DOXYGEN_SHOW_TEMPLATE_SPECIALIZATIONS */
template<template <typename...> class V, typename...Types>
struct make_variant_storage< V<Types...> >
{
  typedef typename std::conditional<
        is_variant_template<V>::value
      , make_variadic_storage<Types...>
      , not_a_variant< V<Types...> > // has no nested type
    >::type::type type;
};
/** \endcond */

/** // doc: make_variant_storage_t {{{
 * \todo Write documentation
 */ // }}}
template<typename Variant>
using make_variant_storage_t = typename make_variant_storage<Variant>::type;
} } } // end namespace yaul::detail::variant

#endif /* YAUL_VARIANT_DETAIL_VARIANT_STORAGE_HPP */
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
