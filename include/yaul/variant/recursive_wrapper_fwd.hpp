// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

// yaul/variant/recursive_wrapper_fwd.hpp

/** // doc: yaul/variant/recursive_wrapper_fwd.hpp {{{
 * \file yaul/variant/recursive_wrapper_fwd.hpp
 * \brief Provides forward declaration of \ref yaul::recursive_wrapper "recursive_wrapper".
 *
 * Also defines \ref yaul::is_recursive_wrapper "is_recursive_wrapper",
 * \ref yaul::wrap_recursive_wrapper "wrap_recursive_wrapper",
 * and \ref yaul::unwrap_recursive_wrapper "unwrap_recursive_wrapper"
 * metafunctions.
 */ // }}}
#ifndef YAUL_VARIANT_RECURSIVE_WRAPPER_FWD_HPP
#define YAUL_VARIANT_RECURSIVE_WRAPPER_FWD_HPP

#include <type_traits>

namespace yaul {
template< typename T > class recursive_wrapper;
/** // doc: is_recursive_wrapper {{{
 * \brief Check if T is a recursive wrapper
 *
 * \tparam T a type to be examined
 *
 * \par Synopsis
 * \code
 *  template< typename T >
 *  struct is_recursive_wrapper
 *    {
 *      typedef std::integral_constant<bool, unspecified> type;
 *      constexpr static bool value = unspecified;
 *    };
 * \endcode
 *
 * \par Description
 * If `W` is a class template matching `template<typename...> class` pattern,
 * `U` is cv-unqualified, non-reference, non-array type, `T` is identical
 * with `W<U>`, and the following expression is `true`
 * \code
 *  yaul::detail::variant::is_recursive_wrapper_template<W>::value
 * \endcode
 * then the following expression
 * \code
 *  is_recursive_wrapper<T>::value
 * \endcode
 * is also `true`. In any other circumstances, the expression evaluates to
 * `false`.
 *
 *
 * \par Example
 * \snippet is_recursive_wrapper.cpp Code
 *
 */ // }}}
template< typename T > struct is_recursive_wrapper;
} // end namespace yaul

namespace yaul { namespace detail { namespace variant {

/** // doc: is_recursive_wrapper_template {{{
 * \brief Checks, whether a given template class may be used as recursive wrapper
 *
 * \tparam T Class template to be examined
 *
 * \par Synopsis
 * \code
 *  template< template <typename...> class >
 *  struct is_recursive_wrapper_template
 *    : std::integral_constant<bool, unspecified> 
 *    { };
 * \endcode
 *
 * \par Description
 * If it holds
 * \code
 *  is_recursive_wrapper_template<W>::value == true
 * \endcode
 * for some class template `W`, then for any suitable type `U`, `W<U>` is
 * treated as a recursive wrapper by other metafunctions (such as
 * \ref yaul::is_recursive_wrapper, \ref yaul::wrap_recursive_wrapper,
 * \ref yaul::unwrap_recursive_wrapper)
 *
 * \par Example
 * \snippet is_recursive_wrapper_template.cpp Code
 */ // }}}
template< template <typename...> class T >
  struct is_recursive_wrapper_template
    : std::integral_constant<bool, false>
  { };

/** \cond DOXYGEN_SHOW_TEMPLATE_SPECIALIZATIONS */
template<>
  struct is_recursive_wrapper_template< ::yaul::recursive_wrapper >
    : std::integral_constant<bool, true>
  { };
/** \endcond */

template< typename T >
  struct is_recursive_wrapper_impl
    : std::integral_constant<bool, false>
  { };

/** \cond DOXYGEN_SHOW_TEMPLATE_SPECIALIZATIONS */
template< typename T, template<typename...> class Wrapper>
  struct is_recursive_wrapper_impl< Wrapper<T> >
    : std::integral_constant<
        bool
        , (std::is_same<
              typename std::remove_cv<
                typename std::remove_reference<T>::type
              >::type
           , T>::value
           && !std::is_array<T>::value
           && is_recursive_wrapper_template<Wrapper>::value)
      >
  { };
/** \endcond */

template< typename T, template <typename...> class Wrapper >
  struct wrap_recursive_wrapper_impl
  {
    typedef typename std::conditional<
        is_recursive_wrapper<Wrapper<T> >::value
      , Wrapper<T>, T
    >::type  type;
  };

/** \cond DOXYGEN_SHOW_TEMPLATE_SPECIALIZATIONS */
template< typename T, template <typename...> class Wrapper >
  struct wrap_recursive_wrapper_impl<T const, Wrapper>
  {
    typedef typename wrap_recursive_wrapper_impl<T,Wrapper>::type const type;
  };
template< typename T, template <typename...> class Wrapper >
  struct wrap_recursive_wrapper_impl<T volatile, Wrapper>
  {
    typedef typename wrap_recursive_wrapper_impl<T,Wrapper>::type volatile type;
  };
template< typename T, template <typename...> class Wrapper >
  struct wrap_recursive_wrapper_impl<T const volatile, Wrapper>
  {
    typedef typename wrap_recursive_wrapper_impl<T,Wrapper>::type const volatile type;
  };
/** \endcond */

template< typename T, bool IsWrapper = yaul::is_recursive_wrapper<T>::value >
  struct unwrap_recursive_wrapper_impl
  {
    typedef T type;
  };

/** \cond DOXYGEN_SHOW_TEMPLATE_SPECIALIZATIONS */
template< template <typename...> class Wrapper, typename T >
  struct unwrap_recursive_wrapper_impl<Wrapper<T>, true>
  {
    typedef T type;
  };
template< typename T, bool IsWrapper >
  struct unwrap_recursive_wrapper_impl<T const, IsWrapper>
  {
    typedef typename unwrap_recursive_wrapper_impl<T>::type const type;
  };
template< typename T, bool IsWrapper >
  struct unwrap_recursive_wrapper_impl<T volatile, IsWrapper>
  {
    typedef typename unwrap_recursive_wrapper_impl<T>::type volatile type;
  };
template< typename T, bool IsWrapper >
  struct unwrap_recursive_wrapper_impl<T const volatile, IsWrapper>
  {
    typedef typename unwrap_recursive_wrapper_impl<T>::type const volatile type;
  };
/** \endcond */

} } } // end namespace yaul::detail::variant

namespace yaul {

template< typename T >
  struct is_recursive_wrapper
    : detail::variant::is_recursive_wrapper_impl<typename std::remove_cv<T>::type>
  { };

/** // doc: wrap_recursive_wrapper {{{
 * \brief Wrap given type `T` with `Wrapper` while preserving cv-qualifiers
 *
 * \tparam T       A type to be wrapped with `Wrapper`.
 * \tparam Wrapper A wrapper class template to wrap with, defaults to \ref
 *                 recursive_wrapper.
 *
 * \par Synopsis
 * \code
 *  template<
 *      typename T
 *    , template<typename..> class Wrapper = recursive_wrapper
 *  >
 *  struct wrap_recursive_wrapper
 *  {
 *    typedef unspecified type;
 *  };
 * \endcode
 *
 * \par Description
 * For any cv-unqualified, non-reference, non-array type `T`, the following
 * expressions are `true`
 * \code
 *  std::is_same<wrap_recursive_wrapper<T>::type, recursive_wrapper<T> >::value
 *  std::is_same<wrap_recursive_wrapper<T const>::type, recursive_wrapper<T> const>::value
 *  std::is_same<wrap_recursive_wrapper<T volatile>::type, recursive_wrapper<T> volatile>::value
 *  std::is_same<wrap_recursive_wrapper<T const volatile>::type, recursive_wrapper<T> const volatile>::value
 * \endcode
 * For any, possibly cv-qualified, non-reference, non-array type `T` and an
 * integer constant `n` the follwing expressions are `true`
 * \code
 *  std::is_same<wrap_recursive_wrapper<T&>::type, T&>::value
 *  std::is_same<wrap_recursive_wrapper<T&&>::type, T&&>::value
 *  std::is_same<wrap_recursive_wrapper<T[]>::type, T[]>::value
 *  std::is_same<wrap_recursive_wrapper<T[n]>::type, T[n]>::value
 * \endcode
 */ // }}}
template< typename T, template<typename...> class Wrapper = recursive_wrapper >
  struct wrap_recursive_wrapper
    : detail::variant::wrap_recursive_wrapper_impl<T,Wrapper>
  { };

/** // doc: unwrap_recursive_wrapper {{{
 * \brief Unwrap a type from recursive wrapper
 *
 * \tparam T  A type, possibly a recursive wrapper, to be unwrapped.
 *
 * \par Synopsis
 * \code
 *  template< typename T >
 *  struct unwrap_recursive_wrapper
 *  {
 *    typedef unspecified type;
 *  };
 * \endcode
 *
 * \par Description
 * If `F` is a class template matching `template<typename..> class` pattern,
 * `X` is a type, `T` is identical with `F<X>`, and the following expression is
 * `true`
 * \code
 *  yaul::is_recursive_wrapper<T>::value
 * \endcode
 * then the following expressions are `true` as well
 * \code
 *  std::is_same<unwrap_recursive_wrapper<F<X> >, X>::value
 *  std::is_same<unwrap_recursive_wrapper<F<X> const>, X const>::value
 *  std::is_same<unwrap_recursive_wrapper<F<X> volatile>, X volatile>::value
 *  std::is_same<unwrap_recursive_wrapper<F<X> const volatile>, X const volatile>::value
 * \endcode
 * For any type `T`, for which
 * \code
 *   yaul::is_recursive_wrapper<T>::value
 * \endcode
 * is `false`, the following expression is `true`
 * \code
 *  std::is_same<unwrap_recursive_wrapper<T>::type, T>::value
 * \endcode
 *
 */ // }}}
template< typename T >
  struct unwrap_recursive_wrapper
    : detail::variant::unwrap_recursive_wrapper_impl<T>
  { };
} // end namespace yaul



#endif /* YAUL_VARIANT_RECURSIVE_WRAPPER_FWD_HPP */
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
