#include <bits/stdc++.h>
#include <Dark/inout>
using namespace std;



signed main() {
    srand(time(NULL));
    for(int i = 1 ; i <= 10 ; ++i) {
        string in  = to_string(i) + ".in";
        string out = to_string(i) + ".out";
        freopen(in.c_str(),"w",stdout);
        int m = rand() % 250 + rand() % 250 + 2; 
        int q = rand() % 250 + rand() % 250 + 2;
        int n = rand() % m + 1;
        dark::writeline(m,q);
        set <pair<int,int>> s;
        if(n >= 10 && rand() % 4 == 1) n >>= 1;
        if(n * (n + 1) / 2 <= m) n = sqrt(2 * m) + rand() % 5;

        while(m--) {
            int x,y;
            do {
                x = rand() % n + 1;
                y = rand() % n + 1; 
            } while(s.count({x,y}));
            dark::writeline(x,y);
            s.insert({x,y}),s.insert({y,x});
        }

        vector <pair <int,int> > v;
        v.reserve(s.size());
        for(auto && iter : s) v.push_back(iter);

        vector <bool> ans;
        while(q--) {
            auto [x,y] = !(rand() % 3) ? v[rand() % v.size()] : 
                        make_pair(rand() % n + 1,rand() % n + 1);
            dark::writeline(x,y);
            ans.push_back(s.count({x,y}));
        }

        freopen(out.c_str(),"w",stdout);
        for(auto &&iter : ans) dark::writeline(iter ? "Yes" : "No");
    }

    return 0;
}