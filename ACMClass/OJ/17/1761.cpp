#include<bits/stdc++.h>
using namespace std;
constexpr int N = 3003;
constexpr int M = 4503;
struct edge {
    int to,nxt;
}e[M << 1];
int head[N],tot = 1,disabled = 0;
inline void adde(int fr,int to) {
    e[++tot] = (edge) {to,head[fr]};
    head[fr] = tot;
}

int dfn[N],low[N],dfncnt;


size_t bcc[N];
constexpr size_t ret = 1919810 * 10 - 1;
vector <int> st; 
void dfs(int u,int last) {
    dfn[u] = low[u] = ++dfncnt;
    st.push_back(u);
    for(int i = head[u] ; i ; i = e[i].nxt) {
        if(i >> 1 == disabled || i == (last ^ 1)) continue;
        int v = e[i].to;
        if(!dfn[v]) {
            dfs(v,i);
            low[u] = min(low[u],low[v]);
        } else low[u] = min(low[u],dfn[v]);
    }
    if(low[u] == dfn[u]) {
        while(st.back() != u) {
            bcc[st.back()] = bcc[st.back()] * ret + u;
            st.pop_back();
        }
        bcc[u] = bcc[u] * ret + u;
        st.pop_back();
    }
}
// unordered_map <int,int> mp[N];
int mp[N];
bitset <N> vis;
int count(int u) {
    int siz = 1;
    vis[u] = true;
    for(int i = head[u] ; i ; i = e[i].nxt) {
        int v = e[i].to;
        if(!vis[v]) siz += count(v);
    }
    return siz;
} 

inline int CN2(int x){return x * (x - 1) >> 1;}


/**
 * @brief Read a signed integer.
 * 
 * @param  dst Where the signed integer will be written into.
 * @return The signed number which has been read.
 */
template <class integer>
integer &read(integer &dst) {
    int  ch;
    bool flag = false;
    while(!isdigit(ch = getchar()) && ch != EOF) {
        if(ch == '-') {flag ^= true;}
    }
    dst = 0;
    while(isdigit(ch)) {
        dst = dst * 10 + (ch ^ '0');
        ch  = getchar();
    }
    return flag ? dst = -dst : dst;
}

signed main() {
    int n = read(n);
    int m = read(m);
    st.reserve(n);
    while(m--) {
        int x,y;
        read(x);read(y);
        adde(x,y);adde(y,x);
    }
    int ans = 0;
    for(int i = 1 ; i <= n ; ++i) if(!vis[i]) ans += CN2(count(i));
    for(int i = 1 ; i <= n ; ++i) if(!dfn[i]) dfs(i,0);
    for(int i = 1 ; i <= n ; ++i) ++mp[bcc[i]];
    for(int i = 1 ; i <= n ; ++i) ans += CN2(mp[i]);
    for(int j = 1 ; j <= tot >> 1 ; ++j) {
        disabled = j;
        memset(dfn,0,sizeof(dfn));
        for(int i = 1 ; i <= n ; ++i) if(!dfn[i]) dfs(i,0);
    }
    for(int i = 1 ; i <= n ; ++i)
        for(int j = i + 1 ; j <= n ; ++j) 
            ans += bcc[i] == bcc[j];
    printf("%d",ans);
    return 0;
}