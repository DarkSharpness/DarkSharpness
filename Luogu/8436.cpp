#include<bits/stdc++.h>
using namespace std;
constexpr int N = 5e5 + 10;
constexpr int M = 2e6 + 10;
struct edge {
    int to,nxt;
}e[M << 1];
int head[N],tot = 1;
inline void adde(int fr,int to) {
    e[++tot] = (edge) {to,head[fr]};
    head[fr] = tot;
}


int dfn[N],low[N],dfncnt;
bitset <N> cut;
void dfs(int u,int fa) {
    dfn[u] = low[u] = ++dfncnt;
    int child = 0;
    for(int i = head[u] ; i ; i = e[i].nxt) {
        int v = e[i].to;
        if(!dfn[v]) {
            ++child;
            dfs(v,u);
            low[u] = min(low[u],low[v]);
            if(low[v] >= dfn[u]) {
                cut[u] = true;
            }
        } else if(i != fa) low[u] = min(low[u],dfn[v]);
    }
    if(fa == 0 && child == 1) {
        cut[u] = false;
    }
}




signed main() {
    int n,m;
    ios::sync_with_stdio(false);
    cin >> n >> m;
    while(m--) {
        int x,y;
        cin >> x >> y;
        adde(x,y);adde(y,x);
    }
    for(int i = 1 ; i <= n ; ++i)
        if(!dfn[i]) dfs(i,0);
    cout << cut.count() << '\n';
    for(int i = 1 ; i <= n ; ++i)
        if(cut[i]) cout << i << ' ';
    return 0;
}