#include <format>
#include <fstream>
#include <iostream>
#include <ranges>
#include <cmath>

signed main() {
    srand(time(0));
    for (int i = 4 ; i <= 10 ; ++i) {
        std::fstream in  (std::format("{}.in", i), std::ios::out);
        std::fstream out (std::format("{}.out", i), std::ios::out);
        const int n = i * i * i * 100;
        in << n << std::endl;
        for (int j = 1 ; j <= n ; ++j)
            in << rand() % 3 + 1 << " ";
    }
    return 0;
}
