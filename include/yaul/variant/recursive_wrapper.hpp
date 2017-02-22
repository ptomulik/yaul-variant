// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

// yaul/variant/recursive_wrapper.hpp

/** // doc: yaul/variant/recursive_wrapper.hpp {{{
 * \file yaul/variant/recursive_wrapper.hpp
 * \todo Write documentation
 */ // }}}
#ifndef YAUL_VARIANT_RECURSIVE_WRAPPER_HPP
#define YAUL_VARIANT_RECURSIVE_WRAPPER_HPP

#include <yaul/variant/recursive_wrapper_fwd.hpp>
#include <yaul/variant/detail/checked_delete.hpp>
#include <utility>

namespace yaul {

template< typename T >
  class recursive_wrapper
  {
  public: // typedefs

    typedef T type;

  private: // representation

      T* p_;

  public: // structors

      ~recursive_wrapper();
      recursive_wrapper();

      recursive_wrapper(recursive_wrapper const& operand);
      recursive_wrapper(T const& operand);

      recursive_wrapper(recursive_wrapper&& operand);
      recursive_wrapper(T&& operand);

  private: // helpers, for modifiers (below)

      void assign(const T& rhs)
        noexcept(noexcept(std::declval<recursive_wrapper&>().get() = rhs));

  public: // modifiers

      recursive_wrapper& operator=(recursive_wrapper const& rhs)
        noexcept(noexcept(std::declval<recursive_wrapper&>().assign( rhs.get() )))
      {
        assign( rhs.get() );
        return *this;
      }

      recursive_wrapper& operator=(T const& rhs)
        noexcept(noexcept(std::declval<recursive_wrapper&>().assign( rhs )))
      {
        assign( rhs );
        return *this;
      }

      recursive_wrapper& operator=(recursive_wrapper&& rhs)
        noexcept(noexcept(std::declval<recursive_wrapper&>().assign( rhs.get() )))
      {
        assign( rhs.get() );
        return *this;
      }

      recursive_wrapper& operator=(T&& rhs)
        noexcept(noexcept(std::declval<recursive_wrapper&>().get() = std::move( rhs )))
      {
        get() = std::move( rhs );
        return *this;
      }

      void swap(recursive_wrapper& operand) noexcept
      {
        T* temp = operand.p_;
        operand.p_ = p_;
        p_ = temp;
      }

  public: // queries

      T& get() & noexcept { return *get_pointer(); }
      const T& get() const & noexcept { return *get_pointer(); }
      volatile T& get() volatile & noexcept { return *get_pointer(); }
      const volatile T& get() const volatile & noexcept { return *get_pointer(); }

      T&& get() && noexcept { return std::move(*get_pointer()); }
      const T&& get() const && noexcept { return std::move(*get_pointer()); }
      volatile T&& get() volatile && noexcept { return std::move(*get_pointer()); }
      const volatile T&& get() const volatile && noexcept { return std::move(*get_pointer()); }

      T* get_pointer() noexcept { return p_; }
      const T* get_pointer() const noexcept { return p_; }
      volatile T* get_pointer() volatile noexcept { return p_; }
      const volatile T* get_pointer() const volatile noexcept { return p_; }
  };

template< typename T >
recursive_wrapper<T>::~recursive_wrapper()
{
  detail::variant::checked_delete(p_);
}

template< typename T>
recursive_wrapper<T>::recursive_wrapper()
  : p_(new T)
{
}

template< typename T>
recursive_wrapper<T>::recursive_wrapper(recursive_wrapper const& operand)
  : p_(new T( operand.get() ))
{
}

template< typename T>
recursive_wrapper<T>::recursive_wrapper(T const& operand)
  : p_(new T( operand ))
{
}

template< typename T>
recursive_wrapper<T>::recursive_wrapper(recursive_wrapper&& operand)
  : p_(new T( std::move(operand.get()) ))
{
}

template< typename T >
recursive_wrapper<T>::recursive_wrapper(T&& operand)
  : p_(new T( std::move(operand) ))
{
}

template< typename T >
void recursive_wrapper<T>::assign(T const& rhs)
  noexcept(noexcept(std::declval<recursive_wrapper&>().get() = rhs))
{
  this->get() = rhs;
}

template< typename T >
inline void swap(recursive_wrapper<T>& lhs, recursive_wrapper<T>& rhs) noexcept
{
  lhs.swap(rhs);
}
} // end namespace yaul

#endif /* YAUL_VARIANT_RECURSIVE_WRAPPER_HPP */
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
