#include <bits/stdc++.h>
#include <Dark/inout>


signed main() {
    freopen("2.in","w",stdout);
    dark::writeline(100,100);
    for(int i = 1 ; i <= 100 ; ++i) {
        for(int j = 1 ; j <= 100 ; ++j) {
            if(i == j) putchar('-');
            else       putchar('*');
        }
        putchar('\n');
    }
    return 0;
}