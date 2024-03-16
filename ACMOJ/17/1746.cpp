#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
//#define int lont long
const int N = 2504;
struct edge{
    int to,nxt;
}e[N << 2];
int head[N],tot = 0;
inline void adde(int fr,int to) {
    e[++tot].to = to;
    e[tot].nxt  = head[fr];
    head[fr]    = tot;
} 

int v[N],s[N];
int k,n;
int siz[N];

double dp[N][N];
double t[N];

void dfs(int id) {
    dp[id][0] = 0;
    dp[id][1] = t[id];
    siz[id] = 1;
    for(int i = head[id] ; i ; i = e[i].nxt) {
        int to = e[i].to;
        dfs(to);
        siz[id] += siz[to];
        for(int j = min(siz[id],k+1) ; j ; --j) {
            for(int l = 0 ; l <= min(siz[to],j-1) ; ++l) {
                dp[id][j] = max(dp[id][j],dp[id][j-l] + dp[to][l]);
            }
        }
    }
}


inline bool check(double mid) {
    for(int i = 1 ; i <= n ; ++i) {
        t[i] = s[i] - mid * v[i];
    }
    for(int i = 0 ; i <= n ; ++i) 
        for(int j = 1 ; j <= k + 1; ++j)
            dp[i][j] = -1e12;
    t[0] = 0;
    dfs(0);
    return dp[0][k+1] >= 0;
}


signed main() {
    scanf("%d%d",&k,&n);
    double l = 10000,r = 0;
    for(int i = 1,R ; i <= n ; ++i) {
        scanf("%d%d%d",v+i,s+i,&R);
        r = max(r,double(s[i])/v[i]);
        l = min(l,double(s[i])/v[i]);
        adde(R,i);
    }
    while(r - l >= 1e-4) {
        double mid = (l + r) * 0.5;
        if(check(mid)) {
            l = mid;
        } else r = mid;
    }
    printf("%.3lf",l);
    return 0;
}