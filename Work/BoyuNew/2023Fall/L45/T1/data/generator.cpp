#include <format>
#include <fstream>
#include <iostream>
#include <ranges>
#include <cmath>

std::size_t my_rand() {
    return (std::size_t)rand() * (RAND_MAX + 1) + rand();
}

signed main() {
    srand(time(0));
    for (int i = 1 ; i <= 10 ; ++i) {
        std::fstream in  (std::format("{}.in", i), std::ios::out);
        std::fstream out (std::format("{}.out", i), std::ios::out);

        const int n = i * 500;

        in << n << '\n';
        for (int i = n ; i --> 0; ) in << (my_rand() % n + 1) << " \n"[i == 0];
    }
    return 0;
}