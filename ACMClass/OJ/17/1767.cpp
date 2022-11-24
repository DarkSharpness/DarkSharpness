#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
//#define int long long
template<typename T> T read(T &x) {
    char c = getchar();
    while (c < '0' || c > '9') {
        c = getchar();
    }
    for (x = 0; c >= '0' && c <= '9'; c = getchar()) {
        x = (x << 3) + (x << 1) + c - '0';
    }
    return x;
}

const int N = 2004;

struct edge {
    int to,nxt;
}e[N * N];
int head[N],tot = 0;
inline void adde(int fr,int to) {
    e[++tot] = (edge){to,head[fr]};
    head[fr] = tot;
}


int dfn[N],low[N],dfncnt = 0;
bitset <N> st;
vector <int> t;
int scccnt = 0;
void dfs(int u) {
    low[u] = dfn[u] = ++dfncnt;
    st[u] = true;
    t.push_back(u);
    for(int i = head[u] ; i ; i = e[i].nxt) {
        int v = e[i].to;
        if(!dfn[v]) {
            dfs(v);
            low[u] = min(low[u],low[v]);
        } else if(st[v]) {
            low[u] = min(low[u],dfn[v]);
        }
    }
    if(low[u] == dfn[u]) {
        ++scccnt;
        while(t.back() != u) {
            st[t.back()] = false;
            t.pop_back();
        }
        t.pop_back();
        st[u] = false;
    }
}

signed main() {
    int T = read(T);
    while(T--) {
        int n = read(n);
        t.reserve(n);
        for(int i = 1 ; i <= n ; ++i) {
            for(int j = 1 ; j <= n ; ++j) {
                int x = read(x);
                if(x) adde(i,j);
            }
        }
        for(int i = 1 ; i <= n ; ++i)
            if(!dfn[i]) dfs(i);
        puts(scccnt == 1 ? "YES" : "NO");
        if(T) {
            st.reset();
            // t.clear();
            memset(low,0,sizeof(low));
            memset(dfn,0,sizeof(dfn));
            memset(head,0,sizeof(head));
            tot = scccnt = dfncnt = 0;
        }
    }



    return 0;
}