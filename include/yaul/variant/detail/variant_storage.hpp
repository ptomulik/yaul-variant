// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

// yaul/variant/detail/variant_storage.hpp

/** // doc: yaul/variant/detail/variant_storage.hpp {{{
 * \file yaul/variant/detail/variant_storage.hpp
 * \brief Provides the \ref yaul::detail::variant::make_variant_storage metafunction
 */ // }}}
#ifndef YAUL_VARIANT_DETAIL_VARIANT_STORAGE_HPP
#define YAUL_VARIANT_DETAIL_VARIANT_STORAGE_HPP

#include <yaul/variant/variant_fwd.hpp>
#include <yaul/variant/detail/variadic_storage.hpp>

namespace yaul { namespace detail { namespace variant {
/** // doc: make_variant_storage {{{
 * \todo Write documentation
 */ // }}}
template<typename Variant>
struct make_variant_storage;

template<template<typename T0, typename... Others> V>
struct make_variant_storage
{
  // TODO: finish
};

} } } // end namespace yaul::detail::variant

#endif /* YAUL_VARIANT_DETAIL_VARIANT_STORAGE_HPP */
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
