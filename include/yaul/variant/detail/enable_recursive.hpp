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
#include <yaul/variant/recursive_variant_tag.hpp>
#include <yaul/variant/recursive_wrapper_fwd.hpp>

#include <type_traits>

namespace yaul { namespace detail { namespace variant {

/** // doc: enable_recursive {{{
 * \brief Attempts \ref yaul::recursive_variant_tag "recursive_variant_tag" 
 *        substitution, wrapping with
 *        \ref yaul::recursive_wrapper "recursive_wrapper" if
 *        substitution occurs with non-indirect result (i.e., not a reference
 *        or pointer) *and* NoWrapper is \c false.
 *
 * \tparam T Type to be scanned for occurrences of
 *          \ref yaul::recursive_variant_tag "recursive_variant_tag", which in
 *          turn are to be substituted with either `RecursiveVariant` or
 *          \ref yaul::recursive_wrapper "recursive_wrapper<RecursiveVariant>"
 *          (with cv-qualifiers appropriately handled).
 * \tparam RecursiveVariant Variant type to be inserted whenever the
 *         \ref yaul::recursive_variant_tag "recursive_variant_tag" is
 *         found in `T`.
 * \tparam NoWrapper Disables wrapping with
 *         \ref yaul::recursive_wrapper "recursive_wrapper". Defaults to
 *         `false` (wrapping enabled).
 *
 * \par Synopsis
 * \code
 *  template<
 *      typename T
 *    , typename RecursiveVariant
 *    , bool NoWrapper = false
 *  >
 *  struct enable_recursive
 *    {
 *      typedef unspecified type;
 *    };
 * \endcode
 *
 * \par Description
 * If `T` is a type, `S` is
 * \code
 *  using S = substitute<T, RecursiveVariant, yaul::recursive_variant_tag>::type;
 * \endcode
 * and `S` is neither a reference nor a pointer type, and is not same as `T`,
 * then the following expression is `true`
 * \code
 *  std::is_same<
 *    enable_recursive<T, RecursiveVariant>::type,
 *    yaul::wrap_recursive_wrapper<S>::type
 *  >::value
 * \endcode
 * otherwise, the following holds
 * \code
 *  std::is_same<enable_recursive<T, RecursiveVariant>::type, S>::value
 * \endcode
 * With `NoWrapper` set to `true`, wrapping is disabled, i.e. the following
 * expression is always `true`
 * \code
 *  std::is_same<enable_recursive<T, RecursiveVariant, true>::type, S>::value
 * \endcode
 *
 * \par Example
 * \snippet enable_recursive.cpp Code
 */ // }}}
template< typename T, typename RecursiveVariant, bool NoWrapper = false >
  struct enable_recursive
    : substitute<T, RecursiveVariant, yaul::recursive_variant_tag>
  {
  };

/** \cond DOXYGEN_SHOW_TEMPLATE_SPECIALIZATIONS */
template< typename T, typename RecursiveVariant >
  struct enable_recursive<T, RecursiveVariant, false>
  {
  private:
    using S = typename substitute<T, RecursiveVariant, yaul::recursive_variant_tag>::type;
  public:
    // wrap with recursive_wrapper only if rebind really changed something
    typedef typename std::conditional<
      ( std::is_same<S, T>::value ||
        std::is_reference<S>::value ||
        std::is_pointer<S>::value )
    , S
    , typename ::yaul::wrap_recursive_wrapper<S>::type
    >::type type;
  };
/** \endcond */

} } } // end yaul::detail::variant

#endif /* YAUL_VARIANT_DETAIL_ENABLE_RECURSIVE_HPP */
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
