#ifndef _DARK_DYNAMIC_ARRAY_H_
#define _DARK_DYNAMIC_ARRAY_H_


#include "exceptions.hpp"

#include <iostream>
#include <climits>
#include <cstddef>


namespace dark {

inline unsigned int LOG2(unsigned x){
    unsigned ret = 0;
    __asm__ __volatile__ ("bsrl %1, %%eax":"=a"(ret):"m"(x));
    return ret;
}
    
}


namespace dark {

using diff_t = std::ptrdiff_t; /* Global Variable. */

/* Namespace for Random Access Iterators.  */
namespace RandomAccess {

template <class T>
class iterator {
  public:
    using difference_type = std::ptrdiff_t;
    using value_type = T;
    using pointer = T*;
    using reference = T&;
    using iterator_category = std::output_iterator_tag;


  protected:
    T *ptr;

   

  public:
    ~iterator() noexcept = default;
    iterator(T *rhs = nullptr) noexcept : ptr(rhs)  {}
    iterator &operator = (const iterator &rhs) noexcept = default;
    /* Return the inner ptr. */
    T *base() const noexcept { return ptr; }


    iterator &operator ++ (void) noexcept { ++ptr; return *this; }
    iterator &operator -- (void) noexcept { --ptr; return *this; }
    iterator operator ++ (int) noexcept { return iterator(ptr++); }
    iterator operator -- (int) noexcept { return iterator(ptr--); }


    iterator &operator += (diff_t __n) noexcept { ptr += __n; return *this; }
    iterator &operator -= (diff_t __n) noexcept { ptr -= __n; return *this; }
    friend iterator operator + (diff_t __n,iterator rhs) noexcept 
    { return iterator(rhs.ptr + __n); }
    friend iterator operator + (iterator lhs,diff_t __n) noexcept 
    { return iterator(lhs.ptr + __n); }
    friend iterator operator - (iterator lhs,diff_t __n) noexcept 
    { return iterator(lhs.ptr - __n); }
    friend diff_t operator - (iterator lhs,iterator rhs) noexcept 
    { return lhs.ptr - rhs.ptr; }


    friend bool operator == (iterator lhs,iterator rhs) noexcept 
    { return lhs.ptr == rhs.ptr; }
    friend bool operator != (iterator lhs,iterator rhs) noexcept 
    { return lhs.ptr != rhs.ptr; }


    T &operator * (void) const noexcept { return *ptr; } 
    T *operator ->(void) const noexcept { return  ptr; }
    T &operator [] (diff_t __n) const noexcept { return ptr[__n]; }
};


template <class T>
class const_iterator {
  protected:
    const T *ptr;
    using difference_type = std::ptrdiff_t;
    using value_type = T;
    using pointer = T*;
    using reference = T&;
    using iterator_category = std::output_iterator_tag;
    using Iterator = iterator <T> ;
  public:
    ~const_iterator() = default;
    const_iterator(const T *rhs = nullptr)  noexcept : ptr(rhs) {}
    const_iterator(Iterator rhs) noexcept : ptr(rhs.base()) {}
    const_iterator &operator = (const const_iterator &rhs) noexcept = default;
    const_iterator &operator = (Iterator rhs) 
    { ptr = rhs.base(); return *this; }
    /* Return the inner ptr. */
    const T *base() const noexcept { return ptr; }

    const_iterator &operator ++ (void) noexcept { ++ptr; return *this; }
    const_iterator &operator -- (void) noexcept { --ptr; return *this; }
    const_iterator operator ++ (int) noexcept { return const_iterator(ptr++); }
    const_iterator operator -- (int) noexcept { return const_iterator(ptr--); }

    const_iterator &operator += (diff_t __n) noexcept
    { ptr += __n; return *this; }
    const_iterator &operator -= (diff_t __n) noexcept
    { ptr -= __n; return *this; }
    friend const_iterator operator + (const_iterator lhs,diff_t __n) noexcept
    { return const_iterator(lhs.ptr + __n); }
    friend const_iterator operator + (diff_t __n,const_iterator rhs) noexcept
    { return const_iterator(rhs.ptr + __n); }
    friend const_iterator operator - (const_iterator lhs,diff_t __n) noexcept
    { return const_iterator(lhs.ptr - __n); }
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


    const T &operator * (void) const { return *ptr; } 
    const T *operator ->(void) const { return  ptr; }
    const T &operator [] (diff_t __n) const { return ptr[__n]; }
};

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
    using iterator               = RandomAccess::iterator       <value_t>;
    using const_iterator         = RandomAccess::const_iterator <value_t>;

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
    iterator begin()  { return head; }
    /* Iterator to one past the last element. */
    iterator end()    { return tail; }

    /* Const_iterator to the first element. */
    const_iterator begin()  const { return head; }
    /* Const_iterator to one past the last element. */
    const_iterator end()    const { return tail; }
    /* Const_iterator to the first element. */
    const_iterator cbegin() const { return head; }
    /* Const_iterator to one past the last element. */
    const_iterator cend()   const { return tail; }


};


}


namespace sjtu {

template <class T>
using vector = dark::dynamic_array <T>;

}


#endif
