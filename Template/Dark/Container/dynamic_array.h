#ifndef _DARK_DYNAMIC_ARRAY_H_
#define _DARK_DYNAMIC_ARRAY_H_

#include "../include/basic.h"
#include <memory>
#include <initializer_list>

namespace dark {


// using value_t = int;

/**
 * @brief A dynamic %array that can expand itself automatically.
 * In other words,user don't need to consider the allocation and 
 * deallocation of data.
 * Note that,if the elements within are pointers,the data pointed 
 * to won't be touched. It's user's responsibility to manage them.
 * 
 * @tparam value_t The value of elements stores within the %array.
 */
template <class value_t>
class dynamic_array : private std::allocator <value_t> {
  protected:
    value_t *head; /* Head pointer to first element. */
    value_t *tail; /* Tail pointer to one past the last element. */
    value_t *term; /* Terminal pointer to the end of storage. */

    /* Allocate memory of __n elements. */
    inline value_t *alloc(size_t __n) { return this->allocate(__n); }
    /* Deallocate of the memory of head. */
    inline void dealloc()      { this->deallocate(head,capacity()); }
    
    /* Destory n elements */
    void destroy_n(value_t *pointer,size_t __n) {
        while(__n--) {this->destroy(pointer++);}
    }

    /* End of unfolding. */
    void reserved_push_back() {}

    /* Push back a sequence of elements with reserved space. */
    template <class U,class ...Args>
    void reserved_push_back(U &&obj,Args &&...objs) {
        this->construct(tail++,std::forward <U> (obj));
        reserved_push_back(std::forward <Args> (objs)...);
    }

  public:

    /* Construct a new empty %array. */
    dynamic_array() : head(nullptr),tail(nullptr),term(nullptr) {}
    /* Clean all the elements. */
    ~dynamic_array() {
        this->destroy_n(head,size());
        dealloc();
    }

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
    dynamic_array(dynamic_array &&rhs) {
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
    inline dynamic_array &operator = (const dynamic_array &rhs) {
        if(this != &rhs) { copy_range(rhs.begin(),rhs.end()); }
        return *this;
    }

    /**
     * @brief Construct a new %array with identical elements with another %array.
     * It will just swap the pointers with another %array.
     * 
     * @param rhs The %array to move from.
     * @attention Constant time complexity in any case.
     */
    inline dynamic_array &operator = (dynamic_array &&rhs) {
        return this->swap(rhs);
    }

    /* Swap the content of two %array in constant time. */
    dynamic_array &swap(dynamic_array &rhs) {
        std::swap(head,rhs.head);
        std::swap(tail,rhs.tail);
        std::swap(term,rhs.term);
        return *this;
    }
    /* Swap the content of two %array in constant time. */
    friend void swap(dynamic_array &lhs,dynamic_array &rhs) {
        std::swap(lhs.head,rhs.head);
        std::swap(lhs.tail,rhs.tail);
        std::swap(lhs.term,rhs.term);
    }

  public:
    /* Count of elements within the %array. */
    constexpr inline size_t size() const {return tail - head;}
    /**
     * @brief Count of elements the %array can hold 
     * before the next allocation.
     */
    constexpr inline size_t capacity() const {return term - head;}
    /**
     * @brief Count of vacancy in the back of the %array  
     * before the next allocation.
     */
    constexpr inline size_t vacancy() const {return term - tail;}
    /* Test whether the %array is empty */
    constexpr inline bool empty()  const {return head == tail;}

    /* Doing nothing to the %array. */
    constexpr void push_back() const {}

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
        reserved_push_back(std::forward <Args> (objs)...);
    }

    /**
     * @brief Construct one element after the back of the %array.
     * 
     * @param obj The object pushed back to initialize the element. 
     * @attention Amortized constant time complexity,
     * multiplied by the construction time of one element.
     */
    template <class ...Args>
    void emplace_back(Args &&...objs) {
        if(tail == term) { reserve(size() << 1 | empty()); }
        this->construct(tail++,std::forward <Args> (objs)...);
    }

    inline void pop_back() { this->destroy(tail--); }


    /**
     * @brief Clear all the elements in the %array.
     * 
     * @attention Linear complexity with respect to size(),
     * multiplied by the deconstruction time of one element.
     */
    void clear() {
        this->destroy_n(head,size());
        tail = head;
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
     * Otherwise , constant time complexity.
     */
    void reserve(size_t __n) {
        if(capacity() < __n) {
            value_t *temp = alloc(__n);

            for(size_t i = 0 ; i < size() ; ++i) {
                this->construct(temp + i,std::move(head[i]));
            }
            // memcpy(temp,head,size() * sizeof(value_t));

            dealloc();
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
    
    template <class Iterator>
    void copy_range(Iterator first,Iterator last) {
        return copy_range(first,last,last - first);
    }

    template <class Iterator>
    void copy_range(Iterator first,Iterator last,size_t __n) {
        if(__n <= capacity()) {
            value_t *temp = head;
            while(first != last && temp != tail) { *(temp++) = *(first++); }
            while(first != last) { this->construct(tail++,*(first++)); }
            resize(__n);
        }
        else {
            this->~dynamic_array();
            term = (tail = head = alloc(__n)) + __n;
            while(tail != term) { this->construct(tail++,*(first++)); } 
        }
    }

    template <class Iterator>
    void move_range(Iterator first,Iterator last) {
        return move_range(first,last,last - first);
    }

    template <class Iterator>
    void move_range(Iterator first,Iterator last,size_t __n) {
        if(__n <= capacity()) {
            value_t *temp = head;
            while(first != last && temp != tail) { *(temp++) = std::move(*(first++)); }
            while(first != last) { this->construct(tail++,std::move(*(first++))); }
            resize(__n);
        }
        else {
            this->~dynamic_array();
            term = (tail = head = alloc(__n)) + __n;
            while(tail != term) { this->construct(tail++,std::move(*(first++))); } 
        }
    }

  public:
    /* Subscript access to the data in the %array.  */
    inline value_t &operator [] (size_t __n) { return head[__n]; }
    /* Subscript access to the data in the %array.  */
    inline const value_t &operator [] (size_t __n) const { return head[__n]; }

    /* Reference to the first element. */
    inline value_t &front() {return *begin();}
    /* Reference to the  last element. */
    inline value_t &back()  {return *--end();}
    /* Const reference to the first element. */
    inline const value_t &front() const {return *begin();}
    /* Const reference to the  last element. */
    inline const value_t &back()  const {return *--end();}


    using iterator       =       value_t *;
    using const_iterator = const value_t *;

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
