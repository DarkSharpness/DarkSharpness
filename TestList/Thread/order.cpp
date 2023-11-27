#include <iostream>
#include <thread>
#include <format>
// #include <bits/stdc++.h>

using namespace std::chrono_literals;

int x , y ;
int r1, r2;

void func_1() {
    std::this_thread::sleep_for(0.1s);
    x = 1;
    r1 = y;
}

void func_2() {
    std::this_thread::sleep_for(0.1s);
    y = 1;
    r2 = x;
}

signed main() {
    std::thread t1;
    std::thread t2;
    for (int i = 0 ; i < 20 ; ++i) {
        x = y = r1 = r2 = 0;
        t1 = std::thread(func_1);
        t2 = std::thread(func_2);
        t1.join();
        t2.join();
        std::cout << std::format("r1 = {}, r2 = {}\n", r1, r2);
    }
    return 0;
}