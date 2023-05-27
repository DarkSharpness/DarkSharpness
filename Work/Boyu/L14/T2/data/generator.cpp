#include <bits/stdc++.h>
#include <Dark/inout>
using namespace std;

int a[1001];

signed main() {
    srand(time(NULL));
    for(int tt = 1 ; tt <= 10 ; ++tt) {
        string in  = to_string(tt) + ".in";
        string out = to_string(tt) + ".out";
        freopen(in.c_str(),"w",stdout);
        int n = rand() % (tt * tt * tt) + 1;
        for(int i = 1 ; i <= n ; ++i)
            a[i] = rand() % min(1000,2 * n) + 1;
        sort(a + 1,a + n + 1);
        n = unique(a + 1,a + n + 1) - a - 1;
        dark::writeline(n);
        dark::writelineRange(a + 1,a + n + 1);
        int ans = rand() % n + 1;
        dark::writeline(a[ans]);
        freopen(out.c_str(),"w",stdout);
        dark::writeline(ans);
    }
    return 0;
}