#include <bits/stdc++.h>
#include <Dark/inout>
using namespace std;

template <size_t __N,size_t __M>
size_t better_rand() {
    if constexpr (__N == 0) return rand();
    else return rand() ^ (better_rand<__N - 1,__M>() << __M);
}

const unsigned long long N = 1e18;


signed main() {
    srand(time(NULL));
    for(int i = 2 ; i <= 10 ; ++i) {
        string in  = to_string(i) + ".in";
        string out = to_string(i) + ".out";

        int a = rand() % i + 1;
        int n = rand() % (i * i) + 3;
        size_t m = better_rand <10,10> () % N + 2;
        freopen(in.c_str(),"w",stdout);

        dark::writeline(a,n,m);
    }
    return 0;
}