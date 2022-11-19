#include <iostream>
#include <algorithm>
using namespace std;

const int M = 1e3 + 4,N = 1e4 + 4;

#define int long long

struct item {
    int w,v;
    inline bool operator < (const item &B) {
        return w * B.v < v * B.w;
    }
}w[M];


int dp[N]; // dp[i][j] 表示已经处理了物品 0 ~ i-1 空间剩余 j 的最优解
          // 事实上,我们不关心历史信息,每次dp是相邻两项转移
          // 所以可以省略第一维的数组.
signed main() {
    int n,m;
    ios::sync_with_stdio(false); // 关闭流同步 加速输入输出
    cin >> n >> m;
    for(int i = 0 ; i < m ; ++i) cin >> w[i].v;
    for(int i = 0 ; i < m ; ++i) cin >> w[i].w;
    sort(w,w+m);
    // dp[0][n] = 0; // 其实不用初始化
    for(int i = 0 ; i < m ; ++i) {        
        for(int j = w[i].w ; j <= n ; ++j) {
            // 因为省了第一维,所以必须从小到大枚举
            // 右边的dp[j] 其实是dp[i][j]
            // 是从 j较大 更新 j较小 的dp结果
            // 所以为了保证在过程中 dp[i][j] 不会出bug,从小到大枚举
            dp[j - w[i].w] = max(dp[j - w[i].w],dp[j] + j * w[i].v);
        }
    }
    int ans = 0;
    for(int i = 0 ; i <= n ; ++i) {
        if(dp[i] > ans) ans = dp[i];
    }
    cout << ans;
    return 0;
}