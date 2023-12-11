#include "src.hpp"
#include <iostream>
#include <vector>

std::size_t my_rand() {
    static std::size_t seed = 114514;
    seed = seed * 1919 + 810;
    return seed ^ (seed << 19) ^ (seed >> 19);
}

void test_leak() {
    using koishi::any;
    using std::string;
    const any a[4] = {
        string("Koishi"),
        int(1919810),
        double(114.514),
        nullptr,
    };
    constexpr int n = 10000;
    std::vector <any> v(n);
    for (int i = 0 ; i < n ; ++i) if (!v[i].is_empty()) std::exit(1);
    for (int i = 0 ; i < n ; ++i) v[i] = a[my_rand() % 4];
    for (int i = 0 ; i < n ; ++i) {
        int t = my_rand() % n;
        if (i != t) v[i] = std::move(v[t]);
    }
    for (int i = 0 ; i < n ; ++i)
        if (v[i].is_empty()) v[i] = a[my_rand() % 4];
    for (int i = 0 ; i < n ; ++i) {
        if (auto __ptr = v[i].try_cast <int> ())    std::cout << *__ptr << '\n';
        if (auto __ptr = v[i].try_cast <double> ()) std::cout << *__ptr << '\n';
        if (auto __ptr = v[i].try_cast <string> ()) std::cout << *__ptr << '\n';
        if (v[i].is_empty()) std::cout << "nullptr\n";
    }
}

signed main() {
    test_leak();
    return 0;
}
