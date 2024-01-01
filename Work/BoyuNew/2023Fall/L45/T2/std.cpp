#include <iostream>

const int N = 1003;
int a[N];
int b[N];
int f[N][N];

signed main() {
    int n;
    std::cin >> n;
    for (int i = 1 ; i <= n ; ++i) std::cin >> a[i];
    for (int i = 1 ; i <= n ; ++i) std::cin >> b[i];
    for (int i = 1 ; i <= n ; ++i) {
        for (int j = 1 ; j <= n ; ++j) {
            if (a[i] == b[j]) {
                f[i][j] = f[i - 1][j - 1] + a[i] * a[i];
            } else {
                f[i][j] = std::max(f[i - 1][j], f[i][j - 1]);
            }
        }
    }
    std::cout << f[n][n] << std::endl;
    return 0;
}
