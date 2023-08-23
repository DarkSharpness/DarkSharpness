#include <bits/stdc++.h>
#include <Dark/inout>
using namespace std;

int get_rand(int n) {
    return (rand() << 8 | rand()) % (2 * n + 1) - n;;
}

signed main() {
    srand(time(NULL));
    for(int i = 2 ; i <= 10 ; ++i) {
        string in  = to_string(i - 1) + ".in";
        string out = to_string(i - 1) + ".out";
        const int n = i * i * i * 100;

        freopen(in.data(),"w",stdout);
        dark::writeline(n);
        long long ans = 0;
        long long sum = 0;
        for(int i = 1; i <= n; i++) {
            int x;
            dark::print(x = get_rand(1e5), ' ');
            sum += x;
            ans = max(ans,sum);
            if(sum < 0) sum = 0;
        }
        freopen(out.data(),"w",stdout);
        dark::writeline(ans);
    }
    return 0;
}
