#pragma once
#include "node.h"
#include <iostream>

namespace dark {

inline static node node_pool[kLen / sizeof(node)];

struct list_allocator : forward_list {
    list_allocator() {
        for (auto &__node : node_pool) push_front(&__node);
    }
};

inline static list_allocator list_alloc; 

inline auto forward_list::push_front(node *__ptr) -> void {
    __ptr->next = head;
    head = __ptr;
}

inline auto forward_list::pop_front() -> node * {
    auto *__ptr = head;
    head = head->next;
    return __ptr;
}

inline auto forward_list::pop_remove() -> void * {
    auto *__ptr = pop_front();
    list_alloc.push_front(__ptr);
    return __ptr->addr;
}

inline auto create_node(void *__ptr) -> node * {
    auto *__new = list_alloc.pop_front();
    __new->addr = __ptr;
    return __new;
}

/* A local helper function. */
inline static offset_t get_bias(void *__ptr) {
    return static_cast<std::byte *>(__ptr) - memory_pool;
}
/* A local helper function. */
inline static void *set_bias(offset_t __n) {
    return memory_pool + __n;
}

inline auto forward_list::debug() -> void {
    for (auto *__ptr = head ; __ptr ; __ptr = __ptr->next)
        std::cerr << "  pos:" << get_bias(__ptr->addr) << "\n";
}

inline void *set_index(number_t __n, rank_t __rk) {
    if (__rk >= kBit) throw std::bad_alloc();
    auto __m = kBit - 1 - __rk;
    return set_bias((__n >> __m) << __m);
}

inline number_t get_index(void *__ptr, rank_t __rk) {
    if (__rk >= kBit) throw std::bad_alloc();
    auto __m = get_bias(__ptr);
    return (__m >> __rk) | (1ull << (kBit - 1 - __rk));
}

} // namespace dark
