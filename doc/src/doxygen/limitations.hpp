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
 *    <th>Compile-time switch</th>
 *    <th>Limitation</th>
 *    <th>Rationale/Explanation</th>
 *  </tr>
 *  <tr>
 *    <td>gcc &lt; 4.9.1 </td>
 *    <td>`YAUL_VARIANT_NO_RRCV_QUALIFIED_FUNCTIONS`</td>
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
 *  <tr>
 *    <td>`__cplusplus < 201402L`</td>
 *    <td>`YAUL_VARIANT_NO_CONSTEXPR_ON_NONCONST_FUNCTIONS`</td>
 *    <td>constexpr specifier is removed from all non-const member functions</td>
 *    <td>Until C++14, `constexpr` implied `const` &mdash; also on non-static
 *        member functions. This led to situations, where for example
 *
 *          - `constexpr int& foo()&;` &nbsp;&nbsp; (1) and
 *          - `constexpr int const& foo() const&;` &nbsp;&nbsp; (2)
 *
 *        were treated as equivalent by a compiler &mdash; they couldn't exist
 *        in parallel (at least gcc didn't allow for this). In Yaul.Variant
 *        library it was decided to remove `constexpr` from all non-const
 *        member functions whenever using standard older than C++14. This
 *        means, instead of (1) and (2) we'll usually find couples such as the
 *        following
 *
 *          - `int& foo()&;` &nbsp; &nbsp; (1') and
 *          - `constexpr int const& foo() const&` &nbsp; &nbsp; (2')
 *
 *        as long, as C++ standard, older than C++14 is used. The issue
 *        currently affects \ref yaul::detail::variant::variadic_union_member.
 *    </td>
 *  </tr>
 *  <tr>
 *    <td>`__cplusplus < 201402L`</td>
 *    <td>`YAUL_VARIANT_NO_CONSTEXPR_ON_NONEMPTY_CTORS`</td>
 *    <td>constructors with non-empty bodies have removed `constexpr` specifier</td>
 *    <td>Before C++14 a constexpr constructor must have empty body. In
 *        Yaul.Variant it was decided to remove `constexpr` specifier from all
 *        possibly-constexpr constructors having non-empty body whenever it
 *        would cause compile errors.
 *    </td>
 *  </tr>
 *  <tr>
 *    <td>`__cplusplus < 201402L` or `defined(__clang__)`</td>
 *    <td>`YAUL_VARIANT_NO_CONSTEXPR_ON_FUNCTIONS_WITH_PLACEMENT_NEW`</td>
 *    <td>functions which use placement new have removed `constexpr` specifier</td>
 *    <td>Since C++14, placement new is allowed in constexpr functions.
 *        However, some compilers (all clang versions, as for the time of this
 *        writting - 2017.03.06) do not obey this rule yet. Before C++14
 *        expressions involving `new` were unconditionally banned from constexpr
 *        functions. In Yaul.Variant it was decided to remove `constexpr`
 *        specifier from possibly-constexpr functions using placement new
 *        expression, whenever it would generate compilation errors.
 *    </td>
 *  </tr>
 *  <tr>
 *    <td>gcc < 8 or clang < 3.6.1</td>
 *    <td>`YAUL_VARIANT_NO_CONSTEXPR_ON_FUNCTIONS_IN_NONLITERAL_CLASS`</td>
 *    <td>`constexpr` specifier is removed from all member functions of non-literal class</td>
 *    <td>Until C++14, constexpr functions couldn't appear as a members of
 *        non-literal classes. This was reported in
 *        [C++ Standard Defect Report 1684][CWGDR.1684] and was relaxed in C++14.
 *        In Yaul.Variant it was decided to remove `constexpr` specifier from
 *        all possibly-constexpr member functions of non-literal classes,
 *        whenever it could cause a compile error.
 *    </td>
 *  </tr>
 * </table>
 *
 *
 * <!-- Links -->
 * [GCC.59296]: https://gcc.gnu.org/bugzilla/show_bug.cgi?id=59296
 * [CWGDR.1684]: http://www.open-std.org/jtc1/sc22/wg21/docs/cwg_defects.html#1684
 */

// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
