#include "src.hpp"
#include "local.h"


template <class T = dynamic_bitset>
void test_func() {
    T x(114514);
    T y(1919810);

    y.flip();

    x ^= y;
    print_detail(x);

    x.flip();
    y ^= x;
    y.flip().flip();

    print_detail(y);
}

template <class T = dynamic_bitset>
void test_rand() {
    T x;
    for(int i = 0 ; i < 1919810 ; ++i) x.push_back(my_rand() & 0b1);
    print_detail(x);
    T y = x;
    for(int i = 0 ; i < 114514 ; ++i) y.set(my_rand() % x.size(), my_rand() & 0b1);
    print_detail(x ^= y);
}

template <class T = dynamic_bitset>
void test_corner() {
    T x;
    T y;
    for (int i = 0; i < 321; ++i) y.push_back(my_rand() & 0b1);
    for (int i = 0; i < 765; ++i) {
        x.push_back(my_rand() & 0b1);
        print_detail(x ^= y);
        if (i == 365) {
            x ^= x;
            print_detail(x);
        }
    }
}

signed main() {
    test_func();
    test_rand();
    test_corner();
    return 0;
}
