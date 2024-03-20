#include <format>
#include <fstream>
#include <iostream>
#include <cstdint>
#include <vector>
#include <algorithm>

std::size_t my_rand() {
    return (std::size_t)rand() * (RAND_MAX + 1) + rand();
}

signed main() {
    srand(time(0));
    for (int i = 1 ; i <= 10 ; ++i) {
        std::fstream in  (std::format("{}.in", i), std::ios::out);
        std::fstream out (std::format("{}.out", i), std::ios::out);

        const int n = i * i * 50;   // Max n = 5000
        const int m = i * i * 10;   // Max n = 1000

        in << n << '\n';
        for (int i = 1; i <= n; i++) {
            int x = my_rand() % n + 1;
            if (my_rand() % m == 1) x = 0;
            in << x << ' ';
        }

        in << '\n' << m << '\n';
        for (int i = 0; i < m; ++i) {
            int x = my_rand() % 5 + 1;
            in << x + i * 5 << '\n';
        }
    }
    return 0;
}
