#include <iostream>
using namespace std;

const int N = 103;
int w[N], v[N], h[N];
int f[N][N][N];


signed main() {
    int n, W, m ;
    cin >> n >> W >> m;
    for (int i = 1; i <= n; i++) cin >> w[i] >> v[i] >> h[i];
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= W; j++) {
            for (int k = 0 ; k <= m ; ++k) {
                f[i][j][k] = f[i - 1][j][k];
                if (j >= w[i] && k >= h[i])
                    f[i][j][k] = max(f[i][j][k], f[i - 1][j - w[i]][k - h[i]] + v[i]);
            }
        }
    }
    cout << f[n][W][m] << endl;
    return 0;
}
