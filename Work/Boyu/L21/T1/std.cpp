#include <iostream>
#include <cstring>

int w[20],v[20];
int f[101];

/* 请不要抄袭! */
signed main() {
    int n,m;
    std::cin >> n >> m;
    for(int i = 0 ; i < n ; ++i)
        std::cin >> w[i] >> v[i];

    memset(f,129,sizeof(f));
    f[0] = 0;
    for(int i = 0 ; i < n ; ++i)
        for(int j = m ; j >= w[i] ; --j)
            f[j] = std::max(f[j - w[i]] + v[i],f[j]);

    int ans = f[1]; // 至少拿一个物品
    for(int i = 1 ; i <= m ; ++i)
        ans = std::max(ans,f[i]);
    std::cout << ans << '\n';
    return 0;
}
