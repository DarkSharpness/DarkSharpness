#include <bits/stdc++.h>
#include <Dark/inout>
using namespace std;


int ans[6000];

int gcd(int x,int y) {
    if(!y) return x;
    return gcd(y,x % y);
}


signed main() {
    srand(time(NULL));
    for(int i = 1 ; i <= 10 ; ++i) {
        string __i = to_string(i) + ".in";
        string __o = to_string(i) + ".out";
        freopen(__i.c_str(),"w",stdout);
        int n = (rand() % 5000) + 1;
        dark::writeline(n);
        for(int j = 1 ; j <= n ; ++j) {
            int x,y;
            if((j & 3) == 0) {
                x = (rand() % 5000) + 1;
                y = (rand() % 5000) + 1;
                ans[j] = gcd(x,y);
            } else if((j & 15) == 1) {
                x = (rand() % 500) + 1;
                y = (rand() % 500) + 2;
                ans[j] = gcd(x,y);
            } else {
                int t = (rand() % 1000) + (rand() % 100) + 1;
                x = t * (rand() % (5000 / t) + 1);
                y = t * (rand() % (5000 / t) + 1);
                ans[j] = gcd(x,y);
            }
            dark::writeline(x,y);
        }
        freopen(__o.c_str(),"w",stdout);
        for(int j = 1 ; j <= n ; ++j)
            dark::writeline(ans[j]);
    }
    return 0;
}
