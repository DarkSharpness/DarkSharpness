#include <iostream>

// no inline, required by [replacement.functions]/3
void* operator new(std::size_t sz) {
    std::printf("new(), size = %zu\n", sz);
    if (sz == 0)
        ++sz; // avoid std::malloc(0) which may return nullptr on success
 
    if (void *ptr = std::malloc(sz))
        return ptr;

    throw std::bad_alloc{}; // required by [new.delete.single]/3
}
 
void operator delete(void* ptr) noexcept {
    std::puts("delete()");
    std::free(ptr);
}
 
void operator delete(void* ptr, std::size_t size) noexcept {
    std::printf("delete(), size = %zu\n", size);
    std::free(ptr);
}

#include "src.hpp"


int main() {
    { sjtu::make_unique <int> (114514); }
    static_assert (sizeof(std::string) == 32);
    { sjtu::unique_ptr <std::string> (new std::string); }
    {
        using func_t = decltype(main) *;
        static_assert(sizeof(func_t) == 8);
        for (int i = 0 ; i < 10 ; ++i)
            sjtu::make_unique <func_t> (main);
    }
    return 0;
}

