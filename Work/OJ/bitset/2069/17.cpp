#include "src.hpp"
#include "local.h"

template <check T = dynamic_bitset>
void test_final() {
    T x;
    for(int i = 0 ; i < 1145 ; ++i) x.push_back(my_rand() & 1);

    T y(1145);

    for(int i = 0 ; i < 1000 ; ++i) {
        for(int i = 0 ; i < 191 ; ++i) y.set(my_rand() % y.size(), my_rand() & 1);  
        print_detail((x <<= i) >>= i);
        switch(i % 3) {
            case 0: x &= y; break;
            case 1: x |= y; break;
            case 2: x ^= y; break;
        }
    }

    for(int i = 0 ; i < 1000 ; ++i) {
        for(int i = 0 ; i < 191 ; ++i) y.set(my_rand() % y.size(), my_rand() & 1);  
        print_detail((x >>= i) <<= i);
        switch(i % 3) {
            case 0: x &= y; break;
            case 1: x |= y; break;
            case 2: x ^= y; break;
        }
    }
}

int main() {
    test_final();
    return 0;
}
