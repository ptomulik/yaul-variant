// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

// yaul/variant/detail/substitute.hpp

/** // doc: yaul/variant/detail/substitute.hpp {{{
 * \file yaul/variant/detail/substitute.hpp
 * \todo Write documentation
 */ // }}}
#ifndef YAUL_VARIANT_DETAIL_SUBSTITUTE_HPP
#define YAUL_VARIANT_DETAIL_SUBSTITUTE_HPP

namespace yaul { namespace detail { namespace variant {
/** \ingroup FixMe FIXME:
 * @{ */
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
    : substitute<volatile Dest, Dest, Source>
  {
    typedef volatile Dest type;
  };
template< typename Dest, typename Source >
  struct substitute<const volatile Source, Dest, Source>
    : substitute<const volatile Dest, Dest, Source>
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
/** @} */
} } } // end namespace yaul::detail::variant

#endif /* YAUL_VARIANT_DETAIL_SUBSTITUTE_HPP */
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
