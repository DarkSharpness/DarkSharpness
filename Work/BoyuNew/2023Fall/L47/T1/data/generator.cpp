#include <format>
#include <fstream>
#include <iostream>

std::size_t my_rand() {
    return (std::size_t)rand() * (RAND_MAX + 1) + rand();
}

signed main() {
    srand(time(0));
    for (int i = 1 ; i <= 10 ; ++i) {
        std::fstream in  (std::format("{}.in", i), std::ios::out);
        std::fstream out (std::format("{}.out", i), std::ios::out);

        const int n = i * i * i * 100;      // Max n = 100000

        in << n << '\n';
        for (int j = 0 ; j < n ; ++j)
            in << (my_rand() % INT_MAX) << ' ';
    }
    return 0;
}
