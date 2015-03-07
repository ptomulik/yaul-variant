// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

// yaul/variant/detail/variant_storage.hpp

/** // doc: yaul/variant/detail/variant_storage.hpp {{{
 * \file yaul/variant/detail/variant_storage.hpp
 * \todo Write documentation
 */ // }}}
#ifndef YAUL_VARIANT_DETAIL_VARIANT_STORAGE_HPP
#define YAUL_VARIANT_DETAIL_VARIANT_STORAGE_HPP

#include <yaul/variant/variant_fwd.hpp>
#include <yaul/variant/detail/static_max.hpp>
#include <type_traits>

namespace yaul { namespace detail { namespace variant {
/** \ingroup DetailMetafunctionsGroup
 * @{ */
/** // doc: variant_storage {{{
 * \todo Write documentation
 */ // }}}
template<typename Variant>
struct variant_storage;
/** \cond DOXYGEN_SHOW_TEMPLATE_SPECIALIZATIONS */
template<typename T0, typename... Others>
struct variant_storage<yaul::variant<T0, Others...> >
  : std::aligned_storage< static_max<sizeof(T0), sizeof(Others)...>::value, 
                          static_max<alignof(T0), alignof(Others)...>::value >
{
};
/** \endcond */
/** @} */
} } } // end namespace yaul::detail::variant

#endif /* YAUL_VARIANT_DETAIL_VARIANT_STORAGE_HPP */
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
