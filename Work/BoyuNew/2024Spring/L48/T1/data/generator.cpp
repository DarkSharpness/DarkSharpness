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

        const int n = i * i * i * 100;  // Max n = 100000
        const int m = i < 5 ? i * 100 : INT32_MAX;

        in << n << ' ' << n << '\n';

        std::vector <int> v;
        v.reserve(n);

        for (int j = 0 ; j < n ; ++j) v.push_back(my_rand() % m);
        std::sort(v.begin(), v.end());

        for (int j = 0 ; j < n ; ++j) in << v[j] << ' ';
        in << '\n';

        const int maxn = v.back();
        for (int j = 0 ; j < n ; ++j) in << my_rand() % maxn << '\n';
    }
    return 0;
}
