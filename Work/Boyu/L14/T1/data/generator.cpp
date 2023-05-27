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
        int n = rand() % 15 + 1;
        int m = rand() % 20 + 1;
        for(int j = 1 ; j <= m ; ++j) {
            a[j] = rand() % n + 1;
            if(rand() % 8 == 0) a[j] = rand() % 15 + 1;
            if(rand() % n == 0) a[j] = 1;
        }
        sort(a + 1,a + m + 1);
        m = unique(a + 1,a + m + 1) - a - 1;
        dark::writeline(n,m);
        dark::writelineRange(a + 1,a + m + 1);
        d[0] = 1;
        for(int i = 1 ; i <= n ; ++i) {
            for(int j = 1 ; j <= m ; ++j) {
                if(i < a[j]) continue;
                else d[i] += d[i - a[j]];
            }
        }
        freopen(out.c_str(),"w",stdout);
        dark::writeline(d[n]);
    }
    return 0;
}