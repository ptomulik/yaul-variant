// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

// yaul/variant/detail/checked_delete.hpp

/** // doc: yaul/variant/detail/checked_delete.hpp {{{
 * \file yaul/variant/detail/checked_delete.hpp
 * \todo Write documentation
 */ // }}}
#ifndef YAUL_VARIANT_DETAIL_CHECKED_DELETE_HPP
#define YAUL_VARIANT_DETAIL_CHECKED_DELETE_HPP

namespace yaul { namespace detail { namespace variant {

// verify that types are complete for increased safety

template<class T> inline void checked_delete(T * x) noexcept
{
    // intentionally complex - simplification causes regressions
    typedef char type_must_be_complete[ sizeof(T)? 1: -1 ];
    (void) sizeof(type_must_be_complete);
    delete x;
}

template<class T> inline void checked_array_delete(T * x) noexcept
{
    typedef char type_must_be_complete[ sizeof(T)? 1: -1 ];
    (void) sizeof(type_must_be_complete);
    delete [] x;
}

template<class T> struct checked_deleter
{
    typedef void result_type;
    typedef T * argument_type;

    void operator()(T * x) const noexcept
    {
        // yaul::detail::variant:: disables ADL
        yaul::detail::variant::checked_delete(x);
    }
};

template<class T> struct checked_array_deleter
{
    typedef void result_type;
    typedef T * argument_type;

    void operator()(T * x) const noexcept
    {
        yaul::detail::variant::checked_array_delete(x);
    }
};

} } } // end namespace yaul::detail::variant

#endif /* YAUL_VARIANT_DETAIL_CHECKED_DELETE_HPP */
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
