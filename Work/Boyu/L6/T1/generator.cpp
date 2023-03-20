#include <bits/stdc++.h>
#include <Dark/inout>

using ull = unsigned long long;
using namespace std;

unsigned long long ran() {
    return rand() | rand () << 16 | ull(rand()) << 32 | ull(rand()) << 48;
}


signed main() {
    srand(time(NULL));
    ran();ran();rand();
    for(int i = 2 ; i <= 10 ; ++i) {
        string in  = to_string(i) + ".in";
        string out = to_string(i) + ".out";
        freopen(in.c_str(),"w",stdout); 
        ull tmp = ran();
        tmp *= rand();
        tmp >>= ((10 - i) * 16);
        cout << tmp;
        freopen(out.c_str(),"w",stdout);
        int cnt[3] = {0,0,0};
        while(tmp) {
            ++cnt[tmp % 3];
            tmp /= 3;
        }
        dark::writeRange(cnt);
    }

    return 0;
}