#include <bits/stdc++.h>
#include <Dark/inout>
using namespace std;


signed main() {
    srand(time(NULL));
    for(int tt = 8 ; tt <= 8 ; ++tt) {
        string in  = to_string(tt) + ".in";
        string out = to_string(tt) + ".out";
        freopen(in.c_str(),"w",stdout);
        string sub("aba");
        string ans;
        ans.reserve(1020);
        for(int i = 0 ; i < 1020 >> 1 ; ++i)
            ans.push_back('a'),ans.push_back('b');
        dark::writeline(ans.data());
        dark::writeline(sub.data());
        freopen(out.c_str(),"w",stdout);
        int x = 0;
        int y = 0;
        while(bool(x = ans.find(sub,x) + 1)) ++y;
        dark::writeline(y); 
    }
    return 0;
}