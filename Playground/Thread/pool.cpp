#include <thread>
#include <vector>
#include <iostream>

signed main() {
    std::vector <std::thread> threads;
    for (int i = 0; i < 10; ++i) {
        threads.emplace_back(std::thread([i]() {
            std::this_thread::sleep_for(std::chrono::seconds(i));
            std::cout << "Hello World!\n";
        }));
    }
    for (auto& thread : threads) thread.join();
    return 0;
}
