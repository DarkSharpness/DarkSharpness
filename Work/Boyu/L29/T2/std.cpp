#include <iostream>
#include <algorithm>
using namespace std;

long long t[100];

signed main() {
    int n;
    long long c;
    cin >> n >> c;
    for(int i = 0 ; i < n ; ++i)
       cin >> t[i];
    sort(t, t + n,greater <long long> ());
    long long cnt = 0;
    int i = 0;
    while(c) {
        cnt += c / t[i];
        c   %= t[i];
        ++i;
    }
    cout << cnt << '\n';
    return 0;
}