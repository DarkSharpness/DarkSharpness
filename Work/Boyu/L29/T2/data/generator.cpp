#include <bits/stdc++.h>
#include <Dark/inout>
using namespace std;

const int N = 1e5 + 2;
long long t[103];

using ll = long long;
long long get_rand() {
    return (rand() | rand() << 16 | ll(rand()) << 32 | ll(rand()) << 48);
}

signed main() {
    srand(time(NULL));
    for(int i = 1 ; i <= 9 ; ++i) {
        string in  = to_string(i) + ".in";
        string out = to_string(i) + ".out";
        const long long maxn = 1ll << (i * 3 + 30);
        long long c = get_rand() % (maxn / 10);
        freopen(in.c_str(),"w",stdout);
        t[0]  = 1;
        int n = 1;
        do {
            int x = rand() % 5 + 1;
            t[n] = t[n - 1] * x;
        } while(t[n++] < maxn);
        std::random_shuffle(t, t + n);
        dark::writeline(n,c);
        dark::writelineRange(t,t + n);
        freopen(out.c_str(),"w",stdout);
        sort(t, t + n,greater <long long> ());
        long long cnt = 0;
        int j = 0;
        while(c) {
            cnt += c / t[j];
            c   %= t[j];
            ++j;
        }
        dark::writeline(cnt);
    }
    return 0;
}