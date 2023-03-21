#include <bits/stdc++.h>
#include <Dark/inout>
using namespace std;


signed main() {
    srand(time(NULL));
    for(int i = 1 ; i <= 10 ; ++i) {
        string __i = to_string(i) + ".in";
        string __o = to_string(i) + ".out";
        freopen(__i.c_str(),"w",stdout);
        int n = (rand() % 98) + 3;
        int m = (rand() % 99) + 2;
        dark::write(n,m);
        freopen(__o.c_str(),"w",stdout);
        for(int i = 0 ; i < n ; ++i){
            for(int j = 0 ; j < m ; ++j)
                putchar('*');
            putchar('\n'); 
        }
    }
    return 0;
}