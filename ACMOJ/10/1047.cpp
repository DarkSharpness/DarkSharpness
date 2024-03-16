#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7;
int n,m,C;


inline void F_read(int &tmp) {
    static char ch;
    while(!isdigit(ch = getchar()));
    tmp = 0;
    while(isdigit(ch)) {
        tmp = tmp * 10 + (ch ^ '0');
        ch = getchar();
    }
}

inline void read() {}
template <class T,class ...V>
void read(T &arg,V &...args) {
    F_read(arg);
    read(args...);
}

const int N = 1e5 +10;
struct edge {
    int to,nxt,len;
}e[N*24];
int head[N] , tot = 0;
inline void adde(int fr,int to,int len) {
    e[++tot].to = to;
    e[tot].len  = len;
    e[tot].nxt  = head[fr];
    head[fr]    = tot;
}
//priority_queue <pair<long long,int>> q;
queue <int>q;
int dp[N];
bitset <N>vis;

inline void dijsktra(int src,int dst) {
    memset(dp,0x1f,sizeof(dp));
    dp[src] = 0;
    q.emplace(src);
    while(!q.empty()) {
        int x = q.front();
        q.pop();
        vis[x] = false;
        for(int i = head[x] ; i ; i = e[i].nxt) {
            int v = e[i].to;
            int sum = dp[x] + e[i].len;
            if(dp[v] > sum) {
                dp[v] = sum;
                if(v != dst) {
                    q.emplace(v);
                    vis[v] = true;
                }
            }

        }

    }
    printf("%d\n",dp[dst]);
}


int main() {
    read(n,m,C);
    for(int i = 1,f,t,v; i <= m; ++i) {
        read(f,t,v);
        adde(f,t,v);
    }
    for(int i = 1; i <= n; ++i) 
        for(int j = 1; j <= n; j <<= 1) 
            if((i^j) <= n && (i^j)) 
                adde(i,i^j,C*j);
    int src,dst;
    read(src,dst);
    dijsktra(src,dst);
    return 0;
}
