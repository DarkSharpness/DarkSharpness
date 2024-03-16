#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
struct edge{
    int nxt,to;
}e[N<<1];
int head[N],tot = 1;
inline void adde(int fr,int to) {
    e[++tot].to = to;
    e[tot].nxt  = head[fr];
    head[fr]    = tot;
}
//bitset <N> isbridge;

struct Edge{
    int nxt,to,org;
}E[N<<1];
int H[N],ttt = 0;
inline void addE(int fr,int to,int id) {
    E[++ttt].to = to;
    E[ttt].org  = id;
    E[ttt].nxt  = H[fr];
    H[fr]       = ttt;
}

int DFNs;
int dfn[N],low[N],st[N],stop;
int COLs,col[N];
void dfs(int id,int in) {
    st[++stop] = id;
    dfn[id] = low[id] = ++DFNs;
    for(int i = head[id] ; i ; i = e[i].nxt) {
        int to = e[i].to;
        if(!dfn[to]) {
            dfs(to,i);
            low[id] = min(low[id],low[to]);
            //if(low[to] > dfn[id]) {
            //    isbridge[in >> 1]   = true;
            //} 
        } else if((i ^ 1) != in) {
            low[id] = min(low[id],dfn[to]);
        }
    } 
    if(dfn[id] == low[id]) {
        col[id] = ++COLs;
        while(st[stop] != id) {
            col[st[stop]] = COLs;
            --stop;
        }
        --stop;
    }
}
int dif[N];
int n,m;
bitset <N> vis;
bitset <N<<1> dir;

void dfss(int id) {
    vis[id] = true;
    for(int i = H[id] ; i ; i = E[i].nxt) {
        int to = E[i].to;
        if(vis[to]) continue;
        dfss(to);
        if(dif[to]) {
            if(dif[to] < 0) {
                dir[E[i].org]   = true;
            } else {
                dir[E[i].org^1] = true;
            }
        }
        dif[id] += dif[to];
    }
}




int main() {
    scanf("%d%d",&n,&m);
    for(int i = 1,x,y ; i <= m; ++i) {
        scanf("%d%d",&x,&y);
        adde(x,y);
        adde(y,x);
    }
    for(int i = 1 ; i <= n; ++i)
        if(!dfn[i]) 
            dfs(i,0);
    for(int i = 1 ; i <= m; ++i) {
        int fr = e[i<<1|1].to;
        int to = e[i<<1].to;
        if(col[fr] != col[to]) {
            //cout << fr << "--" << to << endl;
            addE(col[fr],col[to],i<<1  );
            addE(col[to],col[fr],i<<1|1);
        }
    } 
    int p;
    scanf("%d",&p);
    while(p--) {
        int x,y;
        scanf("%d%d",&x,&y);
        if(col[x] == col[y]) continue;
        ++dif[col[x]];
        --dif[col[y]];
    }
    for(int i = 1 ; i <= COLs ; ++i) {
        if(!vis[i]) {
            dfss(i);
        }
    }
    for(int i = 1 ; i <= m ; ++i) {
        if(dir[i<<1]) {
            putchar('R');
        } else if(dir[i<<1|1]) {
            putchar('L');
        } else {
            putchar('B');
        }
    }
    return 0;
}

