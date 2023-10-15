#include <iostream>
#include <algorithm>
using namespace std;

const int N = 5000;
int a[N];


signed main() {
    freopen("data/10.in","r",stdin);
    int n,w,c;
    cin >> n >> w >> c;
    for(int i = 0 ; i < n ; ++i) cin >> a[i];
    sort(a, a + n);
    if (a[n - 1] > w) {
        cout << -1 << '\n';
        return 0;
    }

    // 有 i 艘船是坐了两个人的
    for(int i = n >> 1 ; i >= 0 ; --i) {
        int z = (i << 1) - 1;
        // 最优情况是头尾配对，最重的搭配最轻的
        bool flag = false;
        for(int j = 0 ; j < i ; ++j) {
            if (a[j] + a[z - j] > w) {
                flag = true;
                break;
            }
        }

        if (!flag) {
            int t = n - (i << 1); // 剩下 t 个人单独乘船
            if (i + t > c) cout << -1 << '\n';
            else           cout << i + t << '\n';
            return 0;
        }
    }

    cout << -1 << '\n';
    return 0;
}