#include <bits/stdc++.h>
#include <Dark/inout>

int a[100][100];

signed main() {
    srand(time(NULL));
    for(int i = 1 ; i <= 10 ; ++i) {
        std::string in  = std::to_string(i) + ".in";
        std::string out = std::to_string(i) + ".out";
        int n = rand() % (i * 10 - 1) + 1;
        int m = rand() % (i * 10 - 1) + 1;
        for(int i = 0 ; i < n ; ++i)
            for(int j = 0 ; j < m ; ++j)
                a[i][j] = rand() & 1;
        freopen(in.data(),"w",stdout);
        dark::writeline(n,m);
        for(int i = 0 ; i < n ; ++i)
            dark::writelineRange(a[i],a[i] + m);
        freopen(out.data(),"w",stdout);
        int ans = 0;
        for(int i = 1 ; i < n ; ++i)
            for(int j = 1 ; j < m ; ++j)
                if(!a[i][j] && !a[i - 1][j - 1]
                && !a[i - 1][j] && !a[i][j - 1])
                    ++ans;
        dark::writeline(ans);
    }
    return 0;
}