#include <iostream>

template <int ...str>
void print() {
    static constexpr char arr[] = {str...};
    for (char c : arr) std::cout << c;
}

using uint128_t = __uint128_t;

template <char ...str>
consteval __uint128_t operator "" _u128() {
    __uint128_t res = 0;
    const uint128_t max = -1;
    for (char c : {str...}) {
        if (c < '0' || c > '9') throw;
        int d = c - '0';
        if (res > max / 10) throw;
        res = res * 10 + d;
        if (res < __uint128_t(d)) throw;
    }
    return res;
}


signed main() {
    print<'h', 'e','l','l','o', '\n'>(); // Hello    
    constexpr uint128_t x = 114514_u128;
    std::cout << (uintptr_t)x << std::endl; // 123123
    return 0;
}