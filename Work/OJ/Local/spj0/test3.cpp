#include <vector>
#include <thread>
#include <format>
#include <iostream>

signed main() {
    for (int i = 1 ; i <= 20 ; ++i) remove (std::format("{}.tmp", i).data());
    return 0;
}
