#include <iostream>
#include <thread>
#include <atomic>
#include <format>
#include <mutex>

int n;
std::mutex m;
void work() {
    for(int i = 1 ; i <= 1000000 ; ++i) {
        m.lock();
        ++n;
        m.unlock();
    }
}

std::atomic <int> a;

void test() {
    for(int i = 1 ; i <= 1000000 ; ++i) { ++a; }
}


signed main() {
    auto start = std::chrono::high_resolution_clock::now();
    std::thread t1(work);
    std::thread t2(work);

    std::cout << t2.get_id() << '\n';

    t1.join();
    std::cout << t1.get_id() << ' ' << t1.joinable() << '\n';
    t2.join();

    auto ending = std::chrono::high_resolution_clock::now();

    std::cout << std::format ("Time elapsed: {}ms\n",
        std::chrono::duration_cast<std::chrono::milliseconds>(ending - start).count());

    std::cout << n << '\n';


    start = std::chrono::high_resolution_clock::now();
    t1 = std::thread(test);
    t2 = std::thread(test);
    t1.join();
    t2.join();
    ending = std::chrono::high_resolution_clock::now();
    std::cout << std::format ("Time elapsed: {}ms\n",
        std::chrono::duration_cast<std::chrono::milliseconds>(ending - start).count());

    std::cout << a << '\n';

    std::cout << sizeof(std::thread) << '\n';
    return 0;
}