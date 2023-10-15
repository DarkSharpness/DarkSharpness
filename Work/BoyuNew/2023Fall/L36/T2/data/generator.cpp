#include <bits/stdc++.h>
using namespace std;


signed main() {
    srand(time(NULL));
    for(int i = 1 ; i <= 10 ; ++i) {
        string in  = to_string(i) + ".in";
        string out = to_string(i) + ".out";

        const int n = i * i * i * 100 - 1;

        freopen(in.c_str(),"w",stdout);

        cout << n << '\n';
        int ans = 0;
        for(int i = 1 ; i <= n ; ++i) {
            int x = rand() & 0x1fff;
            ans ^= x;
            cout << x << ' ';
        }

        freopen(out.c_str(),"w",stdout);
        cout << ans << '\n';
    }
    return 0;
}