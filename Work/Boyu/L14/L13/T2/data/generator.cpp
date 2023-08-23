#include <bits/stdc++.h>
#include <Dark/inout>
using namespace std;

const char charmap[] = {
'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',
'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',
'0','1','2','3','4','5','6','7','8','9'
};


signed main() {
    string str;
    for(int i = 1 ; i <= 10 ; ++i) {
        string in = to_string(i) + ".in";
        string out = to_string(i) + ".out";

        str.clear();
        int n = rand() % 95 + 6;
        for(int i = 0 ; i < n ; ++i)
            str.push_back(charmap[rand() % sizeof(charmap)]);
        freopen(in.c_str(),"w",stdout);
        dark::write(str.c_str());
        freopen(out.c_str(),"w",stdout);
        std::reverse(str.begin(),str.end());
        dark::write(str.c_str());
    }
    return 0;
}
