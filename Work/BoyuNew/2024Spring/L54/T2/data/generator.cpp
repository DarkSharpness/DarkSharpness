#include <format>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <ranges>
#include <vector>
#include <set>
#include <cmath>

struct random_machine {
    std::size_t seed;
    explicit random_machine(std::size_t seed) : seed(seed) {}
    std::size_t operator()() {
        seed ^= seed << 13;
        seed ^= seed >> 17;
        seed ^= seed << 5;
        return seed;
    }

    void next(std::size_t __n) {
        for (std::size_t i = 0 ; i < __n ; ++i)
            (void)(*this)();
    }
};

// Fixed random seed
random_machine my_rand(20240422);

consteval std::array <int, 10> get_num() {
    std::array <int, 10> res = {
        3,
        10,
        1000,
        10000,
        100000,
    };
    for (int i = 5 ; i < 10 ; ++i)
        res[i] = 100000;
    return res;
}

signed main() {
    constexpr int N = 1e7 + 3;
    for (int i = 0 ; i < 10 ; ++i) {
        std::fstream in  (std::format("{}.in", i + 1), std::ios::out);
        std::fstream out (std::format("{}.out", i + 1), std::ios::out);

        my_rand.next(123 * i);

        const int n = get_num().at(i);
        const int m = std::pow(2, my_rand() % int(std::log2(n)));

        in << n << ' ' << m << '\n';

        std::ranges::copy(
            std::views::iota(0, n) |
            std::views::transform([=](int) { return my_rand() % N + 1; }),
            std::ostream_iterator<int>(in, " ")
        );
    }
    return 0;
}
