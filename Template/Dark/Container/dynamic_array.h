#ifndef _DARK_DYNAMIC_ARRAY_H_
#define _DARK_DYNAMIC_ARRAY_H_

#include "../include/basic.h"
#include <memory>
#include <initializer_list>

namespace dark {
// using value_t = int;

template <class value_t>
class dynamic_array : private std::allocator <value_t> {
  protected:
    value_t *head;
    value_t *tail;
    value_t *term;

    inline value_t *alloc(size_t __n) { return this->allocate(__n); }
    inline void dealloc()      { this->deallocate(head,capacity()); }


  public:
    dynamic_array() : head(nullptr),tail(nullptr),term(nullptr) {}
    ~dynamic_array() {
        std::destroy_n(head,size());
        dealloc();
    }

    dynamic_array(std::initializer_list <value_t> __l) {
        tail = head = alloc(__l.size());
        for(auto &it : __l) { *(tail++) = std::move(it);}
    }

    template <class U>
    dynamic_array(size_t __n,U &&obj = value_t()) {
        term = (tail = head = alloc(__n)) + __n;
        while(tail != term) { *(tail++) = std::forward <U> (obj);}
    }

    dynamic_array(const dynamic_array &rhs) {
        tail = head = alloc(rhs.size());
        for(const auto &it : rhs) { *(tail++) = it;}
    }

    dynamic_array(dynamic_array &&rhs) {
        head = rhs.head;
        tail = rhs.tail;
        term = rhs.term;
        rhs.head = rhs.tail = rhs.term = nullptr;
    }


    constexpr inline size_t size()     const {return tail - head;}
    constexpr inline size_t capacity() const {return term - head;}
    constexpr inline size_t vacancy()  const {return term - tail;}
    constexpr inline bool empty() const {return head == tail;}

    template <class U = value_t>
    void push_back(U &&obj = U()) {
        if(tail == term) { reserve(size() << 1 | empty()); } 
        std::_Construct(tail++,std::forward <U> (obj));
    }

    inline void pop_back() { --tail; }


    void resize(size_t __n) {
        if(__n <= size()) {
            size_t count = size() - __n;
            tail -= count;
            std::destroy_n(tail,count);
        } else {
            reserve(__n);
            size_t count = __n - size();
            while(count--) { std::_Construct(tail++); } 
        }
    }

    void reserve(size_t __n) {
        if(capacity() < __n) {
            value_t *temp = alloc(__n);
            memcpy(temp,head,size() * sizeof(value_t));
            dealloc();
            term = temp + __n;
            tail = temp + size();
            head = temp;
        }
    }


    inline value_t &operator [](size_t __n) { return head[__n]; }
    inline const value_t &operator [](size_t __n) const { return head[__n]; }


  public:
    using iterator       = value_t *;
    using const_iterator = const value_t *;
    inline iterator begin() { return head; }
    inline iterator end()   { return tail; }

    inline const_iterator begin()  const {return head;}
    inline const_iterator end()    const {return tail;}
    inline const_iterator cbegin() const {return head;}
    inline const_iterator cend()   const {return tail;}


};




}



#endif
