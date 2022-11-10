#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
//#define int lont long
const int N = 502;
const int M = 25008;
int n;
int h[N];
bitset <M<<1> dp[2][N];
int tot[N];
int sum[N];
int cnt[N];

signed main() {
    ios::sync_with_stdio(false);
    cin >> n;
    int maxn = 0;
    int sumheight = 0;
    for(int i = 1 ; i <= n ; ++i) {
        cin >> h[i];
        if(h[i] > maxn) maxn = h[i];
        ++tot[h[i]];
        sumheight += h[i];
    }
    --tot[maxn];
    int idx = 0;
    dp[0][0][0] = true;
    for(int i = 1 ; i <= maxn ; ++i) {
        sum[i] = sum[i-1] + tot[i];
        if(!tot[i]) continue;
        auto pre = dp[idx];
        idx ^= 1;
        auto cur = dp[idx];
        for(int j = 0 ; j <= sum[i]; ++j) {
            for(int k = 0 ; k <= j ; ++k) {
                cur[j] |= (pre[j-k] << (k * i));
            }
        }
    }
    auto cur = dp[idx][n-1];
    for(int i = 0 ; i+sumheight-maxn < M ; ++i) {
        if(cur[i+sumheight-maxn]) cout << i << ' ';
    }
    return 0;
}