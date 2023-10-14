#include <iostream>
#include <atomic>
#include <thread>

struct pack { int t[1000]; };

std::atomic <uint64_t> a(0);
uint64_t b = 0;
void work1() { a = a + 1; }

signed main() {
    auto t0 = std::chrono::high_resolution_clock::now();
    for(int i = 0 ; i < 1000000 ; ++i) work1();
    auto t1 = std::chrono::high_resolution_clock::now();
    std::cout << std::boolalpha;
    std::cout << (t1 - t0).count() << "\n\n";
    std::atomic <pack> g;
    std::cout << g.is_always_lock_free << '\n';
    std::cout << a.is_always_lock_free << '\n';

    return 0;
}
