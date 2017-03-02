// Copyright (C) 2015-2017, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

// yaul/variant/detail/in_place_tags.hpp

/** // doc: yaul/variant/detail/in_place_tags.hpp {{{
 * \file yaul/variant/detail/in_place_tags.hpp
 * \brief Provides \ref yaul::variant::detail::in_place_type_t and
 *        \ref yaul::variant::detail::in_place_index_t
 */ // }}}
#ifndef YAUL_VARIANT_DETAIL_IN_PLACE_TAGS_HPP
#define YAUL_VARIANT_DETAIL_IN_PLACE_TAGS_HPP

#include <cstddef>

namespace yaul { namespace detail { namespace variant {

/** // doc: in_place_type_t {{{
 * \brief Index disambiguation tag that may be passed to variant's constructors
 */ // }}}
template<class T>
struct in_place_type_t
{
  explicit in_place_type_t() = default;
};

/** // doc: in_place_index_t {{{
 * \brief Index disambiguation tag that may be passed to variant's constructors
 */ // }}}
template<std::size_t I>
struct in_place_index_t
{
  explicit in_place_index_t() = default;
};

} } } // end namespace yaul::detail::variant

#endif /* YAUL_VARIANT_DETAIL_IN_PLACE_TAGS_HPP */
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
