#include <format>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <ranges>
#include <set>

std::size_t my_rand() {
    return (std::size_t)rand() * (RAND_MAX + 1) + rand();
}

const int W = 1e6 - 1;

signed main() {
    // Fixed random seed
    srand(20240410);
    for (int i = 1 ; i <= 10 ; ++i) {
        std::fstream in  (std::format("{}.in", i), std::ios::out);
        std::fstream out (std::format("{}.out", i), std::ios::out);

        const int n = i * i *10;
        const int m = n * 10;
        in << std::format("{} {}\n", n, m);
        for (int i = 1 ; i <= m ; ++i) {
            int u = my_rand() % n + 1;
            int v = my_rand() % n + 1;
            int w = my_rand() % W + 1;
            in << std::format("{} {} {}\n", u, v, w);
        }
    }
    return 0;
}
