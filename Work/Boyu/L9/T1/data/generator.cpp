#include <bits/stdc++.h>
#include <Dark/inout>
using namespace std;


signed main() {
    for(int i = 1 ; i <= 10 ; ++i) {
        string in = to_string(i) + ".in";
        string ot = to_string(i) + ".out";
        freopen(in.c_str(),"w",stdout);
        int n = rand() % 100 + 3;
        dark::writeline(n);
        freopen(ot.c_str(),"w",stdout);
        while(n--) putchar('+');
    }
    return 0;
}