#include <iostream>
using namespace std;

int n,m;
int w[20],v[20];
int ans = -100000; // 初始为负无穷

/**
 * @brief 递归来枚举是否
 * 
 * @param x 表示当前枚举到第几个 
 * @param s 表示当前已占多少空间
 * @param c 表示当前已选价值总和
 */
void solve(int x,int s,int c) {
    if(x == n) {
        if(s && s <= m && ans < c) ans = c;
        return;
    }
    solve(x + 1,s + w[x],c + v[x]);
    solve(x + 1,   s    ,   c    );
}

// 这只是个模板，你可以选择用或者不用它......
signed main() {
    // 输入......
    cin >> n >> m;
    for(int i = 0 ; i < n ; ++i)
        cin >> w[i] >> v[i];
    solve(0,0,0);
    // 输出答案
    cout << ans << '\n';
    return 0;
}