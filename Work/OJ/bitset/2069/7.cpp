#include "src.hpp"
#include "local.h"


template <check T = dynamic_bitset>
void test_corner() {
    T x(114514);
    auto __print = [&]() -> void {
        std::cout << x.none() << ' ' << x.all() << '\n';
        std::cout << "------------------------------\n";
    };
    __print();
    x.flip();
    __print();
    x.set();
    __print();
    x.reset();
    __print();
    x.flip();
    __print();
    x.set(x.size() - 1, false);
    __print();
    x.flip();
    __print();
    x.set().reset().flip().flip();

    for (std::size_t i = 0 ; i < x.size() / 2 ; ++i) x.set(i << 1, false);
    __print();
}

signed main() {
    test_corner();
    return 0;
}
