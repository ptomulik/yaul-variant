// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

// yaul/variant/get.hpp

/** // doc: yaul/variant/get.hpp {{{
 * \file yaul/variant/get.hpp
 * \todo Write documentation
 */ // }}}
#ifndef YAUL_VARIANT_GET_HPP
#define YAUL_VARIANT_GET_HPP

#include <yaul/variant/variant.hpp>
#include <yaul/variant/bad_get.hpp>
#include <yaul/variant/variant_contains.hpp>
#include <yaul/variant/variant_find.hpp>
#include <cstddef>
#include <utility>

namespace yaul {
/** // doc: relaxed_get() {{{
 * \todo Write documentation
 */ // }}}
template<typename U, typename T0, typename... Others>
inline typename std::add_pointer<U>::type
relaxed_get(variant<T0, Others...>* v) noexcept
{
  using Variant = variant<T0, Others...>;
  constexpr std::size_t I = detail::variant::variant_find<U, Variant>::value;
  if(I != v->which())
    return nullptr;
  return reinterpret_cast<U*>(v->data());
}
/** // doc: relaxed_get() {{{
 * \todo Write documentation
 */ // }}}
template<typename U, typename T0, typename... Others>
inline typename std::add_pointer<U const>::type
relaxed_get(variant<T0, Others...> const* v) noexcept
{
  using Variant = variant<T0, Others...>;
  constexpr std::size_t I = detail::variant::variant_find<U, Variant>::value;
  if(I != v->which())
    return nullptr;
  return reinterpret_cast<U const*>(v->data());
}
/** // doc: relaxed_get() {{{
 * \todo Write documentation
 */ // }}}
template<typename U, typename T0, typename... Others>
inline typename std::add_reference<U>::type
relaxed_get(variant<T0, Others...>& v)
{
  using Variant = variant<T0, Others...>;
  constexpr std::size_t I = detail::variant::variant_find<U, Variant>::value;
  if(I != v->which())
    throw bad_get();
  return *reinterpret_cast<U*>(v->data());
}
/** // doc: relaxed_get() {{{
 * \todo Write documentation
 */ // }}}
template<typename U, typename T0, typename... Others>
inline typename std::add_reference<U const>::type
relaxed_get(variant<T0, Others...> const& v)
{
  using Variant = variant<T0, Others...>;
  constexpr std::size_t I = detail::variant::variant_find<U, Variant>::value;
  if(I != v->which())
    throw bad_get();
  return *reinterpret_cast<U const*>(v->data());
}
#if 0
/** // doc: relaxed_get() {{{
 * \todo Write documentation
 */ // }}}
template<typename U, typename T0, typename... Others>
U&& relaxed_get(variant<T0, Others...>&& v)
{
  using Variant = variant<T0, Others...>;
  constexpr std::size_t I = detail::variant::variant_find<U, Variant>::value;
  if(I != v->which())
    throw bad_get();
  return *reinterpret_cast<U*>(v->data());
}
#endif
/** // doc: strict_get() {{{
 * \todo Write documentation
 */ // }}}
template<typename U, typename T0, typename... Others>
inline typename std::add_pointer<U>::type
strict_get(variant<T0, Others...>* v) noexcept
{
  static_assert(variant_contains<U,variant<T0,Others...> >::value,
                "yaul::variant does not contain specified type U, "
                "call to yaul::get<U>(variant<T...>*) will always return NULL");
  return relaxed_get<U>(v);
}
/** // doc: strict_get() {{{
 * \todo Write documentation
 */ // }}}
template<typename U, typename T0, typename... Others>
inline typename std::add_pointer<U const>
strict_get(variant<T0, Others...> const* v) noexcept
{
  static_assert(variant_contains<U,variant<T0,Others...> >::value,
                "yaul::variant does not contain specified type U, "
                "call to yaul::get<U>(const variant<T...>*) will always return NULL");
  return relaxed_get<U>(v);
}
/** // doc: strict_get() {{{
 * \todo Write documentation
 */ // }}}
template<typename U, typename T0, typename... Others>
inline typename std::add_reference<U>::type
strict_get(variant<T0, Others...>& v)
{
  static_assert(variant_contains<U,variant<T0,Others...> >::value,
                "yaul::variant does not contain specified type U, "
                "call to yaul::get<U>(variant<T...>&) will always throw yaul::bad_get exception");
  return relaxed_get<U>(v);
}
/** // doc: strict_get() {{{
 * \todo Write documentation
 */ // }}}
template<typename U, typename T0, typename... Others>
inline typename std::add_reference<U const>::type
strict_get(variant<T0, Others...> const& v)
{
  static_assert(variant_contains<U,variant<T0,Others...> >::value,
                "yaul::variant does not contain specified type U, "
                "call to yaul::get<U>(const variant<T...>&) will always throw yaul::bad_get exception");
  return relaxed_get<U>(v);
}
#if 0
/** // doc: strict_get() {{{
 * \todo Write documentation
 */ // }}}
template<typename U, typename T0, typename... Others>
U&& strict_get(variant<T0, Others...>&& v)
{
  static_assert(variant_contains<U,variant<T0,Others...> >::value,
                "yaul::variant does not contain specified type U, "
                "call to yaul::get<U>(variant<T...>&&) will always throw yaul::bad_get exception");
  return relaxed_get<U>(std::forward<variant<T0,Others...> >(v));
}
#endif
/** // doc: get() {{{
 * \todo Write documentation
 */ // }}}
template<typename U, typename T0, typename... Others>
inline typename std::add_pointer<U>::type
get(variant<T0, Others...>* v) noexcept
{
#if YAUL_VARIANT_USE_RELAXED_GET_BY_DEFAULT
  return relaxed_get<U>(v);
#else
  return strict_get<U>(v);
#endif
}
/** // doc: get() {{{
 * \todo Write documentation
 */ // }}}
template<typename U, typename T0, typename... Others>
inline typename std::add_pointer<U const>::type
get(variant<T0, Others...> const* v) noexcept
{
#if YAUL_VARIANT_USE_RELAXED_GET_BY_DEFAULT
  return relaxed_get<U>(v);
#else
  return strict_get<U>(v);
#endif
}
/** // doc: get() {{{
 * \todo Write documentation
 */ // }}}
template<typename U, typename T0, typename... Others>
inline typename std::add_reference<U>::type
get(variant<T0, Others...>& v)
{
#if YAUL_VARIANT_USE_RELAXED_GET_BY_DEFAULT
  return relaxed_get<U>(v);
#else
  return strict_get<U>(v);
#endif
}
/** // doc: get() {{{
 * \todo Write documentation
 */ // }}}
template<typename U, typename T0, typename... Others>
inline typename std::add_reference<U const>::type
get(variant<T0, Others...> const& v)
{
#if YAUL_VARIANT_USE_RELAXED_GET_BY_DEFAULT
  return relaxed_get<U>(v);
#else
  return strict_get<U>(v);
#endif
}
#if 0
/** // doc: get() {{{
 * \todo Write documentation
 */ // }}}
template<typename U, typename T0, typename... Others>
U&& get(variant<T0, Others...>&& v)
{
#if YAUL_VARIANT_USE_RELAXED_GET_BY_DEFAULT
  return relaxed_get<U>(std::forward<variant<T0,Others...> >(v));
#else
  return strict_get<U>(std::forward<variant<T0,Others...> >(v));
#endif
}
#endif
} // end namespace yaul

#endif /* YAUL_VARIANT_GET_HPP */
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
