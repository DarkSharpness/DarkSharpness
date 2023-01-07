#ifndef _DARK_MEMINFO_HPP_
#define _DARK_MEMINFO_HPP_

#include <iostream>

/* A simple tool to test memory leak and get storage info. */
struct memory_recorder { 
    static std::size_t allocated;
    static std::size_t ptr_count;
    ~memory_recorder() {
        std::printf("\n------------------------------\n");
        std::printf("Space allocated : %llu\n",allocated);
        std::printf("Pointers leaked : %llu\n",ptr_count);
        std::printf( "------------------------------\n" );
    }
};

static memory_recorder MEMORY_RECORDER;

std::size_t memory_recorder::allocated = 0;
std::size_t memory_recorder::ptr_count = 0;

void *operator new (size_t sz) {
    void *p = std::malloc(sz);
    ++memory_recorder::ptr_count;
    memory_recorder::allocated += sz;
    return p;
}

void *operator new [](size_t sz) {
    std::cout << sz << '\n';
    void *p = std::malloc(sz);
    ++memory_recorder::ptr_count;
    memory_recorder::allocated += sz;
    return p;
}

void operator delete(void* p,std::size_t) {
    --memory_recorder::ptr_count;
    return std::free(p);
}

void operator delete[](void *p) {
    --memory_recorder::ptr_count;
    return std::free(p);
}

#endif
