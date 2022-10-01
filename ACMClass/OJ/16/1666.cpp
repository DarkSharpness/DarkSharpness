#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 1e5 + 8;
const int M = 1e5 + 8;
struct edge {
    int to,nxt;
}e[M<<1];
int head[N],tot = 1;
inline void adde(int fr,int to){
    e[++tot].to = to;
    e[tot].nxt  = head[fr];
    head[fr]    = tot;
}

int cnt;
int dfn[N],low[N];
int st[N],top = 0;
int col[N],sum = 0;
bitset <M<<1> cut;
void dfs(int id,int fa) {
    dfn[id] = ++cnt;
    low[id] = cnt;
    st[++top] = id;
    for(int i = head[id]; i ; i = e[i].nxt) {
        int to = e[i].to;
        if(!dfn[to]) {
            dfs(to,id);
            low[id] = min(low[id],low[to]);
            if(low[to] > dfn[id]) {
                cut[i] = true;   //是割边           
            }
        } else if(to != fa) {
            low[id] = min(low[id],dfn[to]);
        }
    }
}
void color(int id) {
    for(int i = head[id]; i ; i = e[i].nxt) {
        int to = e[i].to;
        if(col[to]) continue;
        if(cut[i]) col[to] = ++sum;
        else       col[to] = col[id];
        color(to);
    }

}
struct NewEdge : edge {
    int org;
}E[M<<1];
int first[N],Count = 0;
inline void addEdge(int fr,int to,int org) {
    E[++Count].org = org;
    E[Count].nxt   = first[fr];
    E[Count].to    = to;
    first[fr]      = Count;
}
bitset <N> vis;
bitset <M> dir;
int tag[N];

//dfs2走树
void dfs2(int id) {
    vis[id] = true;
    for(int i = first[id] ; i ; i = E[i].nxt) {
        int to = E[i].to;
        if(vis[to]) continue;//父边
        dfs2(to);
        if(tag[to] < 0) { //正边方向
            dir[E[i].org] = true;
        } else if(tag[to] > 0) {//反边
            dir[E[i].org ^ 1] = true;
        }
        tag[id] += tag[to];//书上差分
    }
}




int main() {
    int n,m,p;
    scanf("%d%d",&n,&m);
    for(int i = 1,x,y ; i <= m ; ++i) {
        scanf("%d%d",&x,&y);
        adde(x,y);
        adde(y,x);
    }
    for(int i = 1 ; i <= n; ++i) 
        if(!dfn[i])
            dfs(i,0);
    for(int i = 1 ; i <= n; ++i)
        if(!col[i]) {
            col[i] = ++sum;
            color(i);
        }
    for(int i = 1 ; i <= m ; ++i) {
        int fr = e[i<<1|1].to,
            to = e[ i<<1 ].to;
        if(col[fr] != col[to]) {
            addEdge(col[fr],col[to],i<<1);  //原来边的编号
            addEdge(col[to],col[fr],i<<1|1);
        }
    }
    scanf("%d",&p);
    for(int i = 1,x,y; i <= p ; ++i) {
        scanf("%d%d",&x,&y);
        
        ++tag[col[x]];
        --tag[col[y]];
    }
    for(int i = 1 ; i <= sum; ++i)
        if(!vis[i]) 
            dfs2(i);
    for(int i = 1 ; i <= m ; ++i) {
        if(dir[i<<1]) putchar('R');
        else if(dir[i<<1|1]) putchar('L');
        else putchar('B');
    }
    return 0;
}
