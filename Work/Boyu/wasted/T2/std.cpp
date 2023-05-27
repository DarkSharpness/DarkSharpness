#include <iostream>
using namespace std;

const int N = 101;
int s[N];

signed main() {
    int n,q;
    cin >> n >> q;
    for(int i = 1 ; i <= n ; ++i) {
        cin >> s[i];
        s[i] += s[i - 1];
    }
    while(q--) {
        int l,r;
        cin >> l >> r;
        cout << s[r] - s[l - 1] << '\n';
    }
    return 0;
}