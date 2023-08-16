#include <bits/stdc++.h>
#include <Dark/inout>
using namespace std;

int get_n(int in) {
    if(in <= 3) return in * in * 10;
    if(in <= 8) return in * in * 10000;
    return 900000 + rand() % 100000;
}

int get_m(int in) {
    if(in <= 3) return in * 4;
    if(in <= 8) return in * 100;
    return 100000000;
}

signed main() {
    srand(time(NULL));
    for(int i = 1 ; i <= 10 ; ++i) {
        string in  = to_string(i) + ".in";
        string out = to_string(i) + ".out";
        const int n = get_n(i);
        const int m = get_m(i);
        map <int,int> mp;
        map <int,std::vector <int>> v;
        freopen(in.data(),"w",stdout);
        dark::writeline(n);
        for(int i = 0 ; i < n ; ++i) {
            int x = rand() % m + 1; ++mp[x];
            dark::print(x,' ');
        }
        freopen(out.data(),"w",stdout);
        for(auto &&[x,cnt] : mp) v[cnt].push_back(x);
        for(auto &&[cnt,vec] : v) {
            dark::print(cnt," : ");
            dark::writelineRange(vec.begin(),vec.end());
        }
    }
    return 0;
}
