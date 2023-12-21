#pragma once

#include <iostream>
#include <format>

namespace dark {

class allocator_debugger;

namespace detail {

/* Error code. */
struct error {
    std::string data;
    explicit error(std::string __s) noexcept : data(std::move(__s))
    { std::cerr << "\n\033[31mFatal error: " << data << "\n\033[0m"; }
    const char *what() const noexcept { return data.c_str(); }
};


/* Warning code. */
struct warning {
    std::string data;
    explicit warning(std::string __s) noexcept : data(std::move(__s))
    { std::cerr << "\033[33mWarning: " << data << "\n\033[0m"; }
    const char *what() const noexcept { return data.c_str(); }
};


/* Normal code. */
struct normal {
    std::string data;
    explicit normal(std::string __s) noexcept : data(std::move(__s))
    { std::cerr << "\033[32m" << data << "\n\033[0m"; }
    const char *what() const noexcept { return data.c_str(); }
};

class allocator_debug_base {
  private:
    struct debug_pack {
        allocator_debug_base *pointer;
        size_t count;
    };

    friend class ::dark::allocator_debugger;

    size_t refer_count = 0;
    size_t alloc_count = 0;
    size_t freed_count = 0;
    size_t alloc_times = 0;
    size_t freed_times = 0;

    inline static allocator_debug_base *single = nullptr;
    inline static constexpr size_t offset = sizeof(debug_pack);

    allocator_debug_base(size_t __n = 0) noexcept { refer_count = __n; }

    /* Aligned to offset. */
    static size_t pack_length(size_t __n) noexcept {
        return (__n + (offset - 1)) / offset + 2;
    }

    /* Aligned to offset. */
    static size_t real_size(size_t __n) noexcept {
        return pack_length(__n) * offset;
    }

    /* Perform some operation on allocated memory. */
    void *allocate(void *__ptr,size_t __n) {
        if(!__ptr) throw std::bad_alloc {};

        alloc_times += 1;
        alloc_count += __n;

        debug_pack __val = {this, __n};
        auto * const __tmp = static_cast <debug_pack *> (__ptr);
        *__tmp = __val;
        *(__tmp + pack_length(__n) - 1) = __val;
        return __tmp + 1;
    }

    /* Perform some operation before deallocation. */
    void *deallocate(void *__ptr) {
        if(!__ptr) return nullptr;
        auto *const __tmp = static_cast <debug_pack *> (__ptr) - 1;
        debug_pack __val = *__tmp;

        if (__val.pointer != this)
            throw error("Invalid deallocation!");

        auto *__end = __tmp + pack_length(__val.count) - 1;
        if (__end->pointer != this
        ||  __end->count != __val.count)
            throw error("Invalid deallocation!");

        freed_times += 1;
        freed_count += __val.count;

        return __tmp;
    }

    ~allocator_debug_base() noexcept {
        const size_t __alloc = alloc_count;
        const size_t __freed = freed_count;
        const size_t __Atime = alloc_times;
        const size_t __Ftime = freed_times;
        auto __str = std::format (
                "Memory leak detected!\n"
                "Allocated: {} bytes, {} times.\n"
                "Freed: {} bytes, {} times.\n"
                "Total loss: {} bytes, {} times.\n",
                alloc_count, alloc_times,
                freed_count, freed_times,
                alloc_count - freed_count,
                alloc_times - freed_times
            );
        if (__alloc != __freed || __Atime != __Ftime) {
            error("\nMemory leak detected!\n" + __str);
        } else {
            normal("\nNo memory leak is found!\n" + __str);
        }
    }
};


} // namespace detail


/**
 * @brief Debug allocator. Safely allocate and deallocate memory.
 */
class allocator_debugger {
  private:
    using _Base = detail::allocator_debug_base;
    inline static _Base base;
    _Base *const __obj;
  public:
    allocator_debugger(_Base &__b = base)
    noexcept : __obj(&__b) {
        if (__obj == &base) return;
        ++__obj->refer_count; 
    }
 
    ~allocator_debugger() noexcept {
        if (__obj == &base) return;
        if (!--__obj->refer_count) delete __obj;
    }

    void *allocate(size_t __n) {
       return __obj->allocate(::std::malloc(__obj->real_size(__n)),__n);
    }

    void deallocate(void *__ptr) noexcept {
        return ::std::free(__obj->deallocate(__ptr));
    }
};

} // namespace dark


void *operator new(std::size_t sz) {
    dark::allocator_debugger __alloc {};
    if (void *ptr = __alloc.allocate(sz)) return ptr;
    throw std::bad_alloc{}; // required by [new.delete.single]/3
}
 
void* operator new[](std::size_t sz) {
    dark::allocator_debugger __alloc {};
    if (void *ptr = __alloc.allocate(sz)) return ptr;
    throw std::bad_alloc{}; // required by [new.delete.single]/3
}
 
void operator delete(void* ptr) noexcept {
    dark::allocator_debugger __alloc {};
    __alloc.deallocate(ptr);
}
 
void operator delete(void* ptr, std::size_t) noexcept {
    dark::allocator_debugger __alloc {};
    __alloc.deallocate(ptr);
}
 
void operator delete[](void* ptr) noexcept {
    dark::allocator_debugger __alloc {};
    __alloc.deallocate(ptr);
}
 
void operator delete[](void* ptr, std::size_t) noexcept {
    dark::allocator_debugger __alloc {};
    __alloc.deallocate(ptr);
}


