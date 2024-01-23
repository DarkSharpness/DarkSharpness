#include <format>
#include <fstream>
#include <iostream>

std::size_t my_rand() {
    return (std::size_t)rand() * (RAND_MAX + 1) + rand();
}

signed main() {
    srand(time(0));
    for (int i = 1 ; i <= 9 ; ++i) {
        std::fstream in  (std::format("{}.in", i), std::ios::out);
        std::fstream out (std::format("{}.out", i), std::ios::out);

        const int n = i * i * i * 100;      // Max n = 100000
        const int m = i * i * i * 10 - 1;   // Max m = 9999

        in << n << '\n';
        for (int j = n ; j --> 0; ) {
            if (rand() & 7) {
                in << (my_rand() % m + 1);
            } else {
                in << (my_rand() % n + 1);
            }
            in << " \n"[i == 0];
        }
    }

    // Corner test for n = 100000
    std::fstream in  ("10.in", std::ios::out);
    std::fstream out ("10.out", std::ios::out);
    const int n = 100000;
    auto && fmt = "100000 ";
    in << n << '\n';
    for (int i = n ; i --> 0; ) in << fmt;
    in << '\n';
    return 0;
}