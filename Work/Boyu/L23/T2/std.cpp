#include <iostream>

const int N = 5e4 + 2;
int f[N]; // 大小
struct node {
    int ls,rs;
}t[N];

int dfs(int x) {
    if(!x) return 0;
    f[x] = 1;
    f[x] += dfs(t[x].ls);
    f[x] += dfs(t[x].rs);
    return f[x];
}

signed main() {
    int n;
    std::cin >> n;
    for(int i = 1 ; i <= n ; ++i)
        std::cin >> t[i].ls >> t[i].rs;
    for(int i = 1 ; i <= n ; ++i)
        if(!f[i]) dfs(i);
    for(int i = 1 ; i <= n ; ++i)
        std::cout << f[i] << '\n';
    return 0;
}