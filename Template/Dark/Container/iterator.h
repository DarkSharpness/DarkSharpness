#ifndef _DARK_ITERATOR_H_
#define _DARK_ITERATOR_H_

#include "../include/basic.h"

namespace dark {

/* Reverse iterators. */
namespace ReverseRandomAccess {

template <class T>
class iterator {
  protected:
    T *pointer;

  public:
    ~iterator() noexcept = default;
    iterator(T *rhs = nullptr) noexcept : pointer(rhs)  {}
    iterator &operator = (const iterator &rhs) noexcept = default;
    /* Return the inner pointer. */
    T *base() const noexcept { return pointer; }


    iterator &operator ++ (void) noexcept { --pointer; return *this; }
    iterator &operator -- (void) noexcept { ++pointer; return *this; }
    iterator operator ++ (int) noexcept { return iterator(pointer--); }
    iterator operator -- (int) noexcept { return iterator(pointer++); }


    iterator &operator += (size_t __n) noexcept { pointer -= __n; return *this; }
    iterator &operator -= (size_t __n) noexcept { pointer += __n; return *this; }
    friend iterator operator + (size_t __n,iterator rhs) noexcept 
    { return iterator(rhs.pointer - __n); }
    friend iterator operator + (iterator lhs,size_t __n) noexcept 
    { return iterator(lhs.pointer - __n); }
    friend iterator operator - (iterator lhs,size_t __n) noexcept 
    { return iterator(lhs.pointer + __n); }
    friend size_t operator - (iterator lhs,iterator rhs) noexcept 
    { return rhs.pointer - lhs.pointer; }


    friend bool operator == (iterator lhs,iterator rhs) noexcept 
    { return lhs.pointer == rhs.pointer; }
    friend bool operator != (iterator lhs,iterator rhs) noexcept 
    { return lhs.pointer != rhs.pointer; }


    T &operator * (void) const noexcept { return *pointer; } 
    T *operator ->(void) const noexcept { return  pointer; }
    T &operator [] (size_t __n) const noexcept { return pointer[-__n]; }
};


template <class T>
class const_iterator {
  protected:
    const T *pointer;
    using iterator = iterator <T>;

  public:
    ~const_iterator() = default;
    const_iterator(const T *rhs = nullptr)  noexcept : pointer(rhs) {}
    const_iterator(iterator rhs) noexcept : pointer(rhs.base()) {}
    const_iterator &operator = (const const_iterator &rhs) noexcept = default;
    const_iterator &operator = (iterator rhs) 
    { pointer = rhs.base(); return *this; }
    /* Return the inner pointer. */
    const T *base() const noexcept { return pointer; }

    const_iterator &operator ++ (void) noexcept { --pointer; return *this; }
    const_iterator &operator -- (void) noexcept { ++pointer; return *this; }
    const_iterator operator ++ (int) noexcept { return const_iterator(pointer--); }
    const_iterator operator -- (int) noexcept { return const_iterator(pointer++); }

    const_iterator &operator += (size_t __n) noexcept
    { pointer -= __n; return *this; }
    const_iterator &operator -= (size_t __n) noexcept
    { pointer += __n; return *this; }
    friend const_iterator operator + (const_iterator lhs,size_t __n) noexcept
    { return const_iterator(lhs.pointer - __n); }
    friend const_iterator operator + (size_t __n,const_iterator rhs) noexcept
    { return const_iterator(rhs.pointer - __n); }
    friend const_iterator operator - (const_iterator lhs,size_t __n) noexcept
    { return const_iterator(lhs.pointer + __n); }

    friend size_t operator - (const_iterator lhs,const_iterator rhs) noexcept
    { return rhs.base() - lhs.base(); }
    friend size_t operator - (const_iterator lhs,iterator rhs) noexcept
    { return rhs.base() - lhs.base(); }
    friend size_t operator - (iterator lhs,const_iterator rhs) noexcept
    { return rhs.base() - lhs.base; }

    friend bool operator == (const_iterator lhs,const_iterator rhs) noexcept 
    { return lhs.base() == rhs.base(); }
    friend bool operator == (iterator lhs,const_iterator rhs) noexcept 
    { return lhs.base() == rhs.base(); }
    friend bool operator == (const_iterator lhs,iterator rhs) noexcept 
    { return lhs.base() == rhs.base(); }
    friend bool operator != (const_iterator lhs,const_iterator rhs) noexcept 
    { return lhs.base() != rhs.base(); }
    friend bool operator != (iterator lhs,const_iterator rhs) noexcept 
    { return lhs.base() != rhs.base(); }
    friend bool operator != (const_iterator lhs,iterator rhs) noexcept 
    { return lhs.base() != rhs.base(); }


    const T &operator * (void) const { return *pointer; } 
    const T *operator ->(void) const { return  pointer; }
    const T &operator [] (size_t __n) const { return pointer[-__n]; }
};


}


/* Namespace for Random Access Iterators.  */
namespace RandomAccess {

/* Reverse iterator type. */
template <class T>
using reverse_iterator = ReverseRandomAccess::iterator <T>;
/* Const reverse iterator type. */
template <class T>
using const_reverse_iterator = ReverseRandomAccess::const_iterator <T>;

template <class T>
class iterator {
  protected:
    T *pointer;

  public:
    ~iterator() noexcept = default;
    iterator(T *rhs = nullptr) noexcept : pointer(rhs)  {}
    iterator &operator = (const iterator &rhs) noexcept = default;
    /* Return the inner pointer. */
    T *base() const noexcept { return pointer; }


    iterator &operator ++ (void) noexcept { ++pointer; return *this; }
    iterator &operator -- (void) noexcept { --pointer; return *this; }
    iterator operator ++ (int) noexcept { return iterator(pointer++); }
    iterator operator -- (int) noexcept { return iterator(pointer--); }


    iterator &operator += (size_t __n) noexcept { pointer += __n; return *this; }
    iterator &operator -= (size_t __n) noexcept { pointer -= __n; return *this; }
    friend iterator operator + (size_t __n,iterator rhs) noexcept 
    { return iterator(rhs.pointer + __n); }
    friend iterator operator + (iterator lhs,size_t __n) noexcept 
    { return iterator(lhs.pointer + __n); }
    friend iterator operator - (iterator lhs,size_t __n) noexcept 
    { return iterator(lhs.pointer - __n); }
    friend size_t operator - (iterator lhs,iterator rhs) noexcept 
    { return lhs.pointer - rhs.pointer; }


    friend bool operator == (iterator lhs,iterator rhs) noexcept 
    { return lhs.pointer == rhs.pointer; }
    friend bool operator != (iterator lhs,iterator rhs) noexcept 
    { return lhs.pointer != rhs.pointer; }


    T &operator * (void) const noexcept { return *pointer; } 
    T *operator ->(void) const noexcept { return  pointer; }
    T &operator [] (size_t __n) const noexcept { return pointer[__n]; }
};


template <class T>
class const_iterator {
  protected:
    const T *pointer;
    using iterator = iterator <T>;

  public:
    ~const_iterator() = default;
    const_iterator(const T *rhs = nullptr)  noexcept : pointer(rhs) {}
    const_iterator(iterator rhs) noexcept : pointer(rhs.base()) {}
    const_iterator &operator = (const const_iterator &rhs) noexcept = default;
    const_iterator &operator = (iterator rhs) 
    { pointer = rhs.base(); return *this; }
    /* Return the inner pointer. */
    const T *base() const noexcept { return pointer; }

    const_iterator &operator ++ (void) noexcept { ++pointer; return *this; }
    const_iterator &operator -- (void) noexcept { --pointer; return *this; }
    const_iterator operator ++ (int) noexcept { return const_iterator(pointer++); }
    const_iterator operator -- (int) noexcept { return const_iterator(pointer--); }

    const_iterator &operator += (size_t __n) noexcept
    { pointer += __n; return *this; }
    const_iterator &operator -= (size_t __n) noexcept
    { pointer -= __n; return *this; }
    friend const_iterator operator + (const_iterator lhs,size_t __n) noexcept
    { return const_iterator(lhs.pointer + __n); }
    friend const_iterator operator + (size_t __n,const_iterator rhs) noexcept
    { return const_iterator(rhs.pointer + __n); }
    friend const_iterator operator - (const_iterator lhs,size_t __n) noexcept
    { return const_iterator(lhs.pointer - __n); }
    friend size_t operator - (const_iterator lhs,const_iterator rhs) noexcept
    { return lhs.base() - rhs.base(); }
    friend size_t operator - (const_iterator lhs,iterator rhs) noexcept
    { return lhs.base() - rhs.base(); }
    friend size_t operator - (iterator lhs,const_iterator rhs) noexcept
    { return lhs.base() - rhs.base(); }

    friend bool operator == (const_iterator lhs,const_iterator rhs) noexcept 
    { return lhs.base() == rhs.base(); }
    friend bool operator == (iterator lhs,const_iterator rhs) noexcept 
    { return lhs.base() == rhs.base(); }
    friend bool operator == (const_iterator lhs,iterator rhs) noexcept 
    { return lhs.base() == rhs.base(); }
    friend bool operator != (const_iterator lhs,const_iterator rhs) noexcept 
    { return lhs.base() != rhs.base(); }
    friend bool operator != (iterator lhs,const_iterator rhs) noexcept 
    { return lhs.base() != rhs.base(); }
    friend bool operator != (const_iterator lhs,iterator rhs) noexcept 
    { return lhs.base() != rhs.base(); }


    const T &operator * (void) const { return *pointer; } 
    const T *operator ->(void) const { return  pointer; }
    const T &operator [] (size_t __n) const { return pointer[__n]; }
};

}


}

#endif
