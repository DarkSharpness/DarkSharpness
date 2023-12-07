#include <thread>
#include <fstream>
#include <iostream>

void func() {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    FILE* fp = std::fopen("test.txt", "w");
    std::fprintf(fp, "Hello World\n");
}

signed main() {
    std::thread t = std::thread(func);
    t.detach();
    std::cout << "Over\n";
    return 0;
}