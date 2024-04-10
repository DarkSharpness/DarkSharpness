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


signed main() {
    // Fixed random seed
    srand(114514);
    std::set <std::pair <int, int>> edges;
    for (int i = 1 ; i <= 10 ; ++i) {
        std::fstream in  (std::format("{}.in", i), std::ios::out);
        std::fstream out (std::format("{}.out", i), std::ios::out);

        const int n = i * i * i * 100;
        const int m = my_rand() % n  + 1;

        in << n << ' ' << m << '\n';
        for (int i = 1 ; i <= m ; ++i) {
            int a = my_rand() % n + 1;
            int b = my_rand() % n + 1;
            if (a > b) std::swap(a, b);
            if (a == b || edges.count({a, b})) {
                --i;
                continue;
            }
            edges.insert({a, b});
            in << a << ' ' << b << '\n';
        }
    }
    return 0;
}
