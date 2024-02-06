/**
 * Average:
 *  stupid: 400ms
 *  strcpy: 220ms
 *  memcpy: 170ms
 */
#pragma GCC optimize("O3")
#include <iostream>
#include <cstring>
#include <chrono>

constexpr long long N = 1024 * 1024 * 1024 - 1;

signed main() {
    // volatile 
    char *src = new char[N];
    // volatile 
    char *dst = new char[N];

    for (long long i = 0 ; i < N ; ++i) src[i] = i % 26 + 'a';

    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();

    for (long long i = 0 ; i < N ; ++i) dst[i] = src[i];

    std::memcpy(dst, src, N);
    // std::strcpy(dst, src);

    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();

    int checksum = 0; // Anti-optimization
    for (long long i = 0 ; i < N ; ++i, ++i)
        checksum += dst[i] ^ reinterpret_cast<intptr_t>(src);
    std::cout << "Time: " <<
        std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count() << "ms\n";
    std::cout << "Checksum: " << checksum << "\n";
    return 0;
}