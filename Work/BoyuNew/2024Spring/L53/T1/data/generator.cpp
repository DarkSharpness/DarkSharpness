#include <format>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <ranges>
#include <vector>
#include <set>

std::size_t my_rand() {
    return (std::size_t)rand() * (RAND_MAX + 1) + rand();
}



signed main() {
    // Fixed random seed
    srand(20240410);
    for (int i = 1 ; i <= 10 ; ++i) {
        std::fstream in  (std::format("{}.in", i), std::ios::out);
        std::fstream out (std::format("{}.out", i), std::ios::out);
        for (int j = i ; --j ;) (void)my_rand();

        const int n = i * i * 100;
        const int m = my_rand() % n + 1;
        auto &&gen = [n]() -> int { return my_rand() % n + 1; };
        in << std::format("{} {}\n", n, m);
        std::set <std::pair <int, int>> edges;
        for (int j = 1, u, v ; j <= m ; ++j) {
            do {
                u = gen(), v = gen();
                if (u > v) std::swap(u, v);
            } while (u == v || edges.count({u, v}));
            edges.insert({u, v});
            in << std::format("{} {}\n", u, v);
        }
    }
    return 0;
}
