#include <bits/stdc++.h>
#include <Dark/inout>
using namespace std;

int x[20],y[20],z[20];

signed main() {
    srand(time(NULL));
    for(int i = 1 ; i <= 10 ; ++i) {
        string in  = to_string(i) + ".in";
        string out = to_string(i) + ".out";

        int n = i + 5;
        int m = rand() % 12 + rand() % (i >> 1 | 1);

        for(int i = 0 ; i < m ; ++i) {
            x[i] = rand() % n;
            y[i] = rand() % n;
            z[i] = rand() % 2;
        }

        int ans = 0;
        for(int i = 0 ; i < (1 << n) ; ++i) {
            bool flag = false;
            for(int j = 0 ; j < m ; ++j) {
                bool __x = (i >> x[j]) & 1;
                bool __y = (i >> y[j]) & 1;
                if((__x ^ __y) != z[j]) {
                    flag = true;
                    break;
                }
            } if(flag) continue;
                ++ans;
        }

        freopen(in.data(),"w",stdout);

        dark::writeline(n,m);
        for(int i = 0 ; i < m ; ++i)
            dark::writeline(x[i],y[i],z[i]);

        freopen(out.data(),"w",stdout);
        dark::writeline(ans);
    }

    return 0;
}