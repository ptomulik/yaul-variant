// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <yaul/variant/detail/in_place_tags.hpp>
#include <yaul/variant/test_config.hpp>


using yaul::detail::variant::in_place_index_t;
using yaul::detail::variant::in_place_type_t;

template<typename T>
constexpr inline T
zero_of(in_place_type_t<T>)
{ return T{0}; }

// test constexpr-ness of in_place_type_t
static_assert(zero_of(in_place_type_t<int>{}) == 0, "");
static_assert(zero_of(in_place_type_t<float>{}) == 0.0f, "");

template<std::size_t I>
constexpr inline std::size_t
index_of(in_place_index_t<I>)
{ return I; }

// test constexpr-ness of in_place_index_t
static_assert(index_of(in_place_index_t<0ul>{}) == 0ul, "");
static_assert(index_of(in_place_index_t<3ul>{}) == 3ul, "");

int main()
{
  return YAUL_VARIANT_TEST_EXIT_CODE;
}
