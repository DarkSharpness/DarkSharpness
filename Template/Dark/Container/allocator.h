#ifndef _DARK_ALLOCATOR_H_
#define _DARK_ALLOCATOR_H_

#include <cstdlib>
#include <memory>

/* Easy wrapping. */
namespace dark {

    /* An implement for node allocator. */
template <class value_t,
          class allocator_t = std::allocator <value_t>,
          class ...Ts>
struct implement : allocator_t , Ts ... {
    using pointer = value_t *;
    size_t count = 0;

    template <class ...Args>
    inline pointer alloc(Args &&...objs) {
        pointer __p = this->allocate(1);
        this->construct(__p,std::forward <Args> (objs)...);
        return __p;
    }

    inline void dealloc(void *__p) {
        this->destroy((pointer)__p);
        this->deallocate((pointer)__p,1);
    }
};
}


#endif
