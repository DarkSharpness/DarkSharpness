// Benchmark
#include "src.hpp"
#include <chrono>
#include <iostream>
#include <list>
#include <random>

struct data_pack {
    std::string str;
    int arr[4];
    data_pack() = default;
    data_pack(int x) { arr[0] = x; }
};

template <size_t _N, typename _List>
void init(_List &l) {
    size_t n = _N;
    while (n-- > 0) l.push_back(n);
}


template <typename _List>
int64_t test_bench(_List &&l) {
    auto it = l.begin();
    if (l.size() & 1) ++it;
    auto start = std::chrono::high_resolution_clock::now();

    /* Random erase. */
    for (int i = 0 ; i < 490000 ; ++i) {
        it = ++l.erase(it);
    }

    it = l.begin();
    /* Random insert */
    for (int i = 0; it != l.end() ; ++i) {
        auto tmp = it;
        l.insert(it, i);
        it = ++ ++tmp;
    }

    /* Random insert */
    for (int i = 0; i < 400000 ; ++i) {
        it = --l.insert(it, i);
    }

    it = l.end();
    for (int i = 0 ; i < 100000 ; ++i) {
        it = -- -- --l.insert(it, 100);
        it = l.erase(it);
        l.pop_front();
    }

    for (int i = 0 ; i < 100000 ; ++i) {
        ++ ++it;
        it = l.erase(it);
        l.push_back(i); 
    }

    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
}

template <typename _List>
int64_t test_assign(_List &&l, _List &&s) {
    auto start = std::chrono::high_resolution_clock::now();
    l = s;
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
}


int main() {
    std::list   <data_pack> l1,l3;
    sjtu::list  <data_pack> l2,l4;
    constexpr size_t N = 1e6;
    init<N>(l1);
    init<N>(l2);
    int64_t t1{}, t2{};

    init<N/2>(l3);
    init<N/2>(l4);
    t1 += test_assign(l3, l1);
    t2 += test_assign(l4, l2);
    l3.clear();
    l4.clear();

    init<N/2*3>(l3);
    init<N/2*3>(l4);
    t1 += test_assign(l3, l1);
    t2 += test_assign(l4, l2);
    l3.clear();
    l4.clear();

    for (int __cnt = 0; __cnt < 4; ++__cnt) {
        t1 += test_bench(l1);
        t2 += test_bench(l2);
    }

    int64_t checksum1{}, checksum2{};
    for (auto &e : l1) checksum1 += e.arr[0];
    for (auto &e : l2) checksum2 += e.arr[0];

    t1 /= 1000000;
    t2 /= 1000000;

    std::cout << (l1.size() == l2.size() && checksum1 == checksum2) << ' ' << t1
              << ' ' << t2 << '\n';
    return 0;
}
