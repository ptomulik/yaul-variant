// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <yaul/variant/variant_fwd.hpp>
#include <yaul/variant/test_config.hpp>


// Check variant forward declarations
using yaul::variant;
using yaul::make_recursive_variant;

typedef variant<int> variant__int_t;
typedef variant<int,float> variant__int_float_t;
typedef make_recursive_variant<int> make_recursive_variant__int_t;
typedef make_recursive_variant<int,float> make_recursive_variant__int_float_t;

int main()
{
  return YAUL_VARIANT_TEST_EXIT_CODE;
}
