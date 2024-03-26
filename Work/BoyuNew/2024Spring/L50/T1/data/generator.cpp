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

        int put = 0;
        int cnt = 0;
        int bin = 0;

        auto __gen = [&]() -> int {
            int op = my_rand() % 3 + 1;
            if (my_rand() % n < 10)
                op = 4;
            if (op == 2 && cnt == 0)
                op = 3;
            if (op == 3 && bin == 0)
                op = (cnt == 0) ? 4 : 2;
            if (op == 4 && put == 5)
                op = 1;
            return op;
        };

        in << n << '\n';
        for (int i = 1 ; i <= 3 ; ++i)
            in << 1 << ' ' << i << '\n';
        cnt = 3;
        for (int i = 4; i < n; i++) {
            int op = __gen();
            in << op;
            if (op == 1) {
                in << ' ' << i;
                ++cnt;
            } else if (op == 2) {
                --cnt; ++bin;
            } else if (op == 3) {
                --bin; ++cnt;
            } else {
                ++put;
            }
            in << '\n';
        }
        in << 4 << '\n';

    }
    return 0;
}
