#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5+2;
ll n,m,r,p;
struct edge { int nxt,to; } e[N<<1];
ll head[N],tot;
inline void adde(int fr,int to) { e[++tot] = (edge) {head[fr],to}; head[fr] = tot; }
int sz[N],dep[N],fa[N],son[N];
int dfn[N],rev[N],top[N],cnt;
void dfs1(int id) {
    sz[id] = 1;
    for(int i = head[id]; i ; i = e[i].nxt) {
        int to = e[i].to;
        if(to == fa[id]) continue;
        dep[to] = dep[id] + 1;
        fa [to] = id;
        dfs1(to);
        sz[id] += sz[to];
        if(sz[to] > sz[son[id]]) son[id] = to;
    }
}
void dfs2(int id,int first) {
    top[id] = first;
    dfn[id] = ++cnt;
    rev[cnt] = id;
    if(!son[id]) return;
    dfs2(son[id],first);
    for(int i = head[id]; i ; i=e[i].nxt) {
        int to = e[i].to;
        if(to == son[id] || to == fa[id]) continue;
        dfs2(to,to);
    }
}
ll v[N];
struct node {
    int l,r;
    ll tag,val;
    ll length() {
        return r-l+1;
    }
}t[N<<2];

#define lc (id<<1)
#define rc (id<<1|1)
#define mid ((t[id].l+t[id].r)>>1)
inline void pushdown(ll id) {
    if(t[id].tag) {
        t[lc].tag += t[id].tag;
        t[lc].val = (t[lc].length()*t[id].tag+t[lc].val)%p;
        t[rc].tag += t[id].tag;
        t[rc].val = (t[rc].length()*t[id].tag+t[rc].val)%p;
        t[id].tag = 0;
    }
}

inline void pushup(ll id) {
    t[id].val = (t[lc].val + t[rc].val)%p ;
}
//建立在dfn上,求出对应dfn的总和
void build(int id,ll l,ll r) {
    t[id].l = l;
    t[id].r = r;
    if(l == r) {
        t[id].val = v[rev[l]];
        return ;
    }
    build(lc, l ,mid);
    build(rc,mid+1,r);
    pushup(id);
}

//必然是从浅层到深层
void update(int id,ll l,ll r,ll tag) {
    if(t[id].l == l && t[id].r == r){
        t[id].tag += tag;
        t[id].val = (t[id].length()*tag + t[id].val)%p;
        return;
    }
    pushdown(id);
    if(l > mid) update(rc,l,r,tag);
    else if(r <= mid) update(lc,l,r,tag);
    else {
        update(lc, l ,mid,tag);
        update(rc,mid+1,r,tag);
    }
    pushup(id);
}
ll query(int id,ll l,ll r) {
    if(t[id].l == l && t[id].r == r) 
        return t[id].val%p;
    pushdown(id);
    if(r <= mid) return query(lc,l,r);
    else if(l > mid) return query(rc,l,r);
    else return (query(lc,l,mid)+query(rc,mid+1,r))%p;
}
inline void add(int x,int y,ll z) {
    while(top[x] != top[y]) {
        if(dep[top[x]] < dep[top[y]]) swap(x,y);
        update(1,dfn[top[x]],dfn[x],z);
        x = fa[top[x]];
    }
    //让x更浅
    if(dep[x] > dep[y]) swap(x,y);
    update(1,dfn[x],dfn[y],z);
}
inline ll ask(int x,int y) {
    long long ans= 0;
    while(top[x] != top[y]) {
        //让x的深度更深层
        if(dep[top[x]] < dep[top[y]]) swap(x,y);
        ans = (ans + query(1,dfn[top[x]],dfn[x])) % p;  
        x = fa[top[x]];     
    }
    //让x更浅
    if(dep[x] > dep[y]) swap(x,y);
    return (ans+query(1,dfn[x],dfn[y]))%p;
}
int main() {
    scanf("%lld%lld%lld%lld",&n,&m,&r,&p);
    for(int i = 1; i <= n ; ++i) scanf("%lld",v+i);
    for(int i = 1,x,y; i < n ; ++i) {
        scanf("%d%d",&x,&y);
        adde(x,y);
        adde(y,x);
    }
    fa[r] = 0;
    dep[r]= 1;
    dfs1(r);
    dfs2(r,r);
    build(1,1,n);
    int num,x,y,z;
    while(m--) {
        scanf("%d",&num);
        switch(num) {
            case 1:
                scanf("%d%d%d",&x,&y,&z);
                add(x,y,z);
                break;
            case 2:
                scanf("%d%d",&x,&y);
                printf("%lld\n",ask(x,y));
                break;
            case 3:
                scanf("%d%d",&x,&y);
                update(1,dfn[x],dfn[x]+sz[x]-1,y);//子树结点连续
                break;
            case 4:
                scanf("%d",&x);
                printf("%lld\n",query(1,dfn[x],dfn[x]+sz[x]-1));
                break;
        }

    }
    return 0;
}