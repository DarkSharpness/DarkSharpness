#include <bits/stdc++.h>
#include <Dark/inout>
using namespace std;

const int N = 1e5 + 3;

std::array <int,N> loc;
std::array <int,N> ans;
std::array <int,N> sum;


signed main() {
    srand(time(NULL));

    for(int i = 1 ; i <= 10 ; ++i) {
        string in  = to_string(i) + ".in";
        string out = to_string(i) + ".out";
        int n = i == 1 ? 10 : i * i * i * 100 - 2;
        int m = (rand() ^ (rand() << 8)) % n + 1;

        loc[0] = 0;
        sum[0] = 0;

        long long last = 0;
        for(int i = 1 ; i <= n + 1 ; ++i) {
            loc[i] = ((rand() ^ (rand() << 3)) >> 9) + 1;
            last += loc[i];
            if (last > __INT32_MAX__) throw;  
            sum[i] = last;
        }

        for(int i = 1 ; i <= m ; ++i) {
            ans[i] = (rand() ^ (rand() << 10)) % (n + 1) + 1;
        }

        freopen(in.data(),"w",stdout);

        dark::writeline(n,m);
        for(int i = 1 ; i <= n ; ++i) dark::writeline(loc[i]);

        for(int i = 1 ; i <= m ; ++i) {
            int r = ans[i];
            int x = (rand() ^ (rand() << 10)) % r + 1;
            int y = sum[r] - sum[x - 1] - rand() % loc[r];
            dark::writeline(x,y);
            if (r <= n) ans[i] = r - x + 1;
            else        ans[i] = -1;
        }

        freopen(out.data(),"w",stdout);
        for(int i = 1 ; i <= m ; ++i) {
            dark::writeline(ans[i]);
        }
    }
    return 0;
}
