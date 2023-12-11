#include <vector>
#include <thread>
#include <format>
#include <iostream>

void test(int i) {
    if (system(std::format("g++ -std=c++20 {0}.cpp -o {0} -O2",i).data()))
        std::cerr << std::format("Test {} compile error!\n", i);

    if (system(std::format("{0} < {0}.in > {0}.out", i).data()))
        std::cerr << std::format("Test {} runtime error!\n", i);
}

signed main() {
    std::vector <std::thread> pool;
    for (int i = 1 ; i <= 10 ; ++i) pool.emplace_back(test, i);

    for (auto &i : pool) i.join();
    for (int i = 1 ; i <= 10 ; ++i) remove(std::format("{}.exe", i).data());
    return 0;
}
