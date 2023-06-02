#include <bits/stdc++.h>
#include <Dark/inout>
using namespace std;


signed main() {
    srand(time(NULL));
    for(int tt = 9 ; tt <= 10 ; ++tt) {
        string in  = to_string(tt) + ".in";
        string out = to_string(tt) + ".out";
        freopen(in.c_str(),"w",stdout);
        string sub = "ab";
        for(int i = 0 ; i < 8 ; ++i) sub += sub;
        string ans = sub;
        dark::writeline(ans.data());
        dark::writeline(sub.data());
        if(tt == 10) sub += 'a';
        freopen(out.c_str(),"w",stdout);
        int x = 0;
        int y = 0;
        while(bool(x = ans.find(sub,x) + 1)) ++y;
        dark::writeline(y); 
    }
    return 0;
}