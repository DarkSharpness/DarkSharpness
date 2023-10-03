#include <iostream>
using namespace std;

const int N = 5009;
long long sum[N];

signed main() {
    int n;
    freopen("data/10.in","r",stdin);
    cin >> n;
    for(int i = 0 ; i < n ; ++i) cin >> sum[i];
    long long ans = 0;
    for(; n != 1 ;) {
        int pos1;  // 最小的所在位置
        int pos2;  // 次小的所在位置
        // 初始化最小和次小的位置
        if (sum[0] > sum[1]) pos1 = 1, pos2 = 0;
        else                 pos1 = 0, pos2 = 1;
        // 找出最小和次小的位置
        for(int j = 2 ; j < n; ++j) {
            if (sum[j] < sum[pos1]) {
                pos2 = pos1;
                pos1 = j;
            } else if (sum[j] < sum[pos2]) {
                pos2 = j;
            }
        }
        ans += sum[pos1] + sum[pos2];
        // 将最小和次小的合并 (直接原地合并即可)
        sum[pos1] += sum[pos2];
        // 将最后一个数移到次小的位置 (因为这个位置用不上了)
        sum[pos2] = sum[--n];
    }
    cout << ans;
    return 0;
}