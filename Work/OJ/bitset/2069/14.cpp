#include "src.hpp"
#include "local.h"

template <class T = dynamic_bitset>
void test_shift() {
    T x(65);
    x.flip();

    for(int i = 50 ; i < 1145 ; ++i) {
        x <<= i * 2;
        x <<= 0;
        print_detail(x);
        x >>= i * 2;
        x >>= 0;
    }

    x <<= 1143 * 2;
    x.set();

    for(int i = 50 ; i < 1145 ; ++i) {
        x >>= i * 2;
        x <<= 0;
        print_detail(x);
        x.flip();
        x <<= i * 2;
        x >>= 0;
        x.flip();
    }

    x >>= 1919810;
    x <<= 99;
    print_detail(x);
}

signed main() {
    test_shift();
    return 0;
}
