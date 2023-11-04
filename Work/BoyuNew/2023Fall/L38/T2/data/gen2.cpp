#include <bits/stdc++.h>

const int N = 1999;

signed main() {
    freopen("2.in","w",stdout);
    std::cout << std::format("{} {}\n", N, N);
    for(int i = 1 ; i <= N ; ++i) {
        for(int j = 1 ; j <= N ; ++j)
            std::cout << "*-"[i == j];
        std::cout << '\n';
    }
    return 0;
}
