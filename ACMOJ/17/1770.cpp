#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
template<typename T> T read(T &x) {
    char c = getchar();
    while (c < '0' || c > '9') {
        c = getchar();
    }
    for (x = 0; isdigit(c) ; c = getchar()) {
        x = x * 10 + (c ^ '0');
    }
    return x;
}
const int N = 1e5 + 11;
const int M = 5e5 + 10;
struct edge {
    int to,nxt;
}e[M << 1];
int head[N],tot = 0;
inline void adde(int fr,int to) {
    e[++tot] = (edge){to,head[fr]};
    head[fr] = tot;
}

struct Edge {
    int id,u,v,val;
    inline bool operator <(const Edge &B) const{
        return val < B.val;
    }
}E[M << 1];

int anc[N];
vector <int> siz(N,1);
int fat[N];
int dfn[N],low[N],dfncnt = 0;

inline int Find(int u) {
    return anc[u] == u ? u : anc[u] = Find(anc[u]);
}

vector <int> st;

int bcc[N],cnt = 0;
void dfs(int u,int last) {
    dfn[u] = low[u] = ++dfncnt;
    st.push_back(u);
    for(int i = head[u] ; i ; i = e[i].nxt) {
        int v = e[i].to;
        if(!dfn[v]) {
            dfs(v,i);
            low[u] = min(low[u],low[v]);
        } else if(i != (last ^ 1)) low[u] = min(low[u],dfn[v]);
    }
    if(low[u] == dfn[u]) {
        ++cnt;
        while(st.back() != u) {
            bcc[st.back()] = cnt; // in one bcc
            st.pop_back();
        }
        bcc[u] = cnt;
        st.pop_back();
    }
}

inline int Get(int u) {
    return fat[u] == u ? u : fat[u] = Get(fat[u]);
}

void dfs2(int u,int top) {
    fat[u] = top;
    for(int i = head[u] ; i ; i = e[i].nxt) {
        int v = e[i].to;
        if(fat[v] != top) dfs2(v,top);
    }
}



inline bool Merge(int u,int v) {
    u = Find(u);
    v = Find(v);
    if(u == v) return false;
    if(siz[u] > siz[v]) swap(u,v);
    anc[u] = v;
    siz[v] += siz[u];
    return true;
}
vector <Edge> vec;
int type[M];

signed main() {
    int n = read(n);
    int m = read(m);
    iota(anc + 1,anc + n + 1,1);
    iota(fat + 1,fat + n + 1,1);
    for(int i = 1 ; i <= m ; ++i) {
        int x = read(x),y = read(y),z = read(z);
        E[i] = (Edge){i,x,y,z};
    }
    sort(E + 1,E + m + 1);
    int last = -1;
    // int dotcnt = 0;
    for(int i = 1 ; i <= m ; ++i) {
        // if(dotcnt == n && last != E[i].val) break;
        if(Merge(E[i].u,E[i].v) || last == E[i].val) {
            last = E[i].val;
            // dotcnt += tmp;
            vec.push_back(E[i]);
        } else {/*type[E[i].id] == 0;*/}
    }
    int j = 0;
    vector <int> tmp;
    for(int i = 0 ; i < vec.size() ; ++i) {
        if(i == vec.size() - 1 || vec[i] < vec[i + 1]) {
            tot = 1;
            for(int k = j ; k <= i ; ++k) { // clear
                int u = Get(vec[k].u);
                int v = Get(vec[k].v);
                if(u == v) continue;
                tmp.push_back(k);
                head[u] = head[v] = 0;
                dfn [u] = dfn [v] = 0;
            }
            for(int k : tmp) {
                int u = Get(vec[k].u);
                int v = Get(vec[k].v);
                adde(u,v);
                adde(v,u);
            }
            for(int k : tmp) {
               int u = Get(vec[k].u);
                int v = Get(vec[k].v);
                if(!dfn[u]) {dfs(u,0);}
            }
            for(int k : tmp) {
                int u = Get(vec[k].u);
                int v = Get(vec[k].v);
                if(bcc[u] == bcc[v]) { 
                    type[vec[k].id] = 1; // in one bcc.
                } else type[vec[k].id] = 2; // bridge
            }
            for(int k = j ; k <= i ; ++k) {
                int u = vec[k].u;
                if(fat[u] == u) dfs2(u,u);
                int v = Get(vec[k].v);
                if(fat[v] == v) dfs2(v,v);
            }
            j = i + 1;
            // #undef u
            // #undef v
            tmp.clear();
        }
    }
    const char *c[3] = {"none","at least one","any"};
    for(int i = 1 ; i <= m ; ++i) 
        puts(c[type[i]]);
    return 0;
}