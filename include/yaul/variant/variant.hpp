// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

// yaul/variant/variant.hpp

/** // doc: yaul/variant/variant.hpp {{{
 * \file yaul/variant/variant.hpp
 * \todo Write documentation
 */ // }}}
#ifndef YAUL_VARIANT_VARIANT_HPP
#define YAUL_VARIANT_VARIANT_HPP

#include <yaul/variant/detail/variant_base.hpp>
#include <yaul/variant/config.hpp>
#include <yaul/variant/detail/variant_assigner.hpp>
#include <yaul/variant/detail/variant_getter.hpp>
#include <yaul/variant/detail/relations.hpp>
#include <yaul/variant/apply_visitor.hpp>
#include <yaul/variant/bad_get.hpp>
#include <yaul/variant/detail/find.hpp>
#include <utility>
#include <type_traits>

namespace yaul {
/** \ingroup group-variant
 * @{ */
/** // doc: variant {{{
 * \todo Write documentation
 */ // }}}
template<typename T0, typename... Others>
  class variant
    : public detail::variant::variant_base<variant<T0,Others...> >
  {
  private:
    using Base = detail::variant::variant_base<variant<T0,Others...> >;
    using invoked_advertently_t = detail::variant::invoked_advertently_t;
    typedef detail::variant::variant_assigner<variant> Assigner;
  public: // ctors
    // FIXME: SFINAE-out default constructor when necessary
    variant()
      noexcept(noexcept(Base()))
      : Base()
    { }

    template< typename T >
    explicit variant(T&& t)
      noexcept( noexcept(Base(invoked_advertently_t(),std::forward<T>(t))) )
      : Base(invoked_advertently_t(),std::forward<T>(t))
    {
      // T&& is a universal reference
      // https://isocpp.org/blog/2012/11/universal-references-in-c11-scott-meyers
    }

    template<typename TT0, typename...  TTs>
    explicit variant(variant<TT0,TTs...>& other)
      noexcept( noexcept(Base(other)) )
      : Base(other)
    { }

    template<typename TT0, typename...  TTs>
    explicit variant(variant<TT0,TTs...> const& other)
      noexcept( noexcept(Base(other)) )
      : Base(other)
    { }

    template<typename TT0, typename...  TTs>
    explicit variant(variant<TT0,TTs...>&& other)
      noexcept( noexcept(Base(std::move(other))) )
      : Base(std::move(other))
    { }

    variant(variant& other)
      noexcept( noexcept(Base(other)) )
      : Base(other)
    { }

    variant(variant const& other)
      noexcept( noexcept(Base(other)) )
      : Base(other)
    { }

    variant(variant&& other)
      noexcept( noexcept(Base(std::move(other))) )
      : Base(std::move(other))
    { }

  private:
    //using Base::which;
    using Base::assign; // FIXME: this is required only for some noexcepts below
    //using Base::apply_visitor;

  public: // value access

    template< typename U >
    typename std::add_pointer<U>::type
    get_ptr() & noexcept
    {
      using T = typename std::add_pointer<U>::type;
      if(detail::variant::find<U,variant>::value != this->which())
        return nullptr;
      return this->apply_visitor(detail::variant::variant_getter<T>());
    }

    template< typename U >
    typename std::add_pointer<
      typename std::add_const<U>::type
    >::type
    get_ptr() const& noexcept
    {
      using T = typename std::add_pointer<
        typename std::add_const<U>::type
      >::type;
      if(detail::variant::find<U,variant>::value != this->which())
        return nullptr;
      return this->apply_visitor(detail::variant::variant_getter<T>());
    }

    template< typename U >
    typename std::add_lvalue_reference<U>::type
    get() &
    {
      using T = typename std::add_lvalue_reference<U>::type;
      if(detail::variant::find<U, variant>::value != this->which())
        throw yaul::bad_get();
      return this->apply_visitor(detail::variant::variant_getter<T>());
    }

    template< typename U >
    typename std::add_lvalue_reference<
      typename std::add_const<U>::type
    >::type&
    get() const&
    {
      using T = typename std::add_lvalue_reference<
        typename std::add_const<U>::type
      >::type;
      if(detail::variant::find<U, variant>::value != this->which())
        throw yaul::bad_get();
      return this->apply_visitor(detail::variant::variant_getter<T>());
    }

    template< typename U >
    typename std::add_rvalue_reference<U>::type
    get() &&
    {
      using T = typename std::add_rvalue_reference<U>::type;
      if(detail::variant::find<U, variant>::value != this->which())
        throw yaul::bad_get();
      return std::move(*this).apply_visitor(detail::variant::variant_getter<T>());
    }

    template< typename U >
    typename std::add_rvalue_reference<
      typename std::add_const<U>::type
    >::type
    get() const &&
    {
      using T = typename std::add_rvalue_reference<
        typename std::add_const<U>::type
      >::type;
      if(detail::variant::find<U, variant>::value != this->which())
        throw yaul::bad_get();
      return std::move(*this).apply_visitor(detail::variant::variant_getter<T>());
    }

  protected: // assignment (private API methods)

    template<typename TT0, typename... TTs>
    void assign(variant<TT0,TTs...>& other)
      noexcept(noexcept(other.apply_visitor(Assigner(std::declval<variant&>()))))
    {
      other.apply_visitor(Assigner(*this));
    }

    template<typename TT0, typename... TTs>
    void assign(variant<TT0,TTs...> const& other)
      noexcept(noexcept(other.apply_visitor(Assigner(std::declval<variant&>()))))
    {
      other.apply_visitor(Assigner(*this));
    }

    template<typename TT0, typename... TTs>
    void assign(variant<TT0,TTs...>&& other)
      noexcept(noexcept(std::move(other).apply_visitor(Assigner(std::declval<variant&>()))))
    {
      std::move(other).apply_visitor(Assigner(*this));
    }

  public: // assignment

    template< typename T >
    variant& operator=(T&& t)
        noexcept( noexcept(std::declval<variant&>().assign(std::forward<T>(t))) )
    {
      this->assign(std::forward<T>(t));
      return *this;
    }

    template<typename TT0, typename... TTs>
    variant& operator=(variant<TT0,TTs...>& other)
      noexcept( noexcept(std::declval<variant&>().assign(other)) )
    {
      this->assign(other);
      return *this;
    }

    template<typename TT0, typename... TTs>
    variant& operator=(variant<TT0,TTs...> const& other)
      noexcept( noexcept(std::declval<variant&>().assign(other)) )
    {
      this->assign(other);
      return *this;
    }

    template<typename TT0, typename... TTs>
    variant& operator=(variant<TT0,TTs...>&& other)
        noexcept( noexcept(std::declval<variant&>().assign(std::forward<variant<TT0,TTs...> >(other))) )
    {
      this->assign(std::forward<variant<TT0,TTs...> >(other));
      return *this;
    }

    variant& operator=(variant& other)
        noexcept( noexcept(std::declval<variant&>().assign(other)) )
    {
      this->assign(other);
      return *this;
    }

    variant& operator=(variant const& other)
        noexcept( noexcept(std::declval<variant&>().assign(other)) )
    {
      this->assign(other);
      return *this;
    }

    variant& operator=(variant&& other)
        noexcept( noexcept(std::declval<variant&>().assign(std::move(other))) )
    {
      this->assign(std::move(other));
      return *this;
    }

  public: // relational
    /** // doc: operator== {{{
     * \todo Write documentation
     */ // }}}
    bool operator==(const variant& rhs) const
      noexcept(noexcept(yaul::apply_visitor(detail::variant::eq_comp(), std::declval<variant const&>(), rhs)))
    {
      if(this->which() != rhs.which())
        return false;

      return yaul::apply_visitor(detail::variant::eq_comp(), *this, rhs);
    }
    /** // doc: operator!= {{{
     * \todo Write documentation
     */ // }}}
    bool operator!=(const variant& rhs) const
      noexcept(noexcept(yaul::apply_visitor(detail::variant::neq_comp(), std::declval<variant const&>(), rhs)))
    {
      if(this->which() != rhs.which())
        return true;

      return yaul::apply_visitor(detail::variant::neq_comp(), *this, rhs);
    }
    /** // doc: operator< {{{
     * \todo Write documentation
     */ // }}}
    bool operator<(const variant& rhs) const
      noexcept(noexcept(yaul::apply_visitor(detail::variant::lt_comp(), std::declval<variant const&>(), rhs)))
    {
      if(this->which() != rhs.which())
        return this->which() < rhs.which();

      return yaul::apply_visitor(detail::variant::lt_comp(), *this, rhs);
    }
    /** // doc: operator> {{{
     * \todo Write documentation
     */ // }}}
    bool operator>(const variant& rhs) const
      noexcept(noexcept(yaul::apply_visitor(detail::variant::gt_comp(), std::declval<variant const&>(), rhs)))
    {
      if(this->which() != rhs.which())
        return this->which() > rhs.which();

      return yaul::apply_visitor(detail::variant::gt_comp(), *this, rhs);
    }
    /** // doc: operator<= {{{
     * \todo Write documentation
     */ // }}}
    bool operator<=(const variant& rhs) const
      noexcept(noexcept(yaul::apply_visitor(detail::variant::le_comp(), std::declval<variant const&>(), rhs)))
    {
      if(this->which() != rhs.which())
        return this->which() <= rhs.which();

      return yaul::apply_visitor(detail::variant::le_comp(), *this, rhs);
    }
    /** // doc: operator>= {{{
     * \todo Write documentation
     */ // }}}
    bool operator>=(const variant& rhs) const
      noexcept(noexcept(yaul::apply_visitor(detail::variant::ge_comp(), std::declval<variant const&>(), rhs)))
    {
      if(this->which() != rhs.which())
        return this->which() >= rhs.which();

      return yaul::apply_visitor(detail::variant::ge_comp(), *this, rhs);
    }
  };

#if 0
/** // doc: make_variant_over {{{
 * \todo Write documentation
 */ // }}}
template<typename Sequence>
class make_variant_over
{
  // TODO: implement
};
#endif
#if 0
/** // doc: swap() {{{
 * \todo Write documentation
 */ // }}}
template<typename... Types>
void swap(variant<Types...>&, variant<Types...>&)
{
  // TODO: implement
}
#endif
#if 0
// XXX: shouldn't this be moved to a separate header?
template<typename CharT, typename Traits, typename... Types>
std::basic_ostream<CharT,Traits>&
operator<<(std::basic_ostream<CharT,Traits>&, const variant<Types...>&)
{
  // TODO: implement
}
#endif
#if 0
/** // doc: hash_value() {{{
 * \todo Write documentation
 */ // }}}
template<typename... Types>
std::size_t hash_value(const variant<Types...>&)
{
  // TODO: implement
}
#endif
/** @} */
} // end namespace yaul

#endif /* YAUL_VARIANT_VARIANT_HPP */
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
