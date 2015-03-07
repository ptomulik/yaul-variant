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
#include <yaul/variant/detail/variant_impl.hpp>
#include <yaul/variant/variant_find.hpp>
#include <utility>

namespace yaul {
/** \ingroup VariantGroup
 * @{ */
/** // doc: variant {{{
 * \todo Write documentation
 */ // }}}
template<typename T0, typename... Others>
class variant
  : public detail::variant::variant_impl<sizeof...(Others), variant<T0, Others...> >
{
private:
  //static constexpr std::size_t size_ = 1ul + sizeof...(Others);
  using Base = detail::variant::variant_impl<sizeof...(Others), variant>;

public: // inherited ctors
  using Base::Base;
  using Base::operator=;

  variant() = default;
  variant(variant&) = default;
  variant(variant const&) = default;
  variant(variant&&) = default;

  variant& operator=(variant&) = default;
  variant& operator=(variant const&) = default;
  variant& operator=(variant&&) = default;

public: // inherited methods
  using Base::which;
  using Base::empty;

#if 0
  variant() = default;
  variant(variant&) = default;
  variant(variant const&) = default;
  variant(variant&&) = default;
  /** // doc: variant() {{{
   * \brief Default constructor
   *
   * \pre
   *    The first bounded type of the \ref yaul::variant "variant" (\c T0, say)
   *    must fulfill the requirements of the \e DefaultConstructible [20.1.4]
   *    concept.
   * \post
   *    Content of <tt>*this</tt> is the default value of the first bounded
   *    type (\c T0).
   * \par Exceptions
   *    May fail with any exceptions arising from the default constructor of
   *    \c T0. If \c T0 is nothrow- default constructible, then this
   *    constructor is \c noexcept.
   */ // }}}
  variant() noexcept(noexcept(internal_T0()))
  {
    new(&storage_) internal_T0();
    which_ = 0ul;
  }
  /** // doc: variant() {{{
   * \todo Write documentation
   */ // }}}
  template<typename T, typename = enable_if_compatible_<T> >
  variant(T& x)
    // noexcept(noexcept(variant_ctors_::apply(&storage_, x)))
  {
    variant_ctors_::apply(&storage_, x);
    which_ = static_cast<which_t>(select_index_(x));
  }
  /** // doc: variant() {{{
   * \todo Write documentation
   */ // }}}
  template<typename T, typename = enable_if_compatible_<T> >
  variant(const T& x)
    // noexcept(noexcept(variant_ctors_::apply(&storage_, x)))
  {
    variant_ctors_::apply(&storage_, x);
    which_ = static_cast<which_t>(select_index_(x));
  }
  /** // doc: variant() {{{
   * \todo Write documentation
   */ // }}}
  template<typename T, typename = enable_if_compatible_<T> >
  variant(T&& x)
    // noexcept(noexcept(variant_ctors_::apply(&storage_, std::forward<T>(x))))
  {
    variant_ctors_::apply(&storage_, std::forward<T>(x));
    which_ = static_cast<which_t>(select_index_(std::forward<T>(x)));
  }
#endif
#if 0
  /** // doc: variant() {{{
   * \todo Write documentation
   */ // }}}
  template<typename... UTypes>
  variant(variant<UTypes...>&)
  {
    // TODO: implement
  }
  /** // doc: variant() {{{
   * \todo Write documentation
   */ // }}}
  template<typename... UTypes>
  variant(const variant<UTypes...>&)
  {
    // TODO: implement
  }
  /** // doc: variant() {{{
   * \todo Write documentation
   */ // }}}
  template<typename... UTypes>
  variant(variant<UTypes...>&&)
  {
  }
  /** // doc: ~variant() {{{
   * \todo Write documentation
   */ // }}}
  ~variant() noexcept
  {
    // TODO: implement
  }

public: // modifiers
  /** // doc: swap() {{{
   * \todo Write documentation
   */ // }}}
  void swap(variant&)
  {
    // TODO: implement
  }
  /** // doc: operator=() {{{
   * \todo Write documentation
   */ // }}}
  variant& operator=(const variant&)
  {
    // TODO: implement
  }
  /** // doc: operator=() {{{
   * \todo Write documentation
   */ // }}}
  variant& operator=(variant&&)
  {
    // TODO: implement
  }
  /** // doc: operator=() {{{
   * \todo Write documentation
   */ // }}}
  template<typename T>
  variant& operator=(const T&)
  {
    // TODO: implement
  }
  /** // doc: operator=() {{{
   * \todo Write documentation
   */ // }}}
  template<typename T>
  variant& operator=(T&&)
  {
    // TODO: implement
  }
public: // queries
  /** // doc: which() {{{
   * \brief Which type is currently selected
   *
   * \returns
   *    The zero-based index into the set of bounded types of the contained
   *    type of <tt>*this</tt>. (For instance,  if called on a <tt>variant<int,
   *    std::::string></tt> object containg a <tt>std::::string</tt>, which()
   *    would return 1.)
   *
   * \par Exceptions
   *    Will throw nothing
   */ // }}}
  int which() const noexcept
  {
    return static_cast<int>(this->which_);
  }
  /** // doc: empty() {{{
   * \brief Whether the variant object is empty
   *
   * \returns
   *    \c false: variant always contains exactly one of its bounded types.
   *    (See \ref FixMe "the section called Never-Empty Guarantee" for more
   *    information)
   *
   * \par Rationale
   *    Facilitates generic compatibility with <a href="FixMe">boost::any</a>.
   *
   * \par Exceptions
   *    Will throw nothing
   *
   * \todo Fix links in documentation
   */ // }}}
  bool empty() const noexcept
  {
    return false;
  }
  /** // doc: type() {{{
   * \brief Return type_info object for the current type contained in variant
   *
   * \returns
   *    <tt>typeid(x)</tt>, where \c x is the content of <tt>*this</tt>
   *
   * \par Exceptions
   *    Will not throw
   */ // }}}
  const std::type_info& type() const noexcept
  {
    // TODO: implement
  }
#endif
#if 0
public: // relational
  /** // doc: operator== {{{
   * \todo Write documentation
   */ // }}}
  bool operator==(const variant&) const
  {
    // TODO: implement
  }
  /** // doc: operator== {{{
   * \todo Write documentation
   */ // }}}
  template<typename U>
  bool operator==(const U&) const
  {
    // TODO: implement
  }
  /** // doc: operator!= {{{
   * \todo Write documentation
   */ // }}}
  bool operator!=(const variant&) const
  {
    // TODO: implement
  }
  /** // doc: operator!= {{{
   * \todo Write documentation
   */ // }}}
  template<typename U>
  bool operator!=(const U&) const
  {
    // TODO: implement
  }
  /** // doc: operator< {{{
   * \todo Write documentation
   */ // }}}
  bool operator<(const variant&) const
  {
    // TODO: implement
  }
  /** // doc: operator< {{{
   * \todo Write documentation
   */ // }}}
  template<typename U>
  bool operator<(const U&) const
  {
    // TODO: implement
  }
  /** // doc: operator> {{{
   * \todo Write documentation
   */ // }}}
  bool operator>(const variant&) const
  {
    // TODO: implement
  }
  /** // doc: operator> {{{
   * \todo Write documentation
   */ // }}}
  template<typename U>
  bool operator>(const U&) const
  {
    // TODO: implement
  }
  /** // doc: operator<= {{{
   * \todo Write documentation
   */ // }}}
  bool operator<=(const variant&) const
  {
    // TODO: implement
  }
  /** // doc: operator<= {{{
   * \todo Write documentation
   */ // }}}
  template<typename U>
  bool operator<=(const U&) const
  {
    // TODO: implement
  }
  /** // doc: operator>= {{{
   * \todo Write documentation
   */ // }}}
  bool operator>=(const variant&) const
  {
    // TODO: implement
  }
  /** // doc: operator>= {{{
   * \todo Write documentation
   */ // }}}
  template<typename U>
  bool operator>=(const U&) const
  {
    // TODO: implement
  }
#endif
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
