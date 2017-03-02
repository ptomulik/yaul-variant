// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

// yaul/variant/recursive_variant_tag.hpp

/** // doc: yaul/variant/recursive_variant_tag.hpp {{{
 * \file yaul/variant/recursive_variant_tag.hpp
 * \brief Defines \ref yaul::recursive_variant_tag tag
 */ // }}}
#ifndef YAUL_VARIANT_RECURSIVE_VARIANT_TAG_HPP
#define YAUL_VARIANT_RECURSIVE_VARIANT_TAG_HPP

namespace yaul {
/** // doc: recursive_variant_tag {{{
 * \brief Tag used (as a placeholder) to denote recursion on variant's list of
 *        alternative types
 *
 * \par Example
 * \code
 * using R = make_recursive_variant< int, char, std::vector<recursive_variant_tag> >::type;
 * \endcode
 */ // }}}
struct recursive_variant_tag{};

/** // doc: recursive_variant_ {{{
 * \brief Alias for recursive_variant_tag
 */ // }}}
using recursive_variant_ = recursive_variant_tag;
} // end namespace yaul

#endif /* YAUL_VARIANT_RECURSIVE_VARIANT_TAG_HPP */
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
