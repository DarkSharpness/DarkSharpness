#include <bits/stdc++.h>
using namespace std;

bool t[4][4];


signed main() {
    srand(time(NULL));
    for(int i = 1 ; i <= 10 ; ++i) {
        ofstream in (std::format("{}.in",i));
        ofstream out(std::format("{}.out",i));
        const int n = i * i * 10;
        const int m = i * i * 100;

        in << n << ' ' << m << '\n';
        const int sqr = sqrt(n);
        const int log = log2(n);
        const int mod = i * i * 150;

        for (int i = 1 ; i <= sqr ; ++i)
            in << (rand() ^ rand() << 8) % (i + 1) + 1 << ' ';

        for (int i = sqr + 1 ; i < n - log ; ++i)
            in << (rand() ^ rand() << 8) % sqr + 1 << ' ';

        for (int i = n - log ; i <= n ; ++i)
            in << (rand() ^ rand() << 8) % mod + 1 << ' ';
    }
    return 0;
}
