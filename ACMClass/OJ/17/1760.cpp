#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
//#define int lont long
const int N = 5e5 + 8;
const int M = 2e6 + 8;

struct edge {
    int to,nxt,fr;
}e[M << 1];


int head[N],cnt = 0;
inline void adde(int fr,int to) {
    e[++cnt] = (edge){to,head[fr],fr};
    head[fr] = cnt;
}


int dfn[N],low[N],dnt = 0;
int tot = 0;
vector <int> st;
bitset <N> color;
bitset <N> invited;
bool dfs(int u,int fa) {
    // int son = 0;
    dfn[u] = low[u] = ++dnt;
    color[u] = color[fa] ^ 1;
    st.push_back(u);
    bool tmp = false;
    for(int i = head[u] ; i ; i = e[i].nxt) {
        int v = e[i].to;
        if(!dfn[v]) {
            bool ans = dfs(v,u);
            low[u] = min(low[u],low[v]);
            if(low[v] >= dfn[u]) {
                int t;
                if(st.back() == v) {
                    st.pop_back(); // 2 points...    
                } else {
                    do {
                        t = st.back();
                        st.pop_back();
                        if(ans) invited[t] = true;
                    } while(t != v);
                    if(ans) invited[u] = true;
                }
            } else {
                tmp |= ans;
            }
        } else {
            if(color[u] == color[v]) tmp = true;     // same color.
            if(v != fa) low[u] = min(low[u],dfn[v]); // backwards.
        }
    }
    // if(st.back() == u) st.pop_back();
    if(low[u] < dfn[u]) return tmp;
    else                return false;
}





signed main() {
    int n,m;
    ios::sync_with_stdio(false);
    cin >> n >> m;
    while(m--) {
        int x,y;
        cin >> x >> y;
        if(x == y) continue;
        adde(x,y);adde(y,x);
    }
    for(int i = 1 ; i <= n ; ++i)
        if(!dfn[i]) {
            st.clear();
            dfs(i,0);
        }
    cout << n - invited.count();
    return 0;
}