#include "src.hpp"
#include "local.h"


template <check T = dynamic_bitset>
void test_func() {
    std::string x = "01";
    for (int i = 0 ; i < 11 ; ++i) x += x;
    T y {x};
    print_detail(y);
    y.flip();
    print_detail(y);
}

signed main() {
    test_func();
    return 0;
}
