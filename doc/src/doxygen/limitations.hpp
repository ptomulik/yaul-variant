// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

// limitations.hpp

/**
 * \page page-limitations Limitations
 *
 * The library has the following known limitations
 *
 * <table>
 *  <caption>Limitations of Yaul.Variant</caption>
 *  <tr>
 *    <th>When</th>
 *    <th>Define</th>
 *    <th>Limitation</th>
 *    <th>Description</th>
 *  </tr>
 *  <tr>
 *    <td>gcc &le; 4.9.1 </td>
 *    <td>YAUL_VARIANT_NO_RREF_CV_QUALIFIED_MEMBERS</td>
 *    <td>rref-cv-qualified member functions are removed from some classes</td>
 *    <td>Due to [gcc bug 59296][GCC.59296], rref-qualified member functions,
 *        that is member functions declared as
 *
 *          - `R C::foo(...) &&;`
 *          - `R C::foo(...) const &&;`
 *          - `R C::foo(...) volatile &&;`
 *          - `R C::foo(...) const volatile &&;`
 *
 *        are ambiguous (actually any
 *        invocation such as `std::move(c).foo()`, where `c` is an instance of
 *        `C`, is ambiguous when more than one overload exists). For this reason,
 *        it was decided to conditionally remove overloads for `const &&`,
 *        `volatile &&`, and `const volatile&&` methods from affected classes
 *        across Yaul.Variant library, as well as all functions that refer
 *        them. This currently affects \ref yaul::recursive_wrapper.
 *    </td>
 *  </tr>
 * </table>
 * 
 *
 * <!-- Links -->
 * [GCC.59296]: https://gcc.gnu.org/bugzilla/show_bug.cgi?id=59296
 */

// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
