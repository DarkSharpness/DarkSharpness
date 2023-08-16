#include <bits/stdc++.h>
#include <Dark/inout>
using namespace std;

const int N = 1e5 + 2;
int cnt[N];


signed main() {
    srand(time(NULL));
    for(int i = 4 ; i <= 10 ; ++i) {
        string in  = to_string(i - 3) + ".in";
        string out = to_string(i - 3) + ".out";
        const int n = i * i * i * 1000;
        const int c = n * i / 100;
        freopen(in.c_str(),"w",stdout);
        dark::writeline(n,c);
        memset(cnt,0,sizeof(cnt));
        for(int i = 0 ; i < n ; ++i) {
            int x = (rand() | rand() << 9) % c + 1;
            dark::write(x); putchar(' ');
            ++cnt[x];
        }
        freopen(out.c_str(),"w",stdout);
        long long ans = 0;
        for(int i = max(c - N,0) + 1 ; i < min(c / 2,N) ; ++i)
            ans += (long long)(cnt[i]) * cnt[c - i];
        dark::writeline(ans);
    }
    return 0;
}