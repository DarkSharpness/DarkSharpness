#include <iostream>
#include <atomic>
#include <mutex>

std::atomic <bool> a;

void spinlock() {
    while (a.exchange(true, std::memory_order_acquire)) {
        // Do nothing
        a.store(false, std::memory_order_release);
    }
}

std::mutex m;

void spinlock2() {
    while (m.try_lock()) {
        // Do nothing
        m.unlock();
    }
}



signed main() {
    return 0;
}