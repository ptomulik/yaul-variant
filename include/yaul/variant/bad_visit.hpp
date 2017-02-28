// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

// yaul/variant/bad_visit.hpp

/** // doc: yaul/variant/bad_visit.hpp {{{
 * \file yaul/variant/bad_visit.hpp
 * \brief Provides definition of \ref yaul::bad_visit "bad_visit" exception class.
 */ // }}}
#ifndef YAUL_VARIANT_BAD_VISIT_HPP
#define YAUL_VARIANT_BAD_VISIT_HPP

#include <exception>

namespace yaul {
/** // doc: bad_visit {{{
 * \brief Exception thrown when a visitation attempt via apply_visitor fails
 *        due to invalid visited subtype or contents.
 */ // }}}
struct bad_visit
  : std::exception
{
public: // std::exception interface
  virtual const char* what() const noexcept
  {
    return "yaul::bad_visit: "
           "failed visitation using yaul::apply_visitor";
  }
};
} // end namespace yaul

#endif /* YAUL_VARIANT_BAD_VISIT_HPP */
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
