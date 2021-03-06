// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

// yaul/variant/detail/storage_dtor.hpp

/** // doc: yaul/variant/detail/storage_dtor.hpp {{{
 * \file yaul/variant/detail/storage_dtor.hpp
 * \todo Write documentation
 */ // }}}
#ifndef YAUL_VARIANT_DETAIL_STORAGE_DTOR_HPP
#define YAUL_VARIANT_DETAIL_STORAGE_DTOR_HPP

#include <cstddef>
#include <utility>

namespace yaul { namespace detail { namespace variant {
/** \ingroup FixMe FIXME:
 * @{ */
/** // doc: storage_dtor_impl {{{
 * \todo Write documentation
 */ // }}}
template< std::size_t I, typename S, typename... Types>
  struct storage_dtor_impl;

/** // doc: storage_dtor {{{
 * \todo Write documentation
 */ // }}}
template< typename S, typename T, typename... Others>
  struct storage_dtor
    : storage_dtor_impl<0ul, S, T, Others...>
  {
    using Base = storage_dtor_impl<0ul, S, T, Others...>;
    using Base::Base;
    using Base::operator();
  };
/** \cond DOXYGEN_SHOW_TEMPLATE_SPECIALIZATIONS */
template< std::size_t I, typename S, typename T, typename... Others>
  struct storage_dtor_impl<I, S, T, Others...>
    : storage_dtor_impl<I+1ul, S, Others...>
  {
    using Base = storage_dtor_impl<I+1ul, S, Others...>;
    using Base::Base;
    using Base::operator();

    void operator()() const&&
      noexcept(
          noexcept(reinterpret_cast<T&>(std::declval<storage_dtor_impl const&&>().storage_).~T()) &&
          noexcept(std::declval<storage_dtor_impl const&&>().Base::operator()())
      )
    {
      if(I == which_)
        reinterpret_cast<T&>(std::move(*this).storage_).~T();
      else
        std::move(*this).Base::operator()();
    }
  protected:
    using Base::storage_;
    using Base::which_;
  };

template< std::size_t I, typename S>
  struct storage_dtor_impl<I, S>
  {
    storage_dtor_impl() = delete;

    storage_dtor_impl(S& storage, int which) noexcept
      : storage_(storage), which_(which)
    { }

    // dummy operator to enable "using Base::operator()" in subclasses
    void operator()() const&& noexcept { }
  protected:
    S& storage_;
    int which_;
  };
/** \endcond */
/** @} */
} } } // end namespace yaul::detail::variant


#include <yaul/variant/variant_fwd.hpp>
#include <yaul/variant/detail/recursive_flag.hpp>
#include <yaul/variant/detail/enable_recursive.hpp>

namespace yaul { namespace detail { namespace variant {
template<typename S, typename Variant>
  struct make_storage_dtor;

template<typename S, typename T0, typename... Others>
  struct make_storage_dtor< S, yaul::variant<T0,Others...> >
  {
    typedef storage_dtor<S, T0,Others...> type;
  };
template<typename S, typename T0, typename... Others>
  struct make_storage_dtor< S, yaul::variant<recursive_flag<T0>,Others...> >
  {
    using Variant = yaul::variant<recursive_flag<T0>,Others...>;
    template< typename T >
      using er_t = typename enable_recursive<T, Variant>::type;
    typedef storage_dtor<S, er_t<T0>,er_t<Others>...> type;
  };
template< typename S, typename Variant >
  using make_storage_dtor_t = typename make_storage_dtor<S, Variant>::type;
} } } // end namespace yaul::detail::variant

#endif /* YAUL_VARIANT_DETAIL_STORAGE_DTOR_HPP */
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
