#ifndef _DARK_ALLOCATOR_H_
#define _DARK_ALLOCATOR_H_

#include <cstdlib>
#include <utility>

/* Easy wrapping. */
namespace dark {

template <class T>
class single_allocator {
  public:
    using pointer = T *;

  private:
    size_t count;

  public:
    single_allocator() noexcept : count(0) {}
    single_allocator(const single_allocator &) noexcept = default;
    single_allocator & operator = (const single_allocator &) noexcept = default;
    ~single_allocator() noexcept = default;

    pointer allocate() 
    { ++count; return (pointer) std::malloc(sizeof(T)); }

    void deallocate(pointer __p) noexcept
    { --count; __p->~T() ;  return std::free(__p);}

    template <class ...Args>
    void construct(pointer __p,Args &&...objs) 
    { ::new ((void *)__p) T(std::forward <Args> (objs)...); }

    size_t size() const noexcept { return count; }
};

}

/* Abandoned part. */
namespace dark {


namespace ALLOCATOR {

struct allocator_node { 
    allocator_node *prev; 
    allocator_node *next;
    allocator_node() : prev(nullptr),next(nullptr) {}
    /* Whether the node points to null memory. */
    bool empty() const { return next; }
    /* Whether the node connects itself. */
    bool round() const { return next == prev; }
};

}

// abandoned draft 

template <class T>
class node_allocator {
  public:
    using pointer = T *;
    using node_t = ALLOCATOR::allocator_node;
  private:
    size_t count;
    node_t cache;

  public:
    node_allocator() noexcept : count(0) {}
    node_allocator(const node_allocator &) noexcept : node_allocator() {}
    node_allocator(node_allocator &&rhs) noexcept : count(0) {
        std::swap(count,rhs.count);
        std::swap(cache,rhs.cache);
    }

    node_allocator & operator = (const node_allocator &rhs) noexcept {
        count = rhs.count;
        return *this;
    }
    ~node_allocator() noexcept = default;

    node_allocator & operator = (node_allocator &&rhs) noexcept {
        

    }


    template <class ...Args>
    pointer alloc(Args &&...objs)  {
        ++count;
        pointer temp;
        if(cache.empty()) temp = (pointer) std::malloc(sizeof(T));
        else {
            temp = (pointer) cache.next;
            if(cache.round()) {
            }
        }
        construct(temp,std::forward <Args> (objs)...);
        return temp;
    }

    void dealloc(pointer __p) noexcept { 
        --count; 
        __p->~T();
        if(cache.empty()) { cache.next = cache.prev = (node_t *)__p; }
        else {
            cache.next = cache.prev = 0;
        }
    }

    template <class ...Args>
    void construct(pointer __p,Args &&...objs) 
    { ::new ((void *)__p) T(std::forward <Args> (objs)...); }

};

}


#endif
