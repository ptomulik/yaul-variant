// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

// yaul/variant/detail/variant_base.hpp

/** // doc: yaul/variant/detail/variant_base.hpp {{{
 * \file yaul/variant/detail/variant_base.hpp
 * \todo Write documentation
 */ // }}}
#ifndef YAUL_VARIANT_DETAIL_VARIANT_BASE_HPP
#define YAUL_VARIANT_DETAIL_VARIANT_BASE_HPP

#include <yaul/variant/variant_fwd.hpp>
#include <yaul/variant/detail/variant_storage.hpp>
#include <type_traits>

namespace yaul { namespace detail { namespace variant {

template<typename Variant>
  struct variant_base
   : make_variant_storage_t<Variant>
{
};

} } } // end namespace yaul::detail::variant

#endif /* YAUL_VARIANT_DETAIL_VARIANT_BASE_HPP */
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
