#include <bits/stdc++.h>
#include <Dark/inout>
using namespace std;


signed main() {
    srand(time(NULL));
    std::vector <int> loc;
    for(int i = 1 ; i <= 10 ; ++i) {
        string in  = to_string(i) + ".in";
        string out = to_string(i) + ".out";

        int n = i * i * 500;
        loc.resize(n);
        for(auto &__p : loc)
            __p = (rand() ^ (rand() << 8) ^ (rand() << 16)) >> 12;

        std::sort(loc.begin(),loc.end());
        n = std::unique(loc.begin(),loc.end()) - loc.begin();
        loc.resize(n);
        int m = abs((rand() | rand() << 16) % (n * 2) - n) + 2;
        for(int j = 0 ; j < (i >> 1) ; ++j)
            m = (rand() | rand() << 16) % m + 2;


        freopen(in.c_str(),"w",stdout);
        dark::writeline(n,m);
        dark::writelineRange(loc.begin(),loc.end());
    }
    return 0;
}