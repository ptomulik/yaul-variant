// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

// yaul/variant/detail/enable_recursive.hpp

/** // doc: yaul/variant/detail/enable_recursive.hpp {{{
 * \file yaul/variant/detail/enable_recursive.hpp
 * \todo Write documentation
 */ // }}}
#ifndef YAUL_VARIANT_DETAIL_ENABLE_RECURSIVE_HPP
#define YAUL_VARIANT_DETAIL_ENABLE_RECURSIVE_HPP

#include <yaul/variant/detail/substitute.hpp>
//#include <yaul/variant/detail/recursive_flag.hpp>
#include <yaul/variant/recursive_wrapper.hpp>
#include <yaul/variant/recursive_variant_fwd.hpp>
#include <yaul/variant/detail/enable_recursive_fwd.hpp>

#include <type_traits>

namespace yaul { namespace detail { namespace variant {
/** \ingroup FixMe FIXME:
 * @{ */

template< typename T, typename RecursiveVariant, bool NoWrapper >
  struct enable_recursive
    : substitute<T, RecursiveVariant, yaul::recursive_variant_>
  {
  };

/** \cond DOXYGEN_SHOW_TEMPLATE_SPECIALIZATIONS */
template< typename T, typename RecursiveVariant >
  struct enable_recursive<T, RecursiveVariant, false>
  {
  private:
    typedef typename substitute<T, RecursiveVariant, yaul::recursive_variant_>::type t_;
  public:
    // wrap with recursive_wrapper only if rebind really changed something
    typedef typename std::conditional<
      ( std::is_same<t_, T>::value ||
        std::is_reference<t_>::value ||
        std::is_pointer<t_>::value )
    , t_
    , typename yaul::wrap_recursive<t_>::type
    >::type type;
  };
/** \endcond */
/** @} */
} } } // end yaul::detail::variant

#endif /* YAUL_VARIANT_DETAIL_ENABLE_RECURSIVE_HPP */
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
