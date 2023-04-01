#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 3e4+8;
int fat[N],son[N],sz[N],dep[N];
int dfn[N],rev[N],top[N],cnt;
struct edge{
    int nxt,to;
}e[N<<1];
int head[N],tot;
inline void adde(int fr,int to) {
    e[++tot].nxt = head[fr];
    head[fr]     = tot;
    e[tot].to    = to;
}
void dfs1(int id) {
    sz[id] = 1;
    for(int i = head[id]; i ; i=e[i].nxt) {
        int to = e[i].to;
        if(to == fat[id]) continue;
        dep[to] =  dep[id] + 1;
        fat[to] = id;
        dfs1(to);
        sz[id] += sz[to];
        if(sz[to] > sz[son[id]]) son[id] = to; 
    }
}
void dfs2(int id,int first) {
    dfn[id]  = ++cnt;
    rev[cnt] = id;
    top[id]  = first;
    if(!son[id]) return ;
    dfs2(son[id],first);
    for(int i = head[id]; i ; i=e[i].nxt) {
        int to = e[i].to;
        if(to == son[id] || to == fat[id]) continue;
        dfs2(to,to);
    }
}
#define INF 1919810


int v[N];
struct segmentTree {
    int M;
    struct node{
        int mxn;
        int val;
        int l,r;
    }t[N<<2];
    #define ls (id<<1)
    #define rs (id<<1|1)
    #define mid ((t[id].l+t[id].r) >> 1)
    inline void pushup(int id) {
        t[id].val = t[ls].val + t[rs].val;
        t[id].mxn = max(t[ls].mxn,t[rs].mxn);
    }
    //递归建树O(n)
    void build(int id,int l,int r){
        t[id].l = l;
        t[id].r = r;
        if(l == r) {
            t[id].mxn = t[id].val = v[rev[l]];
            return ;
        }
        build(ls, l , (l+r)>>1 );
        build(rs,((l+r)>>1)+1,r);
        pushup(id);
    }
    //非递归单点update
    inline void update(int id,int loc,int val) {
        while(t[id].l != t[id].r) {
           if(loc > mid) id = rs;
           else          id = ls;
        }
        t[id].mxn = val;
        t[id].val = val;
        while((id>>=1)) {
            pushup(id);
        }
    }
    inline int  queryV(int id,int l,int r) {
        if(t[id].l == l && t[id].r == r) return t[id].val;
        if(r <= mid)     return queryV(ls,l,r);
        else if(l > mid) return queryV(rs,l,r);
        else return queryV(ls,l,mid)+
                    queryV(rs,mid+1,r);
    }
    inline int  queryM(int id,int l,int r) {
        if(t[id].l == l&&t[id].r == r) return t[id].mxn;
        if(r <= mid)     return queryM(ls,l,r);
        else if(l > mid) return queryM(rs,l,r);
        else return max(queryM(ls, l ,mid),
                        queryM(rs,mid+1,r) );
    }
}T;


inline void change(int u,int t) {
    T.update(1,dfn[u],t);
}

inline void qmax(int u,int v) {
    int ans(-1919810);
    while(top[u] != top[v]) {
        //让u depth 更大
        if(dep[top[u]] < dep[top[v]]) swap(u,v); 
        ans =max(ans,T.queryM(1,dfn[top[u]],dfn[u]));    
        u = fat[top[u]];
    }
    if(dep[u] > dep[v]) swap(u,v);
    cout << max(ans,T.queryM(1,dfn[u],dfn[v]))<< endl;
}
inline void qsum(int u,int v) {
    int ans(0);
    while(top[u] != top[v]) {
        //让u depth 更大
        if(dep[top[u]] < dep[top[v]]) swap(u,v); 
        ans +=T.queryV(1,dfn[top[u]],dfn[u]);    
        u = fat[top[u]];
    }
    if(dep[u] > dep[v]) swap(u,v);
   cout << ans+T.queryV(1,dfn[u],dfn[v]) << endl;
}


int main() {
    ios::sync_with_stdio(false);
    int n;
    cin >> n;
    for(int i = 1,x,y ; i < n; ++i) {
        cin >> x >> y;
        adde(x,y);
        adde(y,x);
    }
    for(int i = 1 ; i <= n ; ++i) 
        cin >> v[i];
    //int r = (rand() % n) + 1;
    int r = 1;
    fat[r] = 0;
    dep[r] = 1;
    dfs1(r);
    dfs2(r,r);
    T.build(1,1,n);
    int q,u,v;
    char buf[20];
    cin >> q;
    while(q--) {
        cin >> buf >> u >> v;
        switch(buf[1]) {
            case 'M':
                qmax(u,v);
                break;
            case 'S':
                qsum(u,v);
                break;
            default:
                change(u,v);
        }
    }
    return 0;
}