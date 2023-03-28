#include <iostream>
#include <thread>
#include <mutex>

void print() { for(int i = 0 ; i < 1000000 ; ++i); std::cout << "this is a leaf thread\n"; }


signed main() {
    std::thread t = std::thread(print);
    // t.detach();
    t.join();
    std::cout << t.joinable() << '\n';
    std::cout << "end of main\n";
    return 0;
}