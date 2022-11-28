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
 *
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



int n,m;
const int N = 2e5 + 10;
struct edge{int to,nxt;}e[N << 4];
int head[N << 3],cnt;
inline void adde(int fr,int to) {e[++cnt] = (edge){to,head[fr]};head[fr] = cnt;}
int dfn[N << 3],low[N << 3],tot,scc[N << 3],top;
vector <int> g[N],st;
void tarjan(int u) {
    dfn[u] = low[u] = ++tot;
    st.push_back(u);
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
            u = st.back();
            st.pop_back();
        } while(low[u] != dfn[u]);
    }
}
int dot = 0;
void build() {
    dot = n << 1 | 1;
    for(int u = 1 ; u <= n ; ++u) {
        if(g[u].size() <= 1) continue;
        int j = 0;
        while(true) {
            int v = g[u][j];   // not compatible.
            adde(++dot,v ^ 1); // virtual node 1
            adde(++dot,v ^ 1); // virtual node 2
            if(!j++) {adde(v,dot + 2);continue;}
            adde(dot - 2,dot - 0); // Forward  list
            adde(dot - 1,dot - 3); // Backward list           
            adde(v,dot - 3); // 0 ~
            if(j != int(g[u].size())) {adde(v,dot + 2);}
            else break; 
        }
    }
}


signed main() {
    read(n);
    read(m);
    while(m--) {
        int a = read(a),b = read(b),c = read(c);
        adde(a << 1 | 1,b << 1 | c);   // True  -> True
        adde((b << 1 | c) ^ 1,a << 1); // False <- False
        g[a].push_back((b << 1 | c)^ 1);
    }
    build();
    for(int i = 2 ; i <= dot ; ++i) if(!dfn[i]) tarjan(i);
    int cntt = 0;
    for(int i = 1 ; i <= n ; ++i) {
        if(scc[i << 1] == scc[i << 1 | 1]) {
            puts("Impossible");
            return 0;
        } else cntt += scc[i << 1 ] < scc[i << 1 | 1];
    }
    write(cntt);putchar('\n');
    for(int i = 1 ; i <= n ; ++i)
        if(scc[i << 1 ] < scc[i << 1 | 1]) {write(i);putchar(' ');}
    return 0;
}