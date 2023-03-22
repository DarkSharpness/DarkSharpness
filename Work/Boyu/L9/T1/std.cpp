#include <iostream>
using namespace std;
const int N = 10000;
int a[N];

signed main() {
    int n;
    cin >> n;
    for(int i = 0 ; i < n ; ++i) cin >> a[i];
    for(int i = n - 1 ; i ; --i) cout << a[i] << ' ';
    cout << a[0];
    return 0;
}
