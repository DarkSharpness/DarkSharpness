#include <bits/stdc++.h>

int w[1003];
int v[1003];

signed main() {
    srand(time(NULL));
    for (int i = 1 ; i <= 10 ; ++i) {
        std::ofstream in (std::format("{}.in",i));
        std::ofstream out(std::format("{}.out",i));

        const int n = i * i * 10;
        const int m = i * 10;
        const int W = i * 100;

        for (int i = 1 ; i <= n ; ++i) {
            w[i] = rand() % m + 1;
            v[i] = rand() % m + 1;
            if (rand() % m == 0) {
                w[i] = rand() % W + 1;
                v[i] = rand() % W + 1;
            }
        }

        in << std::format("{} {}\n", n, W);
        for (int i = 1 ; i <= n ; ++i) in << std::format("{} {}\n", w[i], v[i]);
    }
    return 0;
}