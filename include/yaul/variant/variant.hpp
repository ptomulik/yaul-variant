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

#include <yaul/variant/config.hpp>
#include <yaul/variant/detail/variant_storage.hpp>
#include <yaul/variant/detail/variant_which.hpp>
#include <yaul/variant/detail/variant_impl.hpp>
#include <yaul/variant/detail/storage_ctor.hpp>
#include <yaul/variant/detail/storage_dtor.hpp>
#include <yaul/variant/detail/storage_vtor.hpp>
#include <yaul/variant/detail/storage_assigner.hpp>
#include <yaul/variant/detail/variant_assigner.hpp>
#include <yaul/variant/detail/variant_getter.hpp>
#include <yaul/variant/detail/reflect.hpp>
#include <yaul/variant/detail/relations.hpp>
#include <yaul/variant/apply_visitor.hpp>
#include <yaul/variant/assert.hpp>
#include <yaul/variant/bad_get.hpp>
#include <yaul/variant/variant_find.hpp>
#include <utility>
#include <type_traits>

namespace yaul {
/** \ingroup VariantGroup
 * @{ */
/** // doc: variant {{{
 * \todo Write documentation
 */ // }}}
template<typename T0, typename... Others>
  class variant
  {
  private:
    typedef detail::variant::variant_storage_t<variant> storage_t;
    typedef detail::variant::variant_which_t<variant> which_t;

    // shorthand notation for some visitors...
    typedef detail::variant::make_storage_ctor_t<storage_t, variant> s_ctor_t;
    typedef detail::variant::make_storage_dtor_t<storage_t, variant> s_dtor_t;
    typedef detail::variant::make_storage_assigner_t<storage_t, variant> s_asgn_t;
    typedef detail::variant::make_storage_vtor_t<storage_t, variant> s_vtor_t;
    typedef detail::variant::variant_assigner<variant> v_asgn_t;

  private: // presentation

    which_t which_;
    storage_t storage_;

  private: // helpers, for representation (below)

    void indicate_which(int which_arg) noexcept
    {
      which_ = static_cast<which_t>( which_arg );
    }

    void indicate_backup_which(int which_arg) noexcept
    {
      which_ = static_cast<which_t>( -(which_arg +1) );
    }

  private: // helpers, for queries (below)

    bool using_backup() const noexcept
    {
      return which_ < 0;
    }

  public: // queries

    int which() const noexcept
    {
      // If using heap backup...
      if(using_backup())
        // ... then return adjusted which_:
        return -(which_ + 1);
      // Otherwise, return which_ directly:
      return which_;
    }

    constexpr bool empty() const noexcept
    {
      return false;
    }

    const std::type_info& type() const noexcept
    {
      return apply_visitor(detail::variant::reflect());
    }


  public: // value access

    template< typename U >
    typename std::add_pointer<U>::type
    get_ptr() & noexcept
    {
      using T = typename std::add_pointer<U>::type;
      if(variant_find<U,variant>::value != which())
        return nullptr;
      return apply_visitor(detail::variant::variant_getter<T>());
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
      if(variant_find<U,variant>::value != which())
        return nullptr;
      return apply_visitor(detail::variant::variant_getter<T>());
    }

    template< typename U >
    typename std::add_lvalue_reference<U>::type
    get() &
    {
      using T = typename std::add_lvalue_reference<U>::type;
      if(variant_find<U, variant>::value != which())
        throw yaul::bad_get();
      return apply_visitor(detail::variant::variant_getter<T>());
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
      if(variant_find<U, variant>::value != which())
        throw yaul::bad_get();
      return apply_visitor(detail::variant::variant_getter<T>());
    }

    template< typename U >
    typename std::add_rvalue_reference<U>::type
    get() &&
    {
      using T = typename std::add_rvalue_reference<U>::type;
      if(variant_find<U, variant>::value != which())
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
      if(variant_find<U, variant>::value != which())
        throw yaul::bad_get();
      return std::move(*this).apply_visitor(detail::variant::variant_getter<T>());
    }

  public: // ctors
    variant()
      noexcept(noexcept(s_ctor_t(std::declval<storage_t&>())()))
    {
      indicate_which(s_ctor_t(storage_)());
    }

    template< typename T >
    explicit variant(T&& t)
      noexcept(noexcept(s_ctor_t(std::declval<storage_t&>())(std::forward<T>(t))))
    {
      // T&& is a universal reference
      // https://isocpp.org/blog/2012/11/universal-references-in-c11-scott-meyers
      indicate_which(s_ctor_t(storage_)(std::forward<T>(t)));
    }

    template<typename TT0, typename...  TTs>
    explicit variant(variant<TT0,TTs...>& other)
      noexcept(noexcept(other.apply_visitor(s_ctor_t(std::declval<storage_t&>()))))
    {
      indicate_which(other.apply_visitor(s_ctor_t(storage_)));
    }

    template<typename TT0, typename...  TTs>
    explicit variant(variant<TT0,TTs...> const& other)
      noexcept(noexcept(other.apply_visitor(s_ctor_t(std::declval<storage_t&>()))))
    {
      indicate_which(other.apply_visitor(s_ctor_t(storage_)));
    }

    template<typename TT0, typename...  TTs>
    explicit variant(variant<TT0,TTs...>&& other)
      noexcept(noexcept(std::move(other).apply_visitor(s_ctor_t(std::declval<storage_t&>()))))
    {
      indicate_which(std::move(other).apply_visitor(s_ctor_t(storage_)));
    }

    variant(variant& other)
      noexcept(noexcept(other.apply_visitor(s_ctor_t(std::declval<storage_t&>()))))
    {
      indicate_which(other.apply_visitor(s_ctor_t(storage_)));
    }

    variant(variant const& other)
      noexcept(noexcept(other.apply_visitor(s_ctor_t(std::declval<storage_t&>()))))
    {
      indicate_which(other.apply_visitor(s_ctor_t(storage_)));
    }

    variant(variant&& other)
      noexcept(noexcept(std::move(other).apply_visitor(s_ctor_t(std::declval<storage_t&>()))))
    {
      indicate_which(std::move(other).apply_visitor(s_ctor_t(storage_)));
    }

  public: // dtor
    ~variant()
      noexcept(noexcept(s_dtor_t(std::declval<storage_t&>(), int())()))
    {
      s_dtor_t(storage_, which())();
    }

  public: // assignment

    template< typename T >
    variant& operator=(T&& t)
        noexcept( noexcept(s_ctor_t(std::declval<storage_t&>())(std::declval<T&&>())) &&
                  noexcept(s_asgn_t(std::declval<storage_t&>())(std::forward<T>(t))) )
    {
      if(s_asgn_t(storage_).which(std::forward<T>(t)) == which())
        indicate_which(s_asgn_t(storage_)(std::forward<T>(t)));
      else
        {
          s_dtor_t(storage_, which())();
          indicate_which(s_ctor_t(storage_)(std::forward<T>(t)));
        }
      return *this;
    }

    template<typename TT0, typename... TTs>
    variant& operator=(variant<TT0,TTs...>& other)
      noexcept(noexcept(other.apply_visitor(v_asgn_t(std::declval<variant&>()))))
    {
      other.apply_visitor(v_asgn_t(*this));
      return *this;
    }

    template<typename TT0, typename... TTs>
    variant& operator=(variant<TT0,TTs...> const& other)
      noexcept(noexcept(other.apply_visitor(v_asgn_t(std::declval<variant&>()))))
    {
      other.apply_visitor(v_asgn_t(*this));
      return *this;
    }

    template<typename TT0, typename... TTs>
    variant& operator=(variant<TT0,TTs...>&& other)
      noexcept(noexcept(std::move(other).apply_visitor(v_asgn_t(std::declval<variant&>()))))
    {
      std::move(other).apply_visitor(v_asgn_t(*this));
      return *this;
    }

    variant& operator=(variant& other)
        noexcept( noexcept(std::declval<variant&>().apply_visitor(s_ctor_t(std::declval<storage_t&>()))) &&
                  noexcept(other.apply_visitor(s_asgn_t(std::declval<storage_t&>()))) )
    {
      if(which() == other.which())
        indicate_which(other.apply_visitor(s_asgn_t(storage_)));
      else
        {
          s_dtor_t(storage_, which())();
          indicate_which(other.apply_visitor(s_ctor_t(storage_)));
        }
      return *this;
    }

    variant& operator=(variant const& other)
        noexcept( noexcept(std::declval<variant const&>().apply_visitor(s_ctor_t(std::declval<storage_t&>()))) &&
                  noexcept(other.apply_visitor(s_asgn_t(std::declval<storage_t&>()))) )
    {
      if(which() == other.which())
        indicate_which(other.apply_visitor(s_asgn_t(storage_)));
      else
        {
          s_dtor_t(storage_, which())();
          indicate_which(other.apply_visitor(s_ctor_t(storage_)));
        }
      return *this;
    }

    variant& operator=(variant&& other)
        noexcept( noexcept(std::declval<variant&&>().apply_visitor(s_ctor_t(std::declval<storage_t&>()))) &&
                  noexcept(std::move(other).apply_visitor(s_asgn_t(std::declval<storage_t&>()))) )
    {
      if(which() == std::move(other).which())
        indicate_which(std::move(other).apply_visitor(s_asgn_t(storage_)));
      else
        {
          s_dtor_t(storage_, which())();
          indicate_which(std::move(other).apply_visitor(s_ctor_t(storage_)));
        }
      return *this;
    }


  public: // visitation
    template<typename Visitor>
    typename std::remove_reference<Visitor>::type::result_type // FIXME: elaborate
    apply_visitor(Visitor&& v) &
        noexcept(noexcept(s_vtor_t(int())( std::declval<storage_t&>(), std::forward<Visitor>(v) )))
    {
      YAUL_VARIANT_ASSERT((0 <= which()) && (static_cast<std::size_t>(which()) < (1ul + sizeof...(Others))));
      return s_vtor_t(which())(storage_, std::forward<Visitor>(v));
    }

    template<typename Visitor>
    typename std::remove_reference<Visitor>::type::result_type // FIXME: elaborate
    apply_visitor(Visitor&& v) const &
        noexcept( noexcept(s_vtor_t(int())(std::declval<storage_t const&>(), std::forward<Visitor>(v))) )
    {
      YAUL_VARIANT_ASSERT((0 <= which()) && (static_cast<std::size_t>(which()) < (1ul + sizeof...(Others))));
      return s_vtor_t(which())(storage_, std::forward<Visitor>(v));
    }

    template<typename Visitor>
    typename std::remove_reference<Visitor>::type::result_type // FIXME: elaborate
    apply_visitor(Visitor&& v) &&
        noexcept( noexcept(s_vtor_t(int())(std::declval<storage_t&&>(), std::forward<Visitor>(v))) )
    {
      YAUL_VARIANT_ASSERT((0 <= which()) && (static_cast<std::size_t>(which()) < (1ul + sizeof...(Others))));
      return s_vtor_t(which())(std::move(*this).storage_, std::forward<Visitor>(v));
    }

    template<typename Visitor>
    typename std::remove_reference<Visitor>::type::result_type // FIXME: elaborate
    apply_visitor(Visitor&& v) const&&
        noexcept( noexcept(s_vtor_t(int())(std::declval<storage_t const&&>(), std::forward<Visitor>(v))) )
    {
      YAUL_VARIANT_ASSERT((0 <= which()) && (static_cast<std::size_t>(which()) < (1ul + sizeof...(Others))));
      return s_vtor_t(which())(std::move(*this).storage_, std::forward<Visitor>(v));
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
