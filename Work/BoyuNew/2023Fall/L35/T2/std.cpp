#include <iostream>
#include <algorithm>
using namespace std;

const int N = 5e3 + 3;
int a[N];
int b[N];

int main() {
    int n,m,c;
    std::cin >> n >> m >> c;
    for(int i = 1 ; i <= n ; ++i) std::cin >> a[i];
    for(int i = 1 ; i <= m ; ++i) std::cin >> b[i];

    // 从大到小排序
    std::sort(a + 1, a + n + 1,std::greater <int> ());
    std::sort(b + 1, b + m + 1,std::greater <int> ());

    // 前缀和
    for(int i = 1 ; i <= n ; ++i) a[i] = a[i] + a[i - 1];
    for(int i = 1 ; i <= m ; ++i) b[i] = b[i] + b[i - 1];

    // 枚举 2 出现了多少个
    int beg = std::max(0, (c - n + 1) / 2);
    int end = std::min(m, c / 2);
    int ans = 0;

    // 固定了 2 和 1 的个数后，每次选择尽可能性价比高的 2 和 1
    for(int i = beg ; i != end; ++i) {
        int j = c - 2 * i;

        // 1 的个数显然不超过 n
        // 2 的个数显然不超过 m
        // 所以 2 * i + j = c
        // 且   i <= m
        // 且   j <= n
        // 且   i >= 0
        // 且   j >= 0

        // 前缀和优化了，如果不优化则是 n ^ 2 复杂度，也能过
        // 这边 a[j] 相当于是价格为 1 的最大的 j 个权值和
        ans = std::max(ans, a[j] + b[i]);
    }

    std::cout << ans;    
    return 0;
}