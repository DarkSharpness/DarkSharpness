#include "src.hpp"
#include "local.h"


template <check T = dynamic_bitset>
void test_func() {
    std::string x = "1";
    for (int i = 0 ; i < 10 ; ++i) x += x;
    T y {x};
    print_detail(y);

    y.push_back(1);
    y.push_back(1);
    y.set(y.size() - 2, 0);

    y.reset();

    print_detail(y);
}

signed main() {
    test_func();
    return 0;
}
