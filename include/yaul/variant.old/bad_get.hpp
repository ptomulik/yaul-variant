// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

// yaul/variant/bad_get.hpp

/** // doc: yaul/variant/bad_get.hpp {{{
 * \file yaul/variant/bad_get.hpp
 * \todo Write documentation
 */ // }}}
#ifndef YAUL_VARIANT_BAD_GET_HPP
#define YAUL_VARIANT_BAD_GET_HPP

#include <exception>

namespace boost {
/** // doc: bad_get {{{
 * \brief Exception thrown when a visitation attempt via apply_visitor fails
 *        due to invalid visited subtype or contents.
 */ // }}}
struct bad_get
  : std::exception
{
public: // std::exception interface
  virtual const char* what() const noexcept
  {
    return "yaul::bad_get: "
           "failed to get using yaul::get";
  }
};
} // end namespace boost

#endif /* YAUL_VARIANT_BAD_GET_HPP */
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
