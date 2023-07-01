#include <iostream>
using namespace std;
using ll = long long;

const int N = 1e4 + 3;
int a[N];

signed main() {
    int n,m;
    cin >> n >> m;
    for(int i = 1 ; i <= n ; ++i) {
        int x;
        cin >> x;
        a[x] = i;
    }
    while(m--) {
        int x;
        cin >> x;
        cout << a[x] - 1 << '\n';
    }
    return 0;
}
