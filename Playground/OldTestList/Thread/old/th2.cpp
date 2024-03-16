#include <iostream>
#include <thread>

void modify(int x) { std::cout << ++x << '\n'; }

signed main() {
    int a = 0;
    std::thread t = std::thread(modify,a);
    a = 3;
    t.join();
    t = std::thread(modify,std::ref(a));
    a = 3;
    t.join();

    // std::cout << a << '\n';

    return 0;
}