#pragma once
#include <chrono>
#include <iostream>

static size_t global_sum = 1;

template <typename _Map_t>
void heat(const _Map_t &map) {
    auto __cbeg = map.cbegin();
    auto __cend = map.cend();
    while (__cbeg != __cend) {
        // Anti optimization.
        ++global_sum;
        ++__cbeg;
    }
}

template <size_t _N, typename _Func_t>
void real_test(_Func_t &&func) {
    if constexpr (_N == 0) return;
    else {
        func();
        real_test <_N - 1> (std::forward <_Func_t> (func));
    }
}

template <size_t _N, typename _Func_t>
size_t test(_Func_t &&func) {
    auto __start = std::chrono::high_resolution_clock::now();
    real_test <_N> (std::forward <_Func_t> (func));
    auto __end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast
        <std::chrono::milliseconds> (__end - __start).count();
}

void panic_if(bool cond, std::string msg) {
    if (!cond) return;
    std::cout << "Panic: " << msg;
    std::exit(EXIT_FAILURE);
}

struct random_machine {
    size_t seed = 1919810;
    [[nodiscard]] size_t operator()() {
        seed = seed * 233 % 19260817;
        return seed;
    }
};
