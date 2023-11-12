#include <iostream>
using namespace std;

const long long mod = 1e9 + 7;
const int N = 1e4 + 3;

int  a[N];
bool v[N];

int search(int x,const int k) {
    if (v[x]) return a[x];
    long long sum = 0;
    for(int i = 1 ; i <= k ; ++i)
        sum += search(x - i, k);
    v[x] = true;
    return a[x] = sum % mod;
}

signed main() {
    int m, k;
    cin >> m >> k;
    for(int i = 1; i <= k ; ++i) {
        cin >> a[i];
        v[i] = true;
    }
    while(m--) {
        int x;
        cin >> x;
        cout << search(x, k) << endl;
    }
    return 0;
}
