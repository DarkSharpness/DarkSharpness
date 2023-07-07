#include <bits/stdc++.h>
#include <Dark/inout>
using namespace std;

int w[20],v[20];

signed main() {
    srand(time(NULL));
    for(int i = 2 ; i <= 8 ; ++i) {
        string in  = to_string(i) + ".in";
        string out = to_string(i) + ".out";

        int n = i + 6;
        int m = rand() % (10 + i * 6) + rand() % 10;

        for(int i = 0 ; i < n ; ++i) {
            w[i] = rand() % 6 + 1;
            v[i] = rand() % 20 - 1;
        }

        std::array <int,100> f;
        memset(&f,129,sizeof(f));
        f[0] = 0;
        for(int i = 0 ; i < n ; ++i)
            for(int j = m ; j >= w[i] ; --j)
                f[j] = std::max(f[j - w[i]] + v[i],f[j]);
        freopen(in.data(),"w",stdout);

        dark::writeline(n,m);
        for(int i = 0 ; i < n ; ++i)
            dark::writeline(w[i],v[i]);

        freopen(out.data(),"w",stdout);
        int ans = f[1];
        for(int i = 1 ; i <= m ; ++i)
            ans = std::max(ans,f[i]);
        dark::writeline(ans);
    }

    return 0;
}