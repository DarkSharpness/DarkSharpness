#include <bits/stdc++.h>
#include <Dark/inout>
using namespace std;

std::vector <std::vector<int>> ans;

signed main() {
    srand(time(NULL));
    for(int i = 1 ; i <= 10 ; ++i) {
        string in  = to_string(i) + ".in";
        string out = to_string(i) + ".out";
        const int n = i == 1 ? 1 : i * i * 5;
        const int m = i * i * 10;
        const int k = rand() % (i * 5 + 10);

        std::vector <int> fix;
        fix.reserve(k);
        for(int i = 0 ; i < k ; ++i)
            fix.push_back(rand() % m + 1);

        ans.resize(n);
        for(auto &&vec : ans) vec.resize(m + k);

        for(auto &&vec : ans)
            for(auto &&x : vec)
                x = (rand() | rand() << 9) % (m * 5) + 1;

        for(auto &&vec : ans)
            for(size_t i = 0 ; i < fix.size() ; ++i)
                vec[i] = fix[i];

        for(auto &&vec : ans) {
            sort(vec.begin() , vec.end());
            vec.resize(unique(vec.begin() , vec.end()) - vec.begin());
            std::random_shuffle(vec.begin() , vec.end());
        }

        freopen(in.data(),"w",stdout);

        dark::writeline(n);
        for(auto &&vec : ans) {
            dark::print(vec.size(),' ');
            dark::writelineRange(vec.begin(),vec.end());
        }
    }
    return 0;
}
