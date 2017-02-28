// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

// yaul/variant/detail/variant_base.hpp

/** // doc: yaul/variant/detail/variant_base.hpp {{{
 * \file yaul/variant/detail/variant_base.hpp
 * \todo Write documentation
 */ // }}}
#ifndef YAUL_VARIANT_DETAIL_VARIANT_BASE_HPP
#define YAUL_VARIANT_DETAIL_VARIANT_BASE_HPP

#include <yaul/variant/variant_fwd.hpp>
#include <yaul/variant/detail/variant_base_fwd.hpp>
#include <yaul/variant/detail/all_trivially_destructible.hpp>
#include <yaul/variant/detail/variant_storage.hpp>
#include <yaul/variant/detail/variant_which.hpp>
#include <yaul/variant/detail/storage_ctor.hpp>
#include <yaul/variant/detail/storage_dtor.hpp>
#include <yaul/variant/detail/storage_vtor.hpp>
#include <yaul/variant/detail/storage_assigner.hpp>
#include <yaul/variant/detail/reflect.hpp>
#include <yaul/variant/variant_size.hpp>
#include <yaul/variant/assert.hpp>
#include <utility>
#include <typeinfo>
#include <type_traits>

namespace yaul { namespace detail { namespace variant {
struct invoked_advertently_t {};
} } } // end namespace yaul::detail::variant

namespace yaul { namespace detail { namespace variant {
/** // doc: variant_base {{{
 * \todo Write documentation
 */ // }}}
template< typename Variant, bool TrivialDtor = all_trivially_destructible<Variant>::value >
  class variant_base
  {
  private:

    using Storage = variant_storage_t<Variant>;
    using which_t = variant_which_t<Variant>;
    using StorageCtor = make_storage_ctor_t<Storage, Variant>;
    using StorageDtor = make_storage_dtor_t<Storage, Variant>;
    using StorageAssigner = make_storage_assigner_t<Storage, Variant>;
    using StorageVisitor = make_storage_vtor_t<Storage, Variant>;

  private:
    which_t which_;
    Storage storage_;

  protected:
    void destroy_storage()
      noexcept(noexcept(StorageDtor(std::declval<Storage&>(), int())()))
    {
      StorageDtor(storage_, which())();
    }

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

  public:
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
      return apply_visitor(reflect());
    }

  public: // ctors
    // FIXME: SFINAE-out default constructor when necessary
    variant_base()
      noexcept(noexcept(StorageCtor(std::declval<Storage&>())()))
    {
      indicate_which(StorageCtor(storage_)());
    }

    template< typename T >
    explicit variant_base(invoked_advertently_t,T&& t)
      noexcept(noexcept(StorageCtor(std::declval<Storage&>())(std::forward<T>(t))))
    {
      // T&& is a universal reference
      // https://isocpp.org/blog/2012/11/universal-references-in-c11-scott-meyers
      indicate_which(StorageCtor(storage_)(std::forward<T>(t)));
    }

    template<typename TT0, typename...  TTs>
    explicit variant_base(yaul::variant<TT0,TTs...>& other)
      noexcept(noexcept(other.apply_visitor(StorageCtor(std::declval<Storage&>()))))
    {
      indicate_which(other.apply_visitor(StorageCtor(storage_)));
    }

    template<typename TT0, typename...  TTs>
    explicit variant_base(yaul::variant<TT0,TTs...> const& other)
      noexcept(noexcept(other.apply_visitor(StorageCtor(std::declval<Storage&>()))))
    {
      indicate_which(other.apply_visitor(StorageCtor(storage_)));
    }

    template<typename TT0, typename...  TTs>
    explicit variant_base(yaul::variant<TT0,TTs...>&& other)
      noexcept(noexcept(std::move(other).apply_visitor(StorageCtor(std::declval<Storage&>()))))
    {
      indicate_which(std::move(other).apply_visitor(StorageCtor(storage_)));
    }

    variant_base(Variant& other)
      noexcept(noexcept(other.apply_visitor(StorageCtor(std::declval<Storage&>()))))
    {
      indicate_which(other.apply_visitor(StorageCtor(storage_)));
    }

    variant_base(Variant const& other)
      noexcept(noexcept(other.apply_visitor(StorageCtor(std::declval<Storage&>()))))
    {
      indicate_which(other.apply_visitor(StorageCtor(storage_)));
    }

    variant_base(Variant&& other)
      noexcept(noexcept(std::move(other).apply_visitor(StorageCtor(std::declval<Storage&>()))))
    {
      indicate_which(std::move(other).apply_visitor(StorageCtor(storage_)));
    }

  public: // visitation
    template<typename Visitor>
    typename std::remove_reference<Visitor>::type::result_type // FIXME: elaborate
    apply_visitor(Visitor&& v) &
        noexcept(noexcept(StorageVisitor(int())( std::declval<Storage&>(), std::forward<Visitor>(v) )))
    {
      YAUL_VARIANT_ASSERT((0 <= which()));
      YAUL_VARIANT_ASSERT((static_cast<std::size_t>(which()) < yaul::variant_size<Variant>::value));
      return StorageVisitor(which())(storage_, std::forward<Visitor>(v));
    }

    template<typename Visitor>
    typename std::remove_reference<Visitor>::type::result_type // FIXME: elaborate
    apply_visitor(Visitor&& v) const &
        noexcept( noexcept(StorageVisitor(int())(std::declval<Storage const&>(), std::forward<Visitor>(v))) )
    {
      YAUL_VARIANT_ASSERT((0 <= which()));
      YAUL_VARIANT_ASSERT((static_cast<std::size_t>(which()) < yaul::variant_size<Variant>::value));
      return StorageVisitor(which())(storage_, std::forward<Visitor>(v));
    }

    template<typename Visitor>
    typename std::remove_reference<Visitor>::type::result_type // FIXME: elaborate
    apply_visitor(Visitor&& v) &&
        noexcept( noexcept(StorageVisitor(int())(std::declval<Storage&&>(), std::forward<Visitor>(v))) )
    {
      YAUL_VARIANT_ASSERT((0 <= which()));
      YAUL_VARIANT_ASSERT((static_cast<std::size_t>(which()) < yaul::variant_size<Variant>::value));
      return StorageVisitor(which())(std::move(*this).storage_, std::forward<Visitor>(v));
    }

    template<typename Visitor>
    typename std::remove_reference<Visitor>::type::result_type // FIXME: elaborate
    apply_visitor(Visitor&& v) const&&
        noexcept( noexcept(StorageVisitor(int())(std::declval<Storage const&&>(), std::forward<Visitor>(v))) )
    {
      YAUL_VARIANT_ASSERT((0 <= which()));
      YAUL_VARIANT_ASSERT((static_cast<std::size_t>(which()) < yaul::variant_size<Variant>::value));
      return StorageVisitor(which())(std::move(*this).storage_, std::forward<Visitor>(v));
    }

  protected: //assignment
    template< typename T >
    void assign(T&& t)
        noexcept( noexcept(StorageCtor(std::declval<Storage&>())(std::declval<T&&>())) &&
                  noexcept(StorageAssigner(std::declval<Storage&>())(std::forward<T>(t))) )
    {
      if(StorageAssigner(storage_).which(std::forward<T>(t)) == which())
        indicate_which(StorageAssigner(storage_)(std::forward<T>(t)));
      else
        {
          StorageDtor(storage_, which())();
          indicate_which(StorageCtor(storage_)(std::forward<T>(t)));
        }
    }

    void assign(variant_base& other)
        noexcept( noexcept(std::declval<variant_base&>().apply_visitor(StorageCtor(std::declval<Storage&>()))) &&
                  noexcept(other.apply_visitor(StorageAssigner(std::declval<Storage&>()))) )
    {
      if(which() == other.which())
        indicate_which(other.apply_visitor(StorageAssigner(storage_)));
      else
        {
          StorageDtor(storage_, which())();
          indicate_which(other.apply_visitor(StorageCtor(storage_)));
        }
    }

    void assign(variant_base const& other)
        noexcept( noexcept(std::declval<variant_base const&>().apply_visitor(StorageCtor(std::declval<Storage&>()))) &&
                  noexcept(other.apply_visitor(StorageAssigner(std::declval<Storage&>()))) )
    {
      if(which() == other.which())
        indicate_which(other.apply_visitor(StorageAssigner(storage_)));
      else
        {
          StorageDtor(storage_, which())();
          indicate_which(other.apply_visitor(StorageCtor(storage_)));
        }
    }

    void assign(variant_base&& other)
        noexcept( noexcept(std::declval<variant_base&&>().apply_visitor(StorageCtor(std::declval<Storage&>()))) &&
                  noexcept(std::move(other).apply_visitor(StorageAssigner(std::declval<Storage&>()))) )
    {
      if(which() == std::move(other).which())
        indicate_which(std::move(other).apply_visitor(StorageAssigner(storage_)));
      else
        {
          StorageDtor(storage_, which())();
          indicate_which(std::move(other).apply_visitor(StorageCtor(storage_)));
        }
    }
  };

template< typename Variant>
  class variant_base<Variant, false>
    : public variant_base<Variant, true>
  {
  private:
    using Base = variant_base<Variant, true>;

  public: // ctors
    using Base::Base;

  public: // dtor

    ~variant_base()
      noexcept(noexcept(std::declval<variant_base&>().destroy_storage()))
    {
      this->destroy_storage();
    }
  };

} } } // end namespace yaul::detail::variant

#endif /* YAUL_VARIANT_DETAIL_VARIANT_BASE_HPP */
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
