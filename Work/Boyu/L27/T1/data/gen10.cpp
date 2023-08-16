#include <bits/stdc++.h>
#include <Dark/inout>

int d[100003];

signed main() {
    srand(time(0));
    freopen("10.in","w",stdout);
    int n = 3,m = 9998;
    dark::writeline(n,m);
    int len0 = 9e4;
    dark::write(len0); putchar(' ');
    for(int j = 0 ; j < len0 ; ++j)
        d[j] = (rand() | rand() << 16) % 1000000 + 1;
    std::sort(d,d + len0);
    dark::writelineRange(d,d + len0);
    
    int x = (rand() | rand() << 16) % 1000000 + 1;
    int y = (rand() | rand() << 16) % 1000000 + 1;

    dark::writeline(1,x);
    dark::writeline(1,y);

    while(m-- != 10) {
        int t = bool(rand() & 0b1000) + 2;
        dark::writeline("add",1,t);
        d[len0++] = t == 2 ? x : y;
    }
    for(int i = 0 ; i < 10 ; ++i)
        dark::writeline("print",1);

    freopen("10.out","w",stdout);
    std::sort(d,d + len0);
    for(int i = 0 ; i < 10 ; ++i)
        dark::writelineRange(d,d + len0);

    return 0;
}