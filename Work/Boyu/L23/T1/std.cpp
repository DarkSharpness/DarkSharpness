#include <iostream>

const int N = 1003;

int f[N];

/**
 * @brief 直接找到根节点。这里做了一个小小优化，
 * 我们直接把到根节点路径上的点的父亲设置为根节点。
 * 
 */
int get(int x) {
    return f[x] != x ? f[x] = get(f[x]) : x;
}

signed main() {
    int n,m;
    std::cin >> n >> m;
    for(int i = 1 ; i <= n ; ++i) {
        std::cin >> f[i];
        if(!f[i]) f[i] = i;
    }
    for(int i = 1 ; i <= n ; ++i)
        get(i);
    while(m--) {
        int x,y;
        std::cin >> x >> y;
        if(f[x] == f[y])
            puts("Yes");
        else
            puts("No");
    }
    return 0;
}
