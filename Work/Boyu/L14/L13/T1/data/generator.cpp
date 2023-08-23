#include <bits/stdc++.h>
#include <Dark/inout>
using namespace std;

const char charmap[] = {
'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',
'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',
'0','1','2','3','4','5','6','7','8','9','_','|','?'
};


signed main() {
    for(int i = 1 ; i <= 10 ; ++i) {
        string in = to_string(i) + ".in";
        string out = to_string(i) + ".out";
        freopen(in.c_str(),"w",stdout);

        int n = rand() % 10000 + 5 + rand() % 1000;
        dark::writeline(n);
        int a = 0,b = 0;

        for(int i = 0 ; i < n ; ++i) {
            char c = charmap[rand() % sizeof(charmap)];
            if(c >= 'a' && c <= 'z') ++a;
            if(c >= 'A' && c <= 'Z') ++b;
            putchar(c);
        }
        freopen(out.c_str(),"w",stdout);

        dark::writeline(a);
        dark::write(b);
    }
    return 0;
}
