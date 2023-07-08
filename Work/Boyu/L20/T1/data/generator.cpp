#include <bits/stdc++.h>
#include <Dark/inout>

int a[100];

signed main() {
    srand(time(NULL));
    for(int i = 1 ; i <= 10 ; ++i) {
        std::string in  = std::to_string(i) + ".in";
        std::string out = std::to_string(i) + ".out";
        int n = rand() % (i * 10) + 1;
        for(int j = 0 ; j < n ; ++j)
            a[j] = rand() % (i * i * 10) + 1;
        int ans = 0;
        for(int i = 0 ; i < n ; ++i)
            for(int j = i + 1; j < n ; ++j)
                for(int k = j + 1 ; k < n ; ++k)
                    if (a[i] + a[j] > a[k] &&
                        a[j] + a[k] > a[i] &&
                        a[k] + a[i] > a[j]) ++ans;
        freopen(in.data(),"w",stdout);
        dark::writeline(n);
        dark::writelineRange(a,a + n);
        freopen(out.data(),"w",stdout);
        dark::writeline(ans);
    }
    return 0;
}