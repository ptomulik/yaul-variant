// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

// yaul/variant/detail/apply_visitor_binary.hpp

/** // doc: yaul/variant/detail/apply_visitor_binary.hpp {{{
 * \file yaul/variant/detail/apply_visitor_binary.hpp
 * \todo Write documentation
 */ // }}}
#ifndef YAUL_VARIANT_DETAIL_APPLY_VISITOR_BINARY_HPP
#define YAUL_VARIANT_DETAIL_APPLY_VISITOR_BINARY_HPP

#include <yaul/variant/detail/apply_visitor_unary.hpp>
#include <type_traits>

namespace yaul { namespace detail { namespace variant {
template< typename Visitor, typename Arg2 >
  class binary_visitor_unwrapper
  {
    static_assert(std::is_reference<Visitor>::value, "Visitor is not a reference");
    static_assert(std::is_reference<Arg2>::value, "Arg2 is not a reference");
    Visitor visitor_;
    Arg2 x2_;
  public:
    typedef typename std::remove_reference<Visitor>::type::result_type result_type;

    binary_visitor_unwrapper() = delete;
    binary_visitor_unwrapper(binary_visitor_unwrapper&) = delete;
    binary_visitor_unwrapper(binary_visitor_unwrapper const&) = delete;
    binary_visitor_unwrapper(binary_visitor_unwrapper&&) = default;
    binary_visitor_unwrapper& operator=(binary_visitor_unwrapper const&) = delete;

    binary_visitor_unwrapper(Visitor visitor, Arg2 x2) noexcept
      : visitor_(std::forward<Visitor>(visitor)), x2_(std::forward<Arg2>(x2))
    { }

    template< typename T1 >
    result_type operator()(T1&& x1) const
        noexcept(noexcept(result_type(
              std::forward<Visitor>(visitor_)(
                std::forward<T1>(x1),
                std::forward<Arg2>(x2_)
              )
        )))
    { 
      return  std::forward<Visitor>(visitor_)(
                std::forward<T1>(x1),
                std::forward<Arg2>(x2_)
              );
    }
  };

template< typename Visitor, typename Arg2 >
constexpr binary_visitor_unwrapper<Visitor&&, Arg2&&>
binary_visitor_unwrap(Visitor&& visitor, Arg2&& arg) noexcept
{
  return binary_visitor_unwrapper<Visitor&&,Arg2&&>(
      std::forward<Visitor>(visitor)
    , std::forward<Arg2>(arg)
  );
}

template< typename Visitor, typename Visitable1 >
  class binary_visitor_wrapper
  {
    static_assert(std::is_reference<Visitor>::value, "Visitor is not a reference");
    static_assert(std::is_reference<Visitor>::value, "Visitable1 is not a reference");
    Visitor visitor_;
    Visitable1 v1_;
  public:

    typedef typename std::remove_reference<Visitor>::type::result_type result_type;

    binary_visitor_wrapper() = delete;
    binary_visitor_wrapper(binary_visitor_wrapper&) = delete;
    binary_visitor_wrapper(binary_visitor_wrapper const&) = delete;
    binary_visitor_wrapper(binary_visitor_wrapper&&) = default;
    binary_visitor_wrapper& operator=(binary_visitor_wrapper const&) = delete;

    // we pass references here, so it's noexcept
    constexpr binary_visitor_wrapper(Visitor visitor, Visitable1 v1) noexcept
      : visitor_(std::forward<Visitor>(visitor)),
        v1_(std::forward<Visitable1>(v1))
    { }

    template< typename T2 >
    result_type operator()(T2&& x2) const
        noexcept(noexcept(result_type(
              apply_visitor(
                binary_visitor_unwrap(
                  std::forward<Visitor>(visitor_),
                  std::forward<T2>(x2)
                ),
                std::forward<Visitable1>(v1_)
              )
        )))
    {
      return  apply_visitor(
                binary_visitor_unwrap(
                  std::forward<Visitor>(visitor_),
                  std::forward<T2>(x2)
                ),
                std::forward<Visitable1>(v1_)
              );
    }
  };

template< typename Visitor, typename Visitable >
constexpr binary_visitor_wrapper<Visitor&&, Visitable&&>
binary_visitor_wrap(Visitor&& visitor, Visitable&& visitable) noexcept
{
  // we only pass references to the noexcept constructor, so we're noexcept as well
  return binary_visitor_wrapper<Visitor&&,Visitable&&>(
      std::forward<Visitor>(visitor)
    , std::forward<Visitable>(visitable)
  );
}

} } } // end namespace yaul::detail::variant

namespace yaul {
/** \ingroup FixMe FIXME:
 * @{ */
/** // doc: apply_visitor {{{
 * \todo Write documentation
 */ // }}}
template< typename Visitor, typename Visitable1, typename Visitable2 >
typename std::remove_reference<Visitor>::type::result_type // FIXME: elaborate
apply_visitor(Visitor&& visitor, Visitable1&& v1, Visitable2&& v2)
    noexcept(noexcept(
          apply_visitor(
            detail::variant::binary_visitor_wrap(
                std::forward<Visitor>(visitor),
                std::forward<Visitable1>(v1)
            ),
            std::forward<Visitable2>(v2)
          )
    ))
{
  return  apply_visitor(
            detail::variant::binary_visitor_wrap(
                std::forward<Visitor>(visitor),
                std::forward<Visitable1>(v1)
            ),
            std::forward<Visitable2>(v2)
          );
}
/** @{ */
} // end namespace yaul

#endif /* YAUL_VARIANT_DETAIL_APPLY_VISITOR_BINARY_HPP */
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
