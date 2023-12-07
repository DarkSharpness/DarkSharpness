#include "src.hpp"
#include "utility.h"
#include <iostream>


template <typename _Tp>
void test() {
    _Tp x = {1 , 2};        // 1 / 2 = 0.5;
    std::cout << x << '\n'; // print out 1/2 
    for (int i = 0 ; i < 100 ; ++i) {
        _Tp y = { dark::rand() , dark::rand() };
        x += y;
    }
    std::cout << x << '\n';
}

signed main() {
    test <fraction <int>> ();
    for (int i = 0 ; i < 100 ; ++i) dark::rand();
    std::cout << dark::rand() << '\n';
    return 0;
}