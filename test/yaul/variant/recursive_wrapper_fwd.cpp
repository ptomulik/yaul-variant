// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <yaul/variant/recursive_wrapper_fwd.hpp>
#include <yaul/variant/test_config.hpp>
#include <type_traits>


using yaul::recursive_wrapper;
using yaul::is_recursive_wrapper;
using yaul::unwrap_recursive_wrapper;
using yaul::wrap_recursive_wrapper;
using yaul::detail::variant::is_recursive_wrapper_template;

struct S;
template <typename...> struct F;

//
// is_recursive_wrapper_template
//
static_assert(!is_recursive_wrapper_template<F>::value, "");
static_assert( is_recursive_wrapper_template<recursive_wrapper>::value, "");

//
// is_recursive_wrapper
//
static_assert( is_recursive_wrapper<recursive_wrapper<int> >::value, "");
static_assert( is_recursive_wrapper<recursive_wrapper<int> const>::value, "");
static_assert( is_recursive_wrapper<recursive_wrapper<int> volatile>::value, "");
static_assert( is_recursive_wrapper<recursive_wrapper<int> const volatile>::value, "");
static_assert(!is_recursive_wrapper<recursive_wrapper<int const> >::value, "");
static_assert(!is_recursive_wrapper<recursive_wrapper<int volatile> >::value, "");
static_assert(!is_recursive_wrapper<recursive_wrapper<int const volatile> >::value, "");
static_assert(!is_recursive_wrapper<recursive_wrapper<int&> >::value, "");
static_assert(!is_recursive_wrapper<recursive_wrapper<int const&> >::value, "");
static_assert(!is_recursive_wrapper<recursive_wrapper<int volatile&> >::value, "");
static_assert(!is_recursive_wrapper<recursive_wrapper<int const volatile&> >::value, "");
static_assert(!is_recursive_wrapper<recursive_wrapper<int&&> >::value, "");
static_assert(!is_recursive_wrapper<recursive_wrapper<int const&&> >::value, "");
static_assert(!is_recursive_wrapper<recursive_wrapper<int volatile&&> >::value, "");
static_assert(!is_recursive_wrapper<recursive_wrapper<int const volatile&&> >::value, "");
static_assert(!is_recursive_wrapper<recursive_wrapper<int[2]> >::value, "");
static_assert(!is_recursive_wrapper<recursive_wrapper<int[]> >::value, "");
//
static_assert( is_recursive_wrapper<recursive_wrapper<S> >::value, "");
static_assert( is_recursive_wrapper<recursive_wrapper<S> const >::value, "");
static_assert( is_recursive_wrapper<recursive_wrapper<S> volatile >::value, "");
static_assert( is_recursive_wrapper<recursive_wrapper<S> const volatile >::value, "");
static_assert( is_recursive_wrapper<recursive_wrapper<S*> >::value, "");
static_assert( is_recursive_wrapper<recursive_wrapper<S*> const >::value, "");
static_assert( is_recursive_wrapper<recursive_wrapper<S*> volatile >::value, "");
static_assert( is_recursive_wrapper<recursive_wrapper<S*> const volatile >::value, "");
static_assert( is_recursive_wrapper<recursive_wrapper<S const*> >::value, "");
static_assert( is_recursive_wrapper<recursive_wrapper<S const*> const >::value, "");
static_assert( is_recursive_wrapper<recursive_wrapper<S const*> volatile >::value, "");
static_assert( is_recursive_wrapper<recursive_wrapper<S const*> const volatile >::value, "");
static_assert( is_recursive_wrapper<recursive_wrapper<S volatile*> >::value, "");
static_assert( is_recursive_wrapper<recursive_wrapper<S volatile*> const >::value, "");
static_assert( is_recursive_wrapper<recursive_wrapper<S volatile*> volatile >::value, "");
static_assert( is_recursive_wrapper<recursive_wrapper<S volatile*> const volatile >::value, "");
static_assert( is_recursive_wrapper<recursive_wrapper<S const volatile*> >::value, "");
static_assert( is_recursive_wrapper<recursive_wrapper<S const volatile*> const >::value, "");
static_assert( is_recursive_wrapper<recursive_wrapper<S const volatile*> volatile >::value, "");
static_assert( is_recursive_wrapper<recursive_wrapper<S const volatile*> const volatile >::value, "");
static_assert(!is_recursive_wrapper<S>::value, "");
static_assert(!is_recursive_wrapper<recursive_wrapper<S const> >::value, "");
static_assert(!is_recursive_wrapper<recursive_wrapper<S volatile> >::value, "");
static_assert(!is_recursive_wrapper<recursive_wrapper<S const volatile> >::value, "");
static_assert(!is_recursive_wrapper<recursive_wrapper<S>&>::value, "");
static_assert(!is_recursive_wrapper<recursive_wrapper<S>&&>::value, "");
static_assert(!is_recursive_wrapper<recursive_wrapper<S>*>::value, "");
static_assert(!is_recursive_wrapper<recursive_wrapper<S[2]> >::value, "");
static_assert(!is_recursive_wrapper<recursive_wrapper<S[]> >::value, "");

//
// wrap_recursive_wrapper
//
static_assert(std::is_same<wrap_recursive_wrapper<int>::type, recursive_wrapper<int> >::value, "");

static_assert(std::is_same<wrap_recursive_wrapper<int>::type, recursive_wrapper<int> >::value, "");
static_assert(std::is_same<wrap_recursive_wrapper<int const>::type, recursive_wrapper<int> const>::value, "");
static_assert(std::is_same<wrap_recursive_wrapper<int volatile>::type, recursive_wrapper<int> volatile>::value, "");
static_assert(std::is_same<wrap_recursive_wrapper<int const volatile>::type, recursive_wrapper<int> const volatile>::value, "");

static_assert(std::is_same<wrap_recursive_wrapper<S>::type, recursive_wrapper<S> >::value, "");
static_assert(std::is_same<wrap_recursive_wrapper<S const>::type, recursive_wrapper<S> const>::value, "");
static_assert(std::is_same<wrap_recursive_wrapper<S volatile>::type, recursive_wrapper<S> volatile>::value, "");
static_assert(std::is_same<wrap_recursive_wrapper<S const volatile>::type, recursive_wrapper<S> const volatile>::value, "");

static_assert(std::is_same<wrap_recursive_wrapper<S*>::type, recursive_wrapper<S*> >::value, "");
static_assert(std::is_same<wrap_recursive_wrapper<S const*>::type, recursive_wrapper<S const*> >::value, "");
static_assert(std::is_same<wrap_recursive_wrapper<S volatile*>::type, recursive_wrapper<S volatile*> >::value, "");
static_assert(std::is_same<wrap_recursive_wrapper<S const volatile*>::type, recursive_wrapper<S const volatile*> >::value, "");

static_assert(std::is_same<wrap_recursive_wrapper<S*>::type, recursive_wrapper<S*> >::value, "");
static_assert(std::is_same<wrap_recursive_wrapper<S* const>::type, recursive_wrapper<S*> const>::value, "");
static_assert(std::is_same<wrap_recursive_wrapper<S* volatile>::type, recursive_wrapper<S*> volatile>::value, "");
static_assert(std::is_same<wrap_recursive_wrapper<S* const volatile>::type, recursive_wrapper<S*> const volatile>::value, "");

static_assert(std::is_same<wrap_recursive_wrapper<S&>::type, S& >::value, "");
static_assert(std::is_same<wrap_recursive_wrapper<S const&>::type, S const&>::value, "");
static_assert(std::is_same<wrap_recursive_wrapper<S volatile&>::type, S volatile&>::value, "");
static_assert(std::is_same<wrap_recursive_wrapper<S const volatile&>::type, S const volatile&>::value, "");

static_assert(std::is_same<wrap_recursive_wrapper<S&&>::type, S&& >::value, "");
static_assert(std::is_same<wrap_recursive_wrapper<S const&&>::type, S const&&>::value, "");
static_assert(std::is_same<wrap_recursive_wrapper<S volatile&&>::type, S volatile&&>::value, "");
static_assert(std::is_same<wrap_recursive_wrapper<S const volatile&&>::type, S const volatile&&>::value, "");

static_assert(std::is_same<wrap_recursive_wrapper<S[]>::type, S[] >::value, "");
static_assert(std::is_same<wrap_recursive_wrapper<S const[]>::type, S const[]>::value, "");
static_assert(std::is_same<wrap_recursive_wrapper<S volatile[]>::type, S volatile[]>::value, "");
static_assert(std::is_same<wrap_recursive_wrapper<S const volatile[]>::type, S const volatile[]>::value, "");

static_assert(std::is_same<wrap_recursive_wrapper<S[2]>::type, S[2] >::value, "");
static_assert(std::is_same<wrap_recursive_wrapper<S const[2]>::type, S const[2]>::value, "");
static_assert(std::is_same<wrap_recursive_wrapper<S volatile[2]>::type, S volatile[2]>::value, "");
static_assert(std::is_same<wrap_recursive_wrapper<S const volatile[2]>::type, S const volatile[2]>::value, "");

//
// unwrap_recursive_wrapper
//
static_assert(std::is_same<unwrap_recursive_wrapper<int>::type, int>::value, "");

static_assert(std::is_same<unwrap_recursive_wrapper<recursive_wrapper<int> >::type, int>::value, "");
static_assert(std::is_same<unwrap_recursive_wrapper<recursive_wrapper<int> const>::type, const int>::value, "");
static_assert(std::is_same<unwrap_recursive_wrapper<recursive_wrapper<int> volatile>::type, volatile int>::value, "");
static_assert(std::is_same<unwrap_recursive_wrapper<recursive_wrapper<int> const volatile>::type, const volatile int>::value, "");

static_assert(std::is_same<unwrap_recursive_wrapper<S>::type, S>::value, "");
static_assert(std::is_same<unwrap_recursive_wrapper<S const>::type, S const>::value, "");
static_assert(std::is_same<unwrap_recursive_wrapper<S volatile>::type, S volatile>::value, "");
static_assert(std::is_same<unwrap_recursive_wrapper<S const volatile>::type, S const volatile>::value, "");

static_assert(std::is_same<unwrap_recursive_wrapper<recursive_wrapper<S*> >::type, S*>::value, "");
static_assert(std::is_same<unwrap_recursive_wrapper<recursive_wrapper<S const*> >::type, S const*>::value, "");
static_assert(std::is_same<unwrap_recursive_wrapper<recursive_wrapper<S volatile*> >::type, S volatile*>::value, "");
static_assert(std::is_same<unwrap_recursive_wrapper<recursive_wrapper<S const volatile*> >::type, S const volatile*>::value, "");

static_assert(std::is_same<unwrap_recursive_wrapper<recursive_wrapper<S> const>::type, S const>::value, "");
static_assert(std::is_same<unwrap_recursive_wrapper<recursive_wrapper<S> volatile>::type, S volatile>::value, "");
static_assert(std::is_same<unwrap_recursive_wrapper<recursive_wrapper<S> const volatile >::type, S const volatile>::value, "");

static_assert(std::is_same<unwrap_recursive_wrapper<recursive_wrapper<S*> >::type, S*>::value, "");
static_assert(std::is_same<unwrap_recursive_wrapper<recursive_wrapper<S*> const>::type, S* const>::value, "");
static_assert(std::is_same<unwrap_recursive_wrapper<recursive_wrapper<S*> volatile>::type, S* volatile>::value, "");
static_assert(std::is_same<unwrap_recursive_wrapper<recursive_wrapper<S*> const volatile>::type, S* const volatile>::value, "");

static_assert(std::is_same<unwrap_recursive_wrapper<recursive_wrapper<S const*> >::type, S const*>::value, "");
static_assert(std::is_same<unwrap_recursive_wrapper<recursive_wrapper<S const*> const>::type, S const* const>::value, "");
static_assert(std::is_same<unwrap_recursive_wrapper<recursive_wrapper<S const*> volatile>::type, S const* volatile>::value, "");
static_assert(std::is_same<unwrap_recursive_wrapper<recursive_wrapper<S const*> const volatile>::type, S const* const volatile>::value, "");

static_assert(std::is_same<unwrap_recursive_wrapper<recursive_wrapper<S volatile*> >::type, S volatile*>::value, "");
static_assert(std::is_same<unwrap_recursive_wrapper<recursive_wrapper<S volatile*> const>::type, S volatile* const>::value, "");
static_assert(std::is_same<unwrap_recursive_wrapper<recursive_wrapper<S volatile*> volatile>::type, S volatile* volatile>::value, "");
static_assert(std::is_same<unwrap_recursive_wrapper<recursive_wrapper<S volatile*> const volatile>::type, S volatile* const volatile>::value, "");

static_assert(std::is_same<unwrap_recursive_wrapper<recursive_wrapper<S const volatile*> >::type, S const volatile*>::value, "");
static_assert(std::is_same<unwrap_recursive_wrapper<recursive_wrapper<S const volatile*> const>::type, S const volatile* const>::value, "");
static_assert(std::is_same<unwrap_recursive_wrapper<recursive_wrapper<S const volatile*> volatile>::type, S const volatile* volatile>::value, "");
static_assert(std::is_same<unwrap_recursive_wrapper<recursive_wrapper<S const volatile*> const volatile>::type, S const volatile* const volatile>::value, "");

static_assert(std::is_same<unwrap_recursive_wrapper<recursive_wrapper<S> >::type, S>::value, "");
static_assert(std::is_same<unwrap_recursive_wrapper<recursive_wrapper<S const> >::type, recursive_wrapper<S const> >::value, "");
static_assert(std::is_same<unwrap_recursive_wrapper<recursive_wrapper<S volatile> >::type, recursive_wrapper<S volatile> >::value, "");
static_assert(std::is_same<unwrap_recursive_wrapper<recursive_wrapper<S const volatile> >::type, recursive_wrapper<S const volatile> >::value, "");
static_assert(std::is_same<unwrap_recursive_wrapper<recursive_wrapper<S&> >::type, recursive_wrapper<S&> >::value, "");
static_assert(std::is_same<unwrap_recursive_wrapper<recursive_wrapper<S const&> >::type, recursive_wrapper<S const&> >::value, "");
static_assert(std::is_same<unwrap_recursive_wrapper<recursive_wrapper<S volatile&> >::type, recursive_wrapper<S volatile&> >::value, "");
static_assert(std::is_same<unwrap_recursive_wrapper<recursive_wrapper<S const volatile&> >::type, recursive_wrapper<S const volatile&> >::value, "");
static_assert(std::is_same<unwrap_recursive_wrapper<recursive_wrapper<S&&> >::type, recursive_wrapper<S&&> >::value, "");
static_assert(std::is_same<unwrap_recursive_wrapper<recursive_wrapper<S const&&> >::type, recursive_wrapper<S const&&> >::value, "");
static_assert(std::is_same<unwrap_recursive_wrapper<recursive_wrapper<S volatile&&> >::type, recursive_wrapper<S volatile&&> >::value, "");
static_assert(std::is_same<unwrap_recursive_wrapper<recursive_wrapper<S const volatile&&> >::type, recursive_wrapper<S const volatile&&> >::value, "");

static_assert(std::is_same<unwrap_recursive_wrapper<recursive_wrapper<S[]> >::type, recursive_wrapper<S[]> >::value, "");
static_assert(std::is_same<unwrap_recursive_wrapper<recursive_wrapper<S const[]> >::type, recursive_wrapper<S const[]> >::value, "");
static_assert(std::is_same<unwrap_recursive_wrapper<recursive_wrapper<S volatile[]> >::type, recursive_wrapper<S volatile[]> >::value, "");
static_assert(std::is_same<unwrap_recursive_wrapper<recursive_wrapper<S const volatile[]> >::type, recursive_wrapper<S const volatile[]> >::value, "");

static_assert(std::is_same<unwrap_recursive_wrapper<recursive_wrapper<S[2]> >::type, recursive_wrapper<S[2]> >::value, "");
static_assert(std::is_same<unwrap_recursive_wrapper<recursive_wrapper<S const[2]> >::type, recursive_wrapper<S const[2]> >::value, "");
static_assert(std::is_same<unwrap_recursive_wrapper<recursive_wrapper<S volatile[2]> >::type, recursive_wrapper<S volatile[2]> >::value, "");
static_assert(std::is_same<unwrap_recursive_wrapper<recursive_wrapper<S const volatile[2]> >::type, recursive_wrapper<S const volatile[2]> >::value, "");

template<typename...> struct F1;
template<typename...> struct F2;

namespace yaul { namespace detail { namespace variant {
template<>
  struct is_recursive_wrapper_template<F2>
    : std::integral_constant<bool, true>
  { };
} } } // end namespace yaul::detail::variant

// Test applicability of is_recursive_wrapper and (un)wrap_recursive_wrapper to
// custom class templates.
static_assert(!is_recursive_wrapper<F1<int> >::value, "");
static_assert( is_recursive_wrapper<F2<int> >::value, "");
static_assert( is_recursive_wrapper<F2<int> const>::value, "");
static_assert( is_recursive_wrapper<F2<int> volatile>::value, "");
static_assert( is_recursive_wrapper<F2<int> const volatile>::value, "");
static_assert( is_recursive_wrapper<F2<int> const>::value, "");
static_assert( is_recursive_wrapper<F2<int> volatile>::value, "");
static_assert( is_recursive_wrapper<F2<int> const volatile>::value, "");

static_assert(std::is_same<wrap_recursive_wrapper<int, F1 >::type, int>::value, "");
static_assert(std::is_same<wrap_recursive_wrapper<int, F2>::type, F2<int> >::value, "");
static_assert(std::is_same<wrap_recursive_wrapper<int const, F2>::type, F2<int> const>::value, "");
static_assert(std::is_same<wrap_recursive_wrapper<int volatile, F2>::type, F2<int> volatile>::value, "");
static_assert(std::is_same<wrap_recursive_wrapper<int const volatile, F2>::type, F2<int> const volatile>::value, "");

static_assert(std::is_same<unwrap_recursive_wrapper<F1<int> >::type, F1<int> >::value, "");
static_assert(std::is_same<unwrap_recursive_wrapper<F2<int> >::type, int>::value, "");
static_assert(std::is_same<unwrap_recursive_wrapper<F2<int const> >::type, F2<int const>>::value, "");
static_assert(std::is_same<unwrap_recursive_wrapper<F2<int volatile> >::type, F2<int volatile>>::value, "");
static_assert(std::is_same<unwrap_recursive_wrapper<F2<int const volatile> >::type, F2<int const volatile> >::value, "");
static_assert(std::is_same<unwrap_recursive_wrapper<F2<int> const>::type, int const>::value, "");
static_assert(std::is_same<unwrap_recursive_wrapper<F2<int> volatile>::type, int volatile>::value, "");
static_assert(std::is_same<unwrap_recursive_wrapper<F2<int> const volatile>::type, int const volatile>::value, "");

int main()
{
  return YAUL_VARIANT_TEST_EXIT_CODE;
}
