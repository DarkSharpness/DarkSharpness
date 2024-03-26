#include <format>
#include <fstream>
#include <iostream>
#include <cstdint>
#include <vector>
#include <algorithm>

std::size_t my_rand() {
    return (std::size_t)rand() * (RAND_MAX + 1) + rand();
}

constexpr int nargs[] = {
    1 , 10, 100 , 1000 , 10000,
    int(1e5), int(1e6), int(2e6) , int(2e6) , int(2e6)
};

int buf[nargs[9]];

signed main() {
    srand(time(0));

    for (int i = 1 ; i <= 10 ; ++i) {
        std::fstream in  (std::format("{}.in", i), std::ios::out);
        std::fstream out (std::format("{}.out", i), std::ios::out);

        const int n = nargs[i - 1];
        const int m = INT32_MAX;

        in << n << '\n';
        for (int j = 0 ; j < n ; ++j) buf[j] = my_rand() % m;
        std::sort(buf, buf + n);
        for (int j = 0 ; j < n ; ++j) in << buf[j] << ' ';
    }
    return 0;
}
