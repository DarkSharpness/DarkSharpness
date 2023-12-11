#include <vector>
#include <thread>
#include <format>
#include <iostream>

void test(int i) {
    auto result =
        system(std::format("std_2 < {}.in > {}.tmp", i, i).data());
    if (result) {
        std::cerr << std::format("Test {} failed\n", i);
    }
}

signed main() {
    if (system(std::format("g++ std_2.cpp -o std_2 -O2 -std=c++20").data()))
        throw std::runtime_error("Compile Error");

    std::vector <std::thread> pool;
    for (int i = 1 ; i <= 20 ; ++i) pool.emplace_back(test, i);

    for (auto &i : pool) i.join();
    remove("std_2.exe");
    return 0;
}
