// Copyright (C) 2015, Pawel Tomulik <ptomulik@meil.pw.edu.pl>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

// yaul/variant/recursive_wrapper.hpp

/** // doc: yaul/variant/recursive_wrapper.hpp {{{
 * \file yaul/variant/recursive_wrapper.hpp
 * \brief Provides implementation of \ref yaul::recursive_wrapper "recursive_wrapper"
 */ // }}}
#ifndef YAUL_VARIANT_RECURSIVE_WRAPPER_HPP
#define YAUL_VARIANT_RECURSIVE_WRAPPER_HPP

#include <yaul/variant/recursive_wrapper_fwd.hpp>
#include <yaul/variant/detail/checked_delete.hpp>
#include <yaul/variant/config.hpp>
#include <type_traits>
#include <utility>

namespace yaul {

/** // doc: recursive_wrapper {{{
 * \brief Wrapper class for types that introduce recursion to variants
 *
 *
 * \tparam T A type wrapped with recursive_wrapper. It must be a non-reference,
 *           cv-unqualified, non-array type.
 *
 * \par Description
 * recursive_wrapper internally maintains an instance of type `T`. It owns its
 * own, dynamically allocated pointer to the internal instance of type `T`. The
 * recursive_wrapper is "semi-transparent" for Yaul.Variant API, i.e.
 * recursive_wrapper<T> is mostly handled as it would be `T`.
 *
 * \note  Use \ref yaul::wrap_recursive_wrapper to create new recursive wrappers.
 */ // }}}
template< typename T >
class recursive_wrapper
{
  static_assert(!std::is_reference<T>::value, "type T must not be a reference");
  static_assert(!std::is_array<T>::value, "type T must not be an array");
  static_assert(!std::is_const<T>::value, "type T must not be const-qualified");
  static_assert(!std::is_volatile<T>::value, "type T must be volatile-qualified");
public: // typedefs

  typedef T type;

private: // representation

    T* p_;

public: // structors

    // Ctors are not noexcept, because they allocate memory dynamically
    //! \brief Default constructor
    recursive_wrapper();

    // All (?) the versions of copy ctors are defined to dispatch preciselly
    // particular invocations to appropriate copy constructors of T
    //! \brief Copy constructor
    recursive_wrapper(recursive_wrapper& operand);
    //! \brief Copy constructor
    recursive_wrapper(recursive_wrapper const& operand);
    //! \brief Copy constructor
    recursive_wrapper(recursive_wrapper volatile& operand);
    //! \brief Copy constructor
    recursive_wrapper(recursive_wrapper const volatile& operand);
    //! \brief Copy constructor
    recursive_wrapper(recursive_wrapper&& operand);
#ifndef YAUL_VARIANT_NO_RRCV_QUALIFIED_FUNCTIONS
    //! \brief Copy constructor
    recursive_wrapper(recursive_wrapper const&& operand);
    //! \brief Copy constructor
    recursive_wrapper(recursive_wrapper volatile&& operand);
    //! \brief Copy constructor
    recursive_wrapper(recursive_wrapper const volatile&& operand);
#endif

    // All (?) the versions of init ctors are defined to dispatch preciselly
    // particular invocations to appropriate copy ctors of T
    //! \brief Initialising constructor
    recursive_wrapper(T& operand);
    //! \brief Initialising constructor
    recursive_wrapper(T const& operand);
    //! \brief Initialising constructor
    recursive_wrapper(T volatile& operand);
    //! \brief Initialising constructor
    recursive_wrapper(T const volatile& operand);
    //! \brief Initialising constructor
    recursive_wrapper(T&& operand);
    //! \brief Initialising constructor
    recursive_wrapper(T const&& operand);
    //! \brief Initialising constructor
    recursive_wrapper(T volatile&& operand);
    //! \brief Initialising constructor
    recursive_wrapper(T const volatile&& operand);

    //! \brief Destructor
    ~recursive_wrapper();

private: // helpers, for modifiers (below)

    void assign(T& rhs)
      noexcept(noexcept(std::declval<recursive_wrapper&>().get() = rhs));
    void assign(const T& rhs)
      noexcept(noexcept(std::declval<recursive_wrapper&>().get() = rhs));
    void assign(volatile T& rhs)
      noexcept(noexcept(std::declval<recursive_wrapper&>().get() = rhs));
    void assign(const volatile T& rhs)
      noexcept(noexcept(std::declval<recursive_wrapper&>().get() = rhs));
    void assign(T&& rhs)
      noexcept(noexcept(std::declval<recursive_wrapper&>().get() = std::move(rhs)));
    void assign(const T&& rhs)
      noexcept(noexcept(std::declval<recursive_wrapper&>().get() = std::move(rhs)));
    void assign(volatile T&& rhs)
      noexcept(noexcept(std::declval<recursive_wrapper&>().get() = std::move(rhs)));
    void assign(const volatile T&& rhs)
      noexcept(noexcept(std::declval<recursive_wrapper&>().get() = std::move(rhs)));

public: // modifiers
    //! \brief Assignment operator
    recursive_wrapper& operator=(recursive_wrapper& rhs)
      noexcept(noexcept(std::declval<recursive_wrapper&>().assign( rhs.get() )))
    {
      this->assign( rhs.get() );
      return *this;
    }

    //! \brief Assignment operator
    recursive_wrapper& operator=(recursive_wrapper const& rhs)
      noexcept(noexcept(std::declval<recursive_wrapper&>().assign( rhs.get() )))
    {
      this->assign( rhs.get() );
      return *this;
    }

    //! \brief Assignment operator
    recursive_wrapper& operator=(recursive_wrapper volatile& rhs)
      noexcept(noexcept(std::declval<recursive_wrapper&>().assign( rhs.get() )))
    {
      this->assign( rhs.get() );
      return *this;
    }

    //! \brief Assignment operator
    recursive_wrapper& operator=(recursive_wrapper const volatile& rhs)
      noexcept(noexcept(std::declval<recursive_wrapper&>().assign( rhs.get() )))
    {
      this->assign( rhs.get() );
      return *this;
    }

    //! \brief Assignment operator
    recursive_wrapper& operator=(recursive_wrapper&& rhs)
      noexcept(noexcept(std::declval<recursive_wrapper&>().assign( std::move(rhs).get() )))
    {
      this->assign( std::move(rhs).get() );
      return *this;
    }

#ifndef YAUL_VARIANT_NO_RRCV_QUALIFIED_FUNCTIONS
    //! \brief Assignment operator
    recursive_wrapper& operator=(recursive_wrapper const&& rhs)
      noexcept(noexcept(std::declval<recursive_wrapper&>().assign( std::move(rhs).get() )))
    {
      this->assign( std::move(rhs).get() );
      return *this;
    }

    //! \brief Assignment operator
    recursive_wrapper& operator=(recursive_wrapper volatile&& rhs)
      noexcept(noexcept(std::declval<recursive_wrapper&>().assign( std::move(rhs).get() )))
    {
      this->assign( std::move(rhs).get() );
      return *this;
    }

    //! \brief Assignment operator
    recursive_wrapper& operator=(recursive_wrapper const volatile&& rhs)
      noexcept(noexcept(std::declval<recursive_wrapper&>().assign( std::move(rhs).get() )))
    {
      this->assign( std::move(rhs).get() );
      return *this;
    }
#endif

    //! \brief Assignment operator
    recursive_wrapper& operator=(T& rhs)
      noexcept(noexcept(std::declval<recursive_wrapper&>().assign( rhs )))
    {
      this->assign( rhs );
      return *this;
    }

    //! \brief Assignment operator
    recursive_wrapper& operator=(T const& rhs)
      noexcept(noexcept(std::declval<recursive_wrapper&>().assign( rhs )))
    {
      this->assign( rhs );
      return *this;
    }

    //! \brief Assignment operator
    recursive_wrapper& operator=(T volatile& rhs)
      noexcept(noexcept(std::declval<recursive_wrapper&>().assign( rhs )))
    {
      this->assign( rhs );
      return *this;
    }

    //! \brief Assignment operator
    recursive_wrapper& operator=(T const volatile& rhs)
      noexcept(noexcept(std::declval<recursive_wrapper&>().assign( rhs )))
    {
      this->assign( rhs );
      return *this;
    }

    //! \brief Assignment operator
    recursive_wrapper& operator=(T&& rhs)
      noexcept(noexcept(std::declval<recursive_wrapper&>().assign(std::move( rhs ))))
    {
      this->assign(std::move(rhs));
      return *this;
    }

#ifndef YAUL_VARIANT_NO_RRCV_QUALIFIED_FUNCTIONS
    //! \brief Assignment operator
    recursive_wrapper& operator=(T const&& rhs)
      noexcept(noexcept(std::declval<recursive_wrapper&>().assign(std::move( rhs ))))
    {
      this->assign(std::move(rhs));
      return *this;
    }

    //! \brief Assignment operator
    recursive_wrapper& operator=(T volatile&& rhs)
      noexcept(noexcept(std::declval<recursive_wrapper&>().assign(std::move( rhs ))))
    {
      this->assign(std::move(rhs));
      return *this;
    }

    //! \brief Assignment operator
    recursive_wrapper& operator=(T const volatile&& rhs)
      noexcept(noexcept(std::declval<recursive_wrapper&>().assign(std::move( rhs ))))
    {
      this->assign(std::move(rhs));
      return *this;
    }
#endif

    //! \brief Swaps internal pointers to wrapped objects between `*this` and `operand`
    void swap(recursive_wrapper& operand) noexcept
    {
      T* temp = operand.p_;
      operand.p_ = p_;
      p_ = temp;
    }

public: // queries

    //! \brief Returns reference to the wrapped object
    T& get() & noexcept { return *p_; }
    //! \brief Returns reference to the wrapped object in `const` context
    const T& get() const & noexcept { return *p_; }
    //! \brief Returns reference to the wrapped object in `volatile` context
    volatile T& get() volatile & noexcept { return *p_; }
    //! \brief Returns reference to the wrapped object in `const volatile` context
    const volatile T& get() const volatile & noexcept { return *p_; }

    //! \brief Returns reference to the wrapped object in `&&` context
    T&& get() && noexcept { return std::move(*p_); }
#ifndef YAUL_VARIANT_NO_RRCV_QUALIFIED_FUNCTIONS
    //! \brief Returns reference to the wrapped object in `const &&` context
    const T&& get() const && noexcept { return std::move(*p_); }
    //! \brief Returns reference to the wrapped object in `volatile &&` context
    volatile T&& get() volatile && noexcept { return std::move(*p_); }
    //! \brief Returns reference to the wrapped object in `const volatile &&` context
    const volatile T&& get() const volatile && noexcept { return std::move(*p_); }
#endif
};


// Constructos, destructor and some methods are implemented out-of-line,
// because they require T to be complete-type (and T may refer recursivelly to
// recursive_wrapper<X>, for some type X).
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
recursive_wrapper<T>::recursive_wrapper(T& operand)
  : p_(new T( operand ))
{
}

template< typename T>
recursive_wrapper<T>::recursive_wrapper(T const& operand)
  : p_(new T( operand ))
{
}

template< typename T>
recursive_wrapper<T>::recursive_wrapper(T volatile& operand)
  : p_(new T( operand ))
{
}

template< typename T>
recursive_wrapper<T>::recursive_wrapper(T const volatile& operand)
  : p_(new T( operand ))
{
}

template< typename T >
recursive_wrapper<T>::recursive_wrapper(T&& operand)
  : p_(new T( std::move(operand) ))
{
}

template< typename T >
recursive_wrapper<T>::recursive_wrapper(T const&& operand)
  : p_(new T( std::move(operand) ))
{
}

template< typename T >
recursive_wrapper<T>::recursive_wrapper(T volatile&& operand)
  : p_(new T( std::move(operand) ))
{
}

template< typename T >
recursive_wrapper<T>::recursive_wrapper(T const volatile&& operand)
  : p_(new T( std::move(operand) ))
{
}

template< typename T>
recursive_wrapper<T>::recursive_wrapper(recursive_wrapper& operand)
  : p_(new T( operand.get() ))
{
}

template< typename T>
recursive_wrapper<T>::recursive_wrapper(recursive_wrapper const& operand)
  : p_(new T( operand.get() ))
{
}

template< typename T>
recursive_wrapper<T>::recursive_wrapper(recursive_wrapper volatile& operand)
  : p_(new T( operand.get() ))
{
}

template< typename T>
recursive_wrapper<T>::recursive_wrapper(recursive_wrapper const volatile& operand)
  : p_(new T( operand.get() ))
{
}

template< typename T>
recursive_wrapper<T>::recursive_wrapper(recursive_wrapper&& operand)
  : p_(new T( std::move(operand).get() ))
{
}

#ifndef YAUL_VARIANT_NO_RRCV_QUALIFIED_FUNCTIONS
template< typename T>
recursive_wrapper<T>::recursive_wrapper(recursive_wrapper const&& operand)
  : p_(new T( std::move(operand).get() ))
{
}

template< typename T>
recursive_wrapper<T>::recursive_wrapper(recursive_wrapper volatile&& operand)
  : p_(new T( std::move(operand).get() ))
{
}

template< typename T>
recursive_wrapper<T>::recursive_wrapper(recursive_wrapper const volatile&& operand)
  : p_(new T( std::move(operand).get() ))
{
}
#endif

//
// assign()
//
template< typename T >
void recursive_wrapper<T>::assign(T& rhs)
  noexcept(noexcept(std::declval<recursive_wrapper&>().get() = rhs))
{
  this->get() = rhs;
}

template< typename T >
void recursive_wrapper<T>::assign(T const& rhs)
  noexcept(noexcept(std::declval<recursive_wrapper&>().get() = rhs))
{
  this->get() = rhs;
}

template< typename T >
void recursive_wrapper<T>::assign(T volatile& rhs)
  noexcept(noexcept(std::declval<recursive_wrapper&>().get() = rhs))
{
  this->get() = rhs;
}

template< typename T >
void recursive_wrapper<T>::assign(T const volatile& rhs)
  noexcept(noexcept(std::declval<recursive_wrapper&>().get() = rhs))
{
  this->get() = rhs;
}

template< typename T >
void recursive_wrapper<T>::assign(T&& rhs)
  noexcept(noexcept(std::declval<recursive_wrapper&>().get() = std::move(rhs)))
{
  this->get() = std::move(rhs);
}

template< typename T >
void recursive_wrapper<T>::assign(T const&& rhs)
  noexcept(noexcept(std::declval<recursive_wrapper&>().get() = std::move(rhs)))
{
  this->get() = std::move(rhs);
}

template< typename T >
void recursive_wrapper<T>::assign(T volatile&& rhs)
  noexcept(noexcept(std::declval<recursive_wrapper&>().get() = std::move(rhs)))
{
  this->get() = std::move(rhs);
}

template< typename T >
void recursive_wrapper<T>::assign(T const volatile&& rhs)
  noexcept(noexcept(std::declval<recursive_wrapper&>().get() = std::move(rhs)))
{
  this->get() = std::move(rhs);
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
