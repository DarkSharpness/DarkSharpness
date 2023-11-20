#include "src.hpp"
#include "local.h"

template <check T = dynamic_bitset>
void test_fxxk() {
    T x(233);
    x <<= 65;

    T y(x);
    y.flip();
    for(std::size_t i = 0 ; i != 65 ; ++i)
        y.set(my_rand() % y.size(), my_rand() & 1);

    auto z = x;
    z ^= y;
    z <<= (my_rand() % 64);
    x |= y;
    x >>= (my_rand() % 65);
    y ^= x;
    y >>= (my_rand() % 66);
    z &= x;
    z <<= (my_rand() % 63);
    z |= y;
    y <<= (my_rand() % 67);
    y ^= z;

    print_detail(x);
    print_detail(y);
    print_detail(z);
}

int main() {
    for (int i = 0 ; i < 100 ; ++i) test_fxxk();
    return 0;
}
