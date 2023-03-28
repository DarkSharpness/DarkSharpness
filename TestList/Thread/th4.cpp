#include <iostream>
#include <thread>
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

signed main() {
    std::thread t1(work);
    std::thread t2(work);
    t1.join();
    t2.join();
    std::cout << n << '\n';
    return 0;
}