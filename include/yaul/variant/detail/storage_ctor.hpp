// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

// yaul/variant/detail/storage_ctor.hpp

/** // doc: yaul/variant/detail/storage_ctor.hpp {{{
 * \file yaul/variant/detail/storage_ctor.hpp
 * \todo Write documentation
 */ // }}}
#ifndef YAUL_VARIANT_DETAIL_STORAGE_CTOR_HPP
#define YAUL_VARIANT_DETAIL_STORAGE_CTOR_HPP

#include <cstddef>
#include <utility>

namespace yaul { namespace detail { namespace variant {
/** \ingroup FixMe FIXME:
 * @{ */
/** // doc: storage_ctor_impl {{{
 * \todo Write documentation
 */ // }}}
template< std::size_t I, typename S, typename... Types>
  struct storage_ctor_impl;

/** // doc: storage_ctor {{{
 * \todo Write documentation
 */ // }}}
template< typename S, typename T, typename... Others>
  struct storage_ctor
    : storage_ctor_impl<0ul, S, T, Others...>
  {
    using Base = storage_ctor_impl<0ul, S, T, Others...>;
    using Base::Base;
    using Base::operator();

    typedef int result_type;

    int operator()() const&&
      noexcept(noexcept(T()))
    {
      new(&std::move(*this).storage_) T();
      return 0ul;
    }

  protected:
    using Base::storage_;
  };
/** \cond DOXYGEN_SHOW_TEMPLATE_SPECIALIZATIONS */
template< std::size_t I, typename S, typename T, typename... Others>
  struct storage_ctor_impl<I, S, T, Others...>
    : storage_ctor_impl<I+1ul, S, Others...>
  {
    using Base = storage_ctor_impl<I+1ul, S, Others...>;
    using Base::Base;
    using Base::operator();

    int operator()(T& t) const&&
      noexcept(noexcept(T(t)))
    {
      new(&std::move(*this).storage_) T(t);
      return static_cast<int>(I);
    }
    int operator()(T const& t) const&&
      noexcept(noexcept(T(t)))
    {
      new(&std::move(*this).storage_) T(t);
      return static_cast<int>(I);
    }
    int operator()(T&& t) const&&
      noexcept(noexcept(T(std::move(t))))
    {
      new(&std::move(*this).storage_) T(std::move(t));
      return static_cast<int>(I);
    }

  protected:
    using Base::storage_;
  };

template< std::size_t I, typename S >
  struct storage_ctor_impl<I, S>
  {
    storage_ctor_impl() = delete;

    storage_ctor_impl(S& storage) noexcept
      : storage_(storage)
    { }

    // dummy operator to enable "using Base::operator()" in subclasses
    int operator()() const&& noexcept { return I; }
  protected:
    S& storage_;
  };
/** \endcond */

/** @} */
} } } // end namespace yaul::detail::variant

#include <yaul/variant/variant_fwd.hpp>
#include <yaul/variant/detail/recursive_flag.hpp>
#include <yaul/variant/detail/enable_recursive.hpp>

namespace yaul { namespace detail { namespace variant {
template<typename S, typename Variant>
  struct make_storage_ctor;

template<typename S, typename T0, typename... Others>
  struct make_storage_ctor< S, yaul::variant<T0,Others...> >
  {
    typedef storage_ctor<S, T0,Others...> type;
  };
template<typename S, typename T0, typename... Others>
  struct make_storage_ctor< S, yaul::variant<recursive_flag<T0>,Others...> >
  {
    using Variant = yaul::variant<recursive_flag<T0>,Others...>;
    template< typename T >
      using er_t = typename enable_recursive<T, Variant>::type;
    typedef storage_ctor<S, er_t<T0>,er_t<Others>...> type;
  };
template< typename S, typename Variant >
  using make_storage_ctor_t = typename make_storage_ctor<S, Variant>::type;
} } } // end namespace yaul::detail::variant

#endif /* YAUL_VARIANT_DETAIL_STORAGE_CTOR_HPP */
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
