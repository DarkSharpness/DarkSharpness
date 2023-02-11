#ifndef _DARK_ROUND_ARRAY_H_
#define _DARK_ROUND_ARRAY_H_


#include <memory>
#include <initializer_list>

namespace dark {

using value_t = long long;

class round_array : private std::allocator <value_t>  {
  protected:
    value_t *head;    // Head pointer
    value_t *tail;    // Tail pointer
    value_t *prefix;  // Prefix pointer
    value_t *suffix;  // Suffix pointer
    bool round;       // Whether rounded or not

    /* Allocate memory of __n elements. */
    value_t *alloc(size_t __n) { return this->allocate(__n); }
    /* Deallocate of the memory of head. */
    void dealloc() { this->deallocate(head,capacity()); }
    
    /* Destory __n elements */
    void destroy_n(value_t *pointer,size_t __n) {
        while(__n--) { this->destroy(pointer++); }
    }

    void destroy_in(value_t *ptr1,value_t *ptr2) {
        while(ptr1 != ptr2) this->destroy(ptr1++);
    }

  public:
     /* Construct a new empty %array. */
    round_array() noexcept : round(false),
        head(nullptr),tail(nullptr),prefix(nullptr),suffix(nullptr) {}
    /* Destroy all the elements and deallocate the space. */
    ~round_array() noexcept {
        if(!round) this->destroy_in(prefix,suffix);
        else this->destroy_in(head,suffix),this->destroy_in(prefix,tail);
    }

  public:
    size_t size() const noexcept 
    {    return suffix - prefix + round * (tail - head);  }
    size_t capacity() const noexcept { return tail - head; }

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
