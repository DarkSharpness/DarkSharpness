#include <bits/stdc++.h>
#include <Dark/inout>
using namespace std;

const long long N = 100003;
long long a[N];

long long ran() { return abs(rand() << 16 | rand() | rand() << 8); }

signed main() {
    srand(time(NULL));
    for(long long i = 1 ; i <= 10 ; ++i) {
        string in  = to_string(i) + ".in";
        string out = to_string(i) + ".out";
        freopen(in.c_str(),"w",stdout);
        const long long m = i * i * i * 100;
        long long n = ran() % m + 1;
        long long q = ran() % m + 1;
        dark::writeline(n,q);
        for(long long i = 1 ; i <= n ; ++i) a[i] = (ran() % (m << 1)) - 100;
        dark::writelineRange(a + 1,a + n + 1);
        for(long long i = 1 ; i <= n ; ++i) a[i] += a[i - 1];
        vector <long long> ans;
        while(q--) {
            long long l = ran() % n + 1;
            long long r = ran() % n + 1;
            if(l > r) swap(l,r);
            dark::writeline(l,r);
            ans.push_back(a[r] - a[l - 1]);
        }
        freopen(out.c_str(),"w",stdout);
        for(auto &&iter : ans)
            dark::writeline(iter);
    }
    return 0;
}
