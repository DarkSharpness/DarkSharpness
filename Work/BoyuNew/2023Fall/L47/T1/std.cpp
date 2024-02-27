#include <iostream>
#include <algorithm>
using namespace std;

const int N = 1e5 + 3;
int a[N];
int t[N];

int search(int len,int x) {
    int l = 1, r = len;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (t[mid] < x)
            l = mid + 1;
        else
            r = mid - 1;
    }
    return l;
}

signed main() {
    int n;
    cin >> n;
    for (int i = 1 ; i <= n ; ++i) cin >> a[i];
    int len = 1;
    t[1] = a[1];
    for (int i = 2 ; i <= n ; ++i) {
        if (a[i] > t[len])
            t[++len] = a[i];
        else {
            t[search(len,a[i])] = a[i];
        }
    }
    cout << n - len;
    return 0;
}