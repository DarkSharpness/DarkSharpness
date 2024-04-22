#include <iostream>
using namespace std;

using ll = unsigned long long;
const int N = 1e5 + 10;
int a[N];
int n, m;

bool check(ll x) {
    ll sum = 0;
    ll cnt = m;
    for (int i = 1; i <= n; i++) {
        sum += a[i];
        if (sum > x) {
            sum = a[i]; // In a new segment
            if (--cnt == 0) return false;
        }
    }
    return true;
}

signed main() {
    cin >> n >> m;
    ll sum = 0;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        sum += a[i];
    }

    ll l = 0;
    ll r = sum;

    while (l != r) {
        ll mid = (l + r) / 2;
        if (check(mid)) {
            r = mid;
        } else {
            l = mid + 1;
        }
    }

    cout << l << endl;
    return 0;
}
