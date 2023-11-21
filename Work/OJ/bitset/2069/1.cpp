#include "src.hpp"
#include "local.h"


template <class T = dynamic_bitset>
void basic_init() {
    std::string str = "01";
    str.reserve(129);
    for (int i = 0 ; i < 6 ; ++i) str += str;
    str.push_back('1');

    T x;
    T y {str};
    T z(100);

    print(x);
    print(y);
    print(z);
}

template <class T = dynamic_bitset>
std::size_t stack_killer() {
    T x[1000];
    for (int i = 0 ; i < 1000 ; ++i) x[i] = T("1");

    std::size_t sum = 0;
    for (int i = 0 ; i < 1000 ; ++i) sum += x[i].size();

    return sum;
}

template <class T = dynamic_bitset>
std::size_t press_tester() {
    constexpr std::size_t N = 512 << 20;
    constexpr std::size_t M = 4096;

    T y(N);
    std::size_t sum = 0;
    for (std::size_t i = 0 ; i < N / M ; ++i) sum += y[i * M];

    return sum;
}


signed main() {
    basic_init();
    if (stack_killer() != 1000)
        throw std::runtime_error("Haha");
    if (press_tester() != 0)
        throw std::runtime_error("Haha");
    return 0;
}
