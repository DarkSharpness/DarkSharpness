#include "src.hpp"
#include "local.h"

template <class T = dynamic_bitset>
void test_shift() {
    T x(65);
    x.set();
    while(x.size() != 1919) {
        x.push_back(my_rand() & 0b1);
        x.set(my_rand() % x.size(), my_rand() & 0b1);   
    }
    while(x.size() != 1145) {
        x >>= 1;
        x.flip();
        print_detail(x);
    }
}

signed main() {
    test_shift();
    return 0;
}
