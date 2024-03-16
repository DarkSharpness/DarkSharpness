#include <iostream>
#include <cstring>
#include <Dark/inout>

constexpr int N = 1e5 + 3;
struct edge { int to,nxt; } e[N << 1];
int Head[N],tot;
inline void adde(int fr,int to) 
{ e[++tot] = edge{to,Head[fr]}; Head[fr] = tot; }

constexpr int sqr = 401;

int f[N][N / sqr + 3];
int w[N];
int block;  // block number

inline int index(int i) { return (i - 1) / sqr; }
inline int head(int i)  { return sqr * i  + 1;  }
inline int tail(int i)  { return sqr * (i + 1); }


int dfn[N],dfc; // dfn id
int siz[N];     // subtree dfn last id
long long pre[N + sqr];     // reverse dfn prefix sum
long long tag[N / sqr + 3]; // reverse dfn tag of a block
long long ans[N / sqr + 3]; // ans of a block

inline long long getpre(int i)
{ return pre[dfn[i]] + tag[index(dfn[i])] 
       - pre[siz[i]] - tag[index(siz[i])]; }

long long dfs(int u,int fa) {
    ++f[u][index(u)];
    long long sum = pre[dfn[u] = ++dfc] = w[u];
    for(int i = Head[u] ; i ; i = e[i].nxt) {
        int v = e[i].to;
        if(v == fa) continue;
        memcpy(f[v],f[u],(block + 1) * sizeof(int));
        sum += dfs(v,u);
    }
    siz[u] = dfc + 1;
    ans[index(u)] += sum;
    return sum;
}


signed main() {
    int n,m;
    dark::read_u(n,m);
    for(int i = 1 ; i <= n ; ++i) dark::read(w[i]);
    for(int i = 1,x,y ; i <= n ; ++i) 
    { dark::read_u(x,y); adde(x,y); adde(y,x); }
    block = index(n);
    dfs(e[Head[0]].to,0);
    for(int i = n ; i ; --i) pre[i] += pre[i + 1];
    while(m--) {
        int x,y;
        char opt = dark::read_char(opt);
        dark::read_u(x,y);
        if(opt == '1') { /* At most sqr + N / sqr * 2 */
            long long delta = y - w[x];
            w[x] = y;
            for(int i = 0 ; i <= block ; ++i)  ans[i] += delta * f[x][i];
            int t = index(dfn[x]);
            for(int i = t - 1  ; i >= 0 ; --i) tag[i] += delta;
            t = head(t);
            for(int i = dfn[x] ; i >= t ; --i) pre[i] += delta;
        } else { /* At most 2 * sqr + N /sqr times */
            long long s = 0;
            if(index(x) == index(y)) { // In the same block
                for(int i = x ; i <= y ; ++i) s += getpre(i);
            } else {
                for(int i = index(x) + 1 ; i != index(y) ; ++i) s += ans[i];
                int t = tail(index(x));
                // if(t > n) throw;
                for(int i = x ; i <= t ; ++i) s += getpre(i);
                t = head(index(y));
                for(int i = t ; i <= y ; ++i) s += getpre(i);
            }
            dark::writeline(s);
        }
    }
    return 0;
}
