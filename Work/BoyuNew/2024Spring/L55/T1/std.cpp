#include <iostream>
using namespace std;

const int N = 1e5 + 3;
int a[N];

signed main() {
    int n;
    cin >> n;
    for (int i = 1 ; i <= n ; ++i) cin >> a[i];
    int minn = a[1];
    int ans  = 0;
    for (int i = 2 ; i <= n ; ++i) {
        if (a[i] > minn) ans = max(ans, a[i] - minn);
        else minn = a[i];
    }
    cout << ans << endl;
    return 0;
}
