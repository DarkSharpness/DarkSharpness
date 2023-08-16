#include <bits/stdc++.h>
#include <Dark/inout>

const int n = 1e5;
const int m = 100;

signed main() {
    freopen("9.in","w",stdout);
    dark::writeline(n,m);
    int i = 0;
    while(i < n / 4)      dark::print(1,' '),++i;
    while(i < 3 * n / 4)  dark::print(n - 1,' '),++i;
    while(i < n)          dark::print(m - 1,' '),++i;
    freopen("9.out","w",stdout);
    dark::writeline(static_cast <long long> (n) * n / 16);
    return 0;
}
