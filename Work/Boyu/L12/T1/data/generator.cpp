#include <bits/stdc++.h>
#include <Dark/inout>
using namespace std;

const int N = 100;
int a[N];


signed main() {
    srand(time(NULL));
    for(int i = 1 ; i <= 10 ; ++i) {
        string in  = to_string(i) + ".in";
        string out = to_string(i) + ".out";
        freopen(in.c_str(),"w",stdout);
        int n = rand() % N + 1;
        dark::writeline(n);
        for(int i = 0 ; i != n ; ++i) a[i] = (rand() % 201) - 100;
        dark::writelineRange(a,a + n);
        freopen(out.c_str(),"w",stdout);
        sort(a,a + n);
        dark::writelineRange(a,a + n);
    }
    return 0;
}