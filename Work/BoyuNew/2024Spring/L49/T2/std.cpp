#include <iostream>
using namespace std;

const int N = 5e3 +2;
int nxt[N];


signed main() {
    int n, m;
    cin >> n >> m;

    if (m == 1) {
        for (int i = 1; i <= n; i++) cout << i << ' ';
        cout << '\n';
        return 0;
    }

    for (int i = 1; i < n; i++) nxt[i] = i + 1;
    nxt[n] = 1;
    int x = 1;
    int y = nxt[x]; // 前进 1 步
    while (y != x) {
        // 再前进 m - 2 步
        for (int i = 0 ; i < m - 2; i++) {
            x = y;
            y = nxt[y];
        }
        cout << y << ' ';
        nxt[x] = nxt[y];
        y = nxt[y]; // 前进 1 步
    }

    cout << y << '\n';
    return 0;
}