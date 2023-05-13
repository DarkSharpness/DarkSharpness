#include <iostream>
using namespace std;

const int N = 1003;
int a[N];
int d[N];

signed main() {
    int n,m;
    cin >> n >> m;
    for(int i = 1 ; i <= n ; ++i) cin >> a[i];
    for(int i = 1 ; i <= m ; ++i) {
        int x,y;
        cin >> x >> y;
        d[x] += y;
    }
    int t = 0;
    for(int i = n ; i >= 1 ; --i) {
        t += d[i];
        a[i] += t;
    }
    for(int i = 1 ; i <= n ; ++i)
        cout << a[i] << '\n';
    return 0;
}