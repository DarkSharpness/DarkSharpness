#include <bits/stdc++.h>
#include <Dark/inout>
using namespace std;


signed main() {
    srand(time(NULL));
    std::vector <int> ans;
    std::vector <int> loc;
    for(int i = 1 ; i <= 10 ; ++i) {
        string in  = to_string(i) + ".in";
        string out = to_string(i) + ".out";
        int n = i == 1 ? 10 : i * i * i * 100 - 1;
        ans.resize(n);

        for(auto &__p : ans)
            __p = 
                (rand() ^ (rand() << 8) ^ (rand() << 16) ^ (rand() << 24))
                    >> 12;

        std::sort(ans.begin(),ans.end());
        n = std::unique(ans.begin(),ans.end()) - ans.begin();

        ans.resize(n);
        loc.resize(n);

        for(auto &__p : loc)
            __p = (rand() | rand() << 16) % n;


        freopen(in.data(),"w",stdout);
        dark::writeline(n,n);
        dark::writelineRange(ans.begin(),ans.end());
        for(auto x : loc) dark::writeline(ans[x]);

        freopen(out.data(),"w",stdout);
        for(auto x : loc) dark::writeline(n - x);
    }
    return 0;
}
