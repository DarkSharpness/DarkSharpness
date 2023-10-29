#include <iostream>
using namespace std;

const int N = 1002;
int  a[N]; // 地雷数量
bool b[N]; // 要么是雷，要么不是

// x - 1,x,x + 1 三格的地雷数
int cnt(int x) { return b[x - 1] + b[x] + b[x + 1]; }
int n;

bool dfs(int x) {
    if (x > n) {
        // 检验 n 和 n - 1 即可
        if (cnt(n) != a[n] || cnt(n - 1) != a[n - 1]) return false;
        // 找到了一个解
        for (int i = 1; i <= n; i++) cout << (b[i] ? 'x' : 'o') << ' ';
        return true;
    }

    if (x == 1) {
        b[1] = true;
        if (dfs(x + 1)) return true;
        b[1] = false;
        return dfs(x + 1);
    }

    b[x] = false;

    int remain = a[x - 1] - cnt(x - 1);
    if (remain < 0 || remain > 1) return false;
    // 这个位置恰好放 remain 个雷，只能是 0 ~ 1 个
    b[x] = remain;
    return dfs(x + 1);
}


signed main() {
    cin >> n;
    for(int i = 1 ; i <= n ; ++i) cin >> a[i];
    dfs(1);
    return 0;
}