// #include "any.h" // 你的 any 实现路径
#include "src.hpp"
#include <iostream>

signed main() {
    using koishi::any;
    any x;
    x = 1919810;
    std::cout << x.cast <int> () << std::endl;
    x = 114.514;

    try {
        std::cout << x.cast <int> () << std::endl;
    } catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
    }

    auto ptr = x.try_cast <double> ();
    if (ptr) std::cout << "Double value: " << *ptr << std::endl;
    // if C++ 17 or later, try this:
    // if (auto ptr = x.try_cast <double> ()) std::cout << "Double value: " << *ptr << std::endl;

    any y {x};
    std::cout << y.cast <double> () << std::endl;

    any z {std::move(x)};
    if (x.is_empty()) std::cout << "x is empty" << std::endl;

    std::cout << z.cast <double> () << std::endl;
    return 0;
}
