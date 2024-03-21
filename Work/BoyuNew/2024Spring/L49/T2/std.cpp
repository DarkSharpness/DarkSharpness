#include <iostream>
using namespace std;

const int N = 5e3 +2;
int nxt[N];


signed main() {
    int n, m;
    cin >> n >> m;

    for (int i = 0; i < n; i++) nxt[i] = i + 1;
    nxt[n] = 1;

    int x = 0;
    int y = 1;

    // 初始 y 是第一个开始报数的人
    while (y != x) {
        // 前进 m - 1 步
        for (int i = 0 ; i < m - 1 ; i++) {
            x = y;
            y = nxt[y];
        }

        // y 出列
        cout << y << ' ';
        nxt[x] = nxt[y];

        x = y;
        y = nxt[x];
    }
    return 0;
}
