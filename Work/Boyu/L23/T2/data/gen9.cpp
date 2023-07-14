#include <bits/stdc++.h>
#include <Dark/inout>


signed main() {
    freopen("9.in","w",stdout);
    srand(time(NULL));
    const int n = 5e4 - 1;
    dark::writeline(n);
    for(int i = 1 ; i <= n ; ++i)
        dark::writeline(0,0);
    freopen("9.out","w",stdout);
    for(int i = 0 ; i < n ; ++i)
        dark::writeline(1);
    return 0;
}
