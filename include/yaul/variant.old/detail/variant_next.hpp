// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

// yaul/variant/detail/variant_next.hpp

/** // doc: yaul/variant/detail/variant_next.hpp {{{
 * \file yaul/variant/detail/variant_next.hpp
 * \todo Write documentation
 */ // }}}
#ifndef YAUL_VARIANT_DETAIL_VARIANT_NEXT_HPP
#define YAUL_VARIANT_DETAIL_VARIANT_NEXT_HPP

#include <yaul/variant/variant_fwd.hpp>
#include <yaul/variant/detail/variant_impl_fwd.hpp>
#include <cstddef>

namespace yaul { namespace detail { namespace variant {
/** \ingroup DetailMetafunctionsGroup
 * @{ */
/** // doc: variant_next {{{
 * \todo Write documentation
 */ // }}}
template <typename Class>
  struct variant_next;
/** \cond DOXYGEN_SHOW_TEMPLATE_SPECIALIZATIONS */
template <std::size_t I, typename T0, typename... Others>
struct variant_next<variant_impl<I,yaul::variant<T0,Others...> > >
{
  typedef variant_ctors<I, yaul::variant<T0,Others...> > type;
};
template <std::size_t I, typename T0, typename... Others>
struct variant_next<variant_ctors<I,yaul::variant<T0,Others...> > >
{
  typedef variant_assignment<I, yaul::variant<T0,Others...> > type;
};
template <std::size_t I, typename T0, typename... Others>
struct variant_next<variant_assignment<I,yaul::variant<T0,Others...> > >
{
  typedef variant_impl<I-1, yaul::variant<T0,Others...> > type;
};
/** \endcond */
/** @} */
} } } // end namespace yaul::detail::variant

#endif /* YAUL_VARIANT_DETAIL_VARIANT_NEXT_HPP */
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
