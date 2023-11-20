#include "src.hpp"
#include "local.h"

#include <chrono>

template <check T = dynamic_bitset>
void test_speed_0() {
    const int N = 1 << 19;
    T x;
    for (int i = 0 ; i < 256 ; ++i) x <<= N;
    if (!x.none()) std::cout << "Error\n";
}

template <check T = dynamic_bitset>
void test_speed_1() {
    const int N = 1 << 14;
    T x;
    for (int i = 0 ; i < N ; ++i) x <<= 512;
    if (!x.none()) std::cout << "Error\n";
    for (int i = 0 ; i < N / 2 ; ++i) x >>= (512 * 2);
    if (!x.none()) std::cout << "Error\n";
}

int main() {
    // const auto start    = std::chrono::high_resolution_clock().now();
    test_speed_0();
    test_speed_1();
    // const auto finish   = std::chrono::high_resolution_clock().now();
    // std::cerr << "Time: " <<
    //     std::chrono::duration_cast <std::chrono::milliseconds> (finish - start).count()
    //     << " ms\n";
    return 0;
}
