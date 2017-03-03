// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

// yaul/variant/detail/substitute.hpp

/** // doc: yaul/variant/detail/substitute.hpp {{{
 * \file yaul/variant/detail/substitute.hpp
 * \brief Provides \ref yaul::detail::variant::substitute metafunction
 */ // }}}
#ifndef YAUL_VARIANT_DETAIL_SUBSTITUTE_HPP
#define YAUL_VARIANT_DETAIL_SUBSTITUTE_HPP

namespace yaul { namespace detail { namespace variant {
/** // doc: substitute {{{
 * \brief Handles embedded variant types when substituting for
 *        \ref yaul::recursive_variant_tag "recursive_variant_tag"
 *
 * \tparam T a type to be "scanned" for \c Source type, \c T may be
 *         cv-qualified type, may also be a pointer or reference type,
 * \tparam Dest a cv-unqualified type to substitute \c Source with,
 * \tparam Source a cv-unqualified type to be substituted with \c Dest.
 *
 * \par Synopsis
 * \code
 * template<
 *     typename T
 *   , typename Dest
 *   , typename Source
 *   >
 * struct substitute
 * {
 *    typedef unspecified type;
 * };
 * \endcode
 *
 * \par Description
 * Whenever \c Source is found in \c T, it gets substituted with \c Dest. The
 * metafunction walks recursively through \c T (if T is an instantiation of
 * a class template) searching for \c Source and substitutes every
 * occurrence of \c Source with \c Dest. When substituting, it preservers
 * cv-qualifiers, references and pointers that were originally applied to
 * the occurrences of \c Source in \c T. The main purpose of this metafunction
 * is to substitute \ref yaul::recursive_variant_tag "recursive_variant_tag" with
 * appropriate variant type. This is usually achieved with the following use
 * \code
 * using R = typename substitute<InputVariant, RecursiveVariant, yaul::recursive_variant_tag>::type;
 * \endcode
 * where \c RecursiveVariant is the actual variant type, such as
 * \c variant<recursive_flag<T0>,T1,...> possibly having \c recursive_variant_tag
 * as one of its types \c Ti.
 *
 * \par Example
 * \code
 *   // substitute "double" with "char" in "int" (no match)
 *   using R = substitute<int, char, double>::type;       // R = int
 *   // substitute "int" with "char" in "int"
 *   using R = substitute<int, char, int>::type;          // R = char
 *   // substitute "int" with "char" in "int const"
 *   using R = substitute<int const, char, int>::type;    // R = char const
 *   // substitute "int" with "char" in "int const*"
 *   using R = substitute<int const*, char, int>::type;   // R = char const*
 *   // substitute "int" with "char" in "int const&"
 *   using R = substitute<int const&, char, int>::type;   // R = char const&
 * \endcode
 *
 * \par Example (templates)
 * \code
 * template<typename...> struct F;
 * // substitute "double" with "char" in F<int,float,void> (no match)
 * using R = substitute<F<int,float,void>, char, double>::type;                     // R = F<int,float,void>
 * // substitute "int" with "char" in F<int,float,void>
 * using R = substitute<F<int,float,void>, char, int>::type;                        // R = F<char,float,void>
 * // substitute "int" with "char" in F<int const volatile*,float,void> const*
 * using R = substitute<F<int const volatile*,float,void> const*, char, int>::type; // R = F<char const volatile*,float,void> const*
 * \endcode
 *
 * \par Example (recursive templates)
 * \code
 * template<typename...> struct F;
 * struct T1;
 * struct T2;
 * // substitute "T1" with "T2" in "F<T1 const, double, F<char, T1> const*>"
 * using R = substitute< F<T1 const&, double, F<char,T1> const*>, T2, T1 >::type; // R = F<T2 const&, double, F<char,T2> const*>
 * \endcode
 */ // }}}
template< typename T, typename Dest, typename Source >
  struct substitute
  {
    typedef T type;
  };

/** \cond DOXYGEN_SHOW_TEMPLATE_SPECIALIZATIONS */
//
// tag specializations
//
template< typename Dest, typename Source >
  struct substitute<Source, Dest, Source>
  {
    typedef Dest type;
  };
template< typename Dest, typename Source >
  struct substitute<const Source, Dest, Source>
  {
    typedef const Dest type;
  };
template< typename Dest, typename Source >
  struct substitute<volatile Source, Dest, Source>
  {
    typedef volatile Dest type;
  };
template< typename Dest, typename Source >
  struct substitute<const volatile Source, Dest, Source>
  {
    typedef const volatile Dest type;
  };

//
// pointer specializations
//
template< typename T, typename Dest, typename Source >
  struct substitute<T*, Dest, Source>
  {
    typedef typename substitute<T, Dest, Source>::type* type;
  };
template< typename T, typename Dest, typename Source >
  struct substitute<T const*, Dest, Source>
  {
    typedef typename substitute<T, Dest, Source>::type const* type;
  };
template< typename T, typename Dest, typename Source >
  struct substitute<T volatile*, Dest, Source>
  {
    typedef typename substitute<T, Dest, Source>::type volatile* type;
  };
template< typename T, typename Dest, typename Source >
  struct substitute<T const volatile*, Dest, Source>
  {
    typedef typename substitute<T, Dest, Source>::type const volatile* type;
  };

//
// reference specialization
//
template< typename T, typename Dest, typename Source >
  struct substitute< T&, Dest, Source >
  {
    typedef typename substitute<T, Dest, Source>::type& type;
  };
template< typename T, typename Dest, typename Source >
  struct substitute< T&&, Dest, Source >
  {
    typedef typename substitute<T, Dest, Source>::type&& type;
  };

//
// template expression (i.e., F<...>) specializations
//
template< template<typename...> class F
        , typename... Ts
        , typename Dest
        , typename Source
        >
  struct substitute<
          F<Ts...>
        , Dest
        , Source
        >
  {
    typedef F<typename substitute<Ts, Dest, Source>::type...> type;
  };

//
// cv-qualified template specializations
//
template< template<typename...> class F
        , typename... Ts
        , typename Dest
        , typename Source
        >
  struct substitute<
          F<Ts...> const
        , Dest
        , Source
        >
  {
    typedef F<typename substitute<Ts, Dest, Source>::type...> const type;
  };

template< template<typename...> class F
        , typename... Ts
        , typename Dest
        , typename Source
        >
  struct substitute<
          F<Ts...> volatile
        , Dest
        , Source
        >
  {
    typedef F<typename substitute<Ts, Dest, Source>::type...> volatile type;
  };

template< template<typename...> class F
        , typename... Ts
        , typename Dest
        , typename Source
        >
  struct substitute<
          F<Ts...> const volatile
        , Dest
        , Source
        >
  {
    typedef F<typename substitute<Ts, Dest, Source>::type...> const volatile type;
  };
/** \endcond */
} } } // end namespace yaul::detail::variant

#endif /* YAUL_VARIANT_DETAIL_SUBSTITUTE_HPP */
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
