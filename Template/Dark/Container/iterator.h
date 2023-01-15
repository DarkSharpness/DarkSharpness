#ifndef _DARK_ITERATOR_H_
#define _DARK_ITERATOR_H_

#include "../include/basic.h"

namespace dark {

/* Namespace for Random Access Iterators.  */
namespace RandomAccess {


template <class T>
class iterator {
  protected:
    T *pointer;

  public:
    ~iterator() = default;
    iterator(T *rhs = nullptr) : pointer(rhs) {}
    iterator &operator = (const iterator &rhs) = default;
    /* Return the inner pointer. */
    T *base() const { return pointer; }

    iterator &operator ++ (void) { ++pointer; return *this; }
    iterator &operator -- (void) { --pointer; return *this; }

    iterator operator ++ (int) { return iterator(pointer++); }
    iterator operator -- (int) { return iterator(pointer--); }

    iterator &operator += (size_t __n) { pointer += __n; return *this; }
    iterator &operator -= (size_t __n) { pointer -= __n; return *this; }

    iterator operator - (size_t __n) const { return iterator(pointer - __n); }
    iterator operator + (size_t __n) const { return iterator(pointer + __n); }


    friend iterator operator + (size_t __n,const iterator &rhs) {
        return iterator(__n + rhs.pointer);
    }
    friend size_t operator - (const iterator &lhs,const iterator &rhs) {
        return rhs.pointer - lhs.pointer;
    }
    friend bool operator == (const iterator &lhs,const iterator &rhs) {
        return lhs.pointer == rhs.pointer;
    }
    friend bool operator != (const iterator &lhs,const iterator &rhs) {
        return lhs.pointer != rhs.pointer;
    }


    T &operator * (void) const { return *pointer; } 
    T *operator ->(void) const { return  pointer; }

};

template <class T>
class const_iterator {
  protected:
    const T *pointer;

  public:
    ~const_iterator() = default;
    const_iterator(const T *rhs = nullptr)  : pointer(rhs) {}
    const_iterator(const iterator <T> &rhs) : pointer(rhs.base()) {}
    const_iterator &operator = (const const_iterator &rhs) = default;
    const_iterator &operator = (const iterator <T> &rhs) {
        pointer = rhs.base();
        return *this;
    }

    /* Return the inner pointer. */
    const T *base() const { return pointer; }

    const_iterator &operator ++ (void) { ++pointer; return *this; }
    const_iterator &operator -- (void) { --pointer; return *this; }

    const_iterator operator ++ (int) { return const_iterator(pointer++); }
    const_iterator operator -- (int) { return const_iterator(pointer--); }

    const_iterator &operator += (size_t __n) { pointer += __n; return *this; }
    const_iterator &operator -= (size_t __n) { pointer -= __n; return *this; }

    const_iterator operator - (size_t __n) const { return const_iterator(pointer - __n); }
    const_iterator operator + (size_t __n) const { return const_iterator(pointer + __n); }


    friend const_iterator operator + (size_t __n,const const_iterator &rhs) {
        return const_iterator(__n + rhs.pointer);
    }
    friend size_t operator - (const const_iterator &lhs,const const_iterator &rhs) {
        return rhs.pointer - lhs.pointer;
    }
    friend bool operator == (const const_iterator &lhs,const const_iterator &rhs) {
        return lhs.pointer == rhs.pointer;
    }
    friend bool operator != (const const_iterator &lhs,const const_iterator &rhs) {
        return lhs.pointer != rhs.pointer;
    }


    const T &operator * (void) const { return *pointer; } 
    const T *operator ->(void) const { return  pointer; }

};



}


}

#endif
