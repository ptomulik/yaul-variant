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
#include <yaul/variant/detail/contains.hpp>
#include <type_traits>

namespace yaul {
/** // doc: relaxed_get() {{{
 * \todo Write documentation
 */ // }}}
template<typename U, typename T0, typename... Others>
inline typename std::add_pointer<U>::type
relaxed_get(variant<T0, Others...>* v) noexcept
{
  return v->template get_ptr<U>();
}
/** // doc: relaxed_get() {{{
 * \todo Write documentation
 */ // }}}
template<typename U, typename T0, typename... Others>
inline typename std::add_pointer<
  typename std::add_const<U>::type
>::type
relaxed_get(variant<T0, Others...> const* v) noexcept
{
  return v->template get_ptr<U>();
}
/** // doc: relaxed_get() {{{
 * \todo Write documentation
 */ // }}}
template<typename U, typename T0, typename... Others>
inline typename std::add_lvalue_reference<U>::type
relaxed_get(variant<T0, Others...>& v)
{
  return v.template get<U>();
}
/** // doc: relaxed_get() {{{
 * \todo Write documentation
 */ // }}}
template<typename U, typename T0, typename... Others>
inline typename std::add_lvalue_reference<
  typename std::add_const<U>::type
>::type
relaxed_get(variant<T0, Others...> const& v)
{
  return v.template get<U>();
}
/** // doc: relaxed_get() {{{
 * \todo Write documentation
 */ // }}}
template<typename U, typename T0, typename... Others>
inline typename std::add_rvalue_reference<U>::type
relaxed_get(variant<T0, Others...>&& v)
{
  return std::move(v).template get<U>();
}
/** // doc: relaxed_get() {{{
 * \todo Write documentation
 */ // }}}
template<typename U, typename T0, typename... Others>
inline typename std::add_rvalue_reference<
  typename std::add_const<U>::type
>::type
relaxed_get(variant<T0, Others...> const&& v)
{
  return std::move(v).template get<U>();
}
/** // doc: strict_get() {{{
 * \todo Write documentation
 */ // }}}
template<typename U, typename T0, typename... Others>
inline typename std::add_pointer<U>::type
strict_get(variant<T0, Others...>* v) noexcept
{
  static_assert(detail::variant::contains<U,variant<T0,Others...> >::value,
                "yaul::variant does not contain specified type U, "
                "call to yaul::get<U>(variant<T...>*) will always return NULL");
  return relaxed_get<U>(v);
}
/** // doc: strict_get() {{{
 * \todo Write documentation
 */ // }}}
template<typename U, typename T0, typename... Others>
inline typename std::add_pointer<
  typename std::add_const<U>::type
>::type
strict_get(variant<T0, Others...> const* v) noexcept
{
  static_assert(detail::variant::contains<U,variant<T0,Others...> >::value,
                "yaul::variant does not contain specified type U, "
                "call to yaul::get<U>(const variant<T...>*) will always return NULL");
  return relaxed_get<U>(v);
}
/** // doc: strict_get() {{{
 * \todo Write documentation
 */ // }}}
template<typename U, typename T0, typename... Others>
inline typename std::add_lvalue_reference<U>::type
strict_get(variant<T0, Others...>& v)
{
  static_assert(detail::variant::contains<U,variant<T0,Others...> >::value,
                "yaul::variant does not contain specified type U, "
                "call to yaul::get<U>(variant<T...>&) will always throw yaul::bad_get exception");
  return relaxed_get<U>(v);
}
/** // doc: strict_get() {{{
 * \todo Write documentation
 */ // }}}
template<typename U, typename T0, typename... Others>
inline typename std::add_lvalue_reference<
  typename std::add_const<U>::type
>::type
strict_get(variant<T0, Others...> const& v)
{
  static_assert(detail::variant::contains<U,variant<T0,Others...> >::value,
                "yaul::variant does not contain specified type U, "
                "call to yaul::get<U>(const variant<T...>&) will always throw yaul::bad_get exception");
  return relaxed_get<U>(v);
}
/** // doc: strict_get() {{{
 * \todo Write documentation
 */ // }}}
template<typename U, typename T0, typename... Others>
inline typename std::add_rvalue_reference<U>::type
strict_get(variant<T0, Others...>&& v)
{
  static_assert(detail::variant::contains<U,variant<T0,Others...> >::value,
                "yaul::variant does not contain specified type U, "
                "call to yaul::get<U>(variant<T...>&&) will always throw yaul::bad_get exception");
  return relaxed_get<U>(std::move(v));
}
/** // doc: strict_get() {{{
 * \todo Write documentation
 */ // }}}
template<typename U, typename T0, typename... Others>
inline typename std::add_rvalue_reference<
  typename std::add_const<U>::type
>::type
strict_get(variant<T0, Others...> const&& v)
{
  static_assert(detail::variant::contains<U,variant<T0,Others...> >::value,
                "yaul::variant does not contain specified type U, "
                "call to yaul::get<U>(variant<T...>&&) will always throw yaul::bad_get exception");
  return relaxed_get<U>(std::move(v));
}
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
inline typename std::add_pointer<
  typename std::add_const<U>::type
>::type
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
inline typename std::add_lvalue_reference<U>::type
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
inline typename std::add_lvalue_reference<
  typename std::add_const<U>::type
>::type
get(variant<T0, Others...> const& v)
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
inline typename std::add_rvalue_reference<U>::type
get(variant<T0, Others...>&& v)
{
#if YAUL_VARIANT_USE_RELAXED_GET_BY_DEFAULT
  return relaxed_get<U>(std::move(v));
#else
  return strict_get<U>(std::move(v));
#endif
}
/** // doc: get() {{{
 * \todo Write documentation
 */ // }}}
template<typename U, typename T0, typename... Others>
inline typename std::add_rvalue_reference<
  typename std::add_const<U>::type
>::type
get(variant<T0, Others...> const&& v)
{
#if YAUL_VARIANT_USE_RELAXED_GET_BY_DEFAULT
  return relaxed_get<U>(std::move(v));
#else
  return strict_get<U>(std::move(v));
#endif
}
} // end namespace yaul

#endif /* YAUL_VARIANT_GET_HPP */
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
