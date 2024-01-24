#include <iostream>
#include <format>
#include <thread>
#include <vector>

void remove_file(int i) {
    remove(std::format("{0}.exe", i).c_str());
}

void generate(int i) {
    system(std::format("g++ -Wall -O2 -o {0} {0}.cpp -std=c++20", i).c_str());
    system(std::format("{0}.exe > {0}.ans", i).c_str());
}

signed main() {
    std::vector <std::thread> threads;

    for (int i = 1; i <= 20; ++i) threads.emplace_back(remove_file, i);
    for (auto &thread : threads) thread.join();
    threads.clear();

    for (int i = 1; i <= 20; ++i) threads.emplace_back(generate, i);
    for (auto &thread : threads) thread.join();
    threads.clear();

    for (int i = 1; i <= 20; ++i) threads.emplace_back(remove_file, i);
    for (auto &thread : threads) thread.join();
    threads.clear();

    return 0;
}