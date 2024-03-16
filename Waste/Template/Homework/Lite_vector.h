#ifndef _DARK_DYNAMIC_ARRAY_H_
#define _DARK_DYNAMIC_ARRAY_H_


#include "exceptions.hpp"
// #include "iterator.h"
#ifndef _DARK_ITERATOR_H_
#define _DARK_ITERATOR_H_

#include "exceptions.hpp"
#include <version>
#include <type_traits>
#include <cstddef>

/* Function part. */
namespace dark::RandomAccess {

/* Difference Type */
using diff_t = std::ptrdiff_t;

/* Advance forward. */
template <class T>
inline void advance_ptr(T *&__p,std::true_type)
noexcept { ++__p; }

/* Advance backward. */
template <class T>
inline void advance_ptr(T *&__p,std::false_type)
noexcept { --__p; }

/* Advance forward __n steps. */
template <class T>
inline void advance_ptr(T *&__p,diff_t __n,std::true_type)
noexcept { __p += __n; }

/* Advance backward __n steps. */
template <class T>
inline void advance_ptr(T *&__p,diff_t __n,std::false_type)
noexcept { __p -= __n; }

/* Normal distancing 2 pointers. */
template <class T>
inline diff_t distance_ptr(const T *lhs,const T *rhs,std::true_type) 
noexcept { return lhs - rhs; }

/* Reverse distancing 2 pointers. */
template <class T>
inline diff_t distance_ptr(const T *lhs,const T *rhs,std::false_type) 
noexcept { return rhs - lhs; }



/**
 * @brief Advance toward given diretion.
 * 
 * @tparam dir || 0 if backward || 1 if forward ||
 * @param __p Pointer to advance.
 * @return The new pointer.
 */
template <bool dir,class T>
inline void advance(T *&__p) noexcept
{ return advance_ptr(__p,std::bool_constant <dir>()); }

/**
 * @brief Advance toward diretion by __n steps.
 * 
 * @tparam dir || 0 if backward || 1 if forward ||
 * @param __p Pointer to advance.
 * @param __n The distance to advance.
 * @return The new pointer.
 */
template <bool dir,class T>
inline void advance(T *&__p,diff_t __n) noexcept
{ return advance_ptr(__p,__n,std::bool_constant <dir>()); }

template <bool dir,class T>
inline diff_t distance(const T *lhs,const T *rhs) noexcept
{ return distance_ptr(lhs,rhs,std::bool_constant <dir>()); }



}

/* Class part. */
namespace dark::RandomAccess {

template <class T,bool is_const,bool dir>
class iterator_base {
    using difference_type = std::ptrdiff_t;
    using U = std::conditional_t <is_const,const T,T>; 
    using value_type = U;
    using pointer    = U *;
    using reference  = U &;
    using iterator_category = std::output_iterator_tag;

  private:
    pointer ptr;
    const void *src;
  public:
    iterator_base(pointer __p = nullptr,const void *__s = nullptr) 
    noexcept : ptr(__p) , src(__s) {}

    iterator_base(const iterator_base <T,false,dir> &rhs)
    noexcept : ptr(rhs.ptr) , src(rhs.src) {}
    
    iterator_base &operator = (const iterator_base <T,false,dir> &rhs) 
    noexcept { ptr = rhs.ptr , src = rhs.src; return *this; }

    pointer base()       const noexcept { return ptr; }
    const void *source() const noexcept { return src; }

    iterator_base &operator ++ (void) noexcept
    { advance <dir> (ptr);  return *this; }

    iterator_base &operator -- (void) noexcept 
    { advance <!dir> (ptr); return *this; }

    iterator_base &operator += (diff_t __n) noexcept 
    { advance <dir> (ptr,__n);  return *this; }

    iterator_base &operator -= (diff_t __n) noexcept
    { advance <!dir> (ptr,__n); return *this; }

    /* Non-memeber function part.*/

    friend iterator_base operator ++ (iterator_base &lhs,int)  
    noexcept { iterator_base tmp = lhs; ++lhs; return tmp; }
    friend iterator_base operator -- (iterator_base &lhs,int)  
    noexcept { iterator_base tmp = lhs; --lhs; return tmp; }

    friend iterator_base operator + (iterator_base lhs,diff_t __n) 
    noexcept { return lhs += __n; }

    friend iterator_base operator + (diff_t __n,iterator_base rhs) 
    noexcept { return rhs += __n; }

    friend iterator_base operator - (iterator_base lhs,diff_t __n)
    noexcept { return lhs -= __n; }

    U &operator * (void) const { return *ptr; }
    U *operator ->(void) const { return  ptr; }

    /**
     * @brief Return reference to element __n steps in the direction.
     * 
     * @param __n The distance of targeted element.
     */
    U &operator [](diff_t __n) const {
        pointer tmp = ptr;
        advance <dir> (tmp,__n);
        return *tmp;
    }
};

/* Some other global functions. */

template <class T,bool k1,bool k2,bool dir>
diff_t operator - (const iterator_base <T,k1,dir> &lhs,
                   const iterator_base <T,k2,dir> &rhs) {
    if(lhs.source() != rhs.source) throw sjtu::invalid_iterator();
    return distance <dir> (lhs.base(),rhs.base());
}

template <class T,bool k1,bool k2,bool dir>
bool operator == (const iterator_base <T,k1,dir> &lhs,
                  const iterator_base <T,k2,dir> &rhs) {
    return lhs.base() == rhs.base();
}

template <class T,bool k1,bool k2,bool dir>
bool operator != (const iterator_base <T,k1,dir> &lhs,
                  const iterator_base <T,k2,dir> &rhs) {
    return lhs.base() != rhs.base();
}

/* Namespace for Random Access Iterators.  */

}

#endif


#include <iostream>
#include <climits>
#include <cstddef>

/* Third party function for mutliple push_back. */
namespace dark {

inline unsigned int LOG2(unsigned x){
    unsigned ret = 0;
    __asm__ __volatile__ ("bsrl %1, %%eax":"=a"(ret):"m"(x));
    return ret;
}
    
}




namespace dark {

/**
 * @brief A dynamic %array that can expand itself automatically.
 * In other words, user don't need to consider the allocation and 
 * deallocation of space.
 * Note that if the elements within are pointers, the data pointed 
 * to won't be touched. It's user's responsibility to manage them.
 * 
 * @tparam value_t The type of elements stored within the %array.
 */
template <class value_t>
class dynamic_array : private std::allocator <value_t> {
  public:
    using iterator               = RandomAccess::iterator_base <value_t,0,1>;
    using const_iterator         = RandomAccess::iterator_base <value_t,1,1>;
    using reverse_iterator       = RandomAccess::iterator_base <value_t,0,0>;
    using const_reverse_iterator = RandomAccess::iterator_base <value_t,1,0>;
  protected:
    value_t *head; /* Head pointer to first element. */
    value_t *tail; /* Tail pointer to one past the last element. */
    value_t *term; /* Terminal pointer to the end of storage. */

    /* Allocate memory of __n elements. */
    value_t *alloc(size_t __n) { return this->allocate(__n); }
    /* Deallocate of the memory of head. */
    void dealloc() { this->deallocate(head,capacity()); }
    
    /* Destory __n elements */
    void destroy_n(value_t *pointer,size_t __n) {
        while(__n--) { this->destroy(pointer++); }
    }

    /* End of unfolding. */
    void reserve_push_back() noexcept {}

    /* Push back a sequence of elements with space reserved in advance. */
    template <class U,class ...Args>
    void reserve_push_back(U &&obj,Args &&...objs) {
        this->construct(tail++,std::forward <U> (obj));
        reserve_push_back(std::forward <Args> (objs)...);
    }

    /* Check whether index is out of range. */
    bool out_of_range(size_t __n) const { return __n >= size(); }

    /* Insert after reallocate. */
    template <class ...Args>
    iterator realloc_insert(iterator __i,Args &&...objs) {
        value_t *temp = this->alloc(size() << 1 | empty());
        size_t i = 0; /* Index holder */

        /* Moving. */
        while(i != (size_t)(__i.base() - head)) { /* std::move_backward */
            this->construct(temp + i,std::move(head[i]));
            ++i;
        }
        /* Insertion. */
        this->construct(temp + i,std::forward <Args>(objs)...);
        /* Moving. */
        while(i != size()) {
            this->construct(temp + i + 1,std::move(head[i]));
            ++i;
        }

        this->~dynamic_array();
        __i  = temp + (__i.base() - head);
        term = temp + (size() << 1 | empty());
        tail = temp + size() + 1;
        head = temp;

        return __i;
    }

    /* Insert without reallocate. */
    template <class ...Args>
    iterator reserve_insert(iterator __i,Args &&...objs) {
        value_t *temp = tail++;

        this->construct(temp,std::move(*(temp - 1)));
        --temp;

        while(temp != __i.base()) { /* Move backward. */
            *temp = std::move(*(temp - 1));
            --temp;
        }
        
        // Direct assignment.
        *temp = value_t(std::forward <Args> (objs)...);
        
        // Following is another attempt.

        // this->destroy(temp);
        // this->construct(temp,std::forward <Args> (objs)...);

        return __i;
    }

  public:

    /* Construct a new empty %array. */
    dynamic_array() noexcept : head(nullptr),tail(nullptr),term(nullptr) {}
    /* Destroy all the elements and deallocate the space. */
    ~dynamic_array() noexcept { this->destroy_n(head,size()); dealloc(); }

    /* Construct a new %array from an initializer_list. */
    dynamic_array(std::initializer_list <value_t> __l) 
        : dynamic_array(__l.size()) {
        for(auto &iter : __l) { this->construct(tail++,std::move(iter)); }
    }

    /* Construct a new %array with __n elements' space reserved. */
    dynamic_array(size_t __n) {
        term = (head = tail = alloc(__n)) + __n;
    }

    /**
     * @brief Construct a new %array filled with given length and element.
     * 
     * @param __n The initial length of the %array.
     * @param obj The element to fill the %array.
     */
    dynamic_array(size_t __n,const value_t &obj) 
        : dynamic_array(__n) {
        while(tail != term) { this->construct(tail++,obj); }
    }

    /**
     * @brief Construct a new %array with identical elements with another %array.
     * Note that no vacancy of %array remains, 
     * which means the new %array's size() equals its capacity(). 
     * 
     * @param rhs The %array to copy from.
     * @attention Linear time complexity with respect to the size() of rhs,
     * multiplied by the construction time of one element.
     */
    dynamic_array(const dynamic_array &rhs) 
        : dynamic_array(rhs.size()) {
        for(const auto &iter : rhs) { this->construct(tail++,iter);}
    }

    /**
     * @brief Construct a new %array with identical elements with another %array.
     * It will just take away the pointers from another %array.
     * 
     * @param rhs The %array to move from.
     * @attention Constant time complexity in any case.
     */
    dynamic_array(dynamic_array &&rhs) noexcept {
        head = rhs.head;
        tail = rhs.tail;
        term = rhs.term;
        rhs.head = rhs.tail = rhs.term = nullptr;
    }

    /**
     * @brief Copy assign a new %array with identical elements with another %array.
     * Note that no vacancy of %array remains, 
     * which means the new %array's size() equals its capacity(). 
     * 
     * @param rhs The %array to copy from.
     * @attention Linear time complexity with respect to the size() of rhs,
     * multiplied by the construction time of one element,
     * Note that there might be an additional time cost linear to the 
     * elements destroyed.
     */
    dynamic_array &operator = (const dynamic_array &rhs) {
        if(this != &rhs) { copy_range(rhs.begin(),rhs.size()); }
        return *this;
    }

    /**
     * @brief Construct a new %array with identical elements with another %array.
     * It will just move the pointers from another %array.
     * 
     * @param rhs The %array to move from.
     * @attention Constant time complexity in any case.
     */
    dynamic_array &operator = (dynamic_array &&rhs) noexcept {
        if(this != &rhs) {
            this->~dynamic_array();
            head = rhs.head;
            tail = rhs.tail;
            term = rhs.term;
            rhs.head = rhs.tail = rhs.term = nullptr;
        }
        return *this;
    }

    /* Swap the content of two %array in constant time. */
    dynamic_array &swap(dynamic_array &rhs) noexcept {
        std::swap(head,rhs.head);
        std::swap(tail,rhs.tail);
        std::swap(term,rhs.term);
        return *this;
    }
    /* Swap the content of two %array in constant time. */
    friend void swap(dynamic_array &lhs,dynamic_array &rhs) noexcept {
        std::swap(lhs.head,rhs.head);
        std::swap(lhs.tail,rhs.tail);
        std::swap(lhs.term,rhs.term);
    }

  public:
    /* Count of elements within the %array. */
    size_t size() const noexcept { return tail - head; }
    /**
     * @brief Count of elements the %array can hold 
     * before the next allocation.
     */
    size_t capacity() const noexcept { return term - head; }

    /**
     * @brief Count of vacancy in the back of the %array  
     * before the next allocation.
     */
    size_t vacancy() const noexcept { return term - tail; }
    /* Test whether the %array is empty */
    bool empty()  const noexcept { return head == tail; }

    /* Doing nothing to the %array. */
    void push_back() noexcept {}

    /**
     * @brief Push one element to the back of the %array.
     * 
     * @param obj The object pushed back to initialize the element. 
     * @attention Amortized constant time complexity,
     * multiplied by the construction time of one element.
     */
    template <class U>
    void push_back(U &&obj) {
        if(tail == term) { reserve(size() << 1 | empty()); } 
        this->construct(tail++,std::forward <U> (obj));
    }

    /**
     * @brief Push a sequnce of elements to the back of the %array.
     * 
     * @param objs The objects pushed back to initialize the element.
     * @attention Amortized linear time complexity with respect to count of objs,
     * multiplied by the construction time of one element.
     */
    template <class ...Args>
    void push_back(Args &&...objs) {
        size_t count = sizeof...(objs); // count >= 2 
        if(vacancy() < count) {
            size_t space = capacity() + empty();
            reserve(space << (LOG2((size() + count - 1) / space) + 1));
        }
        reserve_push_back(std::forward <Args> (objs)...);
    }

    /**
     * @brief Construct one element after the back of the %array.
     * 
     * @param objs  A sequence of objects to initialize element. 
     * @attention Amortized constant time complexity,
     * multiplied by the construction time of one element.
     */
    template <class ...Args>
    void emplace_back(Args &&...objs) {
        if(tail == term) { reserve(size() << 1 | empty()); }
        this->construct(tail++,std::forward <Args> (objs)...);
    }

    /* Destroy the last element in the back, with no returning. */
    void pop_back() { 
        if(empty()) throw sjtu::container_is_empty();
        this->destroy(--tail); 
    }

    /**
     * @brief Clear all the elements in the %array.
     * Note that the capacity() of the %array won't shrink.
     * 
     * @attention Linear complexity with respect to size(),
     * multiplied by the deconstruction time of one element.
     */
    void clear() noexcept {
        this->destroy_n(head,size());
        tail = head;
    }

    /**
     * @brief Clear the vacancy of the %array.
     * Note that it will disable the optimization of the %array.
     * 
     * @attention Linear complexity with respect to size(),
     * multiplied by the deconstruction time of one element.
     */
    void shrink() {
        if(tail != term) {
            value_t *temp = alloc(size());
            for(size_t i = 0 ; i < size() ; ++i) {
                this->construct(temp + i,std::move(head[i]));
            }
            this->~dynamic_array();
            term = tail = temp + size();
            head = temp;
        }
    }

    /**
     * @brief Resize the %array to __n.
     * The original data with index smaller than __n won't be touched.  
     * If __n is greater than size(), elements will be appended to the back.
     * These new elements will be assigned by default construction function.
     * 
     * @param __n The new size of the %array.
     * @attention Linear complexity with respect to __n ,
     * multiplied by the construction time of one element.
     * Note that there might be an additional time cost linear to the 
     * elements destroyed.
     */
    void resize(size_t __n) {
        if(__n <= size()) {
            size_t count = size() - __n;
            tail -= count;
            this->destroy_n(tail,count);
        } else {
            reserve(__n);
            size_t count = __n - size();
            while(count--) { this->construct(tail++); } 
        }
    }


    /**
     * @brief Resize the %array to __n.
     * The original data with index smaller than __n won't be touched.  
     * If __n is greater than size(), elements will be appended to the back.
     * These new elements will be assigned by val.
     * 
     * @param __n The new size of the %array.
     * @param val The object to assign the new value.
     * @attention Linear complexity with respect to __n ,
     * multiplied by the construction time of one element.
     * Note that there might be an additional time cost linear to the 
     * elements destroyed.
     */
    void resize(size_t __n,const value_t &val) {
        if(__n <= size()) {
            size_t count = size() - __n;
            tail -= count;
            this->destroy_n(tail,count);
        } else {
            reserve(__n);
            size_t count = __n - size();
            while(count--) { this->construct(tail++,val); } 
        }
    }

    /**
     * @brief Reserve space for __n elements.
     * If __n < capacity(), nothing will be done.
     * 
     * @param __n The space reserved for elements.
     * @attention Linear time complexity with respect to __n,
     * only if __n >= capacity(), multiplied by the time of (de-)construction. 
     * Otherwise, constant time complexity.
     */
    void reserve(size_t __n) {
        if(capacity() < __n) {
            value_t *temp = alloc(__n);
            for(size_t i = 0 ; i < size() ; ++i) {
                this->construct(temp + i,std::move(head[i]));
            }
            this->~dynamic_array();
            term = temp + __n;
            tail = temp + size();
            head = temp;
        }
    }

    /**
     * @brief Resize the %array to __n and assign all the elements by 
     * default construction function of value_t. 
     * 
     * @param __n The new size of the %array.
     * @attention Linear complexity with respect to __n ,
     * multiplied by the construction time of one element.
     * Note that there might be an additional time cost linear to the 
     * elements destroyed.
     */
    void assign(size_t __n) {
        const value_t val = value_t();
        if(__n <= size()) {
            size_t count = size() - __n;
            tail -= count;
            this->destroy_n(tail,count);
            for(auto &iter : *this) { iter = val; }
        } else {
            for(auto &iter : *this) { iter = val; }
            reserve(__n);
            size_t count = __n - size();
            while(count--) this->construct(tail++);
        }
    }

    /**
     * @brief Resize the %array to __n and assign all the elements by val. 
     * 
     * @param __n The new size of the %array.
     * @param val The object to assign the value.
     * @attention Linear complexity with respect to __n ,
     * multiplied by the construction time of one element.
     * Note that there might be an additional time cost linear to the 
     * elements destroyed.
     */
    void assign(size_t __n,const value_t &val) {
        if(__n <= size()) {
            size_t count = size() - __n;
            tail -= count;
            this->destroy_n(tail,count);
            for(auto &iter : *this) { iter = val; }
        } else {
            for(auto &iter : *this) { iter = val; }
            reserve(__n);
            size_t count = __n - size();
            while(count--) this->construct(tail++,val);
        }
    }

    /**
     * @brief Copy elements from a range [first,last).
     * Note that the Iterator must be random access iterator.
     * Otherwise, you should provide the count of elements.
     * 
     * @tparam Iterator A random access iterator type.
     * @param first Iterator to the first element.
     * @param last  Iterator to one past the last element.
     * @attention Linear time complexity with respect to (last - first)
     * multiplied by the time of moving one element.
     * Note that there might be an additional time cost linear to the 
     * elements destroyed.
     */
    template <class Iterator>
    void copy_range(Iterator first,Iterator last) {
        return copy_range(first,last - first);
    }

    /**
     * @brief Copy elements from a range [first,last).
     * The number of elements in the range should be exactly __n,
     * or unexpected error may happen.
     * 
     * 
     * @param first Iterator to the first element.
     * @param last  Iterator to one past the last element.
     * @param __n   Count of all the elements in the range.
     * @attention Linear time complexity with respect to __n,
     * multiplied by the time of copying one element.
     * Note that there might be an additional time cost linear to the 
     * elements destroyed.
     */
    template <class Iterator>
    void copy_range(Iterator first,size_t __n) {
        if(__n <= capacity()) {
            value_t *temp = head;
            while(__n-- && temp != tail) { *(temp++) = *(first++); }
            ++__n;
            while(__n--) { this->construct(tail++,*(first++)); }
            this->destroy_n(temp,tail - temp);
            tail = temp;
        } else {
            this->~dynamic_array();
            term = (tail = head = alloc(__n)) + __n;
            while(__n--) { this->construct(tail++,*(first++)); } 
        }
    }


    /**
     * @brief Move elements from a range [first,last).
     * Note that the Iterator must be random access iterator.
     * Otherwise, you should provide the count of elements.
     * 
     * @tparam Iterator A random access iterator type.
     * @param first Iterator to the first element.
     * @param last  Iterator to one past the last element.
     * @attention Linear time complexity with respect to (last - first),
     * multiplied by the time of moving one element.
     * Note that there might be an additional time cost linear to the 
     * elements destroyed.
     */
    template <class Iterator>
    void move_range(Iterator first,Iterator last) {
        return move_range(first,last - first);
    }

    /**
     * @brief Move elements from a range [first,last).
     * The number of elements in the range should be exactly __n,
     * or unexpected error may happen.
     * 
     * @param first Iterator to the first element.
     * @param last  Iterator to one past the last element.
     * @param __n   Count of all the elements in the range.
     * @attention Linear time complexity with respect to __n,
     * multiplied by the time of moving one element.
     * Note that there might be an additional time cost linear to the 
     * elements destroyed.
     */
    template <class Iterator>
    void move_range(Iterator first,size_t __n) {
        if(__n <= capacity()) {
            value_t *temp = head;
            while(__n-- && temp != tail) { *(temp++) = std::move(*(first++)); }
            ++__n;
            while(__n--) { this->construct(tail++,std::move(*(first++))); }
            this->destroy_n(temp,tail - temp);
            tail = temp;
        } else {
            this->~dynamic_array();
            term = (tail = head = alloc(__n)) + __n;
            while(__n--) { this->construct(tail++,std::move(*(first++))); } 
        }
    }


    /**
     * @brief Insert at certain location.(Actually , it's emplace in vector.)
     * 
     * @param __n  The subscript of element to be inserted.
     * @param objs A sequence of objects to initialize element.
     * @return     iterator to inserted element
     * @exception  sjtu::index_out_of_bound() if out of bound
     * @attention  Amortized linear time complexity,
     * multiplied by the move-assignment time of one element.
     */
    template <class ...Args>
    iterator insert(size_t __n,Args &&...objs) {
        return insert(head + __n,std::forward <Args> (objs)...);
    }

    /**
     * @brief Insert at certain location.(Actually , it's emplace in vector.)
     * 
     * @param __i  The iterator of element to be inserted.
     * @param objs A sequence of objects to initialize element.
     * @return     iterator to inserted element
     * @exception  sjtu::index_out_of_bound() if out of bound
     * @attention  Amortized linear time complexity,
     * multiplied by the move-assignment time of one element.
     */
    template <class ...Args>
    iterator insert(iterator __i,Args &&...objs) {
        if(__i.base() == tail) { /* Insert at the end. */
            emplace_back(std::forward <Args> (objs)...);
            return end();
        }

        if(out_of_range(__i.base() - head)) throw sjtu::index_out_of_bound();

        if(tail == term) return realloc_insert(__i,std::forward <Args> (objs)...);    
        else             return reserve_insert(__i,std::forward <Args> (objs)...);
    }

    /* Erase at __n. */
    iterator erase(size_t __n) { return erase(head + __n); }

    /* Erase at __i. */
    iterator erase(iterator __i) {
        if(out_of_range(__i.base() - head)) throw sjtu::index_out_of_bound();
        value_t *temp = __i.base() + 1;
        while(temp != tail) {
            *(temp - 1) = std::move(*temp);
            ++temp;
        }
        this->destroy(--tail);
        return __i;
    }



  public:

    /* Return the pointer to the first element. */
    value_t *data() { return head; }
    /* Return the pointer to the first element. */
    const value_t *data() const { return head; }

    /* Subscript access to the data in the %array.  */
    value_t &operator [] (size_t __n) { return at(__n); }
    /* Subscript access to the data in the %array.  */
    const value_t &operator [] (size_t __n) const { return at(__n); }

    /* Access to the data in the %array. */
    value_t &at(size_t __n) {
        if(out_of_range(__n)) throw sjtu::index_out_of_bound();
        return head[__n];
    }
    /* Access to the data in the %array.  */
    const value_t &at(size_t __n) const {
        if(out_of_range(__n)) throw sjtu::index_out_of_bound();
        return head[__n];
    }

    /* Reference to the first element. */
    value_t &front() { 
        if(empty()) throw sjtu::container_is_empty();
        return *begin();
    }
    /* Reference to the  last element. */
    value_t &back()  {
        if(empty()) throw sjtu::container_is_empty();
        return *--end();
    }

    /* Const reference to the first element. */
    const value_t &front() const { 
        if(empty()) throw sjtu::container_is_empty();
        return *begin();
    }
    /* Const reference to the  last element. */
    const value_t &back()  const {
        if(empty()) throw sjtu::container_is_empty();
        return *--end();
    }
    
    /* Iterator to the first element. */
    iterator begin() noexcept  { return {head,this}; }
    /* Iterator to one past the last element. */
    iterator end()   noexcept  { return {tail,this}; }

    /* Const_iterator to the first element. */
    const_iterator begin()  const noexcept { return {head,this}; }
    /* Const_iterator to one past the last element. */
    const_iterator end()    const noexcept { return {tail,this}; }
    /* Const_iterator to the first element. */
    const_iterator cbegin() const noexcept { return {head,this}; }
    /* Const_iterator to one past the last element. */
    const_iterator cend()   const noexcept { return {tail,this}; }

};


}

/* WTF is that ??? */
namespace sjtu {

template <class T>
using vector = dark::dynamic_array <T>;

}


#endif
