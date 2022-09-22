#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 504;

int dp[2][N][N];
int loc[N];
int sum[N];
int c[N][N];
#define endl '\n'
inline int query(int x,int y) {
    return sum[y] - sum[x] - loc[x]*(y-x);
}
inline int dist(int x,int y) {
    return loc[y] - loc[x];
}

int main() {
    ios::sync_with_stdio(false);
    int n,m;
    cin >> n >> m;
    for(int i = 2; i <= n ; ++i) {
        cin >> loc[i];
        loc[i] += loc[i-1];
        sum[i] =  sum[i-1]+loc[i];
    }
    for(int i = 1; i <= n ; ++i) {
        int k  = i;
        for(int j = i + 1; j <= n; ++j) {
            while((loc[k]<<1) <= loc[i]+loc[j] ) ++k;
           // cout << k << ":" ;
            c[i][j] -= query(i,j); 
            c[i][j] += query(i,k-1)+query(k,j);
            //cout << c[i][j] << " ";
        }
        //cout << endl;
    }

    memset(dp,60,sizeof(dp));
    
    for(int k = 1 ; k <= n ;++k) { //Ã¶¾ÙLast
        dp[1][k][k] = (k-1)*loc[k]-sum[k-1];
        for(int j = k+1 ; j <=n ; ++j)
            dp[1][j][k] = dp[1][j-1][k] + dist(k,j);
    }

    for(int t = 2,i = 1; t <= m ; ++t) {//m¸ö
        i ^= 1;
        for(int j = i ; j <= n ; ++j) {
            for(int k = i  ;  k < j ; ++k) 
                dp[i][j][k] = dp[i][j-1][k] + dist(k,j);
            for(int k = i-1 ; k < j ; ++k) {
                dp[i][j][j] = min(dp[i][j][j],dp[i^1][j][k]+c[k][j]);
            }
        }

    }
    int ans = 1919810<<10;
    for(int i =m ; i <=n ; ++i){
        ans = min(ans,dp[m & 1][n][i]);
    }
    cout << ans << endl;
    return 0;
}