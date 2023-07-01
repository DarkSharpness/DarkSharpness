#include <bits/stdc++.h>
#include <Dark/inout>
using namespace std;


signed main() {
    freopen("9.in","w",stdout);
    constexpr int x = (1u << 31) - 1;
    dark::writeline('3');
    dark::writeline('+',x,x);
    dark::writeline('-',-x,-1);
    dark::writeline('*',2 - x,x - 1);
    return 0;
}