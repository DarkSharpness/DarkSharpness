#include <iostream>
using namespace std;

const int N = 1003;
const int M = 10003;

int d[N];
int c[M];

signed main() {
    int n, m;
    cin >> n >> m;
    for (int i = 1 ; i <= n; ++i) cin >> d[i];

    for (int i = 1 ; i <= m ; ++i) {
        c[i] = M; // 无穷大

        for (int j = 1 ; j <= n ; ++j) {
            if (d[j] > i) continue;
            int tmp = c[i - d[j]];
            c[i] = min(c[i], tmp + 1);
        }

        cout << (c[i] == M ? -1 : c[i]) << ' ';
    }
    return 0;
}
