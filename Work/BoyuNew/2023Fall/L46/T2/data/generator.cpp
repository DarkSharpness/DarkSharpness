#include <format>
#include <fstream>
#include <iostream>
#include <ranges>
#include <cmath>

std::size_t my_rand() {
    return (std::size_t)rand() * (RAND_MAX + 1) + rand();
}

std::size_t rand64() {
    return (my_rand() << 32) ^ (my_rand());
}


signed main() {
    srand(time(0));
    for (int i = 1 ; i <= 10 ; ++i) {
        std::fstream in  (std::format("{}.in", i), std::ios::out);
        std::fstream out (std::format("{}.out", i), std::ios::out);
        const long long N = pow(10, i * 1.5 + 3);
        in << rand64() % N + 1 << std::endl;
    }
    return 0;
}
