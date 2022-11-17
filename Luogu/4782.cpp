#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
//#define int lont long

inline void read(int &tmp) {
    char ch;
    while(!isdigit(ch = getchar()));
    tmp = 0;
    do {
        tmp = 10 * tmp + (ch ^ '0');
        ch = getchar();
    } while(isdigit(ch));
}


int n,m;
const int N = 1e6 + 10;
struct edge{int to,nxt;}e[N << 1];
int head[N << 1],cnt;
inline void adde(int fr,int to) {
    e[++cnt] = (edge){to,head[fr]};
    head[fr] = cnt;
}


int dfn[N << 1],low[N << 1],tot;
int scc[N << 1],top;
// bool vis[N << 1]; // in vector or not
vector <int> vec;
void tarjan(int u) {
    dfn[u] = low[u] = ++tot;
    vec.push_back(u);
    // vis[u] = true;
    for(int i = head[u] ; i ; i = e[i].nxt) {
        int v = e[i].to;
        if(!dfn[v]) {
            tarjan(v);
            low[u] = min(low[u],low[v]);
        } else if(!scc[v]) {low[u] = min(low[u],dfn[v]);}
    }
    if(low[u] == dfn[u]) {
        ++top;
        do {
            scc[u] = top;
            u = vec.back();
            vec.pop_back();
            // vis[u] = false;
        } while(low[u] != dfn[u]);
    }
}



signed main() {
    read(n);
    read(m);
    vec.reserve(n << 1);
    while(m--) {
        int a,b,c,d;
        read(a);
        read(b);
        read(c);
        read(d);
        adde(a << 1 ^ b ^ 1,c << 1 ^ d);
        adde(c << 1 ^ d ^ 1,a << 1 ^ b);
    }
    // 2 ~ 2n + 1
    for(int i = 2 ; i <= (n << 1 | 1) ; ++i) {
        if(!dfn[i]) tarjan(i);
    }
    for(int i = 1 ; i <= n ; ++i) {
        if(scc[i << 1] == scc[i << 1 | 1]) {
            cout << "No";
            return 0;
        }
    }
    cout << "Yes\n";
    for(int i = 1 ; i <= n ; ++i) {
        printf(scc[i << 1 ] > scc[i << 1 | 1] ? "1 " : "0 ");
    }
    return 0;
}