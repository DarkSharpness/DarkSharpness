#include <bits/stdc++.h>
#include <Dark/inout>
using namespace std;


signed main() {
    srand(time(NULL));
    for(int i = 1 ; i <= 10 ; ++i) {
        string __i = to_string(i) + ".in";
        string __o = to_string(i) + ".out";
        freopen(__i.c_str(),"w",stdout);
        int n = abs((rand() % 9999) + (rand() % 9999) - 9998) + 2;
        dark::writeline(n);
        int sum = 0,max1 = 0,max2 = 0,min1 = 10000,min2 = 10000;
        for(int i = 0 ; i < n ; ++i){
            int x = rand() % 10000 + 1;
            dark::write(x,"");
            sum += x;
            if(x > max1) {
                max2 = max1;
                max1 = x;
            } else if(x > max2) {
                max2 = x;
            }

            if(x < min1) {
                min2 = min1;
                min1 = x;
            } else if(x < min2) {
                min2 = x;
            }
        }
        freopen(__o.c_str(),"w",stdout);
        dark::writeline(max1,max2);
        dark::writeline(min1,min2);
        dark::write(sum);
    }
    return 0;
}

