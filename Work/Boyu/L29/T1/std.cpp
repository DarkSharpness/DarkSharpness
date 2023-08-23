#include <iostream>
using namespace std;

signed main() {
    int n;
    cin >> n;
    long long ans = 0;
    long long sum = 0;
    for(int i = 1; i <= n; i++) {
        int x;
        cin >> x;

        // 累加更新最大值
        sum += x;
        ans = max(ans,sum);
        
        // 舍弃前面的负数
        if(sum < 0) sum = 0;
    }
    cout << ans;

    return 0;
}