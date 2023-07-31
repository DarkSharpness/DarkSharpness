#include <bits/stdc++.h>
#include <Dark/inout>
using namespace std;


int x[1 << 17];

signed main() {
    srand(time(NULL));
    for(int i = 1 ; i <= 10 ; ++i) {
        string in  = to_string(i) + ".in";
        string out = to_string(i) + ".out";
        const int n = 1 << (7 + i);
        const int k = rand() % (7 + i);
        for(int i = 0 ; i < n ; ++i)
            x[i] = abs(rand() | rand() << 16);
        freopen(in.c_str(),"w",stdout);
        dark::writeline(n,k);
        dark::writelineRange(x,x + n);
        freopen(out.c_str(),"w",stdout);
        const int m = 1 << k;
        for(int i = 0 ; i < (n >> k) ; ++i)
            std::sort(x + i * m,x + i * m + m);
        dark::writelineRange(x,x + n);
    }
    return 0;
}