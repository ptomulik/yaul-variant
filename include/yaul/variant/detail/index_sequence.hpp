// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

// yaul/variant/detail/index_sequence.hpp

/** // doc: yaul/variant/detail/index_sequence.hpp {{{
 * \file yaul/variant/detail/index_sequence.hpp
 * \todo Write documentation
 */ // }}}
#ifndef YAUL_VARIANT_DETAIL_INDEX_SEQUENCE_HPP
#define YAUL_VARIANT_DETAIL_INDEX_SEQUENCE_HPP

#include <cstddef>

// C++11 has no std::index_sequence.

namespace yaul { namespace detail { namespace variant {
/** // doc: index_sequence {{{
 * \brief Sequence of indices
 */ // }}}
template <std::size_t... Ints>
struct index_sequence
{
  static constexpr std::size_t size() { return sizeof...(Ints); }
};

template <typename Seq, std::size_t I>
struct index_sequence_append;

template <std::size_t I, std::size_t... Ints>
struct index_sequence_append< index_sequence<Ints...>, I >
{
  typedef index_sequence<Ints..., I> type;
};

/** // doc: make_index_sequence {{{
 * \brief Makes index_sequence<0,...,N-1>
 */ // }}}
template <std::size_t N, std::size_t I = 0ul, typename Seq = index_sequence<> >
struct make_index_sequence
  : make_index_sequence<N-1, I+1, typename index_sequence_append<Seq, I>::type>
{
};

template <std::size_t I, typename Seq>
struct make_index_sequence<0, I, Seq>
{
  typedef Seq type;
};

} } } // end namespace yaul::detail::variant

#endif /* YAUL_VARIANT_DETAIL_INDEX_SEQUENCE_HPP */
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
