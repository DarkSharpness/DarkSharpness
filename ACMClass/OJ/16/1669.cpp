#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 504;

int dp[2][N][N];
int loc[N];
int sum[N];     //sum[i] = loc[1] + ... + loc[i]
int c[N][N];
#define endl '\n'

//x ~ y到 x的距离
inline int query(int x,int y) {
    return sum[y] - sum[x] - loc[x]*(y-x);
}
//x ~ y到 y的距离
inline int rquery(int x,int y) {
    return loc[y] * (y-x) - sum[y-1] + sum[x-1];
}

inline int dist(int x,int y) {
    return loc[y] - loc[x];
}

int main() {
    ios::sync_with_stdio(false);
    int n,m;
    cin >> n >> m;
    loc[1] = 0;
    sum[1] = 0;
    for(int i = 2; i <= n ; ++i) {
        cin >> loc[i];
        loc[i] += loc[i-1];
        sum[i] =  sum[i-1] + loc[i];
    }
    for(int i = 1; i <= n ; ++i) {
        int k = i;
        for(int j = i + 1; j <= n; ++j) {
            while((loc[k]<<1) <= loc[i]+loc[j]) ++k;
            c[i][j] -= query(i,j); 
            c[i][j] += query(i,k-1)+rquery(k,j);
        }
        //cout << endl;
    }

    memset(dp,60,sizeof(dp));
    
    for(int j = 1 ; j <= n ; ++j) {
        for(int k = 1  ;  k < j ; ++k) 
            dp[1][j][k] = dp[1][j-1][k] + dist(k,j);
        dp[1][j][j] = rquery(1,j);
    }
    //cout << dp[0][0][0] <<endl;
    for(int t = 2,i = 1; t <= m ; ++t) {
        i ^= 1;
        for(int j = i ; j <= n ; ++j) {
            for(int k = i  ;  k < j ; ++k) 
                dp[i][j][k] = dp[i][j-1][k] + dist(k,j);
            dp[i][j][j] = 114514 << 14; //初始化的dp[i][j][j]
            for(int g = i-1 ; g < j ; ++g) {//取min
                dp[i][j][j] = min(dp[ i ][j][j],
                        c[g][j] + dp[i^1][j][g]);
            }
        }
    }
    int ans = 1919810 << 10;
    for(int i = m ; i <=n ; ++i){
        ans = min(ans,dp[m & 1][n][i]);
    }
    cout << ans << endl;
    return 0;
}