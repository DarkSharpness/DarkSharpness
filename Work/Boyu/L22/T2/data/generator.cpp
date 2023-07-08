#include <bits/stdc++.h>
#include <Dark/inout>
using namespace std;

const int N = 1e5 + 3;
int f[N];

signed main() {
    srand(time(NULL));
    for(int i = 4 ; i <= 10 ; ++i) {
        string in  = to_string(i) + ".in";
        string out = to_string(i) + ".out";

        int n = (rand() | rand() << 10) % (100 * i * i * i);
        int x = rand() % (i * i * i * 3) - i * i * i;
        int c = rand() % (i * i * i * 2) - i * i * i;

        f[2] = -x;
        for(int i = 4 ; i <= n + 1 ; i += 2) {
            f[i] = f[i >> 1] + c;
            f[i - 1] = f[i] + x; 
        }

        int ans = 0;
        for(int i = 2 ; i <= n ; ++i)
            ans = std::max(ans,f[i]);

        freopen(in.data(),"w",stdout);
        dark::writeline(n,x,c);
        freopen(out.data(),"w",stdout);
        dark::writeline(ans);
    }

    return 0;
}