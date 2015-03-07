// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

// yaul/variant/detail/multivisitors_cpp11_based.hpp

/** // doc: yaul/variant/detail/multivisitors_cpp11_based.hpp {{{
 * \file yaul/variant/detail/multivisitors_cpp11_based.hpp
 * \todo Write documentation
 */ // }}}
#ifndef YAUL_VARIANT_DETAIL_MULTIVISITORS_CPP11_BASED_HPP
#define YAUL_VARIANT_DETAIL_MULTIVISITORS_CPP11_BASED_HPP

#include <cstddef>
#include <tuple>
#include <utility>
#include <type_traits>

namespace yaul { namespace detail { namespace variant {
// C++14 has std::index_sequence stuff, but C++11 does not have it.
template< std::size_t... I > class index_sequence {};

template< std::size_t N, std::size_t... I >
  struct make_index_sequence_impl
    : make_index_sequence_impl<N-1, N-1, I...>
  { };

template< std::size_t... I >
  struct make_index_sequence_impl<0ul, I...>
  {
    typedef index_sequence<I...> type;
  };

template< std::size_t N >
using make_index_sequence = typename make_index_sequence_impl<N>::type;

template< typename... T >
using index_sequence_for = make_index_sequence<sizeof...(T)>;

template<typename... Tail, typename Tuple, std::size_t... I>
constexpr std::tuple<Tail...>
tuple_tail_fwd_impl(Tuple&& tpl, index_sequence<I...>) noexcept
{
  // 1. std::get<>() is noexcept, it returns a reference
  // 2. std::forward_as_tuple() takes references as arguments, no chance to
  //    call a possibly throwing constructor
  // 3. std::forward_as_tuple() is noexcept.
  //
  // so we are fine to state (as above) that we're noexcept as well
  return std::forward_as_tuple(std::get<I+1>(std::forward<Tuple>(tpl))...);
}

template<typename Head, typename... Tail>
constexpr std::tuple<Tail...>
tuple_tail_fwd(std::tuple<Head,Tail...>&& tpl) noexcept
{
  return tuple_tail_fwd_impl<Tail...>(std::move(tpl), index_sequence_for<Tail...>());
}

// only temporary (rvalue reference) objects of this type are usable
template< typename Visitor, typename Visitables, typename Values>
class multivisitor_rewrapper;

template< typename Visitor, typename... Visitables, typename... Values>
multivisitor_rewrapper< Visitor&&, std::tuple<Visitables...>, std::tuple<Values...> >
  make_multivisitor_rewrapper( Visitor&& visitor,
                               std::tuple<Visitables...>&& visitables,
                               std::tuple<Values...>&& values ) noexcept
{
  using visitables_t = std::tuple<Visitables...>;
  using values_t = std::tuple<Values...>;
  return multivisitor_rewrapper<Visitor&&, visitables_t, values_t>(
        std::forward<Visitor>(visitor),
        std::move(visitables),
        std::move(values)
  );
}

// only temporary (rvalue reference) objects of this type are usable
template< typename Visitor, typename... Visitables, typename... Values >
class multivisitor_rewrapper<Visitor, std::tuple<Visitables...>, std::tuple<Values...> >
{
  using visitor_t = Visitor;
  using visitables_t = std::tuple<Visitables...>;
  using values_t = std::tuple<Values...>;

  visitor_t visitor_;
  visitables_t visitables_;
  values_t values_;

  static_assert(std::is_reference<Visitor>::value, "non-reference type passed as Visitor");

public: // structors

  multivisitor_rewrapper(multivisitor_rewrapper&&) = default;

  explicit
  multivisitor_rewrapper(visitor_t v, visitables_t&& us, values_t&& xs) noexcept
    : visitor_(std::forward<visitor_t>(v)), visitables_(std::move(us)), values_(std::move(xs))
  { 
    static_assert(noexcept(visitor_t(std::forward<visitor_t>(v))), "");
    static_assert(noexcept(visitables_t(std::move(us))), "");
    static_assert(noexcept(values_t(std::move(xs))), "");
  }

public: // visitor interfaces
  typedef typename std::remove_reference<Visitor>::type::result_type result_type;

  template< typename T >
  result_type
  operator()(T&& v) &&
    noexcept(noexcept(
            apply_visitor(
                make_multivisitor_rewrapper(
                  std::forward<visitor_t>(std::declval<multivisitor_rewrapper&&>().visitor_),
                  tuple_tail_fwd(std::declval<multivisitor_rewrapper&&>().visitables_),
                  std::declval<std::tuple<Values...,T&&>&&>()
                )
                , std::get<0>(std::declval<multivisitor_rewrapper&&>().visitables_) // head element
            )
    ))
  {
    // we assume that this particular use of std::tuple_cat() will never throw,
    // as we concatenate tuples of references only, so there is no chance to
    // meet a constructor that would throw; that's why we replace
    // std::tuple_cat() in the noexcept specification above with the
    // declval<std::tuple<...>&&>()
    return apply_visitor(
        make_multivisitor_rewrapper(
          std::forward<visitor_t>(std::move(*this).visitor_),
          tuple_tail_fwd(std::move(*this).visitables_),
          std::tuple_cat(std::move(*this).values_, std::forward_as_tuple(std::forward<T>(v)))
        )
        , std::get<0>(std::move(*this).visitables_) // head element
    );
  }

  multivisitor_rewrapper& operator=(multivisitor_rewrapper const&) = delete;
};

// only temporary (rvalue reference) objects of this type are usable
template< typename Visitor, typename... Values >
class multivisitor_rewrapper<Visitor, std::tuple<>, std::tuple<Values...> >
{
  using visitor_t = Visitor;
  using visitables_t = std::tuple<>;
  using values_t = std::tuple<Values...>;

  visitor_t visitor_;
  values_t values_;

public:

  explicit
  multivisitor_rewrapper(visitor_t v, visitables_t&&, values_t&& xs ) noexcept
    : visitor_(std::forward<visitor_t>(v)), values_(std::move(xs))
  {
    static_assert(noexcept(visitor_t(std::forward<visitor_t>(v))), "");
    static_assert(noexcept(values_t(std::move(xs))), "");
  }

  multivisitor_rewrapper(multivisitor_rewrapper&&) = default;

public: // visitor interfaces
  typedef typename std::remove_reference<Visitor>::type::result_type result_type;

  template< class Tuple, std::size_t... I >
  result_type
  do_call(Tuple&& t, index_sequence<I...>) &&
      noexcept(noexcept(
            std::forward<visitor_t>(std::declval<multivisitor_rewrapper&&>().visitor_)(
              std::get<I>(std::forward<Tuple>(t))...
            )
      ))
  {
    return  std::forward<visitor_t>(std::move(*this).visitor_)(
              std::get<I>(std::forward<Tuple>(t))...
            );
  }

  template< typename T >
  result_type
  operator()(T&& v) &&
    noexcept(noexcept(
      std::declval<multivisitor_rewrapper&&>().do_call(
        std::declval<std::tuple<Values...,T&&>&&>(),
        make_index_sequence<1ul + sizeof...(Values)>()
      )
    ))
  {
    // we assume that this particular use of std::tuple_cat() will never throw,
    // as we concatenate tuples of references only, so there is no chance to
    // meet a constructor that would throw; that's why we replace
    // std::tuple_cat() in the noexcept specification above with the
    // declval<std::tuple<...>&&>()
    return std::move(*this).do_call(
        std::tuple_cat( std::move(*this).values_, std::forward_as_tuple(std::forward<T>(v)) ),
        make_index_sequence<1ul + sizeof...(Values)>()
    );
  }

};
} } } // end namespace yaul::detail::variant

#include <yaul/variant/detail/apply_visitor_unary.hpp>

namespace yaul {
/** // doc: apply_visitor() {{{
 * \todo Write documentation
 */ // }}}
template< typename Visitor, typename V1, typename V2, typename V3, typename... VN >
typename std::remove_reference<Visitor>::type::result_type /* OR decltype(auto) */
apply_visitor(Visitor&& visitor, V1&& v1, V2&& v2, V3&& v3, VN&&... vn)
  noexcept(noexcept(
          apply_visitor(
              detail::variant::make_multivisitor_rewrapper(
                  std::forward<Visitor>(visitor),
                  std::forward_as_tuple(  std::forward<V2>(v2),
                                          std::forward<V3>(v3),
                                          std::forward<VN>(vn)... ),
                  std::tuple<>()
              )
            , std::forward<V1>(v1)
          )
  ))
{
  return  apply_visitor(
              detail::variant::make_multivisitor_rewrapper(
                  std::forward<Visitor>(visitor),
                  std::forward_as_tuple(  std::forward<V2>(v2),
                                          std::forward<V3>(v3),
                                          std::forward<VN>(vn)... ),
                  std::tuple<>()
              )
            , std::forward<V1>(v1)
          );
}
} // end namespace yaul

#endif /* YAUL_VARIANT_DETAIL_MULTIVISITORS_CPP11_BASED_HPP */
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
