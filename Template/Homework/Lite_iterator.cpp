#include <version>
// using diff_t = unsigned long long;

namespace dark {

using diff_t = std::ptrdiff_t; /* Global Variable. */

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


    iterator &operator += (diff_t __n) noexcept { pointer -= __n; return *this; }
    iterator &operator -= (diff_t __n) noexcept { pointer += __n; return *this; }
    friend iterator operator + (diff_t __n,iterator rhs) noexcept 
    { return iterator(rhs.pointer - __n); }
    friend iterator operator + (iterator lhs,diff_t __n) noexcept 
    { return iterator(lhs.pointer - __n); }
    friend iterator operator - (iterator lhs,diff_t __n) noexcept 
    { return iterator(lhs.pointer + __n); }
    friend diff_t operator - (iterator lhs,iterator rhs) noexcept 
    { return rhs.pointer - lhs.pointer; }


    friend bool operator == (iterator lhs,iterator rhs) noexcept 
    { return lhs.pointer == rhs.pointer; }
    friend bool operator != (iterator lhs,iterator rhs) noexcept 
    { return lhs.pointer != rhs.pointer; }


    T &operator * (void) const noexcept { return *pointer; } 
    T *operator ->(void) const noexcept { return  pointer; }
    T &operator [] (diff_t __n) const noexcept { return pointer[-__n]; }
};


template <class T>
class const_iterator {
  protected:
    const T *pointer;
    using Iterator = iterator <T>;

  public:
    ~const_iterator() = default;
    const_iterator(const T *rhs = nullptr)  noexcept : pointer(rhs) {}
    const_iterator(Iterator rhs) noexcept : pointer(rhs.base()) {}
    const_iterator &operator = (const const_iterator &rhs) noexcept = default;
    const_iterator &operator = (Iterator rhs) 
    { pointer = rhs.base(); return *this; }
    /* Return the inner pointer. */
    const T *base() const noexcept { return pointer; }

    const_iterator &operator ++ (void) noexcept { --pointer; return *this; }
    const_iterator &operator -- (void) noexcept { ++pointer; return *this; }
    const_iterator operator ++ (int) noexcept { return const_iterator(pointer--); }
    const_iterator operator -- (int) noexcept { return const_iterator(pointer++); }

    const_iterator &operator += (diff_t __n) noexcept
    { pointer -= __n; return *this; }
    const_iterator &operator -= (diff_t __n) noexcept
    { pointer += __n; return *this; }
    friend const_iterator operator + (const_iterator lhs,diff_t __n) noexcept
    { return const_iterator(lhs.pointer - __n); }
    friend const_iterator operator + (diff_t __n,const_iterator rhs) noexcept
    { return const_iterator(rhs.pointer - __n); }
    friend const_iterator operator - (const_iterator lhs,diff_t __n) noexcept
    { return const_iterator(lhs.pointer + __n); }

    friend diff_t operator - (const_iterator lhs,const_iterator rhs) noexcept
    { return rhs.base() - lhs.base(); }
    friend diff_t operator - (const_iterator lhs,Iterator rhs) noexcept
    { return rhs.base() - lhs.base(); }
    friend diff_t operator - (Iterator lhs,const_iterator rhs) noexcept
    { return rhs.base() - lhs.base; }

    friend bool operator == (const_iterator lhs,const_iterator rhs) noexcept 
    { return lhs.base() == rhs.base(); }
    friend bool operator == (Iterator lhs,const_iterator rhs) noexcept 
    { return lhs.base() == rhs.base(); }
    friend bool operator == (const_iterator lhs,Iterator rhs) noexcept 
    { return lhs.base() == rhs.base(); }
    friend bool operator != (const_iterator lhs,const_iterator rhs) noexcept 
    { return lhs.base() != rhs.base(); }
    friend bool operator != (Iterator lhs,const_iterator rhs) noexcept 
    { return lhs.base() != rhs.base(); }
    friend bool operator != (const_iterator lhs,Iterator rhs) noexcept 
    { return lhs.base() != rhs.base(); }


    const T &operator * (void) const { return *pointer; } 
    const T *operator ->(void) const { return  pointer; }
    const T &operator [] (diff_t __n) const { return pointer[-__n]; }
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


    iterator &operator += (diff_t __n) noexcept { pointer += __n; return *this; }
    iterator &operator -= (diff_t __n) noexcept { pointer -= __n; return *this; }
    friend iterator operator + (diff_t __n,iterator rhs) noexcept 
    { return iterator(rhs.pointer + __n); }
    friend iterator operator + (iterator lhs,diff_t __n) noexcept 
    { return iterator(lhs.pointer + __n); }
    friend iterator operator - (iterator lhs,diff_t __n) noexcept 
    { return iterator(lhs.pointer - __n); }
    friend diff_t operator - (iterator lhs,iterator rhs) noexcept 
    { return lhs.pointer - rhs.pointer; }


    friend bool operator == (iterator lhs,iterator rhs) noexcept 
    { return lhs.pointer == rhs.pointer; }
    friend bool operator != (iterator lhs,iterator rhs) noexcept 
    { return lhs.pointer != rhs.pointer; }


    T &operator * (void) const noexcept { return *pointer; } 
    T *operator ->(void) const noexcept { return  pointer; }
    T &operator [] (diff_t __n) const noexcept { return pointer[__n]; }
};


template <class T>
class const_iterator {
  protected:
    const T *pointer;
    using Iterator = iterator <T>;

  public:
    ~const_iterator() = default;
    const_iterator(const T *rhs = nullptr)  noexcept : pointer(rhs) {}
    const_iterator(Iterator rhs) noexcept : pointer(rhs.base()) {}
    const_iterator &operator = (const const_iterator &rhs) noexcept = default;
    const_iterator &operator = (Iterator rhs) 
    { pointer = rhs.base(); return *this; }
    /* Return the inner pointer. */
    const T *base() const noexcept { return pointer; }

    const_iterator &operator ++ (void) noexcept { ++pointer; return *this; }
    const_iterator &operator -- (void) noexcept { --pointer; return *this; }
    const_iterator operator ++ (int) noexcept { return const_iterator(pointer++); }
    const_iterator operator -- (int) noexcept { return const_iterator(pointer--); }

    const_iterator &operator += (diff_t __n) noexcept
    { pointer += __n; return *this; }
    const_iterator &operator -= (diff_t __n) noexcept
    { pointer -= __n; return *this; }
    friend const_iterator operator + (const_iterator lhs,diff_t __n) noexcept
    { return const_iterator(lhs.pointer + __n); }
    friend const_iterator operator + (diff_t __n,const_iterator rhs) noexcept
    { return const_iterator(rhs.pointer + __n); }
    friend const_iterator operator - (const_iterator lhs,diff_t __n) noexcept
    { return const_iterator(lhs.pointer - __n); }
    friend diff_t operator - (const_iterator lhs,const_iterator rhs) noexcept
    { return lhs.base() - rhs.base(); }
    friend diff_t operator - (const_iterator lhs,Iterator rhs) noexcept
    { return lhs.base() - rhs.base(); }
    friend diff_t operator - (Iterator lhs,const_iterator rhs) noexcept
    { return lhs.base() - rhs.base(); }

    friend bool operator == (const_iterator lhs,const_iterator rhs) noexcept 
    { return lhs.base() == rhs.base(); }
    friend bool operator == (Iterator lhs,const_iterator rhs) noexcept 
    { return lhs.base() == rhs.base(); }
    friend bool operator == (const_iterator lhs,Iterator rhs) noexcept 
    { return lhs.base() == rhs.base(); }
    friend bool operator != (const_iterator lhs,const_iterator rhs) noexcept 
    { return lhs.base() != rhs.base(); }
    friend bool operator != (Iterator lhs,const_iterator rhs) noexcept 
    { return lhs.base() != rhs.base(); }
    friend bool operator != (const_iterator lhs,Iterator rhs) noexcept 
    { return lhs.base() != rhs.base(); }


    const T &operator * (void) const { return *pointer; } 
    const T *operator ->(void) const { return  pointer; }
    const T &operator [] (diff_t __n) const { return pointer[__n]; }
};

}


}
