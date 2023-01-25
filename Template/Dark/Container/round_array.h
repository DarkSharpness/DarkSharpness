#ifndef _DARK_ROUND_ARRAY_H_
#define _DARK_ROUND_ARRAY_H_

#include "../include/basic.h"

#include <memory>
#include <initializer_list>

namespace dark {

using value_t = int;

class round_array : private std::allocator <value_t>  {
  protected:
    value_t *head;    // Head pointer
    value_t *tail;    // Tail pointer
    size_t prefix;    // Prefix size
    size_t suffix;    // Suffix size

  public:
    


  public:
    size_t size() const noexcept { return prefix + suffix; }
    size_t capacity() const noexcept { return tail - head; }
    size_t vacancy() const noexcept { return capacity() - size(); }
    bool empty() const noexcept { return !(prefix || suffix); }

    /**
     * @brief Push one element to the back of the %array.
     * 
     * @param obj The object pushed back to initialize the element. 
     * @attention Amortized constant time complexity,
     * multiplied by the construction time of one element.
     */
    template <class U>
    void push_back(U &&obj) {
        if(size() == capacity()) { reserve(size() << 1 | empty()); } 
        this->construct(head + (prefix++),std::forward <U> (obj));
    }

    /**
     * @brief Push one element to the back of the %array.
     * 
     * @param obj The object pushed front to initialize the element. 
     * @attention Amortized constant time complexity,
     * multiplied by the construction time of one element.
     */
    template <class U>
    void push_front(U &&obj) {
        if(size() == capacity()) { reserve(size() << 1 | empty()); } 
        this->construct(tail - (++suffix),std::forward <U> (obj));
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
        if(size() == capacity()) { reserve(size() << 1 | empty()); }
        this->construct(head + (prefix++),std::forward <Args> (objs)...);
    }

    /**
     * @brief Construct one element before the front of the %array.
     * 
     * @param obj The object pushed front to initialize the element. 
     * @attention Amortized constant time complexity,
     * multiplied by the construction time of one element.
     */
    template <class ...Args>
    void emplace_front(Args &&...objs) {
        if(size() == capacity()) { reserve(size() << 1 | empty()); }
        this->construct(tail - (++suffix),std::forward <Args> (objs)...);
    }










    

};


}

#endif
