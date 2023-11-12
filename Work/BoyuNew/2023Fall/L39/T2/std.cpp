#include <iostream>
using namespace std;

const long long mod = 1e9 + 9;
const long long  N  = 1e6 + 3;

bool      vis[2][N];
long long mem[2][N];

// 快速幂，也可以用记忆化搜索
long long pow_10(int n) {
    long long ans = 1;
    long long ten = 10;
    while (n) {
        if (n & 1) ans = ans * ten % mod;
        ten = ten * ten % mod;
        n >>= 1;
    }
    return ans;
}

// 当前在选择第 n 位
long long dfs(int n, bool last_6) {
    if (vis[last_6][n]) return mem[last_6][n];
    vis[last_6][n] = true;

    long long ans = 0;
    if (n + last_6 <= 1) return 0;
    if (last_6) {
        ans += dfs(n - 1,true);          // 6
        ans += 8 * dfs(n - 1,false);     // 除了 6 和 4
        if (n >= 2) ans += pow_10(n - 2); // 4
    } else {
        ans += dfs(n - 1,true);         // 6
        ans += 9 * dfs(n - 1,false);    // 除了 6
    }

    return mem[last_6][n] = ans % mod;
}

signed main() {
    int n;
    cin >> n;
    cout << dfs(n + 1,false) << '\n';
    return 0;
}