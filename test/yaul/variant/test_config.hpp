// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

// yaul/variant/test_config.hpp

/** // doc: yaul/variant/test_config.hpp {{{
 * \file yaul/variant/test_config.hpp
 * \todo Write documentation
 */ // }}}
#ifndef YAUL_VARIANT_TEST_CONFIG_HPP
#define YAUL_VARIANT_TEST_CONFIG_HPP

#include <iostream>

namespace yaul { namespace variant_test {
static int exit_code = 0;
} } // end namespace yaul::variant_test

#define YAUL_VARIANT_TEST_EXIT_CODE yaul::variant_test::exit_code

#define YAUL_VARIANT_STRINGIZE(x) YAUL_VARIANT_STRINGIZE2(x)
#define YAUL_VARIANT_STRINGIZE2(x) #x

#define YAUL_VARIANT_PRINT_ERR_MSG(msg) \
  std::cerr << __FILE__ << ": " << YAUL_VARIANT_STRINGIZE(__LINE__) << ": " << msg << std::endl;

#define YAUL_VARIANT_CHECK(cond) \
  if(!(cond)) \
    { \
      YAUL_VARIANT_PRINT_ERR_MSG("expected (" << #cond << ") to be true"); \
      YAUL_VARIANT_TEST_EXIT_CODE = 1; \
    }

#define YAUL_VARIANT_CHECK_EQUALS(x, y) \
  if(!(x == y)) \
    { \
      YAUL_VARIANT_PRINT_ERR_MSG("expected (" << #x << "==" << #y << "), found (" << (x) << "!=" << (y) << ")"); \
      YAUL_VARIANT_TEST_EXIT_CODE = 1; \
    }

#define YAUL_VARIANT_CHECK_THROWS(code, except) \
    do { \
      bool f = false; \
      try { \
        { code; } \
      } catch(except const&) { \
        f = true; \
      } catch(...) { \
        YAUL_VARIANT_PRINT_ERR_MSG("expected " << #code  << " to throw " << #except << " but it thrown something else"); \
        YAUL_VARIANT_TEST_EXIT_CODE = 1; \
        f = true; \
      } \
      if(!f) { \
        YAUL_VARIANT_PRINT_ERR_MSG("expected " << #code << " to throw " << #except << " but nothing was thrown"); \
        YAUL_VARIANT_TEST_EXIT_CODE = 1; \
      } \
    } while(0);

#endif /* YAUL_VARIANT_TEST_CONFIG_HPP */
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
