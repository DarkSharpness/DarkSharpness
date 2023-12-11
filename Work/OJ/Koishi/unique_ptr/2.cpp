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
    std::vector <unique_ptr <int>> ptr(n);

    for (std::size_t i = 0 ; i < n ; ++i)
        ptr[i] = sjtu::make_unique <int> (i);

    for (std::size_t i = 0 ; i < n ; ++i)
        std::swap(ptr[i], ptr[my_rand() % (i + 1)]);

    for (std::size_t i = 0 ; i < n ; ++i)
        std::swap(ptr[i], ptr[my_rand() % (i + 1)]);

    for (std::size_t i = 0 ; i < n ; ++i)
        std::cout << *ptr[i] << " \n"[i + 1 == n];
}

signed main() {
    rand_test <100000> ();
    return 0;
}