#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
const int N = 2508;
struct edge {
    int nxt,to;
}e[N];
int head[N],tot = 0;
inline void adde(int fr,int to) {
    e[++tot].nxt = head[fr];
    head[fr] = tot;
    e[tot].to = to;
}
int n,k;
int v[N],s[N],r;
double f[N];

inline void dfs(int id) {
    
    for(int i = head[id] ; i ; i = e[i].nxt) {
        dfs(e[i].to);
    }
    for(int i = head[id] ; i ; i = e[i].nxt) {
        int to = e[i].to;
    }
}


signed main() {
    ios::sync_with_stdio(false);
    cin >> k >> n;
    for(int i = 1 ; i <= n ; ++i) {
        cin >> v[i] >> s[i] >> r;
        adde(r,i);
    }
    dfs(0);
    return 0;
}