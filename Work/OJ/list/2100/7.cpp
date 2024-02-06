// Benchmark
#include "src.hpp"
#include <chrono>
#include <iostream>
#include <list>

template <size_t _N, typename _List> void init(_List &l) {
  size_t n = _N;
  while (n-- > 0)
    l.push_back(n);
}

template <typename _List> int visit(_List &l) {
  int cnt = 0;
  for ([[maybe_unused]] auto &e : l)
    ++cnt;
  return cnt;
}

template <typename _Func> int64_t test_bench(_Func &&f) {
  auto start = std::chrono::high_resolution_clock::now();
  f();
  auto end = std::chrono::high_resolution_clock::now();
  return std::chrono::duration_cast<std::chrono::nanoseconds>(end - start)
      .count();
}

int main() {
  std::list<double> l1;
  sjtu::list<double> l2;
  constexpr size_t N = 5e6;
  init<N>(l1);
  init<N>(l2);
  int result1, result2;
  auto t1 = test_bench([&]() { result1 = visit(l1); });
  auto t2 = test_bench([&]() { result2 = visit(l2); });
  for (int __cnt = 0; __cnt < 9; ++__cnt) {
    t1 += test_bench([&]() { result1 += visit(l1); });
    t2 += test_bench([&]() { result2 += visit(l2); });
  }
  t1 /= 1000000;
  t2 /= 1000000;
  double checksum1{}, checksum2{};
  for (auto e : l1)
    checksum1 += e;
  for (auto e : l2)
    checksum2 += e;
  std::cout << (result1 == result2 && checksum1 == checksum2) << ' ' << t1
            << ' ' << t2 << '\n';
  return 0;
}
