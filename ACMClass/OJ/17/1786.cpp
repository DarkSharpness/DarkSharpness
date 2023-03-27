#include <iostream>
#include <Dark/inout>

const int N = 3e5 + 3;
const int M = 1e6 + 2;

int n;
int cnt = 0;
int map[M];

int tot = 0;
struct node {
    int ls,rs;
    int data;
} t[N * 23];

int h[N]; /* Root. */
int next[N];

struct tree {
    int u;
    void clone(int &id) {
        t[++tot] = t[id];
        id = tot;
    }
    void modify(int &id,int l,int r,int loc,int val) {
        clone(id);
        if(l == r) return (void) (t[id].data = val);
        int mid = (l + r) >> 1;
        if(loc > mid) modify(t[id].rs,mid + 1,r,loc,val);
        else          modify(t[id].ls, l , mid ,loc,val);
    }
    int query(int &id,int l,int r,int loc) {
        if(!id) return 0;
        if(l == r) return t[id].data;
        int mid = (l + r) >> 1;
        if(loc > mid) return query(t[id].rs,mid + 1,r,loc);
        else          return query(t[id].ls, l , mid ,loc);
    }
    void add(int val) {
        next[u + 1] = query(h[next[u]],1,n,val); // ch[next[u]][val]        
        h[u] = h[next[u]];
        modify(h[u],1,n,val,u + 1); // ch[u][val] = u + 1
        ++u;
        dark::writeline(u - next[u]);
    }
    void remove() {
        if(!--u) h[u] = 0;
    }

    tree() : u(0) {}
} hastin;



signed main() {
    dark::read_u(n);
    for(int i = 1,m ; i <= n ; ++i) {
        char opt;
        dark::read_char(opt);
        if(opt == '1') {
            dark::read_u(m);
            if(!map[m]) map[m] = ++cnt; // Discretion
            hastin.add(map[m]);
        } else hastin.remove();
    }
    return 0;
}
