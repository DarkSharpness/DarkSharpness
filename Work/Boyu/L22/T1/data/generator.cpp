#include <bits/stdc++.h>
#include <Dark/inout>
using namespace std;

const int N = 5e4 + 7;
int f[N];
int a[N],b[N],c[N],d[N];


signed main() {
    srand(time(NULL));
    for(int i = 1 ; i <= 10 ; ++i) {
        string in  = to_string(i) + ".in";
        string out = to_string(i) + ".out";

        int n = (rand() | rand() << 8) % (50 * i * i * i);
        memset(f,0,sizeof(f));
        for(int j = 0 ; j < n ; ++j) {
            a[j] = rand() % (2 * i * i + 3) + 1;
            b[j] = rand() % (2 * i * i + 3) + 1;
            c[j] = rand() % (2 * i * i + 3) + 1;
            d[j] = rand() % (2 * i * i + 3) + 1;
        }
        freopen(in.data(),"w",stdout);
        dark::writeline(n);
        for(int i = 0 ; i < n ; ++i)
            dark::writeline(a[i],b[i],c[i],d[i]);
        freopen(out.data(),"w",stdout);
        for(int i = 0 ; i < n ; ++i) {
            if(i + a[i] <= n)
                f[i + a[i]] = std::max(f[i + a[i]],f[i] + c[i]);
            if(i + b[i] <= n)
                f[i + b[i]] = std::max(f[i + b[i]],f[i] + d[i]);
            f[i + 1] = std::max(f[i + 1],f[i]);
        }
        dark::writeline(f[n]);
    }
    return 0;
}