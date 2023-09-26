#include <bits/stdc++.h>
#include <Dark/inout>
using namespace std;


signed main() {
    srand(time(NULL));
    for(int i = 3 ; i <= 10 ; ++i) {
        string in  = to_string(i) + ".in";
        freopen(in.c_str(),"w",stdout);
        const int n = i * i;
        dark::writeline(n,n);
        for(int i = 0 ; i < n ; ++i) {
            for(int j = 0 ; j < n ; ++j) {
                int tmp = (rand() << 3 | rand()) ^ (rand() << 5);
                tmp %= 100;
                if(tmp < 10) putchar('#');
                else if(tmp < 40) putchar('-');
                else putchar('*');
            } putchar('\n');
        }
    }
    return 0;
}