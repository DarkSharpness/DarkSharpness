#include <iostream>
#include <cstring>

const int N = 5e4 + 9;
int f[N]; /* 第 i 天开始之前可以获得的技能点之和最大值 */
int a[N],b[N],c[N],d[N];

signed main() {
    int n;
    std::cin >> n;
    for(int i = 0 ; i < n ; ++i)
        std::cin >> a[i] >> b[i] >> c[i] >> d[i];
    for(int i = 0 ; i < n ; ++i) {
        if(i + a[i] <= n) // 选择 1
            f[i + a[i]] = std::max(f[i + a[i]],f[i] + c[i]);
        if(i + b[i] <= n) // 选择 2
            f[i + b[i]] = std::max(f[i + b[i]],f[i] + d[i]);
        // 选择摸鱼
        f[i + 1] = std::max(f[i + 1],f[i]);
    }
    std::cout << f[n] << '\n';
    return 0;
}
