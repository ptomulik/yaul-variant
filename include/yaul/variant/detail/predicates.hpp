// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

// yaul/variant/detail/predicates.hpp

/** // doc: yaul/variant/detail/predicates.hpp {{{
 * \file yaul/variant/detail/predicates.hpp
 * \todo Write documentation
 */ // }}}
#ifndef YAUL_VARIANT_DETAIL_PREDICATES_HPP
#define YAUL_VARIANT_DETAIL_PREDICATES_HPP

#include <type_traits>

namespace yaul { namespace detail { namespace variant {
template<typename P>
  struct not_
  {
    template<typename T>
      struct apply
        : std::integral_constant<
            typename P::template apply<T>::value_type,
          !(P::template apply<T>::value)
        >
      { };
  };

/** \ingroup FixMe FIXME
 * @{ */
template<typename U>
struct same_as
  {
    template<typename T>
      struct apply
        : std::is_same<U,T>
      {};
  };
/** \endcond */
/** @} */
} } }  // end namespace yaul::detail::variant

#endif /* YAUL_VARIANT_DETAIL_PREDICATES_HPP */
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
