#pragma once
#include "node.h"
#include "buddy.h"
#include <format>
#include <iostream>

namespace dark {

inline auto forward_list::push_front(node *__ptr) -> void {
    __ptr->next = next;
    next->prev = __ptr;
    __ptr->prev = this;
    this->next = __ptr;
}

inline auto forward_list::pop_front() -> node * {
    auto __ret = next;
    next = next->next;
    next->prev = this;
    return __ret;

}

/* A local helper function. */
inline static offset_t get_bias(void *__ptr) {
    return static_cast <std::byte *> (__ptr) - memory_pool;
}
/* A local helper function. */
inline static void *set_bias(offset_t __n) {
    return memory_pool + __n;
}

inline void *set_index(number_t __n, rank_t __rk) {
    if (__rk >= kBit) throw std::bad_alloc();
    const auto __m = kBit - 1 - __rk;
    return set_bias((__n >> __m) << __rk);
}

inline number_t get_index(void *__ptr, rank_t __rk) {
    if (__rk >= kBit) throw std::bad_alloc();
    const auto __m = get_bias(__ptr);
    return (__m >> __rk) | (1ull << (kBit - 1 - __rk));
}

inline void forward_list::debug(rank_t __rk) {
    const auto __len = 1ull << __rk;
    for (auto __ptr = next ; __ptr != this ; __ptr = __ptr->next) {
        const auto __off = get_bias(__ptr);
        std::cerr << std::format("  [{}, {})\n", __off, __off + __len);
    }
}

inline void global_allocator::debug() {
    for (std::size_t i = kAlign ; i < kBit ; ++i) {
        auto &list = free_list[i];
        std::cerr << std::format("Free list {}:\n", i);
        list.debug(i);
    }

    std::cerr << "\n\nMemory allocated:\n";

    // Array to store whether in an free block.

    bool *arr = new bool[1 << (kBit - kAlign)] {};

    for (std::size_t i = 1 ; i < (1 << (kBit - kAlign)) ; ++i)
        arr[i] = test(i);
    for (std::size_t i = 1 ; i < (1 << (kBit - kAlign)) ; ++i)
        arr[i] |= arr[i >> 1];
    for (std::size_t i = (1 << (kBit - kAlign)) - 1 ; i > 0 ; --i)
        arr[i >> 1] |= arr[i];

    for (std::size_t i = 0 ; i < kBit - kAlign ; ++i) {
        rank_t __rk = kBit - 1 - i;
        std::size_t __beg = 1 << i;
        std::size_t __end = 1 << (i + 1);
        std::cerr << std::format("  Rank {}:\n", __rk);
        for (auto j = __beg ; j != __end ; ++j) {
            if (arr[j] || !arr[j >> 1]) continue;
            auto l = (j - __beg) << __rk;
            auto r = l + (1 << __rk);
            std::cerr << std::format("    [{}, {})\n", l, r);
        }
    }

    delete [] arr;
}



} // namespace dark
