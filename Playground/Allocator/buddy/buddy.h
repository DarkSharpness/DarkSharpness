#pragma once
#include "node.h"
#include <iostream>

namespace dark {

struct global_allocator {
private:
    /* Count of bits in one std::uint64_t */
    static constexpr std::size_t kCnt = 64;
    static constexpr std::size_t kArr = kLen * 2 / kCnt;

    forward_list free_list[kBit] {};    // Free list
    std::uint64_t bitmap[kArr] {};      // Whether a block is available

    /* Reset given bit to 1, and test whether buddy is dead. */
    bool reset_and_test(number_t __n, rank_t __rk) {
        auto &__val = bitmap[__n / kCnt];
        auto  __off = __n % kCnt;   // This offset.
        auto  __bud = __off ^ 1;    // The buddy's offset

        if ((__val >> __bud) & 0b1) {
            __val ^= 1ull << __off;
            remove_buddy(__n, __rk);
            return true;
        } else { /* Buddy not available case. */
            __val |= 1ull << __off;
            return false;
        }
    }

    /* Set given bit to 1. */
    void set_free(number_t __n) {
        bitmap[__n / kCnt] |= 1ull << (__n % kCnt);
    }
    /* Set given bit to 0. */
    void set_busy(number_t __n) {
        bitmap[__n / kCnt] &= ~(1ull << (__n % kCnt));
    }

    /* Test whether given range is available. */
    bool test(number_t __n) {
        return (bitmap[__n / kCnt] >> (__n % kCnt)) & 1;
    }

    /* Remove the buddy from free list. */
    void remove_buddy(number_t __n, rank_t __rk) {
        auto *__ptr = cast_node(set_index(__n ^ 1, __rk));
        __ptr->prev->next = __ptr->next;
        __ptr->next->prev = __ptr->prev;
    }

    /* Recursively find a suitable block. */
    void *try_alloc(rank_t __rk) {
        if (!free_list[__rk].empty()) {
            auto *__ptr = free_list[__rk].pop_front();
            set_busy(get_index(__ptr, __rk));
            return __ptr;
        }

        /* Find the first non-empty list.  */
        rank_t __m = __rk;
        while (free_list[++__m].empty())
            if (__m == kBit - 1) throw std::bad_alloc();

        void *__raw = free_list[__m].pop_front();
        auto  __num = get_index(__raw, __m);
        set_busy(__num);

        while (--__m >= __rk) {
            /* Split into 2 blocks, and recycle the latter one */
            auto *__ptr = static_cast <std::byte *> (__raw) + (1ull << __m);
            auto *__new = cast_node((void *)__ptr);

            free_list[__m].push_front(__new);
            set_free((__num <<= 1) | 1);
        }

        return __raw; // Return the first block.
    }

    /* Recycle a block and try to merge recursively. */
    void try_dealloc(number_t __n, rank_t __rk) {
        if (reset_and_test(__n, __rk))
            return try_dealloc(__n >> 1, __rk + 1);

        auto *__raw = set_index(__n, __rk);
        auto *__new = cast_node(__raw);
        free_list[__rk].push_front(__new);
    }

    static rank_t get_rank(std::size_t __n) {
        rank_t __m = kAlign; // Align min.
        while ((1ull << __m) < __n) ++__m;
        return __m;
    }

public:
    void first_init() {
        free_list[kBit - 1].push_front(cast_node(memory_pool));
        bitmap[0] = 2; // Only 1 block available.
    }

    void *allocate(std::size_t __n) {
        return try_alloc(get_rank(__n));
    }

    void deallocate(void *__ptr, std::size_t __n) {
        auto __rank = get_rank(__n);
        return try_dealloc(get_index(__ptr, __rank), __rank);
    }

    void debug();
};

inline static global_allocator alloc {};

inline void *malloc(std::size_t __n) {
    return alloc.allocate(__n);
}

inline void free(void *__ptr, std::size_t __n) {
    alloc.deallocate(__ptr, __n);
}

inline void debug() { return alloc.debug(); }

} // namespace dark
