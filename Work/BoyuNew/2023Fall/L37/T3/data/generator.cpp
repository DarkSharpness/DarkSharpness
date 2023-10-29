#include <bits/stdc++.h>
using namespace std;

bool b[1005];
int cnt(int x) { return b[x - 1] + b[x] + b[x + 1]; }

signed main() {
    srand(time(NULL));
    for(int i = 1 ; i <= 10 ; ++i) {
        string in  = to_string(i) + ".in";
        string out = to_string(i) + ".out";
        const int n = rand() % (i * i * 10) + 1;
        b[0] = b[n + 1] = 0;
        b[1] = b[2] = 1;
        for(int i = 3 ; i <= n ; ++i) {
            if (!b[i - 1] && !b[i - 2]) b[i] = 1;
            else b[i] = (rand() % 9) & 1;
        }

        freopen(in.c_str(), "w", stdout);
        cout << n << endl;
        for(int i = 1 ; i <= n ; ++i) cout << cnt(i) << ' ';
        freopen(out.c_str(), "w", stdout);
        std::ranges::copy(std::span{b + 1, b + n + 1} | std::views::transform([](bool x) { return"ox"[x]; })
        , ostream_iterator <char> (cout, " "));
    }
    return 0;
}
