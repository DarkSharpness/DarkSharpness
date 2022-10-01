#include<bits/stdc++.h>
using namespace std;
const int N = 1e5 +16;

int col[N],cls = 0;

namespace graph { //原来的图
    struct edge{
        int nxt,to;
    }e[N<<1];
    int head[N] , tot = 1;
    inline void adde(int fr,int to){
        e[++tot].to = to;
        e[tot].nxt  = head[fr];
        head[fr]    = tot;
    }
    int dfn[N],low[N];
    int st[N] ,top = 0;
    int cnt;
    bitset <N> dir;
    void dfs(int id,int fa) {
        low[id] = dfn[id] = ++cnt;
        st[++top] = id;
        for(int i = head[id] ; i ; i = e[i].nxt) {
            int to = e[i].to;
            if(to == fa) continue;
            if(!dfn[to]) dfs(to,id);
            low[id] = min(low[to],low[id]);
        }
        if(low[id] == dfn[id]) { //没去过比自己更小的地方
            col[id] = ++cls;
            while(st[top] != id) {
                col[st[top]] = cls;
                --top;
            }
            --top;
        }
    }
}

namespace tree {
    struct Edge{
        int nxt,to,org;
        //org 存储原来的边的编号
    }E[N<<1];
    int Head[N] , TOT = 0; 
    inline void addE(int fr,int to,int org){
        E[++TOT].to = to;
        E[TOT].nxt  = Head[fr];
        E[TOT].org  = org;
        Head[fr]    = TOT;
    }

    int tag[N];
    bitset <N> vis;
    void dfs2(int id) {
        vis[id] = true;
        for(int i = Head[id] ; i ; i = E[i].nxt) {
            int to = E[i].to;
            if(!vis[to]) {
                dfs2(to); 
                if(tag[to] > 0) {
                    graph::dir[E[i].org ^ 1] = true;
                } else if(tag[to] < 0) {
                    graph::dir[E[i].org] = true;
                }
                tag[id] += tag[to];
            }
        }
    }
    void dfs3(int id,int fa) {
        for(int i = Head[id]; i ; i = E[i].nxt) {
            //cout << E[i].org << endl;
            if(E[i].to != fa)
                dfs3(E[i].to,id);
        }
    }

}


int n,m,p;


int main() {
    scanf("%d%d",&n,&m);
    for(int i = 1,x,y; i <= m ;++i) {
        scanf("%d%d",&x,&y);        
        graph::adde(x,y);
        graph::adde(y,x);
    }
    for(int i = 1 ; i <= n ; ++i)
        if(!graph::dfn[i])
            graph::dfs(i,0);

    for(int i = 1 ; i <= m ; ++i) {
        int to = graph::e[ i<<1 ].to, 
            fr = graph::e[i<<1|1].to;
        if(col[fr] == col[to]) continue;
        tree::addE(col[fr],col[to],i<<1);
        tree::addE(col[to],col[fr],i<<1|1);
    }
    scanf("%d",&p);
    for(int i = 1,x,y ; i <= p ; ++i) {
        scanf("%d%d",&x,&y);
        ++tree::tag[col[x]];
        --tree::tag[col[y]];
    }
    for(int i = 1 ; i <= cls ; ++i) {
        if(!tree::vis[i]) {
            tree::vis[i] = true;
            tree::dfs2(i);
        }
    }
    //tree::dfs3(1,0);
    for(int i = 1 ; i <= m ; ++i) {
        if(graph::dir[i<<1]) putchar('R');
        else if(graph::dir[i<<1|1]) putchar('L');
        else putchar('B');
        //putchar('\n');
    }
    return 0;
}