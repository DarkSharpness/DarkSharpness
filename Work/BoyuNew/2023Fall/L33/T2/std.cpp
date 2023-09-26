#include <iostream>
using namespace std;

const int N = 1e5 + 3;
int a[N];

int main() {
    int n,m;
    cin >> n >> m;
    for(int i = 0 ; i < n ; ++i) cin >> a[i];
    int l = 1;
    int r = (a[n - 1] - a[0]) / (m - 1) + 1;
    int ans = 0;
    // 二分答案 枚举范围 [l,r)
    while(l != r) {
        int mid = (l + r) >> 1;

        int cnt = 1;    // 第一个点当然是选的
        int pre = a[0]; // 从第一个点开始
        bool tmp = false;

        // 枚举 mid 的时候最多可以有多少个点
        for(int i = 1 ; i < n ; ++i) {
            if(a[i] - pre >= mid) {
                // 如果发现 cnt >= m 说明 mid 可以更大
                if(++cnt >= m) {
                    tmp = true;
                    break;
                } pre = a[i];
            }
        }

        if (tmp) l = mid + 1 , ans = mid;
        else     r = mid;
    } cout << ans;
    return 0;
}