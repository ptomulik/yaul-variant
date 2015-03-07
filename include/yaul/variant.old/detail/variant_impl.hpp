// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

// yaul/variant/detail/variant_impl.hpp

/** // doc: yaul/variant/detail/variant_impl.hpp {{{
 * \file yaul/variant/detail/variant_impl.hpp
 * \todo Write documentation
 */ // }}}
#ifndef YAUL_VARIANT_DETAIL_VARIANT_IMPL_HPP
#define YAUL_VARIANT_DETAIL_VARIANT_IMPL_HPP

#include <yaul/variant/config.hpp>
#include <yaul/variant/detail/variant_impl_fwd.hpp>
#include <yaul/variant/detail/variant_impl_core.hpp>
#include <yaul/variant/detail/variant_index.hpp>
#include <yaul/variant/variant_type.hpp>
#include <yaul/variant/variant_fwd.hpp>
#include <type_traits>
#include <utility>
#include <cstddef>

namespace yaul { namespace detail { namespace variant {
/** \ingroup FixMeGroup FIXME:
 * @{ */
/** // doc: variant_impl_dflt_ctor {{{
 * \todo Write documentation
 */ // }}}
template< std::size_t I
        , typename Variant
        , typename Next
        , bool Enable = std::is_default_constructible<
            typename variant_type<I,Variant>::type
          >::value >
  struct variant_impl_dflt_ctor
    : variant_impl_core<I, Variant, Next>
  {
    using Base = variant_impl_core<I, Variant, Next>;
    using Base::Base;
    using Base::operator=;

    variant_impl_dflt_ctor() = delete;
    variant_impl_dflt_ctor(variant_impl_dflt_ctor&) = default;
    variant_impl_dflt_ctor(variant_impl_dflt_ctor const&) = default;
    variant_impl_dflt_ctor(variant_impl_dflt_ctor&&) = default;

    variant_impl_dflt_ctor& operator=(variant_impl_dflt_ctor&) = default;
    variant_impl_dflt_ctor& operator=(variant_impl_dflt_ctor const&) = default;
    variant_impl_dflt_ctor& operator=(variant_impl_dflt_ctor&&) = default;
  };
/** \cond DOXYGEN_SHOW_TEMPLATE_SPECIALIZATIONS */
template <std::size_t I, typename Variant, typename Next>
  struct variant_impl_dflt_ctor<I, Variant, Next, true>
    : variant_impl_core<I, Variant, Next>
  {
    using TI = typename variant_type<I, Variant>::type;
    using Base = variant_impl_core<I, Variant, Next>;
    using Base::Base;
    using Base::operator=;

    variant_impl_dflt_ctor()
#ifndef YAUL_VARIANT_DISABLE_NOEXCEPT_PROPAGATION_IN_DFLT_CTOR
        noexcept(noexcept(Base(variant_index<I>())))
#endif
      : Base(variant_index<I>())
    { }
    variant_impl_dflt_ctor(variant_impl_dflt_ctor&) = default;
    variant_impl_dflt_ctor(variant_impl_dflt_ctor const&) = default;
    variant_impl_dflt_ctor(variant_impl_dflt_ctor&&) = default;

    variant_impl_dflt_ctor& operator=(variant_impl_dflt_ctor&) = default;
    variant_impl_dflt_ctor& operator=(variant_impl_dflt_ctor const&) = default;
    variant_impl_dflt_ctor& operator=(variant_impl_dflt_ctor&&) = default;
  };
/** \endcond */

/** // doc: variant_impl_seleft_dflt_ctor {{{
 * \todo Write documentation
 */ // }}}
template< std::size_t I, typename Variant, typename Next >
struct variant_impl_select_base
{
  typedef variant_impl_core<I, Variant, Next> type;
};
template< typename Variant, typename Next >
struct variant_impl_select_base<0ul, Variant, Next>
{
  typedef variant_impl_dflt_ctor<0ul, Variant, Next> type;
};

/** // doc: variant_impl_lref_ctor {{{
 * \todo Write documentation
 */ // }}}
template< std::size_t I
        , typename Variant
        , typename Next
        , bool Enable = std::is_constructible<
            typename variant_type<I,Variant>::type
          , typename variant_type<I,Variant>::type&
          >::value
        >
  struct variant_impl_lref_ctor
    : variant_impl_core<I, Variant, Next>
  {
    using Base = variant_impl_core<I, Variant, Next>;
    using Base::Base;
    using Base::operator=;

    variant_impl_lref_ctor() = default;
    variant_impl_lref_ctor(variant_impl_lref_ctor&) = default;
    variant_impl_lref_ctor(variant_impl_lref_ctor const&) = default;
    variant_impl_lref_ctor(variant_impl_lref_ctor&&) = default;

    variant_impl_lref_ctor& operator=(variant_impl_lref_ctor&) = default;
    variant_impl_lref_ctor& operator=(variant_impl_lref_ctor const&) = default;
    variant_impl_lref_ctor& operator=(variant_impl_lref_ctor&&) = default;
  };

/** \cond DOXYGEN_SHOW_TEMPLATE_SPECIALIZATIONS */
template< std::size_t I, typename Variant, typename Next>
  struct variant_impl_lref_ctor<I, Variant, Next, false>
    : variant_impl_select_base<I, Variant, Next>::type
  {
    using Base = typename variant_impl_select_base<I, Variant, Next>::type;
    using Base::Base;
    using Base::operator=;

    variant_impl_lref_ctor() = default;
    variant_impl_lref_ctor(variant_impl_lref_ctor&) = delete;
    variant_impl_lref_ctor(variant_impl_lref_ctor const&) = default;
    variant_impl_lref_ctor(variant_impl_lref_ctor&&) = default;

    variant_impl_lref_ctor& operator=(variant_impl_lref_ctor&) = default;
    variant_impl_lref_ctor& operator=(variant_impl_lref_ctor const&) = default;
    variant_impl_lref_ctor& operator=(variant_impl_lref_ctor&&) = default;
  };
template< typename Variant, typename Next>
  struct variant_impl_lref_ctor<0ul, Variant, Next, true>
    : variant_impl_dflt_ctor<0ul, Variant, Next>
  {
    using Base = variant_impl_dflt_ctor<0ul, Variant, Next>;
    using Base::Base;
    using Base::operator=;

    variant_impl_lref_ctor() = default;
    variant_impl_lref_ctor(variant_impl_lref_ctor& other)
#ifndef YAUL_VARIANT_DISABLE_NOEXCEPT_PROPAGATION_IN_COPY_CTOR
        noexcept(noexcept(Base(variant_index<0ul>(), other)))
#endif
      : Base(variant_index<0ul>(), other)
    { }
    variant_impl_lref_ctor(variant_impl_lref_ctor const&) = default;
    variant_impl_lref_ctor(variant_impl_lref_ctor&&) = default;

    variant_impl_lref_ctor& operator=(variant_impl_lref_ctor&) = default;
    variant_impl_lref_ctor& operator=(variant_impl_lref_ctor const&) = default;
    variant_impl_lref_ctor& operator=(variant_impl_lref_ctor&&) = default;
  };
/** \endcond */

template< std::size_t I
        , typename Variant
        , typename Next
        , bool Enable = std::is_constructible<
            typename variant_type<I,Variant>::type
          , typename variant_type<I,Variant>::type const&
          >::value
        >
  struct variant_impl_cref_ctor
    : variant_impl_lref_ctor<I, Variant, Next>
  {
    using Base = variant_impl_lref_ctor<I, Variant, Next>;
    using Base::Base;
    using Base::operator=;

    variant_impl_cref_ctor() = default;
    variant_impl_cref_ctor(variant_impl_cref_ctor&) = default;
    variant_impl_cref_ctor(variant_impl_cref_ctor const&) = default;
    variant_impl_cref_ctor(variant_impl_cref_ctor&&) = default;

    variant_impl_cref_ctor& operator=(variant_impl_cref_ctor&) = default;
    variant_impl_cref_ctor& operator=(variant_impl_cref_ctor const&) = default;
    variant_impl_cref_ctor& operator=(variant_impl_cref_ctor&&) = default;
  };

/** \cond DOXYGEN_SHOW_TEMPLATE_SPECIALIZATIONS */
template< std::size_t I, typename Variant, typename Next>
  struct variant_impl_cref_ctor<I, Variant, Next, false>
    : variant_impl_lref_ctor<I, Variant, Next>
  {
    using Base = variant_impl_lref_ctor<I, Variant, Next>;
    using Base::Base;
    using Base::operator=;

    variant_impl_cref_ctor() = default;
    variant_impl_cref_ctor(variant_impl_cref_ctor&) = default;
    variant_impl_cref_ctor(variant_impl_cref_ctor const&) = delete;
    variant_impl_cref_ctor(variant_impl_cref_ctor&&) = default;

    variant_impl_cref_ctor& operator=(variant_impl_cref_ctor&) = default;
    variant_impl_cref_ctor& operator=(variant_impl_cref_ctor const&) = default;
    variant_impl_cref_ctor& operator=(variant_impl_cref_ctor&&) = default;
  };
template< typename Variant, typename Next>
  struct variant_impl_cref_ctor<0ul, Variant, Next, true>
    : variant_impl_lref_ctor<0ul, Variant, Next>
  {
    using Base = variant_impl_lref_ctor<0ul, Variant, Next>;
    using Base::Base;
    using Base::operator=;

    variant_impl_cref_ctor() = default;
    variant_impl_cref_ctor(variant_impl_cref_ctor&) = default;
    variant_impl_cref_ctor(variant_impl_cref_ctor const& other)
#ifndef YAUL_VARIANT_DISABLE_NOEXCEPT_PROPAGATION_IN_COPY_CTOR
          noexcept(noexcept(Base(variant_index<0ul>(), other)))
#endif
      : Base(variant_index<0ul>(), other)
    { }
    variant_impl_cref_ctor(variant_impl_cref_ctor&&) = default;

    variant_impl_cref_ctor& operator=(variant_impl_cref_ctor&) = default;
    variant_impl_cref_ctor& operator=(variant_impl_cref_ctor const&) = default;
    variant_impl_cref_ctor& operator=(variant_impl_cref_ctor&&) = default;
  };
/** \endcond */

template< std::size_t I
        , typename Variant
        , typename Next
        , bool Enable = std::is_constructible<
            typename variant_type<I,Variant>::type
          , typename variant_type<I,Variant>::type&&
          >::value
        >
  struct variant_impl_move_ctor
    : variant_impl_cref_ctor<I, Variant, Next>
  {
    using Base = variant_impl_cref_ctor<I, Variant, Next>;
    using Base::Base;
    using Base::operator=;

    variant_impl_move_ctor() = default;
    variant_impl_move_ctor(variant_impl_move_ctor&) = default;
    variant_impl_move_ctor(variant_impl_move_ctor const&) = default;
    variant_impl_move_ctor(variant_impl_move_ctor&&) = default;

    variant_impl_move_ctor& operator=(variant_impl_move_ctor&) = default;
    variant_impl_move_ctor& operator=(variant_impl_move_ctor const&) = default;
    variant_impl_move_ctor& operator=(variant_impl_move_ctor&&) = default;
  };

/** \cond DOXYGEN_SHOW_TEMPLATE_SPECIALIZATIONS */
template< std::size_t I, typename Variant, typename Next>
  struct variant_impl_move_ctor<I, Variant, Next, false>
    : variant_impl_cref_ctor<I, Variant, Next >
  {
    using Base = variant_impl_cref_ctor<I, Variant, variant_impl<I-1,Variant> >;
    using Base::Base;
    using Base::operator=;

    variant_impl_move_ctor() = default;
    variant_impl_move_ctor(variant_impl_move_ctor&) = default;
    variant_impl_move_ctor(variant_impl_move_ctor const&) = default;
    variant_impl_move_ctor(variant_impl_move_ctor&& other) = delete;

    variant_impl_move_ctor& operator=(variant_impl_move_ctor&) = default;
    variant_impl_move_ctor& operator=(variant_impl_move_ctor const&) = default;
    variant_impl_move_ctor& operator=(variant_impl_move_ctor&&) = default;
  };
template< typename Variant, typename Next >
  struct variant_impl_move_ctor<0ul, Variant, Next, true>
    : variant_impl_cref_ctor<0ul, Variant, Next>
  {
    using Base = variant_impl_cref_ctor<0ul, Variant, variant_impl<0ul-1,Variant> >;
    using Base::Base;
    using Base::operator=;

    variant_impl_move_ctor() = default;
    variant_impl_move_ctor(variant_impl_move_ctor&) = default;
    variant_impl_move_ctor(variant_impl_move_ctor const&) = default;
    variant_impl_move_ctor(variant_impl_move_ctor&& other)
#ifndef YAUL_VARIANT_DISABLE_NOEXCEPT_PROPAGATION_IN_MOVE_CTOR
          noexcept(noexcept(Base(variant_index<0ul>(), std::move(other))))
#endif
      : Base(variant_index<0ul>(), std::move(other))
    { }

    variant_impl_move_ctor& operator=(variant_impl_move_ctor&) = default;
    variant_impl_move_ctor& operator=(variant_impl_move_ctor const&) = default;
    variant_impl_move_ctor& operator=(variant_impl_move_ctor&&) = default;
  };
/** \endcond */

template< std::size_t I
        , typename Variant
        , typename Next
        , bool Enable = std::is_assignable<
            typename variant_type<I,Variant>::type
          , typename variant_type<I,Variant>::type&
          >::value && std::is_constructible<
            typename variant_type<I,Variant>::type
          , typename variant_type<I,Variant>::type&
          >::value
        >
  struct variant_impl_lref_assign
    : variant_impl_move_ctor<I, Variant, Next>
  {
    using Base = variant_impl_move_ctor<I, Variant, Next>;
    using Base::Base;
    using Base::operator=;

    variant_impl_lref_assign() = default;
    variant_impl_lref_assign(variant_impl_lref_assign&) = default;
    variant_impl_lref_assign(variant_impl_lref_assign const&) = default;
    variant_impl_lref_assign(variant_impl_lref_assign&&) = default;

    variant_impl_lref_assign& operator=(variant_impl_lref_assign&) = default;
    variant_impl_lref_assign& operator=(variant_impl_lref_assign const&) = default;
    variant_impl_lref_assign& operator=(variant_impl_lref_assign&&) = default;

    Variant& operator= (typename variant_type<I, Variant>::type& t)
#ifndef YAUL_VARIANT_DISABLE_NOEXCEPT_PROPAGATION_IN_LREF_ASSIGNMENT
        noexcept(noexcept(reinterpret_cast<variant_impl_lref_assign*>(0)->assign(variant_index<I>(), t)))
#endif
    {
      assign(variant_index<I>(), t);
      return static_cast<Variant&>(*this);
    }
  };

/** \cond DOXYGEN_SHOW_TEMPLATE_SPECIALIZATIONS */
template< std::size_t I, typename Variant, typename Next>
  struct variant_impl_lref_assign<I, Variant, Next, false>
    : variant_impl_move_ctor<I, Variant, Next >
  {
    using Base = variant_impl_move_ctor<I, Variant, variant_impl<I-1,Variant> >;
    using Base::Base;
    using Base::operator=;

    variant_impl_lref_assign() = default;
    variant_impl_lref_assign(variant_impl_lref_assign&) = default;
    variant_impl_lref_assign(variant_impl_lref_assign const&) = default;
    variant_impl_lref_assign(variant_impl_lref_assign&&) = default;

    variant_impl_lref_assign& operator=(variant_impl_lref_assign&) = delete;
    variant_impl_lref_assign& operator=(variant_impl_lref_assign const&) = default;
    variant_impl_lref_assign& operator=(variant_impl_lref_assign&&) = default;

    Variant& operator= (typename variant_type<I, Variant>::type& t) = delete;
  };

template< typename Variant, typename Next >
  struct variant_impl_lref_assign<0ul, Variant, Next, true>
    : variant_impl_move_ctor<0ul, Variant, Next>
  {
    using Base = variant_impl_move_ctor<0ul, Variant, variant_impl<0ul-1,Variant> >;
    using Base::Base;
    using Base::operator=;

    variant_impl_lref_assign() = default;
    variant_impl_lref_assign(variant_impl_lref_assign&) = default;
    variant_impl_lref_assign(variant_impl_lref_assign const&) = default;
    variant_impl_lref_assign(variant_impl_lref_assign&&) = default;

    variant_impl_lref_assign& operator=(variant_impl_lref_assign& other)
#ifndef YAUL_VARIANT_DISABLE_NOEXCEPT_PROPAGATION_IN_COPY_ASSIGNMENT
    //  noexcept(noexcept(Base::assign_variant(variant_index<0ul>(),other)))
#endif
    {
      (void)other;
      return *this;
      //return Base::assign_variant(variant_index<0ul>(),other);
    }
    variant_impl_lref_assign& operator=(variant_impl_lref_assign const&) = default;
    variant_impl_lref_assign& operator=(variant_impl_lref_assign&&) = default;


    Variant& operator= (typename variant_type<0ul, Variant>::type& t)
#ifndef YAUL_VARIANT_DISABLE_NOEXCEPT_PROPAGATION_IN_LREF_ASSIGNMENT
        noexcept(noexcept(reinterpret_cast<variant_impl_lref_assign*>(0)->assign(variant_index<0ul>(), t)))
#endif
    {
      assign(variant_index<0ul>(), t);
      return static_cast<Variant&>(*this);
    }
  };
/** \endcond */

template< std::size_t I
        , typename Variant
        , typename Next
        , bool Enable = std::is_assignable<
            typename variant_type<I,Variant>::type
          , typename variant_type<I,Variant>::type const&
          >::value && std::is_constructible<
            typename variant_type<I,Variant>::type
          , typename variant_type<I,Variant>::type const&
          >::value
        >
  struct variant_impl_cref_assign
    : variant_impl_move_ctor<I, Variant, Next>
  {
    using Base = variant_impl_move_ctor<I, Variant, Next>;
    using Base::Base;
    using Base::operator=;

    variant_impl_cref_assign() = default;
    variant_impl_cref_assign(variant_impl_cref_assign&) = default;
    variant_impl_cref_assign(variant_impl_cref_assign const&) = default;
    variant_impl_cref_assign(variant_impl_cref_assign&&) = default;

    variant_impl_cref_assign& operator=(variant_impl_cref_assign&) = default;
    variant_impl_cref_assign& operator=(variant_impl_cref_assign const&) = default;
    variant_impl_cref_assign& operator=(variant_impl_cref_assign&&) = default;

    Variant& operator= (typename variant_type<I, Variant>::type const& t)
#ifndef YAUL_VARIANT_DISABLE_NOEXCEPT_PROPAGATION_IN_CREF_ASSIGNMENT
        noexcept(noexcept(reinterpret_cast<variant_impl_cref_assign*>(0)->assign(variant_index<I>(), t)))
#endif
    {
      assign(variant_index<I>(), t);
      return static_cast<Variant&>(*this);
    }
  };

/** \cond DOXYGEN_SHOW_TEMPLATE_SPECIALIZATIONS */
template< std::size_t I, typename Variant, typename Next>
  struct variant_impl_cref_assign<I, Variant, Next, false>
    : variant_impl_move_ctor<I, Variant, Next >
  {
    using Base = variant_impl_move_ctor<I, Variant, variant_impl<I-1,Variant> >;
    using Base::Base;
    using Base::operator=;

    variant_impl_cref_assign() = default;
    variant_impl_cref_assign(variant_impl_cref_assign&) = default;
    variant_impl_cref_assign(variant_impl_cref_assign const&) = default;
    variant_impl_cref_assign(variant_impl_cref_assign&&) = default;

    variant_impl_cref_assign& operator=(variant_impl_cref_assign&) = default;
    variant_impl_cref_assign& operator=(variant_impl_cref_assign const&) = delete;
    variant_impl_cref_assign& operator=(variant_impl_cref_assign&&) = default;

    Variant& operator= (typename variant_type<I, Variant>::type const& t) = delete;
  };

template< typename Variant, typename Next >
  struct variant_impl_cref_assign<0ul, Variant, Next, true>
    : variant_impl_move_ctor<0ul, Variant, Next>
  {
    using Base = variant_impl_move_ctor<0ul, Variant, variant_impl<0ul-1,Variant> >;
    using Base::Base;
    using Base::operator=;

    variant_impl_cref_assign() = default;
    variant_impl_cref_assign(variant_impl_cref_assign&) = default;
    variant_impl_cref_assign(variant_impl_cref_assign const&) = default;
    variant_impl_cref_assign(variant_impl_cref_assign&&) = default;

    variant_impl_cref_assign& operator=(variant_impl_cref_assign&) = default;
    variant_impl_cref_assign& operator=(variant_impl_cref_assign const& other)
#ifndef YAUL_VARIANT_DISABLE_NOEXCEPT_PROPAGATION_IN_COPY_ASSIGNMENT
     // noexcept(noexcept(Base::assign_variant(variant_index<0ul>(),other)))
#endif
    {
      (void)other;
      return *this;
      //return Base::assign_variant(variant_index<0ul>(),other);
    }
    variant_impl_cref_assign& operator=(variant_impl_cref_assign&&) = default;

    Variant& operator= (typename variant_type<0ul, Variant>::type const& t)
#ifndef YAUL_VARIANT_DISABLE_NOEXCEPT_PROPAGATION_IN_CREF_ASSIGNMENT
        noexcept(noexcept(reinterpret_cast<variant_impl_cref_assign*>(0)->assign(variant_index<0ul>(), t)))
#endif
    {
      assign(variant_index<0ul>(), t);
      return static_cast<Variant&>(*this);
    }
  };
/** \endcond */

template< std::size_t I
        , typename Variant
        , typename Next
        , bool Enable = std::is_assignable<
            typename variant_type<I,Variant>::type
          , typename variant_type<I,Variant>::type&&
          >::value && std::is_constructible<
            typename variant_type<I,Variant>::type
          , typename variant_type<I,Variant>::type&&
          >::value
        >
  struct variant_impl_move_assign
    : variant_impl_cref_assign<I, Variant, Next>
  {
    using Base = variant_impl_cref_assign<I, Variant, Next>;
    using Base::Base;
    using Base::operator=;

    variant_impl_move_assign() = default;
    variant_impl_move_assign(variant_impl_move_assign&) = default;
    variant_impl_move_assign(variant_impl_move_assign const&) = default;
    variant_impl_move_assign(variant_impl_move_assign&&) = default;

    variant_impl_move_assign& operator=(variant_impl_move_assign&) = default;
    variant_impl_move_assign& operator=(variant_impl_move_assign const&) = default;
    variant_impl_move_assign& operator=(variant_impl_move_assign&&) = default;

    Variant& operator= (typename variant_type<I, Variant>::type&& t)
#ifndef YAUL_VARIANT_DISABLE_NOEXCEPT_PROPAGATION_IN_RREF_ASSIGNMENT
        noexcept(noexcept(reinterpret_cast<variant_impl_move_assign*>(0)->assign(variant_index<I>(), std::move(t))))
#endif
    {
      assign(variant_index<I>(), std::move(t));
      return static_cast<Variant&>(*this);
    }
  };

/** \cond DOXYGEN_SHOW_TEMPLATE_SPECIALIZATIONS */
template< std::size_t I, typename Variant, typename Next>
  struct variant_impl_move_assign<I, Variant, Next, false>
    : variant_impl_cref_assign<I, Variant, Next >
  {
    using Base = variant_impl_cref_assign<I, Variant, variant_impl<I-1,Variant> >;
    using Base::Base;
    using Base::operator=;

    variant_impl_move_assign() = default;
    variant_impl_move_assign(variant_impl_move_assign&) = default;
    variant_impl_move_assign(variant_impl_move_assign const&) = default;
    variant_impl_move_assign(variant_impl_move_assign&&) = default;

    variant_impl_move_assign& operator=(variant_impl_move_assign&) = default;
    variant_impl_move_assign& operator=(variant_impl_move_assign const&) = default;
    variant_impl_move_assign& operator=(variant_impl_move_assign&&) = delete;

    Variant& operator= (typename variant_type<I, Variant>::type&& t) = delete;
  };
template< typename Variant, typename Next >
  struct variant_impl_move_assign<0ul, Variant, Next, true>
    : variant_impl_cref_assign<0ul, Variant, Next>
  {
    using Base = variant_impl_cref_assign<0ul, Variant, variant_impl<0ul-1, Variant> >;
    using Base::Base;
    using Base::operator=;

    variant_impl_move_assign() = default;
    variant_impl_move_assign(variant_impl_move_assign&) = default;
    variant_impl_move_assign(variant_impl_move_assign const&) = default;
    variant_impl_move_assign(variant_impl_move_assign&&) = default;

    variant_impl_move_assign& operator=(variant_impl_move_assign&) = default;
    variant_impl_move_assign& operator=(variant_impl_move_assign const&) = default;
    variant_impl_move_assign& operator=(variant_impl_move_assign&& other)
#ifndef YAUL_VARIANT_DISABLE_NOEXCEPT_PROPAGATION_IN_MOVE_ASSIGNMENT
     // noexcept(noexcept(Base::assign_variant(variant_index<0ul>(), std::move(other))))
#endif
    {
      (void)other;
      return *this;
      // return Base::assign_variant(variant_index<0ul>(), std::move(other));
    }

    Variant& operator= (typename variant_type<0ul, Variant>::type&& t)
#ifndef YAUL_VARIANT_DISABLE_NOEXCEPT_PROPAGATION_IN_RREF_ASSIGNMENT
        noexcept(noexcept(reinterpret_cast<variant_impl_move_assign*>(0)->assign(variant_index<0ul>(), std::move(t))))
#endif
    {
      assign(variant_index<0ul>(), std::move(t));
      return static_cast<Variant&>(*this);
    }
  };
/** \endcond */

/** // doc: variant_impl {{{
 * \todo Write documentation
 */ // }}}
template<std::size_t I, typename Variant>
  struct variant_impl
    : variant_impl_move_assign<I, Variant, variant_impl<I-1,Variant> >
  {
    using Next = variant_impl<I-1,Variant>;
    using Base = variant_impl_move_assign<I, Variant, Next>;
    using Base::Base;
    using Base::operator=;
    using TI = typename variant_type<I, Variant>::type;

    typedef variant_impl Self;
    static constexpr Self*        that_ = reinterpret_cast<Self*>(0);
    static constexpr const Self* cthat_ = reinterpret_cast<Self*>(0);

    variant_impl() = default;
    variant_impl(variant_impl&) = default;
    variant_impl(variant_impl const&) = default;
    variant_impl(variant_impl&&) = default;

    variant_impl& operator=(variant_impl&) = default;
    variant_impl& operator=(variant_impl const&) = default;
    variant_impl& operator=(variant_impl&&) = default;

    template< typename T = TI
            , typename = typename std::enable_if<
                std::is_constructible<TI, T&>::value
              >::type >
    variant_impl(TI& t)
#ifndef YAUL_VARIANT_DISABLE_NOEXCEPT_PROPAGATION_IN_LREF_CTOR
          noexcept(noexcept(Base(variant_index<I>(), t)))
#endif
      : Base(variant_index<I>(), t)
    { }

    template< typename T = TI
            , typename = typename std::enable_if<
                std::is_constructible<TI, T const&>::value
              >::type >
    variant_impl(TI const& t)
#ifndef YAUL_VARIANT_DISABLE_NOEXCEPT_PROPAGATION_IN_CREF_CTOR
          noexcept(noexcept(Base(variant_index<I>(), t)))
#endif
      : Base(variant_index<I>(), t)
    { }

    template< typename T = TI
            , typename = typename std::enable_if<
                std::is_constructible<TI, T&&>::value
              >::type >
    variant_impl(TI&& t)
#ifndef YAUL_VARIANT_DISABLE_NOEXCEPT_PROPAGATION_IN_RREF_CTOR
          noexcept(noexcept(Base(variant_index<I>(), std::move(t))))
#endif
      : Base(variant_index<I>(), std::move(t))
    { }
#if 0
    template< typename T = TI
            , typename = typename std::enable_if<
                std::is_assignable<TI,T&>::value &&
                std::is_constructible<TI,T&>::value
              >::type
            >
    Variant& operator= (TI& t)
#ifndef YAUL_VARIANT_DISABLE_NOEXCEPT_PROPAGATION_IN_LREF_ASSIGNMENT
        noexcept(noexcept(that_->assign(variant_index<I>(), t)))
#endif
    {
      assign(variant_index<I>(), t);
      return static_cast<Variant&>(*this);
    }

    template< typename T = TI
            , typename = typename std::enable_if<
                std::is_assignable<TI,T const&>::value &&
                std::is_constructible<TI, T const&>::value
              >::type
            >
    Variant& operator= (TI const& t)
#ifndef YAUL_VARIANT_DISABLE_NOEXCEPT_PROPAGATION_IN_CREF_ASSIGNMENT
        noexcept(noexcept(that_->assign(variant_index<I>(), t)))
#endif
    {
      assign(variant_index<I>(), t);
      return static_cast<Variant&>(*this);
    }

    template< typename T = TI
            , typename = typename std::enable_if<
                std::is_assignable<TI,T&&>::value &&
                std::is_constructible<TI,T&&>::value
              >::type
            >
    Variant& operator= (TI&& t)
#ifndef YAUL_VARIANT_DISABLE_NOEXCEPT_PROPAGATION_IN_RREF_ASSIGNMENT
        noexcept(noexcept(that_->assign(variant_index<I>(), std::move(t))))
#endif
    {
      assign(variant_index<I>(), std::move(t));
      return static_cast<Variant&>(*this);
    }
#endif
  };
/** @} */
} } } // end namespace yaul::detail::variant

#endif /* YAUL_VARIANT_DETAIL_VARIANT_IMPL_HPP */
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
