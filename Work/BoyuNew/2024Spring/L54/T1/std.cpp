#include <iostream>
#include <algorithm>
using namespace std;

const int N = 1e6 + 2;

int a[N];
int b[N];

signed main() {
    int n;
    cin >> n;
    for (int i = 1 ; i <= n ; ++i) cin >> a[i];
    int cnt = 1;
    b[1] = a[1]; // Length = 1, minimum tail = a[1]

    for (int i = 2 ; i <= n ; ++i) {
        int pos = lower_bound(b + 1, b + cnt + 1, a[i]) - b;
        // b[pos - 1] < a[i] <= b[pos]
        // a[i] can be appended after b[pos - 1]
        // so we update b[pos] = a[i]
        b[pos] = a[i];
        // If exceed the length, update the length
        if (pos > cnt) cnt = pos;
    }
    cout << cnt << endl;
    return 0;
}
