#include <iostream>
using namespace std;

const int N = 1e3 + 3;
int w[N], v[N];
int f[N][N];


signed main() {
    int n, W;
    cin >> n >> W;
    for (int i = 1; i <= n; i++) cin >> w[i] >> v[i];
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= W; j++) {
            f[i][j] = f[i - 1][j];
            if (j >= w[i]) f[i][j] = max(f[i][j], f[i - 1][j - w[i]] + v[i]);
        }
    }
    cout << f[n][W] << endl;
    return 0;
}
