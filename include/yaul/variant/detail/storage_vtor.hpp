// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

// yaul/variant/detail/storage_vtor.hpp

/** // doc: yaul/variant/detail/storage_vtor.hpp {{{
 * \file yaul/variant/detail/storage_vtor.hpp
 * \todo Write documentation
 */ // }}}
#ifndef YAUL_VARIANT_DETAIL_STORAGE_VTOR_HPP
#define YAUL_VARIANT_DETAIL_STORAGE_VTOR_HPP

#include <cstddef>
#include <utility>
#include <yaul/variant/detail/storage_cast.hpp>

namespace yaul { namespace detail { namespace variant {
/** \ingroup FixMe FIXME:
 * @{ */
/** // doc: storage_vtor_impl {{{
 * \todo Write documentation
 */ // }}}
template< std::size_t I, typename S, typename... Types>
  struct storage_vtor_impl;

/** // doc: storage_vtor {{{
 * \todo Write documentation
 */ // }}}
template< typename S, typename T, typename... Others>
  struct storage_vtor
    : storage_vtor_impl<0ul, S, T, Others...>
  {
    using Base = storage_vtor_impl<0ul, S, T, Others...>;
    using Base::Base;
    using Base::operator();
  };

/** \cond DOXYGEN_SHOW_TEMPLATE_SPECIALIZATIONS */
template< std::size_t I, typename S, typename T, typename... Others>
  struct storage_vtor_impl<I, S, T, Others...>
    : storage_vtor_impl<I+1ul, S, Others...>
  {
    using Base = storage_vtor_impl<I+1ul, S, Others...>;
    using Base::Base;
    using Base::operator();

    template<typename F>
    typename std::remove_reference<F>::type::result_type // FIXME: elaborate
    operator()(S& s, F&& f) const&&
      noexcept(
          noexcept(std::forward<F>(f)(detail::variant::storage_cast<T&>(s))) &&
          noexcept(std::declval<storage_vtor_impl const&&>().Base::operator()(s,std::forward<F>(f)))
      )
    {
      if(I == which_)
        return std::forward<F>(f)(detail::variant::storage_cast<T&>(s));
      else
        return std::move(*this).Base::operator()(s, std::forward<F>(f));
    }

    template<typename F>
    typename std::remove_reference<F>::type::result_type // FIXME: elaborate
    operator()(S const& s, F&& f) const&&
      noexcept(
          noexcept(std::forward<F>(f)(detail::variant::storage_cast<T const&>(s))) && 
          noexcept(std::declval<storage_vtor_impl const&&>().Base::operator()(s, std::forward<F>(f)))
      )
    {
      if(I == which_)
        return std::forward<F>(f)(detail::variant::storage_cast<T const&>(s));
      else
        return std::move(*this).Base::operator()(s, std::forward<F>(f));
    }

    template<typename F>
    typename std::remove_reference<F>::type::result_type // FIXME: elaborate
    operator()(S&& s, F&& f) const&&
      noexcept(
          noexcept(std::forward<F>(f)(detail::variant::storage_cast<T&&>(std::move(s)))) &&
          noexcept(std::declval<storage_vtor_impl const&&>().Base::operator()(std::move(s), std::forward<F>(f)))
      )
    {
      if(I == which_)
        return std::forward<F>(f)(detail::variant::storage_cast<T&&>(std::move(s)));
      else
        return std::move(*this).Base::operator()(std::move(s), std::forward<F>(f));
    }

    template<typename F>
    typename std::remove_reference<F>::type::result_type // FIXME: elaborate
    operator()(S const&& s, F&& f) const&&
      noexcept(
          noexcept(std::forward<F>(f)(detail::variant::storage_cast<T const&&>(std::move(s)))) &&
          noexcept(std::declval<storage_vtor_impl const&&>().Base::operator()(std::move(s), std::forward<F>(f)))
      )
    {
      if(I == which_)
        return std::forward<F>(f)(detail::variant::storage_cast<T const&&>(std::move(s)));
      else
        return std::move(*this).Base::operator()(std::move(s), std::forward<F>(f));
    }

  protected:
    using Base::which_;
  };

//
// specialization for recursive_variant<TT>, breaks the endless recursions that
// would occur in noexcept(...) deduction
//
template< std::size_t I, typename S, typename TT, typename... Others>
  struct storage_vtor_impl<I, S, recursive_variant<TT>, Others...>
    : storage_vtor_impl<I+1ul, S, Others...>
  {
    using Base = storage_vtor_impl<I+1ul, S, Others...>;
    using Base::Base;
    using Base::operator();
    using T = recursive_variant<TT>;

    template<typename F>
    typename std::remove_reference<F>::type::result_type // FIXME: elaborate
    operator()(S& s, F&& f) const&&
      noexcept
    {
      if(I == which_)
        return std::forward<F>(f)(detail::variant::storage_cast<T&>(s));
      else
        return std::move(*this).Base::operator()(s, std::forward<F>(f));
    }

    template<typename F>
    typename std::remove_reference<F>::type::result_type // FIXME: elaborate
    operator()(S const& s, F&& f) const&&
      noexcept
    {
      if(I == which_)
        return std::forward<F>(f)(detail::variant::storage_cast<T const&>(s));
      else
        return std::move(*this).Base::operator()(s, std::forward<F>(f));
    }

    template<typename F>
    typename std::remove_reference<F>::type::result_type // FIXME: elaborate
    operator()(S&& s, F&& f) const&&
      noexcept
    {
      if(I == which_)
        return std::forward<F>(f)(detail::variant::storage_cast<T&&>(std::move(s)));
      else
        return std::move(*this).Base::operator()(std::move(s), std::forward<F>(f));
    }

    template<typename F>
    typename std::remove_reference<F>::type::result_type // FIXME: elaborate
    operator()(S const&& s, F&& f) const&&
      noexcept
    {
      if(I == which_)
        return std::forward<F>(f)(detail::variant::storage_cast<T const&&>(std::move(s)));
      else
        return std::move(*this).Base::operator()(std::move(s), std::forward<F>(f));
    }

  protected:
    using Base::which_;
  };

template< std::size_t I, typename S, typename T>
  struct storage_vtor_impl<I, S, T>
  {
    storage_vtor_impl() = delete;

    storage_vtor_impl(int which) noexcept
      : which_(which)
    { }

    template<typename F>
    typename std::remove_reference<F>::type::result_type // FIXME: elaborate
    operator()(S& s, F&& f) const&&
      noexcept( noexcept(std::forward<F>(f)(detail::variant::storage_cast<T&>(s))) )
    {
      return std::forward<F>(f)(detail::variant::storage_cast<T&>(s));
    }

    template<typename F>
    typename std::remove_reference<F>::type::result_type // FIXME: elaborate
    operator()(S const& s, F&& f) const&&
      noexcept( noexcept(std::forward<F>(f)(detail::variant::storage_cast<T const&>(s))) )
    {
      return std::forward<F>(f)(detail::variant::storage_cast<T const&>(s));
    }

    template<typename F>
    typename std::remove_reference<F>::type::result_type // FIXME: elaborate
    operator()(S&& s, F&& f) const&&
      noexcept( noexcept(std::forward<F>(f)(detail::variant::storage_cast<T&&>(std::move(s)))) )
    {
      return std::forward<F>(f)(detail::variant::storage_cast<T&&>(std::move(s)));
    }

    template<typename F>
    typename std::remove_reference<F>::type::result_type // FIXME: elaborate
    operator()(S const&& s, F&& f) const&&
      noexcept( noexcept(std::forward<F>(f)(detail::variant::storage_cast<T const&&>(std::move(s)))) )
    {
      return std::forward<F>(f)(detail::variant::storage_cast<T const&&>(std::move(s)));
    }

  protected:
    int which_;
  };

template< std::size_t I, typename S, typename TT>
  struct storage_vtor_impl<I, S, recursive_variant<TT> >
  {
    using T = recursive_variant<TT>;

    storage_vtor_impl() = delete;

    storage_vtor_impl(int which) noexcept
      : which_(which)
    { }

    template<typename F>
    typename std::remove_reference<F>::type::result_type // FIXME: elaborate
    operator()(S& s, F&& f) const&&
      noexcept
    {
      return std::forward<F>(f)(detail::variant::storage_cast<T&>(s));
    }

    template<typename F>
    typename std::remove_reference<F>::type::result_type // FIXME: elaborate
    operator()(S const& s, F&& f) const&&
      noexcept
    {
      return std::forward<F>(f)(detail::variant::storage_cast<T const&>(s));
    }

    template<typename F>
    typename std::remove_reference<F>::type::result_type // FIXME: elaborate
    operator()(S&& s, F&& f) const&&
      noexcept
    {
      return std::forward<F>(f)(detail::variant::storage_cast<T&&>(std::move(s)));
    }

    template<typename F>
    typename std::remove_reference<F>::type::result_type // FIXME: elaborate
    operator()(S const&& s, F&& f) const&&
      noexcept
    {
      return std::forward<F>(f)(detail::variant::storage_cast<T const&&>(std::move(s)));
    }

  protected:
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
  struct make_storage_vtor;

template<typename S, typename T0, typename... Others>
  struct make_storage_vtor< S, yaul::variant<T0,Others...> >
  {
    typedef storage_vtor<S, T0, Others...> type;
  };
template<typename S, typename T0, typename... Others>
  struct make_storage_vtor< S, yaul::variant<recursive_flag<T0>,Others...> >
  {
    using Variant = yaul::variant<recursive_flag<T0>,Others...>;
    template< typename T >
      using er_t = typename enable_recursive<T, Variant>::type;
    typedef storage_vtor<S, er_t<T0>,er_t<Others>...> type;
  };
template< typename S, typename Variant >
  using make_storage_vtor_t = typename make_storage_vtor<S, Variant>::type;
} } } // end namespace yaul::detail::variant

#endif /* YAUL_VARIANT_DETAIL_STORAGE_VTOR_HPP */
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
