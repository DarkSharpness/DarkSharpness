#include <iostream>
#include <vector>
using namespace std;

const int N = 1e6 + 3;

int fat[N];
int dep[N];

int dfs(int x) {
    if (dep[x]) return dep[x];
    // 记忆化搜索
    int ans = 1 + dfs(fat[x]);
    return dep[x] = ans;
}

signed main() {
    int n;
    cin >> n;
    for (int i = 1 ; i <= n ; ++i) {
        int x;
        cin >> x;
        fat[i] = x;
    }
    dep[0] = -1;
    for (int i = 1 ; i <= n ; ++i)
        std::cout << dfs(i) << ' ';
    return 0;
}
