#include <bits/stdc++.h>
#include <Dark/inout>

const int N = 1e5 + 3;

std::array <int,N> loc;
std::array <int,N> ans;
std::array <int,N> sum;

signed main() {
    srand(time(0));
    const int n = 100000 - 1;
    const int m = 100000 - 1;
    long long last = 0;
    for(int i = 1 ; i <= n + 1 ; ++i) {
        loc[i] = ((rand() ^ (rand() << 3)) >> 9) + 1;
        last += loc[i];
        if (last > __INT32_MAX__) throw;  
        sum[i] = last;
    }

    freopen("10.in","w",stdout);

    dark::writeline(n,m);
    dark::writelineRange(loc.begin() + 1,n);

    for(int i = 1 ; i <= m ; ++i) {
        int r = n - (rand() % (n / 3) == 0 ? (-1) : (rand() % 100));
        int x = (rand() ^ (rand() << 10)) % (r >> 3) + 1;
        int y = sum[r] - sum[x - 1] - rand() % loc[r];
        dark::writeline(x,y);
        if (r <= n) ans[i] = r - x + 1;
        else        ans[i] = -1;
    }

    freopen("10.out","w",stdout);
    for(int i = 1 ; i <= m ; ++i) dark::writeline(ans[i]);


    return 0;
}