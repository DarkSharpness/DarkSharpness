#include <iostream>
using namespace std;
const int N = 1e5 + 3;
int cnt[N];

signed main() {
    int n;
    cin >> n;
    for (int i = 1 ; i <= n ; ++i) {
        int x;
        cin >> x;
        ++cnt[x];
    }
    long long ans = 0;
    long long res = 0;
    for (int i = 1 ; i < N ; ++i) {
        res += cnt[i];
        if (res != 0) {
            --res;
            ans += res;
        }
    }
    ans += res * (res - 1) / 2;
    cout << ans << endl;
    return 0;
}