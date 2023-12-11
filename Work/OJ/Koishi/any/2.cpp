#include "src.hpp"
#include <iostream>

void test_cast() {
    using koishi::any;
    any a = std::string("Hello, world!");
    std::cout << a.cast <std::string> () << std::endl;
    const any b = a;
    std::cout << b.cast <std::string> () << std::endl;

    a = 114.514;
    std::cout << a.cast <double> () << std::endl;
    const any c = std::move(a);
    std::cout << c.cast <double> () << std::endl;
    if (a.is_empty()) std::cout << "a is empty" << std::endl;
}

void test_try_cast() {
    using koishi::any;
    any a = std::string("Hello, world!");
    std::cout << *a.try_cast <std::string> () << std::endl;
    const any b = a;
    std::cout << *b.try_cast <std::string> () << std::endl;
}

signed main() {
    test_cast();
    test_try_cast();    
    return 0;
}
