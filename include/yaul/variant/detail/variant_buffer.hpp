// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

// yaul/variant/detail/variant_buffer.hpp

/** // doc: yaul/variant/detail/variant_buffer.hpp {{{
 * \file yaul/variant/detail/variant_buffer.hpp
 * \todo Write documentation
 */ // }}}
#ifndef YAUL_VARIANT_DETAIL_VARIANT_BUFFER_HPP
#define YAUL_VARIANT_DETAIL_VARIANT_BUFFER_HPP

//#include <yaul/variant/variant_fwd.hpp>
#include <yaul/variant/detail/static_max.hpp>
#include <yaul/variant/detail/enable_recursive.hpp>
#include <yaul/variant/detail/recursive_flag.hpp>
#include <type_traits>

namespace yaul { namespace detail { namespace variant {
/** \ingroup group-detail-metafunctions
 * @{ */

template<typename Variant>
struct variant_buffer_impl;

/** \cond DOXYGEN_SHOW_TEMPLATE_SPECIALIZATIONS */
template<template <typename...> class V, typename T0, typename... Others>
  struct variant_buffer_impl<V<T0,Others...> >
    : std::aligned_storage< static_max<sizeof(T0), sizeof(Others)...>::value,
                            static_max<alignof(T0), alignof(Others)...>::value >
  {
  };

template<template <typename...> class V, typename T0, typename... Others>
  struct variant_buffer_impl<V<recursive_flag<T0>, Others...> >
  {
  private:
    using Variant = V<recursive_flag<T0>, Others...>;
    template< typename T >
      using er_t = typename enable_recursive<T, Variant>::type;
  public:
    typedef typename std::aligned_storage<
        static_max<sizeof(er_t<T0>), sizeof(er_t<Others>)...>::value,
        static_max<alignof(er_t<T0>), alignof(er_t<Others>)...>::value
      >::type type;
  };
/** \endcond */

/** // doc: variant_buffer {{{
 * \brief Returns a type suitable for variant's storage buffer
 *
 * \tparam Variant A variant type for which the buffer has to serve
 *
 * \par Synopsis
 * \code
 *  template<typename Variant>
 *  struct variant_buffer
 *    {
 *      typename unspecified type;
 *    };
 * \endcode
 *
 * \par Description
 * If `V` is a class template matching `template<typename...> class` pattern,
 * `T0`, ..., `Tn` are types, and `T` is identical with `V<T0,...,Tn>`, then
 * \code
 *  variant_buffer<T>::type
 * \endcode
 * yields a type whose instance has enough capacity to contain an instance of
 * any alternative type of variant `V<T0,...,Tn>`. The `variant_buffer`
 * metafunction also handles recursive variants.
 */ // }}}
template<typename Variant>
struct variant_buffer
  : variant_buffer_impl<Variant>
{ };
/** // doc: variant_buffer_t {{{
 * \brief Alias for `typename variant_buffer<Variant>::type`
 */ // }}}
template<typename Variant>
using variant_buffer_t = typename variant_buffer<Variant>::type;
/** @} */
} } } // end namespace yaul::detail::variant

#endif /* YAUL_VARIANT_DETAIL_VARIANT_BUFFER_HPP */
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
