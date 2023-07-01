#include <bits/stdc++.h>
#include <Dark/inout>
using namespace std;

const int N = 10002;

int a[N];
int x[N];

signed main() {
    srand(time(NULL));
    for(int i = 1 ; i <= 10 ; ++i) {
        string in  = to_string(i) + ".in";
        string out = to_string(i) + ".out";
        int t = i * i * 50;
        int n = rand() % t + rand() % t + 2;
        int m = rand() % t + rand() % t + 2;
        freopen(in.data(),"w",stdout);
        dark::writeline(n,m);

        iota(a + 1,a + n + 1,1);
        random_shuffle(a + 1,a + n + 1);
        for(int i = 1 ; i <= n ; ++i)
            x[a[i]] = i;

        dark::writelineRange(a + 1,a + n + 1);
        for(int i = 1 ; i <= m ; ++i) {
            a[i] = rand() % t + rand() % t + 2;
            dark::writeline(a[i]);
        }

        freopen(out.data(),"w",stdout);
        for(int i = 1 ; i <= m ; ++i)
            dark::writeline(x[a[i]] - 1);
    }
    return 0;
}