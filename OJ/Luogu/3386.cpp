#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
//#define int lont long
const int M = 5e4 + 16;
const int N = 508;
struct edge {
    int to,nxt;
}e[M << 1];
int head[N << 1],tot = 0;

inline void adde(int fr,int to) {
    e[++tot].to = to;
    e[tot].nxt  = head[fr];
    head[fr]    = tot;
}
bitset <N << 1> vis;
int match[N << 1];

/// @brief Search for augmented path. 
bool dfs(int id) {
    for(int i = head[id],to ; i ; i = e[i].nxt) {
        if(!vis[to = e[i].to]) {
            vis[to] = true;
            if(!match[to] || dfs(match[to])) {
                match[to] = id;
                return true;
            }
        }
    }
    return false;
}


signed main() {
    int n,m,e;
    memset(match,0,sizeof(match));
    scanf("%d%d%d",&n,&m,&e);
    for(int i = 1,x,y ; i <= e ; ++i) {
        scanf("%d%d",&x,&y);
        adde(x,y+n);
        adde(y+n,x);
    }
    int ans = 0;
    for(int i = 1 ; i <= n ; ++i) {
        vis.reset();
        if(dfs(i)) ++ans;
    }
    printf("%d",ans);
    return 0;
}