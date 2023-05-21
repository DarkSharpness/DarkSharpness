#include <iostream>

const int N = 5e5 + 3;
const int M = 50;
struct edge { int to,nxt; } e[N];
int head[N],tot;
inline void adde(int fr,int to)
{ e[++tot] = {to,head[fr]}; head[fr] = tot; }

bool vis[M];
void dfs(int u) {
    vis[u] = true;
    for(int i = head[u] ; i ; i = e[i].nxt) 
        if(!vis[e[i].to]) dfs(e[i].to);
}

bool deg[M];
signed main() {
    int n;
    scanf("%d",&n);
    while(n--) {
        int x,y;
        scanf("%d%d",&x,&y);
        adde(x,y);
        adde(y,x);
        deg[x] = !deg[x];
        deg[y] = !deg[y];
    }
    for(int i = 0 ; i < M ; ++i)
        if(head[i]) { dfs(i); break; }
    bool flag = false;
    int  cnt = 0;
    for(int i = 0 ; i < M ; ++i)
        if(head[i] && (!vis[i] || (deg[i] && ++cnt > 2)))
            { flag = true; break; }
    puts(flag ? "Impossible" : "Possible");
    return 0;
}
