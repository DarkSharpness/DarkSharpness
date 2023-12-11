#include "2090.cpp"
#include <iostream>

signed main() {
    sjtu::any_ptr a = sjtu::make_any_ptr(int(1));
    sjtu::any_ptr b = a;

    a.unwrap <int> () = 2;
    std::cout << b.unwrap<int>() << std::endl; // 2

    b = new std::string;
    b.unwrap <std::string> () = "Hello, world!";
    std::cout << b.unwrap <std::string> () << std::endl; // Hello, world!

    try {
        a.unwrap <std::string> () = "a";
    } catch (const std::exception &e) {
        std::cout << e.what() << std::endl; // bad cast
    }

    return 0;
}