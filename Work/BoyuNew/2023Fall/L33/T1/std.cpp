#include <iostream>
using namespace std;

const int N = 1e5 + 3;
int a[N];

signed main() {
    int n,m;
    cin >> n >> m;
    for(int i = 0 ; i < n ; ++i) cin >> a[i];
    while(m--) {
        int x,l = 0 , r = n;
        cin >> x;
        // 在范围 [l,r) 中查找 x
        while(l != r) { // 如果不放心可以写 l < r
            int mid = (l + r) >> 1;
            if (x == a[mid]) { // 由于下标从 0 , 所以答案为 n - mid
                cout << (n - mid) << '\n';
                break;
            }
            /* mid 不可能是答案，范围变为 [l,mid + 1) */
            else if (x < a[mid]) r = mid;
            /* mid 不可能是答案，范围变为 [mid + 1,r) */
            else l = mid + 1;
        } // 因为一定存在，所以不用担心结束。
    }
    return 0;
}