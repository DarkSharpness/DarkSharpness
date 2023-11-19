#include <iostream>
#include <queue>
using namespace std;

bool t[4][4];
int make(int n) {
    int ans = 0;
    for (int i = 0 ; i < n ; ++i)
        for (int j = 0 ; j < n ; ++j)
            ans |= t[i][j] << (i * n + j);
    return ans;
}

const int N = 1 << 16;
bool vis[N];

struct point { int state, step; };

signed main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i)
        for (int j = 0 ; j < n ; ++j)
            cin >> t[i][j];
    queue <point> q;
    q.push({make(n) , 0});

    int mask1 = (1 << n) - 1;   // 交换一行
    int mask2 = 0;              // 交换一列
    for (int i = 0 ; i < n ; ++i) mask2 |= 1 << (i * n);

    while (!q.empty()) {
        const int val = q.front().state;
        const int step = q.front().step + 1;
        q.pop();
        if (val == 0) {
            cout << step - 1 << endl;
            return 0;
        }

        vis[val] = true;
        for (int i = 0 ; i < n ; ++i) {
            int nxt = val ^ (mask1 << (i * n));
            if (vis[nxt]) continue;
            vis[nxt] = true;
            q.push({ nxt, step });
        }

        for (int i = 0 ; i < n ; ++i) {
            int nxt = val ^ (mask2 << i);
            if (vis[nxt]) continue;
            vis[nxt] = true;
            q.push({ nxt, step });
        }
    }
    cout << -1 << endl;
    return 0;
}