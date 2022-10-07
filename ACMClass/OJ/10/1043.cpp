#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2004;

int c[N][N];
int dp[N];
bitset <N> f;

template <class T>
inline void ffread(T &tmp) {
    static char ch;
    tmp = 0;
    while(!isdigit(ch = getchar()));
    while(isdigit(ch)) {
        tmp = tmp * 10 + (ch^'0');
        ch = getchar();
    }
}

//终点
inline void read() {}

template <class T,class ...V>
void read(T &arg,V& ...args) {
    ffread(arg);
    read(args...);
}


int main() {
    int n,x;
    read(n);
    //覆盖点 x -> (x-1,x) 区间
    for(int i = 0 ; i < n ; ++i)
        for(int j = i+1 ; j <= n ; ++j) {
            read(x);
            c[j][i] = c[i][j] = x;
        }
    memset(dp,63,sizeof(dp));
    //prim 
    dp[0] = 0;//最短的边长
    f[0] = true;
    memcpy(dp,c[0],(n+1) << 2);
    for(int i = 1 ; i < n ; ++i) {
        int root = 0;//找最小的距离
        for(int j = 1 ; j <= n ; ++j) //没选过
            if(!f[j] && (f[root] || dp[j] < dp[root])) 
                root = j;
        f[root] = true;
        for(int j = 0 ; j <= n ; ++j) 
            if(!f[j] && dp[j] > c[root][j]) 
                dp[j] = c[root][j];
    }
    ll ans = 0;
    for(int i = 1 ; i <= n ; ++i) ans += dp[i];
    printf("%lld\n",ans);
    return 0;
}