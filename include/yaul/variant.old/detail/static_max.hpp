// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

// yaul/variant/detail/static_max.hpp

/** // doc: yaul/variant/detail/static_max.hpp {{{
 * \file yaul/variant/detail/static_max.hpp
 * \todo Write documentation
 */ // }}}
#ifndef YAUL_VARIANT_DETAIL_STATIC_MAX_HPP
#define YAUL_VARIANT_DETAIL_STATIC_MAX_HPP

#include <type_traits>
#include <cstddef>

namespace yaul { namespace detail { namespace variant {
/** \ingroup DetailMetafunctionsGroup
 * @{ */
/** // doc: static_max {{{
 * \brief Find maximum integer among multiple values
 *
 * \tparam arg1
 *    first argument
 * \tparam others
 *    rest of the arguments
 *
 * \par Synopsis
 *
 * \code
 *  namespace yaul { namespace detail { namespace variant {
 *    template<std::size_t arg1, std::size_t... others>
 *    struct static_max
 *    {
 *      typedef unspecified type;
 *      static constexpr std::size_t value = unspecified;
 *    };
 *  } } }
 * \endcode
 */ // }}}
template<std::size_t arg1, std::size_t... others>
struct static_max;

/** \cond DOXYGEN_SHOW_TEMPLATE_SPECIALIZATIONS */
template<std::size_t arg1>
struct static_max<arg1>
  : std::integral_constant<std::size_t, arg1>
{ };
template<std::size_t arg1, std::size_t arg2, std::size_t... rest>
struct static_max<arg1,arg2,rest...>
  : static_max<((arg1 >= arg2) ? arg1 : arg2), rest...>
{ };
/** \endcond */
/** @} */
} } } // end namespace taul::detail::variant

#endif /* YAUL_VARIANT_DETAIL_STATIC_MAX_HPP */
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
