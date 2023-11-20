#include "src.hpp"
#include "local.h"


template <check T = dynamic_bitset>
void test_func() {
    std::string x = "1";
    for (int i = 0 ; i < 10 ; ++i) x += x;
    T y {x};

    print_detail(y);
    for (int i = 0 ; i < 63 ; ++i) y.push_back(0);
    print_detail(y);

    y.set();

    print_detail(y);
}

signed main() {
    test_func();
    return 0;
}
