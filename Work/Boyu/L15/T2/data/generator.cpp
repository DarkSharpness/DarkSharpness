#include <bits/stdc++.h>
#include <Dark/inout>
using namespace std;

char char_map(int i) {
    i %= (26 + 26 + 10);
    if(i < 26) return 'a' + i;
    i -= 26;
    if(i < 26) return 'A' + i;
    
    return '0' + i % 10;   
}

signed main() {
    srand(time(NULL));
    for(int tt = 1 ; tt <= 7 ; ++tt) {
        string in  = to_string(tt) + ".in";
        string out = to_string(tt) + ".out";
        freopen(in.c_str(),"w",stdout);
        string sub;
        sub.reserve(300);
        int len = rand() % 64 + 1;
        while(len--)
            sub.push_back(char_map(rand()));
        len = rand() % 1000 + 1;
        string ans;
        ans.reserve(1024);
        for(;;) {
            if(rand() % 10) {
                if(ans.size() + 1> len) break;
                ans.push_back(char_map(rand()));
            } else {
                if(ans.size() + sub.size() > len) break;
                ans += sub;
            }
        }
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