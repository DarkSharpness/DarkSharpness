#include <format>
#include <fstream>
#include <iostream>
#include <cstdint>
#include <vector>
#include <algorithm>

std::size_t my_rand() {
    return (std::size_t)rand() * (RAND_MAX + 1) + rand();
}

const int nargs[5] = { 1 , 10, 100 , 1000 , 5000 };

signed main() {
    srand(time(0));
    for (int i = 1 ; i <= 5 ; ++i) {
        std::fstream in  (std::format("{}.in", i), std::ios::out);
        std::fstream out (std::format("{}.out", i), std::ios::out);

        const int n = nargs[i - 1];  // Max n = 100000
        const int m = my_rand() % (i * i * 200) + 1;

        in << n << ' ' << m << '\n';
    }
    return 0;
}
