#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

const int N = 1e5 + 3;
int a[N];

signed main() {
    priority_queue <int, vector<int>, greater<int>> q;
    int n;
    cin >> n;
    for (int i = 1 ; i <= n ; ++i) cin >> a[i];
    q.push(a[1]);
    unsigned long long ans = 0;
    for (int i = 2 ; i <= n ; ++i) {
        int tmp = q.top();
        if (a[i] > tmp) {
            q.pop();
            q.push(a[i]);
            ans += a[i] - tmp;
        }
        q.push(a[i]);
    }
    cout << ans << endl;
    return 0;
}
