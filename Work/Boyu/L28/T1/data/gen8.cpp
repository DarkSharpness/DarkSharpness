#include <bits/stdc++.h>
#include <Dark/inout>

const int n = 1e5;

signed main() {
    freopen("8.in","w",stdout);
    dark::writeline(n,n);
    int i = 0;
    while(i < n / 4)      dark::print(1,' '),++i;
    while(i < 3 * n / 4)  dark::print(n - 1,' '),++i;
    while(i < n)          dark::print(1,' '),++i;
    freopen("8.out","w",stdout);
    dark::writeline(static_cast <long long> (n) * n / 4);
    return 0;
}
