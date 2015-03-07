// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

// yaul/variant/detail/storage_assigner.hpp

/** // doc: yaul/variant/detail/storage_assigner.hpp {{{
 * \file yaul/variant/detail/storage_assigner.hpp
 * \todo Write documentation
 */ // }}}
#ifndef YAUL_VARIANT_DETAIL_STORAGE_ASSIGNER_HPP
#define YAUL_VARIANT_DETAIL_STORAGE_ASSIGNER_HPP

#include <cstddef>
#include <utility>
#include <yaul/variant/recursive_wrapper_fwd.hpp>

namespace yaul { namespace detail { namespace variant {
/** \ingroup FixMe FIXME:
 * @{ */
/** // doc: storage_assigner_impl {{{
 * \todo Write documentation
 */ // }}}
template< std::size_t I, typename S, typename... Types>
  struct storage_assigner_impl;

/** // doc: storage_assigner {{{
 * \todo Write documentation
 */ // }}}
template< typename S, typename T, typename... Others>
  struct storage_assigner
    : storage_assigner_impl<0ul, S, T, Others...>
  {
    using Base = storage_assigner_impl<0ul, S, T, Others...>;
    using Base::Base;
    using Base::operator();
    using Base::which;

    typedef int result_type;
  };
/** \cond DOXYGEN_SHOW_TEMPLATE_SPECIALIZATIONS */
template< std::size_t I, typename S, typename T, typename... Others>
  struct storage_assigner_impl<I, S, T, Others...>
    : storage_assigner_impl<I+1ul, S, Others...>
  {
  public:
    using Base = storage_assigner_impl<I+1ul, S, Others...>;
    using Base::Base;
    using Base::operator();
    using Base::which;

    int operator()(T& t) const&&
      noexcept(noexcept(std::declval<T&>() = t))
    {
      reinterpret_cast<T&>(std::move(*this).storage_) = t;
      return static_cast<int>(I);
    }
    int operator()(T const& t) const&&
      noexcept(noexcept(std::declval<T&>() = t))
    {
      reinterpret_cast<T&>(std::move(*this).storage_) = t;
      return static_cast<int>(I);
    }
    int operator()(T&& t) const&&
      noexcept(noexcept(std::declval<T&>() = std::move(t)))
    {
      reinterpret_cast<T&>(std::move(*this).storage_) = std::move(t);
      return static_cast<int>(I);
    }

    int which(T&) const&& noexcept { return static_cast<int>(I); }
    int which(T const&) const&& noexcept { return static_cast<int>(I); }
    int which(T&&) const&& noexcept { return static_cast<int>(I); }

  protected:
    using Base::storage_;
  };


//
// Specialization for yaul::recursive_wrapper<>.
//
// this specialization is provided to break infinite cycles in noexcept(...)
// computation (withohut this, endless recursion occur when working with
// recursive variants).
//
// note, that each variant involving recursive_wrapper is not nothrow-assignable
// because recursive_wrapper is not nothrow-copy-constructible (althrough it
// may be nothrow-assignable, consider recursive_wrapper<int> as example).
//
template< std::size_t I, typename S, typename TT, typename... Others>
  struct storage_assigner_impl<I, S, yaul::recursive_wrapper<TT>, Others...>
    : storage_assigner_impl<I+1ul, S, Others...>
  {
  public:
    using Base = storage_assigner_impl<I+1ul, S, Others...>;
    using Base::Base;
    using Base::operator();
    using Base::which;
    using T = yaul::recursive_wrapper<TT>;

    int operator()(T& t) const&&
    {
      reinterpret_cast<T&>(std::move(*this).storage_) = t;
      return static_cast<int>(I);
    }
    int operator()(T const& t) const&&
    {
      reinterpret_cast<T&>(std::move(*this).storage_) = t;
      return static_cast<int>(I);
    }
    int operator()(T&& t) const&&
    {
      reinterpret_cast<T&>(std::move(*this).storage_) = std::move(t);
      return static_cast<int>(I);
    }

    int which(T&) const&& noexcept { return static_cast<int>(I); }
    int which(T const&) const&& noexcept { return static_cast<int>(I); }
    int which(T&&) const&& noexcept { return static_cast<int>(I); }

  protected:
    using Base::storage_;
  };

template< std::size_t I, typename S>
  struct storage_assigner_impl<I, S>
  {
    storage_assigner_impl() = delete;

    storage_assigner_impl(S& storage) noexcept
      : storage_(storage)
    { }

    // dummy operator to enable "using Base::operator()" in subclasses
    int operator()() const&& noexcept { return static_cast<int>(I); }
    // dummy method to enable "using Base::which" in subclasses
    int which() const&& noexcept { return static_cast<int>(I); }
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
  struct make_storage_assigner;

template<typename S, typename T0, typename... Others>
  struct make_storage_assigner< S, yaul::variant<T0,Others...> >
  {
    typedef storage_assigner<S, T0,Others...> type;
  };
template<typename S, typename T0, typename... Others>
  struct make_storage_assigner< S, yaul::variant<recursive_flag<T0>,Others...> >
  {
    using Variant = yaul::variant<recursive_flag<T0>,Others...>;
    template< typename T >
      using er_t = typename enable_recursive<T, Variant>::type;
    typedef storage_assigner<S, er_t<T0>,er_t<Others>...> type;
  };
template< typename S, typename Variant >
  using make_storage_assigner_t = typename make_storage_assigner<S, Variant>::type;
} } } // end namespace yaul::detail::variant

#endif /* YAUL_VARIANT_DETAIL_STORAGE_ASSIGNER_HPP */
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
