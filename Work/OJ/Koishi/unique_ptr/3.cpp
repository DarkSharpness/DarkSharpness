#include "src.hpp"
#include <iostream>
#include <vector>

std::size_t my_rand() {
    static std::size_t seed = 114514;
    seed = seed * 1919 + 810;
    return seed ^ (seed << 19) ^ (seed >> 19);
}

template <std::size_t n>
void rand_test() {
    using sjtu::unique_ptr;
    std::vector <unique_ptr <std::string>> ptr(n);
    for (std::size_t i = 0 ; i < n ; ++i)
        ptr[i] = unique_ptr <std::string> (new std::string(std::to_string(i)));

    for (std::size_t i = 0 ; i < n ; ++i) {
        unique_ptr <std::string> tmp;
        tmp = unique_ptr <std::string> (ptr[i].release());
        if (ptr[i].get()) std::exit(1);
    
        auto &rhs = ptr[my_rand() % n];
        ptr[i] = unique_ptr <std::string> (rhs.release());
        if (rhs.get()) std::exit(1); 

        rhs = unique_ptr <std::string> (tmp.release());
        if (tmp.get()) std::exit(1);
    }

    for (std::size_t i = 0 ; i < n ; ++i)
        std::cout << *ptr[i] << " \n"[i + 1 == n];
}

signed main() {
    rand_test <100000> ();
    return 0;
}