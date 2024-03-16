#include <iostream>
#include <cstring>

const int N = 15;
int  a[N];
int g[N][N];
int value;
bool success;
int n,m;
int l[N * N >> 1],r[N * N >> 1];

void dfs(int depth) {
    if(!depth || !value) return void(success = !value);
    for(int i = 0 ; i < m ; ++i) {
        int x = l[i] , y = r[i];
        int evalue = value - g[x][a[x]] - g[y][a[y]] + g[x][a[y]] + g[y][a[x]];
        if(evalue >> 1 < depth) {
            std::swap(value,evalue);
            std::swap(a[x],a[y]);
            dfs(depth - 1);
            if(success) return;
            std::swap(value,evalue);
            std::swap(a[x],a[y]);
        }
    }
}

signed main() {
    memset(g,60,sizeof(g));
    scanf("%d%d",&n,&m);
    for(int i = 1 ; i <= n ; ++i) scanf("%d",a + i);
    for(int i = 1 ; i <= n ; ++i) g[i][i] = 0;
    for(int i = 0 ; i < m ; ++i) {
        int x,y;
        scanf("%d%d",&x,&y);
        if(x == y) { --i,--m; continue; }
        l[i] = x;
        r[i] = y;
        g[x][y] = g[y][x] = 1;
    }
    for(int k = 1 ; k <= n ; ++k)
        for(int i = 1 ; i <= n ; ++i)
            for(int j = 1 ; j <= n ; ++j)
                if(g[i][j] > g[i][k] + g[k][j])
                    g[i][j] = g[i][k] + g[k][j];
    for(int i = 1 ; i <= n ; ++i) value += g[i][a[i]];
    const int max_depth = 30;
    for(int i = 0 ; i < max_depth ; ++i)
    { dfs(i); if(success) return printf("%d",i) * 0; }
    return 0;
}
