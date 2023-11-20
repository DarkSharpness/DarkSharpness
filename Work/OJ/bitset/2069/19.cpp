#include "src.hpp"
#include "local.h"

#include <chrono>

template <check T = dynamic_bitset>
void test_speed() {
    const int N = 1024 << 20;
    T x(N);

    x.reset();
    if (!x.none()) std::cout << "Error\n";

    x.set();
    if (!x.all())  std::cout << "Error\n";

    x ^= x;
    if (!x.none()) std::cout << "Error\n";

    x |= x;
    if (!x.none()) std::cout << "Error\n";

    x &= x;
    if (!x.none()) std::cout << "Error\n";

    x.flip();
    if (!x.all())  std::cout << "Error\n";
}

int main() {
    // const auto start    = std::chrono::high_resolution_clock().now();
    test_speed();
    test_speed();
    // const auto finish   = std::chrono::high_resolution_clock().now();
    // std::cerr << "Time: " <<
    //     std::chrono::duration_cast <std::chrono::milliseconds> (finish - start).count()
    //     << " ms\n";
    return 0;
}
