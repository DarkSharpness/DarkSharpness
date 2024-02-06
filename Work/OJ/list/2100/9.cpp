// Benchmark
#include "src.hpp"
#include <chrono>
#include <iostream>
#include <list>
#include <random>


template <size_t _N, typename _List> void init(_List &l) {
  size_t n = _N;
  while (n-- > 0)
    l.push_back(n);
}

template <typename _List> int64_t test_bench(_List &&l) {
  srand(114514);
  constexpr size_t M = 1024;
  static decltype(l.begin()) vec[M];

  size_t cnt = 0;
  for (auto __beg = l.begin(), __end = l.end();;) {
    if (rand() % 255 == 0) {
      vec[cnt++] = __beg;
      if (cnt == M)
        break;
    }
    ++*__beg; // Modify the element!
    if (++__beg == __end)
      throw std::runtime_error("???");
  }
  std::shuffle(vec, vec + M, std::mt19937(std::random_device()()));

  auto start = std::chrono::high_resolution_clock::now();

  for (size_t i = 0; i < 233; ++i)
    for (auto &it : vec)
      it = l.insert(it, 0.0);

  auto end = std::chrono::high_resolution_clock::now();
  return std::chrono::duration_cast<std::chrono::nanoseconds>(end - start)
      .count();
}

int main() {
  std::list<double> l1;
  sjtu::list<double> l2;
  constexpr size_t N = 1e6;
  init<N>(l1);
  init<N>(l2);
  int64_t t1{}, t2{};
  for (int __cnt = 0; __cnt < 20; ++__cnt) {
    t1 += test_bench(l1);
    t2 += test_bench(l2);
  }
  t1 /= 1000000;
  t2 /= 1000000;
  double checksum1{}, checksum2{};
  for (auto e : l1)
    checksum1 += e;
  for (auto e : l2)
    checksum2 += e;
  std::cout << (l1.size() == l2.size() && checksum1 == checksum2) << ' ' << t1
            << ' ' << t2 << '\n';
  return 0;
}
