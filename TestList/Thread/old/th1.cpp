#include <iostream>
#include <thread>


signed main() {
    std::thread th[10];
    for(int i = 0 ; i < 10 ; ++i)
        th[i] = std::thread([i](){ std::cout << "thread" << i << '\n'; });

    for(int i = 0 ; i < 10 ; ++i)
        th[i].join();

    return 0;
}