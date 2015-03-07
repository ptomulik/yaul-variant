// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

// yaul/variant/detail/variant_impl_core.hpp

/** // doc: yaul/variant/detail/variant_impl_core.hpp {{{
 * \file yaul/variant/detail/variant_impl_core.hpp
 * \todo Write documentation
 */ // }}}
#ifndef YAUL_VARIANT_DETAIL_VARIANT_IMPL_CORE_HPP
#define YAUL_VARIANT_DETAIL_VARIANT_IMPL_CORE_HPP

#include <yaul/variant/config.hpp>
#include <yaul/variant/assert.hpp>
#include <yaul/variant/detail/variant_storage.hpp>
#include <yaul/variant/detail/variant_index.hpp>
#include <yaul/variant/detail/initializer_visitor.hpp>
#include <yaul/variant/detail/destructor_visitor.hpp>
#include <yaul/variant/variant_type.hpp>
#include <yaul/variant/variant_size.hpp>
#include <yaul/variant/variant_find.hpp>
#include <yaul/variant/bad_visit.hpp>
#include <type_traits>
#include <utility>
#include <cstddef>

namespace yaul { namespace detail { namespace variant {
/** \ingroup FixMe FIXME:
 * @{ */
/** // doc: variant_impl_core {{{
 * \todo Write documentation
 */ // }}}
template<std::size_t I, typename Variant, typename Next>
struct variant_impl_core
  : Next
{
  using Base = Next;
  using Base::Base;
  using Base::operator=;
  variant_impl_core() = default;
  variant_impl_core(variant_impl_core&) = default;
  variant_impl_core(variant_impl_core const&) = default;
  variant_impl_core(variant_impl_core&&) = default;
};
/** \cond DOXYGEN_SHOW_TEMPLATE_SPECIALIZATIONS */
template<typename Variant, typename Next>
struct variant_impl_core<0ul, Variant, Next>
{
private:
  typedef variant_impl_core Self;
  static constexpr Self*        that_ = reinterpret_cast<Self*>(0);
  static constexpr const Self* cthat_ = reinterpret_cast<Self*>(0);

  template<std::size_t I>
  using var_t = typename variant_type<I, Variant>::type;

  template<std::size_t I>
  using cvar_t = typename std::add_const<var_t<I> >::type;

  template<typename T>
  using raw_t = typename std::remove_cv<typename std::remove_reference<T>::type>::type;

  typedef typename variant_storage<Variant>::type Storage;
  typedef int Which;
  static constexpr Which size_ = variant_size<Variant>::value;
  using top_index_t = variant_index<size_-1ul>;
  Storage storage_;
  Which which_;

private:
  using Initializer = initializer_visitor<Self>;
  using Destructor = destructor_visitor<Self>;
  friend Initializer;

public: // constructor/destructor

  typedef Storage storage_type;
  typedef Which which_type;

  variant_impl_core() = delete;
  variant_impl_core(variant_impl_core&) = delete;
  variant_impl_core(variant_impl_core const&) = delete;
  variant_impl_core(variant_impl_core&&) = delete;

  template<std::size_t I>
  variant_impl_core(variant_index<I>)
#ifndef YAUL_VARIANT_DISABLE_NOEXCEPT_PROPAGATION_IN_DFLT_CTOR
    noexcept(noexcept(typename variant_type<I,Variant>::type()))
#endif
  {
    using TI = var_t<I>;
    new (&storage_) TI();
    which_ = I;
  }

  template<std::size_t I>
  variant_impl_core(variant_index<I>, variant_impl_core& other)
#ifndef YAUL_VARIANT_DISABLE_NOEXCEPT_PROPAGATION_IN_COPY_CTOR
    noexcept(noexcept(other.apply_visitor(Initializer(*that_))))
#endif
  {
    other.apply_visitor(Initializer(*this));
  }

  template<std::size_t I>
  variant_impl_core(variant_index<I>, const variant_impl_core& other)
#ifndef YAUL_VARIANT_DISABLE_NOEXCEPT_PROPAGATION_IN_COPY_CTOR
    noexcept(noexcept(other.apply_visitor(Initializer(*that_))))
#endif
  {
    other.apply_visitor(Initializer(*this));
  }

  template<std::size_t I>
  variant_impl_core(variant_index<I>, variant_impl_core&& other)
#ifndef YAUL_VARIANT_DISABLE_NOEXCEPT_PROPAGATION_IN_MOVE_CTOR
    noexcept(noexcept(std::move(other).apply_visitor(Initializer(*that_))))
#endif
  {
    std::move(other).apply_visitor(Initializer(*this));
  }

  template<std::size_t I>
  variant_impl_core(variant_index<I>, var_t<I>& t)
#ifndef YAUL_VARIANT_DISABLE_NOEXCEPT_PROPAGATION_IN_LREF_CTOR
    noexcept(noexcept(var_t<I>(t)))
#endif
  {
    using TI = var_t<I>;
    new (&storage_) TI(t);
    which_ = I;
  }

  template<std::size_t I>
  variant_impl_core(variant_index<I>, var_t<I> const& t)
#ifndef YAUL_VARIANT_DISABLE_NOEXCEPT_PROPAGATION_IN_CREF_CTOR
    noexcept(noexcept(var_t<I>(t)))
#endif
  {
    using TI = var_t<I>;
    new (&storage_) TI(t);
    which_ = I;
  }

  template<std::size_t I>
  variant_impl_core(variant_index<I>, var_t<I>&& t)
#ifndef YAUL_VARIANT_DISABLE_NOEXCEPT_PROPAGATION_IN_RREF_CTOR
    noexcept(noexcept(var_t<I>(std::move(t))))
#endif
  {
    using TI = var_t<I>;
    new (&storage_) TI(std::move(t));
    which_ = I;
  }

  ~variant_impl_core() noexcept
  {
    destruct_();
  }

  int which() const noexcept  { return static_cast<int>(which_); }
  bool empty() const noexcept { return false; }

public: // assignment
  template<std::size_t I>
  void assign(variant_index<I>, var_t<I>& t)
#ifndef YAUL_VARIANT_DISABLE_NOEXCEPT_PROPAGATION_IN_LREF_ASSIGNMENT
    noexcept(
      noexcept(*reinterpret_cast<var_t<I>*>(&that_->storage_) = t) &&
      noexcept(that_->initialize_(t))
    )
#endif
  {
    if(which() == I)
      {
        *reinterpret_cast<var_t<I>*>(&storage_) = t;
      }
    else
      {
        destruct_();
        initialize_(t);
      }
  }
  template<std::size_t I>
  void assign(variant_index<I>, const var_t<I>& t)
#ifndef YAUL_VARIANT_DISABLE_NOEXCEPT_PROPAGATION_IN_CREF_ASSIGNMENT
    noexcept(
      noexcept(*reinterpret_cast<var_t<I>*>(&that_->storage_) = t) &&
      noexcept(that_->initialize_(t))
    )
#endif
  {
    if(which() == I)
      {
        *reinterpret_cast<var_t<I>*>(&storage_) = t;
      }
    else
      {
        destruct_();
        initialize_(t);
      }
  }
  template<std::size_t I>
  void assign(variant_index<I>, var_t<I>&& t)
#ifndef YAUL_VARIANT_DISABLE_NOEXCEPT_PROPAGATION_IN_RREF_ASSIGNMENT
    noexcept(
      noexcept(*reinterpret_cast<var_t<I>*>(&that_->storage_) = std::move(t)) &&
      noexcept(that_->initialize_(std::move(t)))
    )
#endif
  {
    if(which() == I)
      {
        *reinterpret_cast<var_t<I>*>(&storage_) = std::move(t);
      }
    else
      {
        destruct_();
        initialize_(std::move(t));
      }
  }

public: // visitation

  template<typename Visitor>
  typename std::remove_reference<Visitor>::type::result_type // FIXME: elaborate
  apply_visitor(Visitor&& v) &
#ifndef YAUL_VARIANT_DISABLE_NOEXCEPT_PROPAGATION_IN_APPLY_VISITOR
      noexcept(noexcept(that_->visit_impl_(top_index_t(), std::forward<Visitor>(v))))
#endif
  {
    YAUL_VARIANT_ASSERT((0 <= which()) && (which() < size_));
    return visit_impl_(top_index_t(), std::forward<Visitor>(v));
  }

  template<typename Visitor>
  typename std::remove_reference<Visitor>::type::result_type // FIXME: elaborate
  apply_visitor(Visitor&& v) const &
#ifndef YAUL_VARIANT_DISABLE_NOEXCEPT_PROPAGATION_IN_APPLY_VISITOR
      noexcept(noexcept(cthat_->visit_impl_(top_index_t(), std::forward<Visitor>(v))))
#endif
  {
    YAUL_VARIANT_ASSERT((0 <= which()) && (which() < size_));
    return visit_impl_(top_index_t(), std::forward<Visitor>(v));
  }

  template<typename Visitor>
  typename std::remove_reference<Visitor>::type::result_type // FIXME: elaborate
  apply_visitor(Visitor&& v) &&
#ifndef YAUL_VARIANT_DISABLE_NOEXCEPT_PROPAGATION_IN_APPLY_VISITOR
      noexcept(noexcept(std::move(*that_).visit_impl_(top_index_t(), std::forward<Visitor>(v))))
#endif
  {
    YAUL_VARIANT_ASSERT((0 <= which()) && (which() < size_));
    return std::move(*this).visit_impl_(top_index_t(), std::forward<Visitor>(v));
  }
private: // visitation
  ///////////////////////////////////////////////////////////////////////////
  // The following two methods dispatch visitation to appropriate overloaded
  // version of the visitor provided. This works similar to a
  //  switch(which())
  //    {
  //      case 0:
  //        return v(*reinterpret_cast<var_t<0>*>(&storage_));
  //      case 1:
  //        return v(*reinterpret_cast<var_t<1>*>(&storage_));
  //      ...
  //      default:
  //        throw bad_visit();
  //    }
  // but is implemented with templates and method overloading.
  ///////////////////////////////////////////////////////////////////////////
  template<std::size_t I, typename Visitor>
  typename std::remove_reference<Visitor>::type::result_type // FIXME: elaborate
  visit_impl_(variant_index<I>, Visitor&& v) &
#ifndef YAUL_VARIANT_DISABLE_NOEXCEPT_PROPAGATION_IN_APPLY_VISITOR
    noexcept(noexcept(std::forward<Visitor>(v)(*reinterpret_cast<var_t<I>*>(&that_->storage_))) &&
             noexcept(that_->visit_impl_(variant_index<I-1>(), std::forward<Visitor>(v))))
#endif
  {
    if(which() == I)
      return std::forward<Visitor>(v)(*reinterpret_cast<var_t<I>*>(&storage_));
    else
      return visit_impl_(variant_index<I-1>(), std::forward<Visitor>(v));
  }
  template<typename Visitor>
  typename std::remove_reference<Visitor>::type::result_type // FIXME: elaborate
  visit_impl_(variant_index<0ul>, Visitor&& v) &
#ifndef YAUL_VARIANT_DISABLE_NOEXCEPT_PROPAGATION_IN_APPLY_VISITOR
    noexcept(noexcept(std::forward<Visitor>(v)(*reinterpret_cast<var_t<0ul>*>(&that_->storage_))))
#endif
  {
    YAUL_VARIANT_ASSERT(which() == 0);
    return std::forward<Visitor>(v)(*reinterpret_cast<var_t<0ul>*>(&storage_));
  }

  ///////////////////////////////////////////////////////////////////////////
  // Same as above, but for const *this
  ///////////////////////////////////////////////////////////////////////////
  template<std::size_t I, typename Visitor>
  typename std::remove_reference<Visitor>::type::result_type // FIXME: elaborate
  visit_impl_(variant_index<I>, Visitor&& v) const &
#ifndef YAUL_VARIANT_DISABLE_NOEXCEPT_PROPAGATION_IN_APPLY_VISITOR
    noexcept(noexcept(std::forward<Visitor>(v)(*reinterpret_cast<cvar_t<I>*>(&cthat_->storage_))) &&
             noexcept(cthat_->visit_impl_(variant_index<I-1>(), std::forward<Visitor>(v))))
#endif
  {
    // note: noexcept would make no sense, because bad_visit may be thrown...
    if(which() == I)
      return std::forward<Visitor>(v)(*reinterpret_cast<cvar_t<I>*>(&storage_));
    else
      return visit_impl_(variant_index<I-1>(), std::forward<Visitor>(v));
  }
  template<typename Visitor>
  typename std::remove_reference<Visitor>::type::result_type // FIXME: elaborate
  visit_impl_(variant_index<0ul>, Visitor&& v) const &
#ifndef YAUL_VARIANT_DISABLE_NOEXCEPT_PROPAGATION_IN_APPLY_VISITOR
    noexcept(noexcept(std::forward<Visitor>(v)(*reinterpret_cast<cvar_t<0ul>*>(&cthat_->storage_))))
#endif
  {
    // note: noexcept would make no sense, because bad_visit may be thrown...
    YAUL_VARIANT_ASSERT(which() == 0);
    return std::forward<Visitor>(v)(*reinterpret_cast<cvar_t<0ul>*>(&storage_));
  }

  ///////////////////////////////////////////////////////////////////////////
  // Same as above, but for && *this
  ///////////////////////////////////////////////////////////////////////////
  template<std::size_t I, typename Visitor>
  typename std::remove_reference<Visitor>::type::result_type // FIXME: elaborate
  visit_impl_(variant_index<I>, Visitor&& v) &&
#ifndef YAUL_VARIANT_DISABLE_NOEXCEPT_PROPAGATION_IN_APPLY_VISITOR
    noexcept(noexcept(std::forward<Visitor>(v)(
                        std::forward<var_t<I> >(
                          *reinterpret_cast<var_t<I>*>(&that_->storage_)
                        )
                      )) &&
             noexcept(std::move(*that_).visit_impl_(variant_index<I-1>(), std::forward<Visitor>(v))))
#endif
  {
    if(which() == I)
      return  std::forward<Visitor>(v)(
                std::forward<var_t<I> >(
                  *reinterpret_cast<var_t<I>*>(&storage_)
                )
              );
    else
      return std::move(*this).visit_impl_(variant_index<I-1>(), std::forward<Visitor>(v));
  }
  template<typename Visitor>
  typename std::remove_reference<Visitor>::type::result_type // FIXME: elaborate
  visit_impl_(variant_index<0ul>, Visitor&& v) &&
#ifndef YAUL_VARIANT_DISABLE_NOEXCEPT_PROPAGATION_IN_APPLY_VISITOR
    noexcept(noexcept(std::forward<Visitor>(v)(
                        std::forward<var_t<0ul> >(
                          *reinterpret_cast<var_t<0ul>*>(&that_->storage_)
                        )
    )))
#endif
  {
    YAUL_VARIANT_ASSERT(which() == 0);
    return  std::forward<Visitor>(v)(
              std::forward<var_t<0ul> >(
                *reinterpret_cast<var_t<0ul>*>(&storage_)
              )
            );
  }

protected: // initialization
  template<typename T>
  void initialize_(T&& t)
#ifndef YAUL_VARIANT_DISABLE_NOEXCEPT_PROPAGATION_IN_INITIALIZE
    noexcept(noexcept(raw_t<T>(std::forward<T>(t))))
#endif
  {
    new(&storage_) raw_t<T>(std::forward<T>(t));
    which_ = variant_find<raw_t<T>, Variant>::value;
  }
protected:
  void destruct_()
    noexcept
  {
    apply_visitor(Destructor());
    which_ = -1;
  }
};
/** \endcond */
/** @} */
} } } // end namespace yaul::detail::variant

#endif /* YAUL_VARIANT_DETAIL_VARIANT_IMPL_CORE_HPP */
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
