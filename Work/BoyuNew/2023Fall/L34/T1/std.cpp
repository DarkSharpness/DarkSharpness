#include <iostream>
using namespace std;

const int N = 1e5 + 3;
long long a[N];

signed main() {
    int n,m;
    cin >> n >> m;
    for(int i = 1;i <= n;i++) {
        cin >> a[i];
        a[i] = a[i] + a[i - 1]; // 前缀和
    }
    while(m--) {
        int x,y;
        cin >> x >> y;
        int l = x;
        int r = n + 1;

        // 枚举区间 [l,r)
        while(l != r) {
            int mid = (l + r) >> 1;
            if(a[mid] - a[x - 1] >= y) {
                r = mid;
            } else {
                l = mid + 1;
            }
        }

        if (r == n + 1) {
            cout << -1 << endl;
        } else {
            cout << (r - x + 1) << endl;
        }
    }
    return 0;
}