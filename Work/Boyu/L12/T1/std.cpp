#include <iostream>
#include <algorithm>
using namespace std;

const int N = 100;
int a[N]; // 不要抄答案!!!

signed main() {
    int n;
    cin >> n;
    for(int i = 0 ; i != n ; ++i) cin >> a[i];
    sort(a,a + n);
    for(int i = 0 ; i != n ; ++i) cout << a[i] << ' ';
    return 0;
}
