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
#include <yaul/variant/detail/enable_recursive.hpp>
#include <yaul/variant/detail/recursive_flag.hpp>
#include <type_traits>

namespace yaul { namespace detail { namespace variant {
/** \ingroup group-detail-metafunctions
 * @{ */

template<typename Variant>
struct variant_storage_impl;

/** \cond DOXYGEN_SHOW_TEMPLATE_SPECIALIZATIONS */
template<typename T0, typename... Others>
  struct variant_storage_impl<yaul::variant<T0,Others...> >
    : std::aligned_storage< static_max<sizeof(T0), sizeof(Others)...>::value,
                            static_max<alignof(T0), alignof(Others)...>::value >
  {
  };

template<typename T0, typename... Others>
  struct variant_storage_impl<yaul::variant<recursive_flag<T0>, Others...> >
  {
  private:
    using Variant = yaul::variant<recursive_flag<T0>, Others...>;
    template< typename T >
      using er_t = typename enable_recursive<T, Variant>::type;
  public:
    typedef typename std::aligned_storage<
        static_max<sizeof(er_t<T0>), sizeof(er_t<Others>)...>::value,
        static_max<alignof(er_t<T0>), alignof(er_t<Others>)...>::value
      >::type type;
  };
/** \endcond */

/** // doc: variant_storage {{{
 * \todo Write documentation
 */ // }}}
template<typename Variant>
struct variant_storage
  : variant_storage_impl<Variant>
{ };
/** // doc: variant_storage_t {{{
 * \todo Write documentation
 */ // }}}
template<typename Variant>
using variant_storage_t = typename variant_storage<Variant>::type;
/** @} */
} } } // end namespace yaul::detail::variant

#endif /* YAUL_VARIANT_DETAIL_VARIANT_STORAGE_HPP */
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
