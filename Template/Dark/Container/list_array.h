#ifndef _DARK_LIST_ARRAY_H
#define _DARK_LIST_ARRAY_H

#include "../include/basic.h"
#include <memory>
#include <initializer_list>

namespace dark {

using value_t = long long;

// template <class value_t>

class list_array : std::allocator <value_t> {
  protected:
    value_t *head; /* Head pointer. */
    value_t *tail; /* Tail pointer. */

    /* Allocate memory of __n elements. */
    inline value_t *alloc(size_t __n) { return this->allocate(__n); }
    /* Deallocate of the memory of head. */
    inline void dealloc()      { this->deallocate(head,size()); }
    
    /* Destory __n elements */
    void destroy_n(value_t *pointer,size_t __n) {
        while(__n--) { this->destroy(pointer++); }
    }
  public:
    /* Construct a new empty %array. */
    list_array() : head(nullptr),tail(nullptr) {}
    /* Destroy all the elements and deallocate the space. */
    ~list_array() { this->destroy_n(head,size()); dealloc(); }

    /* Construct a new %array from an initializer_list. */
    list_array(std::initializer_list <value_t> __l) 
        : list_array(__l.size()) {
        for(auto &iter : __l) { this->construct(tail++,std::move(iter)); }
    }

    /* Construct a new %array with __n elements' space reserved. */
    list_array(size_t __n) { head = tail = alloc(__n); }

    /**
     * @brief Construct a new %array filled with given length and element.
     * 
     * @param __n The initial length of the %array.
     * @param obj The element to fill the %array.
     */
    list_array(size_t __n,const value_t &obj) 
        : list_array(__n) {
        while(__n--) { this->construct(tail++,obj); }
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
    list_array(const list_array &rhs) 
        : list_array(rhs.size()) {
        for(const auto &iter : rhs) { this->construct(tail++,iter);}
    }



  public:
    /* Count of elements within the %array. */
    constexpr inline size_t size() const {return tail - head;}

    /* Test whether the %array is empty */
    constexpr inline bool empty()  const {return head == tail;}

  public:
    /* Return the pointer to the first element. */
    inline value_t *data() { return head; }
    /* Return the pointer to the first element. */
    inline const value_t *data() const { return head; }
    /* Subscript access to the data in the %array.  */
    inline value_t &operator [] (size_t __n) { return head[__n]; }
    /* Subscript access to the data in the %array.  */
    inline const value_t &operator [] (size_t __n) const { return head[__n]; }

    /* Reference to the first element. */
    inline value_t &front() {return *begin();}
    /* Reference to the  last element. */
    inline value_t &back()  {return *--end();}
    /* Const reference to the first element. */
    inline const value_t &front() const {return *cbegin();}
    /* Const reference to the  last element. */
    inline const value_t &back()  const {return *--cend();}


    /* Iterator to the first element. */
    inline iterator begin() { return head; }
    /* Iterator to the one past last element. */
    inline iterator end()   { return tail; }

    /* Const_iterator to the first element. */
    inline const_iterator begin()  const {return head;}
    /* Const_iterator to one past the last element. */
    inline const_iterator end()    const {return tail;}
    /* Const_iterator to the first element. */
    inline const_iterator cbegin() const {return head;}
    /* Const_iterator to one past the last element. */
    inline const_iterator cend()   const {return tail;}

};




}




#endif
