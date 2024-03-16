#include <iostream>
#include <vector>
#include <thread>
#include <format>

using namespace std::chrono_literals;

void f(int &x) {
    std::this_thread::sleep_for(std::chrono::seconds(x + 1));
    std::cout << std::format ("Hello from thread {}\n", x);
}

signed main() {
    std::vector <std::thread> threads;
    std::vector <int> v(10);
    const auto start = std::chrono::high_resolution_clock::now();
    for(size_t i = 0 ; i < 10 ; ++i) {
        threads.emplace_back(f, std::ref(v.emplace_back(i)));
    }
    std::cout << "Hello from main!\n";
    for(auto& t : threads) t.detach();
    int tmp = 2;
    threads[9] = std::thread {f, std::ref(tmp)};
    // Wait for all threads to finish
    std::this_thread::sleep_for(12s);
    for(auto &t : threads) if (t.joinable()) t.join();
    const auto ending = std::chrono::high_resolution_clock::now();
    std::cout << std::format ("Time elapsed: {}ms\n",
        std::chrono::duration_cast<std::chrono::milliseconds>(ending - start).count());
    return 0;
}
