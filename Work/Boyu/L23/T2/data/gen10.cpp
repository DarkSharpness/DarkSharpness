#include <bits/stdc++.h>
#include <Dark/inout>


signed main() {
    freopen("10.in","w",stdout);
    srand(time(NULL));
    const int n = 5e4 - 1;
    dark::writeline(n);
    for(int i = 1 ; i < n ; ++i)
        if(rand() & 0b100)
            dark::writeline(i + 1,0);
        else
            dark::writeline(0,i + 1);
    dark::writeline(0,0);
    freopen("10.out","w",stdout);
    for(int i = 0 ; i < n ; ++i)
        dark::writeline(n - i);
    return 0;
}
