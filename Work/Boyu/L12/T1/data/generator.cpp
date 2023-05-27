#include <bits/stdc++.h>
#include <Dark/inout>
using namespace std;

const int N = 1003;
int a[N];
int d[N];

signed main() {
    srand(time(NULL));
    for(int i = 1 ; i <= 10 ; ++i) {
        string in  = to_string(i) + ".in";
        string out = to_string(i) + ".out";
        memset(a,0,sizeof(a));
        memset(d,0,sizeof(d));
        freopen(in.c_str(),"w",stdout);
        int n = rand() % N + 1;
        int m = rand() % N + 1;
        dark::writeline(n,m);
        for(int j = 1 ; j <= n ; ++j) a[j] = (rand() % 2001) - 1000;
        dark::writelineRange(a + 1,a + n + 1);
        while(m--) {
            int x = rand() % n + 1;
            int y = (rand() % 2001) - 1000;
            dark::writeline(x,y);
            d[x] += y;
        }
        int t = 0;
        for(int j = n ; j >= 1 ; --j) {
            t += d[j];
            a[j] += t;
        }
        freopen(out.c_str(),"w",stdout);
        for(int j = 1 ; j <= n ; ++j)
            cout << a[j] << '\n';
    }
    return 0;
}