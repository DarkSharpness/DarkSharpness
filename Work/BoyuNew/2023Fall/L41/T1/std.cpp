#include <iostream>
using namespace std;
// #include <bits/stdc++.h>

const int N = 1e3 + 3;
int a[N];
int f[N];


signed main() {
    int n;
    cin >> n;
    for (int i = 1 ; i <= n ; ++i) cin >> a[i] , f[i] = 1;

    int ans = 1;
    for (int i = 2 ; i <= n ; ++i) {
        for (int j = 1 ; j < i ; ++j)
            if (a[j] > a[i]) f[i] = max(f[i] , f[j] + 1);
        ans = max(ans , f[i]);
    }

    cout << ans << '\n';
    return 0;
}
