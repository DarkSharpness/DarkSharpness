#include <bits/stdc++.h>
#include <Dark/inout>
using namespace std;


signed main() {
    srand(time(NULL));
    for(int i = 1 ; i <= 10 ; ++i) {
        string in = to_string(i) + ".in";
        string ot = to_string(i) + ".out";
        freopen(in.c_str(),"w",stdout);
        int a[] = {rand() - rand(),rand() - rand(),rand() - rand()};
        dark::writelineRange(a,a + 3);
        freopen(ot.c_str(),"w",stdout);
        sort(a,a + 3);
        dark::writeline(a[1]);
    }
    return 0;
}