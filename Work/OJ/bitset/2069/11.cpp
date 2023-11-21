#include "src.hpp"
#include "local.h"


template <class T = dynamic_bitset>
void test_xor() {
    T a;
    T b;
    T x;
    T y;
    for (int i = 0 ; i < 1145 ; ++i) a.push_back(my_rand() & 0b1);
    for (int i = 0 ; i < 1145 ; ++i) b.push_back(my_rand() & 0b1);

    x = a;
    x &= b;
    x.flip();

    y = a;
    y |= b;
    y &= x;

    // y = ~(a & b) & (a | b) = a ^ b

    x = a;
    x ^= b; // x = a ^ b

    print_detail(x ^= y); // Now, x must be 0
}



template <class T = dynamic_bitset>
void test_swap() {
    constexpr auto __gen = []() -> T {
        T x;
        for(int i = 0 ; i < 1919 ; ++i) x.push_back(my_rand() & 0b1);
        return x;
    };
    T x = __gen();
    T y = __gen();

    const auto X = x;
    const auto Y = y;

    x ^= y;
    y ^= x;
    x ^= y;

    print_detail((x ^= Y).flip());
    print_detail((y ^= X).flip().flip());
}


signed main() {
    for (int i = 0 ; i < 3 ; ++i) test_xor();
    for (int i = 0 ; i < 3 ; ++i) test_swap();
    return 0;
}
