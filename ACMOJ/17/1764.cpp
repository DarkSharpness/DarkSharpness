#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
/// @brief Read an unsigned integer.
/// @param dst Where the unsigned integer will be written into.
template <class integer>
integer &read(integer &dst) {
    int  ch;
    while(!isdigit(ch = getchar()) && ch != EOF);
    dst = 0;
    while(isdigit(ch)) {
        dst = dst * 10 + (ch ^ '0');
        ch  = getchar();
    }
    return dst;
}
/**
 * @brief  Print out integer fast.
 * 
 * @tparam integer Any integer type. You may leave it blank
 *         or set the integer type yourself. For example, 
 *         Fwrite <unsigned> (-1) will be 4294967295.
 * @param  src The number to be written.
 */
template <class integer>
void write(integer src) {
    static char ch[20];
    if(src == 0) {
        putchar('0');
    } else if(src < 0) {
        src = -src;
        putchar('-');
    }
    int32_t top = 19;
    while(src) {
        ch[--top] = (src % 10) ^ '0';
        src /= 10;
    }
    printf("%s",ch + top);
}


constexpr int N = 114514;
constexpr int M = 1919810;
struct edge{int fr,to,nxt;}e[M << 1];
int head[N],tot = 0;
unordered_set <long long> s;
inline void adde(int fr,int to) {e[++tot] = edge{fr,to,head[fr]};head[fr] = tot;}
int dfn[N],dfs = 0,low[N],scc[N],siz[N],num,in[N],out[N],sub[N],cnt[N];
vector <int> st,g[N];
queue <int> q;
void tarjan(int u) {
    dfn[u] = low[u] = ++dfs;
    st.push_back(u);
    for(int i = head[u] ; i ; i = e[i].nxt) {
        int v = e[i].to;
        if(!dfn[v]) { tarjan(v);low[u] = min(low[u],low[v]);} 
        else if(!scc[v]) low[u] = min(low[u],dfn[v]);
    }
    if(low[u] == dfn[u]) {
        siz[scc[u] = ++num] = 1;
        while(st.back() != u) {++siz[scc[st.back()] = num];st.pop_back();}
        st.pop_back(); // pop out u
    }
}

signed main() {
    int n = read(n),m = read(m), mod = read(mod);
    for(int i = 1,x,y ; i <= m ; ++i) {read(x);read(y);adde(x,y);}
    for(int i = 1 ; i <= n ; ++i) if(!dfn[i]) tarjan(i);    
    for(int i = 1 ; i <= m ; ++i) {
        int u = scc[e[i].fr],v = scc[e[i].to];
        if(u != v && s.insert(u * N + v).second) {
            g[u].push_back(v);++out[u],++in[v];
        }
    }
    for(int i = 1 ; i <= num ; ++i) if(!in[i]) {cnt[i] = 1;q.push(i);}
    while(!q.empty()) { // TOPO: DAG longest list
        int u = q.front();q.pop();
        sub[u] += siz[u];
        for(auto v : g[u]) {
            if(sub[u] > sub[v]) {sub[v] = sub[u];cnt[v] = cnt[u];}
            else if(sub[u] == sub[v]) {cnt[v] = (cnt[v] + cnt[u]) % mod;}
            if(!--in[v]) {q.push(v);} --out[u];
        }
    }
    int maxn = 0; int ans = 0;
    for(int i = 1 ; i <= num ; ++i) {
        if(sub[i] > maxn) {maxn = sub[i]; ans = cnt[i];}
        else if(sub[i] == maxn) {ans = (ans + cnt[i]) % mod;}
    }
    write(maxn);putchar('\n');write(ans % mod);
    return 0;
}