// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

// yaul/variant/detail/variadic_storage.hpp

/** // doc: yaul/variant/detail/variadic_storage.hpp {{{
 * \file yaul/variant/detail/variadic_storage.hpp
 * \brief Provides \ref yaul::detail::variant::variadic_storage,
 *        \ref yaul::detail::variant::make_variadic_storage, and
 *        \ref yaul::detail::variant::make_variadic_storage_t
 */ // }}}
#ifndef YAUL_VARIANT_DETAIL_VARIADIC_STORAGE_HPP
#define YAUL_VARIANT_DETAIL_VARIADIC_STORAGE_HPP

#include <yaul/variant/detail/variadic_union.hpp>
#include <yaul/variant/detail/variadic_element.hpp>
#include <yaul/variant/detail/variadic_index.hpp>
#include <yaul/variant/detail/index_sequence.hpp>
#include <yaul/variant/detail/in_place_tags.hpp>
#include <yaul/variant/detail/all.hpp>
#include <type_traits>
#include <cstddef>
#include <array>
#include <new>

namespace yaul {
/** // doc: variant_npos {{{
 * \brief Returned by \ref yaul::variant::index() when
 *        valueless_by_exception() is `true`.
 */ // }}}
constexpr std::size_t variant_npos = -1;
}

namespace yaul { namespace detail { namespace variant {

template<std::size_t I, typename Union>
#if !defined(YAUL_VARIANT_NO_CONSTEXPR_VOID)
constexpr
#endif
void variadic_union_destruct(Union&& u)
  noexcept(noexcept(std::forward<Union>(u).destruct(in_place_index_t<I>{})))
{ std::forward<Union>(u).destruct(in_place_index_t<I>{}); }

template<typename Union, std::size_t... Indices>
struct variadic_storage_vtable
{
  static constexpr void (*dtors[])(Union const&) =
    { &variadic_union_destruct<Indices, Union const&>... };
};

template<typename Union, std::size_t... Indices>
constexpr void (*variadic_storage_vtable<Union,Indices...>::dtors[])(Union const&);

/** // doc: variadic_storage {{{
 * \brief Variadic storage class for use by variant implementation. Provides
 *  destructor, constructors, value assignment and index management methods.
 *
 * \tparam TriviallyDestructible `true` iff all `Types` are trivially destructible
 * \tparam Types underlying types
 *
 * \par Synopsis
 *
 * \code
 * template<bool TriviallyDestructible, typename... Types>
 *  struct variadic_storage
 *  {
 *  private:
 *    template <std::size_t I>
 *    using T = typename variadic_element<I, Types...>::type;
 *  public:
 *    typedef variadic_index<Types...> index_type;
 *    typedef variadic_union<Types...> union_type;
 *    template<std::size_t I, typename... Args>
 *      constexpr variadic_storage(in_place_index_t<I>, Args&&... args);  // (1)
 *    template<std::size_t I> constexpr T<I>& get()& noexcept;
 *    template<std::size_t I> constexpr T<I> const& get() const& noexcept;
 *    template<std::size_t I> constexpr T<I> volatile& get() volatile& noexcept;
 *    template<std::size_t I> constexpr T<I> const volatile& get() const volatile& noexcept;
 *    template<std::size_t I> constexpr T<I>&& get()&& noexcept;
 *    template<std::size_t I> constexpr T<I> const&& get() const&& noexcept;
 *    template<std::size_t I> constexpr T<I> volatile&& get() volatile&& noexcept;
 *    template<std::size_t I> constexpr T<I> const volatile&& get() const volatile&& noexcept;
 *    template<std::size_t I, typename T>
 *      void assign(T&&);
 *    template<std::size_t I, typename... Args>
 *      void emplace(Args&&... args);
 *    constexpr index_type index() const noexcept;
 *    constexpr bool valueless_by_exception() const noexcept;
 *    ~variadic_storage();                                                // (2)
 *
 *  protected:
 *    union_type union_;
 *    index_type index_;
 *  };
 * \endcode
 *
 * - (1) the constructor is `noexcept` iff the call to underlying
 *   `variadic_union` constructor is `noexcept`, i.e. iff the expression
 *   `union_type(in_place_index_t<I>{},std::forward<Args>(args)...)` is
 *   `noexcept`
 * - (2) Only defined if `TriviallyDestructible` is `false`, the destructor is
 *   `noexcept` iff all the `Types` are noexcept-destructible. If
 *   `TriviallyDestructible` is `true`, the `variadic_storage` is also
 *   trivially destructible.
 */ // }}}
template<bool TriviallyDestructible, typename... Types>
struct variadic_storage
{
private:
  using Union = variadic_union<Types...>;
  using Index = variadic_index_t<Types...>;
  template<std::size_t I> using T = typename variadic_element<I, Types...>::type;

  // FIXME: constexpr possible?
  void set_index(int i) noexcept
  { index_ = static_cast<Index>(i); }
  // FIXME: what was this used for? constexpr possible?
  void set_backup_index(int i) noexcept
  { index_ = static_cast<Index>(-(i+1)); }
  // FIXME: is it necessary?
  constexpr bool using_backup() const noexcept
  { return index_ < 0; }

  constexpr bool using_backup() const volatile noexcept
  { return index_ < 0; }

  template<std::size_t I, typename T>
  struct _is_assign_noexcept
  {
    static constexpr bool value
      = noexcept(std::declval<Union&>().get(in_place_index_t<I>{}) = std::forward<T>(std::declval<T&&>()));
  };

  template<std::size_t I, typename... Args>
  struct _is_emplace_noexcept
  {
    static constexpr bool value
      = noexcept(Union(in_place_index_t<I>{}, std::forward<Args>(std::declval<Args&&>())...));
  };

public:

  typedef Index index_type;
  typedef Union union_type;

  template<std::size_t I, typename... Args>
  constexpr
  variadic_storage(in_place_index_t<I>, Args&&... args)
    noexcept(noexcept(Union(in_place_index_t<I>{}, std::forward<Args>(args)...)))
    : union_(in_place_index_t<I>{}, std::forward<Args>(args)...), index_(I)
  { }

  template<std::size_t I>
#if !defined(YAUL_VARIANT_NO_CONSTEXPR_ON_NONCONST_FUNCTIONS)
  constexpr
#endif
  T<I>& get()& noexcept
  { return union_.get(in_place_index_t<I>{}); }

  template<std::size_t I>
  constexpr T<I> const& get() const& noexcept
  { return union_.get(in_place_index_t<I>{}); }

  template<std::size_t I>
#if !defined(YAUL_VARIANT_NO_CONSTEXPR_ON_NONCONST_FUNCTIONS)
  constexpr
#endif
  T<I> volatile& get() volatile& noexcept
  { return union_.get(in_place_index_t<I>{}); }

  template<std::size_t I>
  constexpr T<I> const volatile& get() const volatile& noexcept
  { return union_.get(in_place_index_t<I>{}); }

  template<std::size_t I>
#if !defined(YAUL_VARIANT_NO_CONSTEXPR_ON_NONCONST_FUNCTIONS)
  constexpr
#endif
  T<I>&& get()&& noexcept
  { return std::move(union_).get(in_place_index_t<I>{}); }

#ifndef YAUL_VARIANT_NO_RRCV_QUALIFIED_FUNCTIONS
  template<std::size_t I>
  constexpr T<I> const&& get() const&& noexcept
  { return std::move(union_).get(in_place_index_t<I>{}); }

  template<std::size_t I>
#if !defined(YAUL_VARIANT_NO_CONSTEXPR_ON_NONCONST_FUNCTIONS)
  constexpr
#endif
  T<I> volatile&& get() volatile&& noexcept
  { return std::move(union_).get(in_place_index_t<I>{}); }

  template<std::size_t I>
  constexpr T<I> const volatile&& get() const volatile&& noexcept
  { return std::move(union_).get(in_place_index_t<I>{}); }
#endif

  template <std::size_t I, typename T>
    // FIXME: constexpr possible?
  typename std::enable_if<_is_assign_noexcept<I,T>::value>::type
  assign(T&& v) noexcept
  {
    static_assert((I < sizeof...(Types)),
                  "The index should be in [0, number of alternatives)");
    union_.get(in_place_index_t<I>{}) = std::forward<T>(v);
    index_ = I;
  }

  template <std::size_t I, typename T>
    // FIXME: constexpr possible?
  typename std::enable_if<_is_assign_noexcept<I,T>::value>::type
  assign(T&& v) volatile noexcept
  {
    static_assert((I < sizeof...(Types)),
                  "The index should be in [0, number of alternatives)");
    union_.get(in_place_index_t<I>{}) = std::forward<T>(v);
    index_ = I;
  }

  template <std::size_t I, typename T>
    // FIXME: constexpr possible?
  typename std::enable_if<!_is_assign_noexcept<I,T>::value>::type
  assign(T&& v)
  {
    static_assert((I < sizeof...(Types)),
                  "The index should be in [0, number of alternatives)");
    try {
      union_.get(in_place_index_t<I>{}) = std::forward<T>(v);
    } catch (...) {
      index_ = Index(::yaul::variant_npos); // valueless_by_exception
      throw;
    }
    index_ = I;
  }

  template <std::size_t I, typename T>
    // FIXME: constexpr possible?
  typename std::enable_if<!_is_assign_noexcept<I,T>::value>::type
  assign(T&& v) volatile
  {
    static_assert((I < sizeof...(Types)),
                  "The index should be in [0, number of alternatives)");
    try {
      union_.get(in_place_index_t<I>{}) = std::forward<T>(v);
    } catch (...) {
      index_ = Index(::yaul::variant_npos); // valueless_by_exception
      throw;
    }
    index_ = I;
  }

  template<std::size_t I, typename... Args>
  typename std::enable_if<_is_emplace_noexcept<I, Args...>::value>::type
  emplace(Args&&... args) noexcept
  {
    static_assert((I < sizeof...(Types)),
                  "The index should be in [0, number of alternatives)");
    ::new(&union_) Union(in_place_index_t<I>{}, std::forward<Args>(args)...);
    index_ = Index(::yaul::variant_npos);
    index_ = I;
  }

  template<std::size_t I, typename... Args>
  typename std::enable_if<_is_emplace_noexcept<I, Args...>::value>::type
  emplace(Args&&... args) volatile noexcept
  {
    static_assert((I < sizeof...(Types)),
                  "The index should be in [0, number of alternatives)");
    // FIXME: well, this const_cast is a bad practice/undefined behaviour (?)
    ::new(const_cast<Union*>(&union_)) Union(in_place_index_t<I>{}, std::forward<Args>(args)...);
    index_ = Index(::yaul::variant_npos);
    index_ = I;
  }

  template<std::size_t I, typename... Args>
  typename std::enable_if<!_is_emplace_noexcept<I, Args...>::value>::type
  emplace(Args&&... args)
  {
    static_assert((I < sizeof...(Types)),
                  "The index should be in [0, number of alternatives)");
    try {
      ::new(&union_) Union(in_place_index_t<I>{}, std::forward<Args>(args)...);
    } catch(...) {
      index_ = Index(::yaul::variant_npos);
      throw;
    }
    index_ = I;
  }

  template<std::size_t I, typename... Args>
  typename std::enable_if<!_is_emplace_noexcept<I, Args...>::value>::type
  emplace(Args&&... args) volatile
  {
    static_assert((I < sizeof...(Types)),
                  "The index should be in [0, number of alternatives)");
    try {
      // FIXME: well, this const_cast is a bad practice/undefined behaviour (?)
      ::new(const_cast<Union*>(&union_)) Union(in_place_index_t<I>{}, std::forward<Args>(args)...);
    } catch(...) {
      index_ = Index(::yaul::variant_npos);
      throw;
    }
    index_ = I;
  }

  constexpr index_type
  index() const noexcept
  { return using_backup() ? -(index_ + 1) : index_; }

  // FIXME: is this correct?
  index_type
  index() const volatile noexcept
  { return using_backup() ? -(index_ + 1) : index_; }

  /** // doc: valueless_by_exception {{{
   * \brief Returns `false` if and only if the variant holds a value
   *
   * \par Notes
   *
   * A variant may become valueless in the following situations:
   *
   * - (guaranteed) an exception is thrown during the move initialization of
   *   the contained value from the temporary in copy assignment
   * - (guaranteed) an exception is thrown during the move initialization of
   *   the contained value during move assignment
   * - (optionally) an exception is thrown when initializing the contained
   *   value during a type-changing assignment
   * - (optionally) an exception is thrown when initializing the contained
   *   value during a type changing emplace
   */ // }}}
  constexpr bool valueless_by_exception() const
  { return index_ == Index(::yaul::variant_npos); }

protected:
  Union union_;
  Index index_;
};
/** \cond DOXYGEN_SHOW_TEMPLATE_SPECIALIZATIONS */
template<typename... Types>
struct variadic_storage<false, Types...>
  : variadic_storage<true, Types...>
{
private:
  using Base = variadic_storage<true, Types...>;
  using Union = typename Base::union_type;
  using Index = typename Base::index_type;

  template<size_t... Indices>
#if !defined(YAUL_VARIANT_NO_CONSTEXPR_VOID)
  constexpr
#endif
  void destruct_impl(index_sequence<Indices...>) const
    noexcept(all<noexcept(variadic_union_destruct<Indices>(std::declval<Union const&>()))...>::value)
  {
    if(this->index() != Index(::yaul::variant_npos))
      variadic_storage_vtable<Union, Indices...>::dtors[this->index_](this->union_);
  }

#if !defined(YAUL_VARIANT_NO_CONSTEXPR_VOID)
  constexpr
#endif
  void destruct() const
    noexcept(noexcept(
          std::declval<variadic_storage&>().
          destruct_impl(typename make_index_sequence<sizeof...(Types)>::type{})
          ))
  {
    destruct_impl(typename make_index_sequence<sizeof...(Types)>::type{});
  }

  // FIXME: constexpr possible?
  void reset()
    noexcept(noexcept(std::declval<variadic_storage&>().destruct()))
  {
    destruct();
    //destruct_impl(typename make_index_sequence<sizeof...(Types)>::type{});
    this->index_ = Index(::yaul::variant_npos);
  }

public:
  using Base::Base;

  template <std::size_t I, typename T>
    // FIXME: constexpr possible?
  void assign(T&& v)
    noexcept(noexcept(std::declval<variadic_storage&>().destruct()) &&
             noexcept(std::declval<Base&>().template assign<I>(std::forward<T>(v))))
  {
    static_assert((I < sizeof...(Types)),
                  "The index should be in [0, number of alternatives)");
    if(I != this->index())
      destruct();
    this->Base::template assign<I>(std::forward<T>(v));
  }

  template <std::size_t I, typename T>
    // FIXME: constexpr possible?
  void assign(T&& v) volatile
    noexcept(noexcept(std::declval<variadic_storage&>().destruct()) &&
             noexcept(std::declval<Base&>().template assign<I>(std::forward<T>(v))))
  {
    static_assert((I < sizeof...(Types)),
                  "The index should be in [0, number of alternatives)");
    if(I != this->index())
      destruct();
    this->Base::template assign<I>(std::forward<T>(v));
  }

  template<std::size_t I, typename... Args>
  void emplace(Args&&... args)
    noexcept(noexcept(std::declval<variadic_storage&>().destruct()) &&
             noexcept(std::declval<Base&>().template emplace<I>(std::forward<Args>(args)...)))
  {
    static_assert((I < sizeof...(Types)),
                  "The index should be in [0, number of alternatives)");
    if(I != this->index())
      destruct();
    this->Base::template emplace<I>(std::forward<Args>(args)...);
  }

  ~variadic_storage()
    noexcept(noexcept(std::declval<variadic_storage&>().reset()))
  { reset(); }
};
/** \endcond */

/** // doc: make_variadic_storage {{{
 * \brief Yields appropriate instantiation of `variadic_storage` template
 *
 * \tparam Types types used to make up the variadic storage
 *
 * \par Synopsis
 * \code
 *  template<typename... Types>
 *  struct make_variadic_storage
 *  {
 *    constexpr static bool trivial; // (1)
 *    typedef variadic_storage<trivial,Types...> type;
 *  };
 * \endcode
 *
 * - (1) set to `true` iff all the `Types` are trivially destructible
 */ // }}}
template<typename... Types>
struct make_variadic_storage
{
  constexpr static bool trivial = all<
    std::is_trivially_destructible<Types>::value...
  >::value;
  typedef variadic_storage<trivial,Types...> type;
};

/** // doc: variadic_storage_t {{{
 * \brief Alias for \ref make_variadic_storage "make_variadic_storage<Types...>::type"
 */ // }}}
template<typename... Types>
using make_variadic_storage_t = typename make_variadic_storage<Types...>::type;

} } } // end namespace yaul::detail::variant

#endif /* YAUL_VARIANT_DETAIL_VARIADIC_STORAGE_HPP */
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
