#include <bits/stdc++.h>
#include <Dark/inout>
using namespace std;


signed main() {
    freopen("10.in","w",stdout);
    constexpr int x = (1u << 31) - 2;
    dark::writeline('3');
    dark::writeline('+',1,x);
    dark::writeline('-',1,x >> 1);
    dark::writeline('/',x,x);
    return 0;
}