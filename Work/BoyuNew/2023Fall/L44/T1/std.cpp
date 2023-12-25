#include <iostream>
const int N = 1003;
const int M = 10;
int a[N];
int f[N];
int s[N][M];

signed main() {
    int n;
    std::cin >> n;
    for (int i = 1, x ; i <= n ; ++i) {
        std::cin >> x;
        a[i] = x;
        for (int j = 0 ; j < M ; ++j) s[i][j] = s[i - 1][j];
        ++s[i][x];
    }
    for (int i = 1 ; i <= n ; ++i) {
        for (int j = 0 ; j < i ; ++j) {
            for (int k = 1 ; k < M ; ++k) {
                int t = s[i][k] - s[j][k];
                f[i] = std::max(f[i], f[j] + k * t * t);
            }
        }
    }
    std::cout << f[n] << std::endl;
    return 0;
}
