#pragma once
#include "node.h"
#include <iostream>

namespace dark {

struct global_allocator {
private:
    /* Count of bits in one std::uint64_t */
    static constexpr std::size_t kCnt = 64;

    forward_list free_list[kBit] {};
    std::uint64_t bitmap[kLen * 2 / kCnt] {};

    /* Reset given bit to 0, and test whether buddy is dead. */
    bool reset_and_test(number_t __n) {
        auto &__val = bitmap[__n / kCnt];
        auto  __off = __n % kCnt;
        __val &= ~(1ull << __off);
        return ((__val >> (__off & ~1)) & 3) == 0;
    }

    /* Set given bit to 1. */
    void set(number_t __n) {
        bitmap[__n / kCnt] |= 1ull << (__n % kCnt);
    }

    /* Test whether given bit is 1. */
    bool test(number_t __n) {
        return (bitmap[__n / kCnt] >> (__n % kCnt)) & 1;
    }

    void *try_alloc(rank_t __rk) {
        if (__rk >= kBit) throw std::bad_alloc();
        if (!free_list[__rk].empty())
            return free_list[__rk].pop_remove();

        /* Split into 2 blocks, and recycle the latter one */
        auto *__raw = try_alloc(__rk + 1);
        auto *__ptr = static_cast<std::byte *>(__raw);
        auto *__new = create_node(__ptr + (1 << __rk));
        free_list[__rk].push_front(__new);
        return __raw;
    }

    void try_dealloc(number_t __n, rank_t __rk) {
        if (reset_and_test(__n)) /* Recycle parent if success */
            return try_dealloc(__n >> 1, __rk + 1);

        auto *__ptr = set_index(__n, __rk);
        auto *__new = create_node(__ptr);
        free_list[__rk].push_front(__new);
    }

    static rank_t get_rank(std::size_t __n) {
        rank_t __m = kAlign; // Align min.
        while ((1ull << __m) < __n) ++__m;
        return __m;
    }

public:
    void first_init() {
        free_list[kBit - 1].push_front(create_node(memory_pool));
        bitmap[0] = 1; // To prevent reset_and_test return true when __n = 1
    }

    void *allocate(std::size_t __n) {
        rank_t __rank = get_rank(__n);
        void *__ptr = try_alloc(__rank);
        set(get_index(__ptr, __rank));
        return __ptr;
    }

    void deallocate(void *__ptr, std::size_t __n) {
        auto __rank = get_rank(__n);
        return try_dealloc(get_index(__ptr, __rank), __rank);
    }

    void debug() {
        int cnt = 0;
        for (auto list : free_list) {
            std::cerr << "Free list " << cnt++ << ":\n";
            list.debug();
        }

        std::cerr << "\n\nRanges in use:\n";

        for (std::size_t i = 0 ; i < kBit - kAlign ; ++i) {
            rank_t __rk = kBit - 1 - i;
            std::size_t __beg = 1 << i;
            std::size_t __end = 1 << (i + 1);
            std::cerr << "  rank " << __rk << ":\n";
            for (auto j = __beg ; j != __end ; ++j) {
                if (!test(j)) continue;
                auto l = (j - __beg) << __rk;
                auto r = l + (1 << __rk);
                std::cerr << "    [" << l << ',' << r << "]\n";
            }
        }
    }
};

inline static global_allocator alloc {};

inline void *malloc(std::size_t __n) {
    static bool first = true;
    if (first) {
        alloc.first_init();
        first = false;
    }
    return alloc.allocate(__n);
}

inline void free(void *__ptr, std::size_t __n) {
    alloc.deallocate(__ptr, __n);
}

inline void debug() { return alloc.debug(); }

} // namespace dark
