// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

// tutorial.hpp

/**
 * \page page-tutorial Tutorial
 *
 * In this tutorial we will walk through examples, starting from simplest one
 * and progressing towards more advanced.
 *
 * \section sec-tutorial-1 Assigning values and querying variant
 *
 * The most basic operations on \ref yaul::variant include construction,
 * assignment and simple queries.
 *
 * \subsection sec-tutorial-1-which Value of which type is currently assigned?
 *
 * An instance of variant at any given time holds a value of one of its
 * alternative types. By invoking variant's method \c which() we may obtain the
 * index of currently assigned value type. For example, in
 * \ref yaul::variant<int,char>, \c int will be identified by index \c 0 and
 * \c char is identified by index \c 1.
 *
 * <b>Example</b>
 *
 * \snippet variant_simple_which.cpp Code
 *
 * <b>Output</b>
 *
 * \snippet variant_simple_which.cpp Output
 *
 * \subsection sec-tutorial-1-naive-get Getting currently assigned value with yaul::get()
 *
 * Getting currently assigned value is possible with the \ref yaul::get
 * function, although it's not the usual method. The following example
 * demonstrates possible use and typical pitfalls of this approach.
 *
 * <b>Example</b>
 * \snippet variant_simple_get.cpp Code
 *
 * <b>Output</b>
 * \snippet variant_simple_get.cpp Output
 *
 * \subsection sec-tutorial-1-dispatched-get Getting currently assigned value safely - dispatched yaul::get()
 *
 * As it may be seen from the previous example, to use \ref yaul::get() safely
 * we must know in advance which type is currently assigned to variant \c v.
 * A simple dispatching technique based on the index returned by the
 * \c which() may be used in some cases (however, it's still not the best
 * practice).
 *
 * <b>Example</b>
 * \snippet variant_dispatched_get.cpp Code
 *
 * <b>Output</b>
 * \snippet variant_dispatched_get.cpp Output
 *
 * \section sec-tutorial-2 Using visitors
 *
 * A recommended way of handling any value that may be assigned to a variant is
 * to create and use visitors. A visitor is a functor object derived from
 * \ref yaul::static_visitor<R>, where \c R is its return type. The visitor
 * shall define an overloaded \c operator() for each of variant's alternative
 * types. The operator shall perform desired operation on the provided value
 * (which is the current value taken from variant).
 *
 * \subsection sec-tutorial-2-simple-visitor Simple visitor that prints value
 *
 * The previous program may be rewritten using a simple visitor with overloaded
 * \c operator() as in the following example.
 *
 * <b>Example</b>
 * \snippet variant_simple_visitor.cpp Code
 *
 * <b>Output</b>
 * \snippet variant_simple_visitor.cpp Output
 *
 * \subsection sec-tutorial-2-template-visitor Simple visitor with template operator()
 *
 * In many cases, a template \c operator() may be used instead of implementing
 * overloaded function for each alternative type.
 *
 * <b>Example</b>
 * \snippet variant_simple_visitor_w_template.cpp Code
 *
 * <b>Output</b>
 * \snippet variant_simple_visitor_w_template.cpp Output
 *
 * \subsection sec-tutorial-2-binary-visitor Binary visitor
 *
 * A visitor may accept two values from two different variants. In the
 * following example a visitor called \c join converts its operands to
 * strings and joins them with a user-provided separator.
 *
 * <b>Example</b>
 * \snippet variant_simple_binary_visitor.cpp Code
 *
 * <b>Possible output</b>
 * \snippet variant_simple_binary_visitor.cpp Output
 *
 * \subsection sec-tutorial-2-multivisitor Multi-visitors
 *
 * A multi-visitor takes three or more arguments so it's possible to combine
 * three or more variants in a single invocation of \ref yaul::apply_visitor().
 * The previously shown binary visitor may be quickly extended to a
 * multi-visitor (example below). Note, the \ref yaul/variant/multivisitors.hpp
 * included.
 *
 * <b>Example</b>
 * \snippet variant_simple_multivisitor.cpp Code
 *
 * <b>Possible output</b>
 * \snippet variant_simple_multivisitor.cpp Output
 */

// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
