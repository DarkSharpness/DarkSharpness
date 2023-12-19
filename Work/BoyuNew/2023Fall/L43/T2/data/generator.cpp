#include <bits/stdc++.h>

int w[1003];
int v[1003];
int h[1003];

signed main() {
    srand(time(NULL));
    for (int i = 1 ; i <= 10 ; ++i) {
        std::ofstream in (std::format("{}.in",i));
        std::ofstream out(std::format("{}.out",i));

        const int n = i * 10;
        const int M = sqrt(i) * 2;
        const int W = sqrt(i) * 10;

        for (int i = 1 ; i <= n ; ++i) {
            w[i] = rand() % M + 1;
            v[i] = rand() % M + 1;
            h[i] = rand() % M + 1;
            if (rand() % M == 0) {
                w[i] = rand() % W + 1;
                v[i] = rand() % W + 1;
            }
        }

        in << std::format("{} {} {}\n", n, W, W);
        for (int i = 1 ; i <= n ; ++i) in << std::format("{} {} {}\n", w[i], v[i], h[i]);
    }
    return 0;
}