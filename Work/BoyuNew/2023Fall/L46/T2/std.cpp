#include <iostream>
using namespace std;
using ll = long long;
const ll N = 20;
const ll M = 1e9 + 7;
ll a[N];    // a[i] = pow(10,i)
ll b[N];    // b[i] = 1 ~ a[i]-1 的和

signed main() {
    // 初始化
    a[0] = 1;
    b[0] = 0;
    for (int i = 1 ; i < N ; ++i) {
        a[i] = a[i - 1] * 10;
        b[i] = (b[i - 1] * 10 + 45 * a[i - 1]) % M;
    }
    // 輸入
    long long n;
    long long ans = 0;
    cin >> n;
    for (int j = 18; j >= 0 ; --j) {
        if (a[j] > n) continue;
        long long x = n / a[j]; // x = n / a[i]
        long long y = n % a[j]; // y = n % a[i]

        // 先统计 1 ~ x * a[i] - 1 的和
        // 再统计 x & a[i] ~ n 的最高位之和
        // 剩下的部分再递归
        ans += x * b[j] + x * (x - 1) / 2 * a[j] + x * (y + 1);
        ans %= M;

        n = y;
    }
    cout << ans << endl;
    return 0;
}
