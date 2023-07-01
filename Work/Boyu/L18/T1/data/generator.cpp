#include <bits/stdc++.h>
#include <Dark/inout>
using namespace std;

__int128 ran() {
    return 
        __int128(rand()) << 0  |
        __int128(rand()) << 16 |
        __int128(rand()) << 32 |
        __int128(rand()) << 48 |
        __int128(rand()) << 64 |
        __int128(rand()) << 80 |
        __int128(rand()) << 96;
}

signed main() {
    srand(time(NULL));
    const __int128_t N = __int128_t(1) << 80 | 3;
    const __int128_t M = __int128_t(1) << 16 | 7;
    for(int i = 1 ; i <= 10 ; ++i) {
        string in  = to_string(i) + ".in";
        string out = to_string(i) + ".out";
        __int128_t x = ran() % N;
        __int128_t y = ran() % M;
        freopen(in.data(),"w",stdout);
        dark::writeInt(x);
        putchar(' ');
        dark::writeInt(y);
        freopen(out.data(),"w",stdout);
        dark::writelineInt(x + y);
        dark::writelineInt(x - y);
        dark::writelineInt(x * y);
    }

    return 0;
}