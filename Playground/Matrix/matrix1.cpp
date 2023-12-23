#pragma GCC optimize("O3")
#include <chrono>
#include <iostream>

const int N = 1000;
int a[N][N];
int b[N][N];
int c[N][N];

signed main() {
    for (int i = 0 ; i < N ; ++i)
        for (int j = 0 ; j < N ; ++j)
            a[i][j] = rand(), b[i][j] = rand();
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0 ; i < N ; ++i)
        for (int j = 0 ; j < N ; ++j)
            for (int k = 0 ; k < N ; ++k)
                c[i][j] += a[i][k] * b[k][j];
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds> (end - start).count() << "ms\n";
    return 0;
}