#include <iostream>
// #include <bits/stdc++.h>

const int N = 503;
const int M = 20;

int h[N];
int a[N][N];
int s[N][N]; // s[i][j] = a[i][i] + ... + a[i][j]
int f[N][M];

signed main() {
    int n,K;
    std::cin >> n >> K;

    for (int i = 1 ; i <= n ; ++i) {
        std::cin >> h[i];
        for (int j = i - 1 ; j >= 1; --j) {
            a[j][i] = a[j + 1][i] + (h[j] > h[i]);
        }
    }
    for (int i = 1 ; i <= n ; ++i) {
        for (int j = i + 1 ; j <= n ; ++j) {
            s[i][j] = s[i][j - 1] + a[i][j];
        }
    }

    // s[i][j]: i ~ j 分为一队的遮挡次数
    // f[i][j]: 分到 i，分了 j 个队的最小遮挡次数
    for (int i = 1 ; i <= n ; ++i) f[i][1] = s[1][i];

    for (int i = 1 ; i <= n ; ++i) {
        for (int k = 2 ; k <= K ; ++k) {
            f[i][k] = 1e9; // 无限大初始化
            for (int j = 1 ; j < i ; ++j) {
                f[i][k] = std::min(f[i][k], f[j - 1][k - 1] + s[j][i]);
            }
        }
    }

    std::cout << f[n][K] << std::endl;

    return 0;
}